// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>
#include <boost/ui/native/all.hpp>

#include <boost/bind.hpp>

#include <wx/wx.h>

#include <sstream>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("Boost.UI native API usage example");

    wxWindow* native_dlg = ui::native::from_widget(dlg);
    wxCHECK(native_dlg, 1);
    native_dlg->SetTransparent(224);

    std::ostringstream ss;
    ss << wxGetLibraryVersionInfo().ToString();
    ss << "\nBuild options: " << WX_BUILD_OPTIONS_SIGNATURE;
    wxStaticText* staticText = new wxStaticText(native_dlg, wxID_ANY, ss.str());

    wxButton* button = new wxButton(native_dlg, wxID_ANY, "C&lose");
    button->Bind(wxEVT_BUTTON, boost::bind(&wxDialog::Close, native_dlg, false));

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
    return ui::entry(argc, argv, &ui_main);
}
