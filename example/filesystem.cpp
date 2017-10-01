// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Boost.Filesystem file manager example.

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED

#include <boost/config.hpp>
#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

#include <fstream>

// Visual C++ 2015
#if defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB >= 650)
#include <chrono>
#include <filesystem>
namespace fs = std::experimental::filesystem;
#else
#define BOOST_UI_NO_CXX11_HDR_FILESYSTEM
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

namespace ui = boost::ui;

class filesystem_dialog : public ui::dialog
{
    typedef filesystem_dialog this_type;

public:
    explicit filesystem_dialog(const fs::path& p);

private:
    fs::path selected_path() const;
    void show_file_info(const fs::path& file);
    std::wstring show_image(const fs::path& file);

    void on_file_select(ui::index_event& e);
    void on_file_activate(ui::index_event& e);
    void on_file_key_press(ui::key_event& e);
    void on_change_path();
    void on_up();
    void on_initial_path();
    void on_home_path();
    void on_temp_path();
    void on_copy();
    void on_rename();
    void on_remove();

    void load_path(const fs::path& p);
    void refresh();

    fs::path m_path;
    const fs::path m_initial_path;

    ui::label m_path_label;
    ui::listbox m_files_listbox;
    ui::button m_up_button;
    ui::button m_copy_button;
    ui::button m_rename_button;
    ui::button m_remove_button;
    ui::image_widget m_image_widget;
    ui::label m_file_info_label;
};

filesystem_dialog::filesystem_dialog(const fs::path& p)
    : ui::dialog(
#if !defined(BOOST_UI_NO_CXX11_HDR_FILESYSTEM)
        "C++17 "
#else
        "Boost."
#endif
        "Filesystem + Boost.UI Example"), m_path(p), m_initial_path(p)
{
    ui::vbox(*this)
        << (ui::hbox()
                << m_path_label.create(*this)
                    .layout().stretch()
                << ui::button(*this, "Chan&ge...")
                    .on_press(&this_type::on_change_path, this)
                    .tooltip("Edit current path")
           ).layout().justify()
        << ( ui::hbox()
            << m_files_listbox.create(*this)
                .on_select_event(boost::bind(&this_type::on_file_select, this, _1))
                .on_activate_event(boost::bind(&this_type::on_file_activate, this, _1))
                .on_key_press_event(boost::bind(&this_type::on_file_key_press, this, _1))
                .tooltip("List of files in the current path")
                .layout().justify().stretch()
            << ( ui::vbox().layout().justify()
                << m_up_button.create(*this, "&Up")
                    .on_press(&this_type::on_up, this)
                    .tooltip("Move to the parent directory")
                    .layout().justify()
                << ui::button(*this, "&Initial path")
                    .on_press(&this_type::on_initial_path, this)
                    .tooltip("Move to the initial path at application start")
                    .layout().justify()
                << ui::button(*this, "&Home path")
                    .on_press(&this_type::on_home_path, this)
                    .tooltip("Move to the user's home directory")
                    .layout().justify()
                << ui::button(*this, "&Temp path")
                    .on_press(&this_type::on_temp_path, this)
                    .tooltip("Move to the system temporary directory")
                    .layout().justify()
                << ui::button(*this, "Re&fresh")
                    .on_press(&this_type::refresh, this)
                    .tooltip("Reread files")
                    .layout().justify()
                << m_copy_button.create(*this, "&Copy")
                    .on_press(&this_type::on_copy, this)
                    .tooltip("Copies file")
                    .layout().justify()
                << m_rename_button.create(*this, "Re&name")
                    .on_press(&this_type::on_rename, this)
                    .tooltip("Renames file")
                    .layout().justify()
                << m_remove_button.create(*this, "&Remove")
                    .on_press(&this_type::on_remove, this)
                    .tooltip("Removes file")
                    .layout().justify()
                << m_image_widget.create(*this)
                    .layout().justify().stretch()
               )
            << m_file_info_label.create(*this)
                .tooltip("Information about selected file")
                .layout().justify().stretch(4)
           ).layout().justify().stretch()
        ;

    resize(800, 600);

    refresh();
}

fs::path filesystem_dialog::selected_path() const
{
    return m_path / m_files_listbox.selected_string().wstring();
}

static std::wstring bytes_to_wstring(const boost::uintmax_t fsz)
{
    std::wostringstream ss;
    const long double s = static_cast<long double>(fsz);
    if ( s / ( 1024 * 1024 * 1024 ) > 10 )
        ss << s / (1024 * 1024 * 1024) << " GiB";
    else if ( s > 10 * 1024 * 1024 )
        ss << s / (1024 * 1024) << " MiB";
    else if ( s > 10 * 1024 )
        ss << s / 1024 << " KiB";
    else
        ss << s << " B";
    return ss.str();
}

