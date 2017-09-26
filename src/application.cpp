// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/application.hpp>
#include <boost/ui/string.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/exception/get_error_info.hpp>

#include <sstream>
#include <map>

#include <wx/app.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>

#include <boost/ui/native/winmain.cpp>

#if !wxCHECK_VERSION(3, 0, 0)
#error Boost.UI requires wxWidgets 3.0.0+
#endif

#ifndef wxOVERRIDE
#define wxOVERRIDE
#endif

namespace {

int (*g_ui_main)() = NULL;
int (*g_ui_main_args)(int, char*[]) = NULL;
int g_argc = 0;
char** g_argv = NULL;

template <class charT>
void show_exception_raw(const std::basic_string<charT>& message,
                        const charT* title)
{
    wxString str = title;
    if ( wxTheApp )
        str << wxS(" - ") << wxTheApp->GetAppDisplayName();
#if wxUSE_MSGDLG
    wxMessageBox(message, str, wxICON_ERROR);
#else
    wxLogDebug(wxS("Error: %s: %s"), str, message);
#endif
}

void show_exception(const boost::exception& e, const char* where)
{
    std::ostringstream ss;

    const std::exception* pe = dynamic_cast<const std::exception*>(&e);
    if ( pe )
        ss << "\"" << pe->what() << "\"\n\n";
    ss  << "Caught boost::exception (" << typeid(e).name() << ")"
        << where;

    const char* const* file = boost::get_error_info<boost::throw_file>(e);
    const int*   line = boost::get_error_info<boost::throw_line>(e);
    if ( file && line )
        ss << "\n\nSource: " << *file << ":" << *line;

    const char* const* function = boost::get_error_info<boost::throw_function>(e);
    if ( function )
        ss << "\nFunction: " << *function;

    show_exception_raw(ss.str(), "boost::exception");
}

void show_exception(const std::exception& e, const char* where)
{
    std::ostringstream ss;
    ss  << "\"" << e.what() << "\"\n\n"
        << "Caught std::exception (" << typeid(e).name() << ")"
        << where;
    show_exception_raw(ss.str(), "std::exception");
}

void show_exception(const boost::ui::uistring& e, const char* where)
{
    std::wostringstream ss;
    ss  << "\"" << e.wstring() << "\"\n\n"
        << L"Caught boost::ui::uistring"
        << where;
    show_exception_raw(ss.str(), L"boost::ui::uistring");
}

void show_exception(const char* where)
{
    std::ostringstream ss;
    ss  << "Caught unknown exception"
        << where;
    show_exception_raw(ss.str(), "Unknown exception");
}

} // unnamed namespace

class boost_ui_app : public wxApp
{
public:
    virtual ~boost_ui_app();
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnRun() wxOVERRIDE;

#if wxUSE_CMDLINE_PARSER
    virtual bool OnCmdLineError(wxCmdLineParser& WXUNUSED(parser)) wxOVERRIDE
    {
        return true; // Don't exit on parsing errors
    }
#endif

    virtual void CallEventHandler(wxEvtHandler* handler,
                                  wxEventFunctor& functor,
                                  wxEvent& event) const wxOVERRIDE;

    void on_timeout(int milliseconds, const boost::function<void()>& fn);

private:
#if wxUSE_TIMER
    void on_timer(wxTimerEvent& event);

    typedef std::map< int, std::pair< wxTimer*, boost::function<void()> > > timers_type;
    timers_type m_timers;
#endif
};

boost_ui_app::~boost_ui_app()
{
#if wxUSE_TIMER
    for ( timers_type::iterator iter = m_timers.begin(); iter != m_timers.end(); ++iter )
        delete iter->second.first;
#endif
}

bool boost_ui_app::OnInit()
{
    // Don't try to parse command line in
    // wxApp::OnInit();

    return true;
}

