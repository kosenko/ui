// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Show native API usage.

#include <boost/ui.hpp>
#include <boost/ui/native/all.hpp>

#include <boost/bind.hpp>

#include <wx/wx.h>

#include <sstream>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("Boost.UI native API usage example");

    wxWindow* native_dialog = ui::native::from_widget(dlg);
    wxCHECK_MSG(native_dialog, 1, "Invalid native dialog");
    native_dialog->SetTransparent(224);

    std::ostringstream ss;
    ss << wxGetLibraryVersionInfo().ToString();
    ss << "\nBuild options: " << WX_BUILD_OPTIONS_SIGNATURE;
    wxStaticText* staticText = new wxStaticText(native_dialog, wxID_ANY, ss.str());

    wxButton* button = new wxButton(native_dialog, wxID_ANY, "C&lose");
    button->Bind(wxEVT_BUTTON, boost::bind(&wxDialog::Close, native_dialog, false));

    ui::vbox(dlg)
        << ui::native_widget(staticText)
            .layout().stretch()
        << ui::native_widget(button)
            .layout().center()
        ;

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
