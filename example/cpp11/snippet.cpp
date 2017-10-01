// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Compilable source code snippets that are used in documentation.

#include <boost/config.hpp>

#include <chrono>

#include <boost/ui.hpp>

#include <functional> // std::bind()

namespace ui = boost::ui;

/// [button]
class button_dialog : public ui::dialog
{
public:
    button_dialog() : ui::dialog("Button usage dialog")
    {
        ui::button(*this, "&Press me")
            .on_press(&button_dialog::on_press_me, this);

        show_modal();
    }

private:
    void on_press_me()
    {
        ui::info_dlg("Hello");
    }
};
/// [button]

int ui_main()
{
    ui::dialog parent("Boost.UI documentation snippets");

    ui::vbox layout(parent);

    layout << ui::button(parent, "&button").on_press([]{ button_dialog(); });

    layout << ui::button(parent, "&Event").on_press([]
    {
/// [event]
ui::dialog dlg("Example dialog");
ui::button(dlg, "&Quit").on_press(&ui::dialog::close, &dlg);
dlg.show_modal();
/// [event]
    });

    layout << ui::button(parent, "&Timeout").on_press([]
    {
/// [on_timeout]
ui::on_timeout(std::chrono::milliseconds(1000), []{ BOOST_UI_LOG; });
/// [on_timeout]
    });

/// [combobox]
ui::combobox combobox = ui::combobox(parent, "Initial text",
    { "Option 1", "Option 2", "Option 3" })
    .on_select_event([&](ui::index_event& e)
    {
        ui::log::info() << "Selected index: " << e.index()
                        << ", text: " << combobox.text();
    });
/// [combobox]
    layout << combobox.layout().justify();

    parent.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
