// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/image.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/bitmap.h>
#include <wx/artprov.h>
#include <wx/mstream.h>
#include <wx/log.h>

#include <map>
#include <vector>
#include <stdexcept>

#ifndef wxOVERRIDE
#define wxOVERRIDE
#endif

namespace boost {
namespace ui    {

static void init_image_handlers()
{
    static bool initilized = false;
    if ( !initilized )
    {
        wxInitAllImageHandlers();
        initilized = true;
    }
}

class image::impl : public wxBitmap, private detail::memcheck
{
public:
    impl() {}
    impl(const wxBitmap& bitmap) : wxBitmap(bitmap) {}
};

image::image() : m_impl(new impl)
{
}

image::image(const image& other) : m_impl(new impl)
{
    *m_impl = *other.m_impl;
}

image& image::operator=(const image& other)
{
    *m_impl = *other.m_impl;
    return *this;
}

image::~image()
{
    delete m_impl;
}

namespace {
class my_log_buffer : public wxLogBuffer
{
public:
    virtual void Flush() wxOVERRIDE
    {
        // Don't call wxLogBuffer::Flush()
        wxLog::Flush();
    }

};
}

image& image::load(std::istream& s)
{
    *m_impl = wxBitmap();

    std::vector<char> container;
    container.assign(std::istreambuf_iterator<char>(s),
                     std::istreambuf_iterator<char>());

    const void* data = container.empty() ? NULL : &*container.begin();
    wxMemoryInputStream ms(data, container.size());

    init_image_handlers();

    wxLogBuffer* logger = new my_log_buffer;
    wxLog* oldLog = wxLog::SetActiveTarget(logger);

    wxImage image;
    image.LoadFile(ms);

    const wxString errors = logger->GetBuffer();
    delete wxLog::SetActiveTarget(oldLog);

    if ( !image.IsOk() )
    {
        if ( !errors.empty() )
            BOOST_THROW_EXCEPTION(std::runtime_error( std::string(errors.c_str()) ));

        return *this;
    }

    *m_impl = wxBitmap(image);

    return *this;
}

image image::xdg(const char* name, coord_type width, coord_type height)
{
    typedef std::map<std::string, wxArtID> map_type;
    map_type s_map;
    if ( s_map.empty() )
    {
        static const map_type::value_type map_data[] =
        {
// Table 2. Standard Action Icons
std::make_pair("application-exit",              wxART_QUIT              ),
std::make_pair("document-new",                  wxART_NEW               ),
std::make_pair("document-open",                 wxART_FILE_OPEN         ),
std::make_pair("document-save",                 wxART_FILE_SAVE         ),
std::make_pair("document-save-as",              wxART_FILE_SAVE_AS      ),
std::make_pair("edit-copy",                     wxART_COPY              ),
std::make_pair("edit-cut",                      wxART_CUT               ),
std::make_pair("edit-delete",                   wxART_DELETE            ),
std::make_pair("edit-find",                     wxART_FIND              ),
std::make_pair("edit-find-replace",             wxART_FIND_AND_REPLACE  ),
std::make_pair("edit-paste",                    wxART_PASTE             ),
std::make_pair("edit-redo",                     wxART_REDO              ),
std::make_pair("edit-undo",                     wxART_UNDO              ),
std::make_pair("folder-new",                    wxART_NEW_DIR           ),
std::make_pair("go-down",                       wxART_GO_DOWN           ),
std::make_pair("go-first",                      wxART_GOTO_FIRST        ),
std::make_pair("go-home",                       wxART_GO_HOME           ),
std::make_pair("go-last",                       wxART_GOTO_LAST         ),
std::make_pair("go-next",                       wxART_GO_BACK           ),
std::make_pair("go-previous",                   wxART_GO_FORWARD        ),
std::make_pair("go-up",                         wxART_GO_UP             ),
std::make_pair("list-add",                      wxART_PLUS              ),
std::make_pair("list-remove",                   wxART_MINUS             ),
std::make_pair("window-close",                  wxART_CLOSE             ),
#if wxCHECK_VERSION(3, 1, 0)
std::make_pair("view-fullscreen",               wxART_FULL_SCREEN       ),
#endif

// Table 6. Standard Device Icons
std::make_pair("drive-harddisk",                wxART_HARDDISK          ),
std::make_pair("drive-removable-media",         wxART_REMOVABLE         ),
std::make_pair("media-floppy",                  wxART_FLOPPY            ),
std::make_pair("media-optical",                 wxART_CDROM             ),

// Table 10. Standard MIME Type Icons
std::make_pair("application-x-executable",      wxART_EXECUTABLE_FILE   ),

// Table 11. Standard Place Icons
std::make_pair("folder",                        wxART_FOLDER            ),

// Table 12. Standard Status Icons
std::make_pair("dialog-error",                  wxART_ERROR             ),
std::make_pair("dialog-information",            wxART_INFORMATION       ),
std::make_pair("dialog-question",               wxART_QUESTION          ),
std::make_pair("dialog-warning",                wxART_WARNING           ),
std::make_pair("folder-open",                   wxART_FOLDER_OPEN       ),
        };

        s_map = map_type(map_data, map_data + sizeof map_data / sizeof map_data[0]);
    }

    image img;
    *img.m_impl = wxArtProvider::GetBitmap(s_map[name], wxART_OTHER,
                                           wxSize(width, height));
    return img;
}

coord_type image::width() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("ui::image::width(): invalid image"));

    return m_impl->GetWidth();
}

coord_type image::height() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("ui::image::height(): invalid image"));

    return m_impl->GetHeight();
}

bool image::valid() const BOOST_NOEXCEPT
{
    return m_impl->IsOk();
}

} // namespace ui
} // namespace boost