static std::wstring file_time_to_wstring(const time_t ft)
{
    wchar_t buf[100];
    std::wcsftime(buf, sizeof buf / sizeof buf[0], L"%A %c", std::localtime(&ft));
    return buf;
}

#ifndef BOOST_UI_NO_CXX11_HDR_FILESYSTEM

static std::wstring file_time_to_wstring(const fs::file_time_type ft)
{
    return file_time_to_wstring(std::chrono::system_clock::to_time_t(ft));
}

#endif

void filesystem_dialog::show_file_info(const fs::path& file)
{
    m_file_info_label.clear();

    std::wostringstream ss;
    ss << fs::canonical(file).filename();

    if ( fs::is_directory(file) )
        ss << L"\nDirectory";

    if ( fs::is_symlink(file) )
        ss << L"\nSymbolic link";

    if ( fs::is_regular_file(file) )
        ss << L"\nRegular file";

    if ( fs::is_other(file) )
        ss << L"\nOther";

    try
    {
        if ( fs::is_empty(file) )
            ss << L"\nEmpty";
    }
    catch(const fs::filesystem_error& e)
    {
        ui::log::error() << "\nfs::is_empty(): Filesystem error: " << e.what();
    }

    ss << std::endl;

    if ( fs::is_regular_file(file) )
        ss << L"\nSize: " << bytes_to_wstring(fs::file_size(file));

    try
    {
        ss << "\nLast write time: " << file_time_to_wstring(fs::last_write_time(file));
    }
    catch(const fs::filesystem_error& e)
    {
        ui::log::error() << "\nfs::last_write_time(): Filesystem error: " << e.what();
    }

    const fs::perms p = fs::status(file).permissions();
    ss << L"\nPermissions : " << std::oct << static_cast<int>(p) << L" ("
#if !defined(BOOST_UI_NO_CXX11_HDR_FILESYSTEM)
        << ((p & fs::perms::owner_read   ) != fs::perms::none ? L"r" : L"-")
        << ((p & fs::perms::owner_write  ) != fs::perms::none ? L"w" : L"-")
        << ((p & fs::perms::owner_exec   ) != fs::perms::none ? L"x" : L"-")
        << ((p & fs::perms::group_read   ) != fs::perms::none ? L"r" : L"-")
        << ((p & fs::perms::group_write  ) != fs::perms::none ? L"w" : L"-")
        << ((p & fs::perms::group_exec   ) != fs::perms::none ? L"x" : L"-")
        << ((p & fs::perms::others_read  ) != fs::perms::none ? L"r" : L"-")
        << ((p & fs::perms::others_write ) != fs::perms::none ? L"w" : L"-")
        << ((p & fs::perms::others_exec  ) != fs::perms::none ? L"x" : L"-")
#else
        << ((p & fs::owner_read   ) != fs::no_perms ? L"r" : L"-")
        << ((p & fs::owner_write  ) != fs::no_perms ? L"w" : L"-")
        << ((p & fs::owner_exe    ) != fs::no_perms ? L"x" : L"-")
        << ((p & fs::group_read   ) != fs::no_perms ? L"r" : L"-")
        << ((p & fs::group_write  ) != fs::no_perms ? L"w" : L"-")
        << ((p & fs::group_exe    ) != fs::no_perms ? L"x" : L"-")
        << ((p & fs::others_read  ) != fs::no_perms ? L"r" : L"-")
        << ((p & fs::others_write ) != fs::no_perms ? L"w" : L"-")
        << ((p & fs::others_exe   ) != fs::no_perms ? L"x" : L"-")
#endif
        << L")";

    if ( !fs::is_directory(file) )
        ss << "\nHard link count: " << fs::hard_link_count(file);

    ss << std::endl;

    ss << L"\nRoot name: " << file.root_name();
    ss << L"\nRoot directory: " << file.root_directory();
    ss << L"\nRoot path: " << file.root_path();
    ss << L"\nFilename: " << file.filename();
    ss << L"\nStem: " << file.stem();
    ss << L"\nExstension: " << file.extension();
    ss << L"\n\nPath: " << file;
    ss << L"\nGeneric string: " << file.generic_wstring();
    ss << L"\nRelative path: " << file.relative_path();
    ss << L"\nParent path: " << file.parent_path();
    ss << L"\nSystem complete: " << fs::system_complete(file);
    ss << L"\nAbsolute: " << fs::absolute(file);
    ss << L"\nCanonical: " << fs::canonical(file);

    const std::wstring image_description = show_image(file);
    if ( !image_description.empty() )
        ss << L"\n\nImage: "  << image_description;

    try
    {
        const fs::space_info si = fs::space(file.parent_path());
        ss << L"\n\nVolume information:";
        ss << L"\nCapacity: " << bytes_to_wstring(si.capacity);
        ss << L"\nFree: "       << bytes_to_wstring(si.free);
        ss << L"\nAvailable: "  << bytes_to_wstring(si.available);
    }
    catch(const fs::filesystem_error& e)
    {
        ui::log::error() << "\nfs::space(): Filesystem error: " << e.what();
    }

    m_file_info_label.text(ss.str());

}