int boost_ui_app::OnRun()
{
    try
    {
#if wxUSE_TIMER
        Bind(wxEVT_TIMER, &boost_ui_app::on_timer, this);
#endif
        if ( g_ui_main_args )
            return g_ui_main_args(g_argc, g_argv);

        if ( g_ui_main )
            return g_ui_main();
    }
    catch ( boost::exception& e )
    {
        show_exception(e, " in the main Boost.UI function, terminating");
    }
    catch ( std::exception& e )
    {
        show_exception(e, " in the main Boost.UI function, terminating");
    }
    catch ( boost::ui::uistring& e )
    {
        show_exception(e, " in the main Boost.UI function, terminating");
    }
    catch ( ... )
    {
        show_exception(" in the main Boost.UI function, terminating");
    }

    return EXIT_FAILURE;
}

void boost_ui_app::CallEventHandler(wxEvtHandler* handler,
                                    wxEventFunctor& functor,
                                    wxEvent& event) const
{
    try
    {
        wxApp::CallEventHandler(handler, functor, event);
    }
    catch ( boost::exception& e )
    {
        show_exception(e, " in a Boost.UI event handler");
    }
    catch ( std::exception& e )
    {
        show_exception(e, " in a Boost.UI event handler");
    }
    catch ( boost::ui::uistring& e )
    {
        show_exception(e, " in a Boost.UI event handler");
    }
    catch ( ... )
    {
        show_exception(" in a Boost.UI event handler");
    }
}

void boost_ui_app::on_timeout(int milliseconds, const boost::function<void()>& fn)
{
    if ( milliseconds < 0 )
        return;

#if wxUSE_TIMER
    wxTimer* timer = new wxTimer(this);
    m_timers.insert(std::make_pair( timer->GetId(), std::make_pair(timer, fn) ));
    timer->StartOnce(milliseconds);
#else
    fn();
#endif
}

#if wxUSE_TIMER
void boost_ui_app::on_timer(wxTimerEvent& event)
{
    const int id_ = event.GetTimer().GetId();
    timers_type::const_iterator iter = m_timers.find(id_);
    wxCHECK(iter != m_timers.end(), );
    iter->second.second();
}
#endif

wxIMPLEMENT_APP_NO_MAIN(boost_ui_app);

namespace boost  {
namespace ui     {
namespace detail {

// Implemenation of <boost/assert.hpp>

void assertion_failed_msg(char const* expr, char const* msg, char const* function,
                          char const* file, long line)
{
#if wxDEBUG_LEVEL
    wxOnAssert(file, line, function, expr, msg);
#else
    assert(false);
#endif
}

static void parse_cmdline(int argc, char* argv[])
{
#if wxUSE_LOG
    for ( int i = 0; i < argc; i++ )
    {
        if ( ::strcmp(argv[i], "--verbose") == 0 )
        {
            wxLog::SetVerbose(true);
            break;
        }
    }
#endif
}

#ifdef BOOST_UI_DEBUG_HOOKS
int memcheck::s_count = 0;
#endif

static int entry(int argc, char* argv[])
{
    const int ret = wxEntry(argc, argv);
#ifdef BOOST_UI_DEBUG_HOOKS
    const int count = memcheck::count();
    if ( count )
    {
        wxLogDebug(wxS("memcheck leaks count: %d"), count);
    }
#endif
    return ret;
}

} // detail namespace

int entry(int argc, char* argv[], int (*ui_main)())
{
    g_ui_main = ui_main;
    detail::parse_cmdline(argc, argv);
    return detail::entry(argc, argv);
}

int entry(int argc, char* argv[], int (*ui_main)(int, char*[]))
{
    g_argc = argc;
    g_argv = argv;
    g_ui_main_args = ui_main;
    detail::parse_cmdline(argc, argv);
    return detail::entry(argc, argv);
}

namespace detail {

void on_timeout(int milliseconds, const boost::function<void()>& fn)
{
    wxGetApp().on_timeout(milliseconds, fn);
}

void sleep_for_milliseconds(unsigned long milliseconds)
{
    wxMilliSleep(milliseconds);
}

void sleep_for_microseconds(unsigned long microseconds)
{
    wxMicroSleep(microseconds);
}

} // namespace detail

} // namespace ui
} // namespace boost
