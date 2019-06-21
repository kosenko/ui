// Copyright (c) 2019 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Data representation example
// Shows bit representation of floating-point numbers

#include <boost/ui.hpp>
#include <sstream>
#include <limits>

namespace ui = boost::ui;

class data_representation_dialog : public ui::dialog
{
    typedef data_representation_dialog this_type;

public:
    data_representation_dialog();

private:
    void update_from_check_boxes();
    void update_from_string_box();
    void update();
    void update_check_boxes();
    void update_string_box();
    void update_label();

    std::vector<ui::check_box> m_check_boxes;
    ui::string_box m_string_box;
    ui::label m_label;

    //typedef bool value_type;
    //typedef char value_type; // not works yet
    //typedef unsigned char value_type; // not works yet
    //typedef wchar_t value_type;
    //typedef short value_type;
    //typedef unsigned short value_type;
    //typedef int value_type;
    //typedef unsigned value_type;
    //typedef long value_type;
    //typedef unsigned long value_type;
    //typedef long long value_type;
    //typedef unsigned long long value_type;
    typedef float value_type;
    //typedef double value_type;
    //typedef long double value_type; // not works yet

    value_type m_value;

    static const auto BITS_COUNT = CHAR_BIT * sizeof(m_value);
};

data_representation_dialog::data_representation_dialog()
    : ui::dialog("Number data representation example"), m_value(0)
{
    auto main_layout = ui::vbox(*this);
    auto check_boxes_layout = ui::vbox();
    main_layout << check_boxes_layout.layout().center();
    for ( auto j = 0u; j < sizeof(m_value); j++ ) {
        auto check_boxes_row = ui::hbox();
        check_boxes_layout << check_boxes_row;
        for ( auto i = 0u; i < CHAR_BIT; i++ ) {
            auto cb = ui::check_box(*this, "");
            cb.tooltip("Bit #" + std::to_string(BITS_COUNT - 1 - m_check_boxes.size()));
            m_check_boxes.push_back(cb);
            check_boxes_row << cb.on_toggle(&this_type::update_from_check_boxes, this);
        }
    }

    main_layout << m_string_box.create(*this, "")
        .on_edit(&this_type::update_from_string_box, this)
        .layout().justify();

    main_layout << m_label.create(*this, "")
        .layout().justify();

    main_layout << (ui::vbox().layout().center()
            << ( ui::hbox()
                << ui::button(*this, "+ 1").on_press([this]{
                    m_value++;
                    update();
                })
                << ui::button(*this, "- 1").on_press([this]{
                    m_value -= 1;
                    update();
                })
                << ui::button(*this, "* 2").on_press([this]{
                    m_value *= 2;
                    update();
                })
                << ui::button(*this, "/ 2").on_press([this]{
                    m_value /= 2;
                    update();
                })
            )
            << ( ui::hbox()
                << ui::button(*this, "* -1").on_press([this]{
                    m_value *= -1;
                    update();
                })
                << ui::button(*this, "1 / x").on_press([this]{
                    m_value = 1 / m_value;
                    update();
                })
                << ui::button(*this, "= 0").on_press([this]{
                    m_value = 0;
                    update();
                })
                << ui::button(*this, "= 1").on_press([this]{
                    m_value = 1;
                    update();
                })
            )
            << ( ui::hbox()
                << ui::button(*this, "max").on_press([this]{
                    m_value = std::numeric_limits<value_type>::max();
                    update();
                })
                << ui::button(*this, "min").on_press([this]{
                    m_value = std::numeric_limits<value_type>::min();
                    update();
                })
                << ui::button(*this, "denorm_min").on_press([this]{
                    m_value = std::numeric_limits<value_type>::denorm_min();
                    update();
                })
                << ui::button(*this, "lowest").on_press([this]{
                    m_value = std::numeric_limits<value_type>::lowest();
                    update();
                })
            )
            << ( ui::hbox()
                << ui::button(*this, "infinity").on_press([this]{
                    m_value = std::numeric_limits<value_type>::infinity();
                    update();
                })
                << ui::button(*this, "quiet_NaN").on_press([this]{
                    m_value = std::numeric_limits<value_type>::quiet_NaN();
                    update();
                })
                << ui::button(*this, "signaling_NaN").on_press([this]{
                    m_value = std::numeric_limits<value_type>::signaling_NaN();
                    update();
                })
            )
            << ( ui::hbox()
                << ui::button(*this, "epsilon").on_press([this]{
                    m_value = std::numeric_limits<value_type>::epsilon();
                    update();
                })
                << ui::button(*this, "round_error").on_press([this]{
                    m_value = std::numeric_limits<value_type>::round_error();
                    update();
                })
            )
        )
        ;

    resize(500, 700);

    update_from_check_boxes();
}

void data_representation_dialog::update_from_check_boxes()
{
    std::bitset<BITS_COUNT> data;
    for ( auto i = 0u; i < m_check_boxes.size(); i++ ) {
        data[BITS_COUNT - 1 - i] = m_check_boxes[i].is_checked();
    }
    const unsigned long long l = data.to_ullong();
    static_assert(sizeof l >= sizeof m_value, "long too short");
    m_value = *reinterpret_cast<const value_type*>(&l);

    update_string_box();
    update_label();
}

void data_representation_dialog::update_from_string_box()
{
    std::wistringstream ss(m_string_box.text().wstring());
    m_value = 0;
    ss >> m_value;

    update_check_boxes();
    update_label();
}

void data_representation_dialog::update()
{
    update_check_boxes();
    update_string_box();
    update_label();
}

void data_representation_dialog::update_check_boxes()
{
    const unsigned long long l = *reinterpret_cast<unsigned long long*>(&m_value);
    std::bitset<BITS_COUNT> data(l);
    for ( auto i = 0u; i < m_check_boxes.size(); i++ ) {
        m_check_boxes[i].check(data[BITS_COUNT - 1 - i]);
    }
}

void data_representation_dialog::update_string_box()
{
    std::wostringstream os;
    os << m_value;
    m_string_box.text(os.str());
}

void data_representation_dialog::update_label()
{
    std::wostringstream os;
    os << m_value;
    m_label.text(os.str());
}

int ui_main()
{
    data_representation_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