std::wstring filesystem_dialog::show_image(const fs::path& file)
{
    m_image_widget.clear();

    if ( fs::is_directory(file) )
        return std::wstring();

    std::ifstream fsm(file.string().c_str());
    if ( !fsm )
        return std::wstring();

    ui::image img;
    try
    {
        img.load(fsm);
    }
    catch(const std::exception&)
    {
        // TODO: Log exception text to the info label
    }

    std::wostringstream ss;
    if ( img.valid() )
    {
        m_image_widget.image(img);
        ss << img.width() << L" x " << img.height();
    }

    return ss.str();
}

void filesystem_dialog::on_file_select(ui::index_event& e)
{
    m_copy_button.enable();
    m_rename_button.enable();
    m_remove_button.enable();

    show_file_info(m_path / m_files_listbox[e.index()].wstring());
}

void filesystem_dialog::on_file_activate(ui::index_event& e)
{
    const fs::path new_path = m_path / m_files_listbox[e.index()].wstring();

    if ( fs::is_directory(new_path) )
        load_path(fs::canonical(new_path));
}

void filesystem_dialog::on_file_key_press(ui::key_event& e)
{
    if ( e.key_code() == 8 ) // Backspace
        on_up();
}

void filesystem_dialog::on_change_path()
{
    std::wstring filename = m_path.wstring();
    if ( !ui::prompt("Enter new path", "Change current directory", filename) )
        return;

    load_path(filename);
}

void filesystem_dialog::on_up()
{
    if ( m_path.has_parent_path() )
        load_path(m_path.parent_path());
}

void filesystem_dialog::on_initial_path()
{
    load_path(m_initial_path);
}

void filesystem_dialog::on_home_path()
{
#ifdef BOOST_WINDOWS
    load_path(getenv("USERPROFILE"));
#else
    load_path(getenv("HOME"));
#endif
}

void filesystem_dialog::on_temp_path()
{
    load_path(fs::temp_directory_path());
}

void filesystem_dialog::on_copy()
{
    if ( !m_files_listbox.has_selection() )
        return;

    std::wstring filename = m_files_listbox.selected_string().wstring();
    if ( !ui::prompt("Enter new file name", "File coping", filename) )
        return;

    fs::copy(selected_path(), filename);

    refresh();
}

void filesystem_dialog::on_rename()
{
    if ( !m_files_listbox.has_selection() )
        return;

    std::wstring filename = m_files_listbox.selected_string().wstring();
    if ( !ui::prompt("Enter new file name", "File renaming", filename) )
        return;

    fs::rename(selected_path(), filename);

    refresh();
}

void filesystem_dialog::on_remove()
{
    if ( !m_files_listbox.has_selection() )
        return;

    const fs::path p = selected_path();

    if ( !ui::confirm(L"Are you sure that want to remove file " + p.wstring() + L"?") )
        return;

    if ( !fs::remove(p) )
        return;

    refresh();
}

void filesystem_dialog::load_path(const fs::path& p)
{
    if ( p == m_path )
        return;

    fs::current_path(p);
    m_path = p;
    refresh();
}

struct compare_path
{
    bool operator()(const fs::path p1, const fs::path p2) const
    {
        if ( fs::is_directory(p1) && !fs::is_directory(p2) )
            return true;
        else if ( !fs::is_directory(p1) && fs::is_directory(p2) )
            return false;
        else
            return boost::algorithm::ilexicographical_compare(p1.wstring(), p2.wstring());
    }
};

void filesystem_dialog::refresh()
{
    m_file_info_label.clear();
    m_copy_button.disable();
    m_rename_button.disable();
    m_remove_button.disable();

    m_path_label.text(m_path.wstring());
    show_file_info(m_path);

    std::vector<fs::path> files;
    std::copy(fs::directory_iterator(m_path), fs::directory_iterator(),
              std::back_inserter(files));
    std::sort(files.begin(), files.end(), compare_path());

    m_files_listbox.clear();

    for ( std::vector<fs::path>::const_iterator iter = files.begin();
         iter != files.end(); ++iter )
    {
        std::wstring filename = iter->filename().wstring();
        if ( fs::is_directory(*iter) )
            filename += L'/';
        m_files_listbox.push_back(filename);
    }

    m_up_button.enable(m_path.has_parent_path());
}

int ui_main()
{
    filesystem_dialog dlg(fs::current_path());
    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
