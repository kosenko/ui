// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Visualize sorting algorithms work.
// Work in progress.

#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_CHRONO)
#include <chrono>
namespace chrono_ns = std::chrono;
#else
#define BOOST_UI_USE_CHRONO
#include <boost/chrono.hpp>
namespace chrono_ns = boost::chrono;
#endif

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <vector>
#include <list>
#ifndef BOOST_NO_CXX11_HDR_FORWARD_LIST
#include <forward_list>
#endif
#include <set>
#include <cstdlib>
#include <ctime>

namespace ui = boost::ui;

template <class T>
T std_next(T x, typename std::iterator_traits<T>::difference_type n = 1)
{
    std::advance(x, n);
    return x;
}

template <class T>
T std_prev(T x, typename std::iterator_traits<T>::difference_type n = 1)
{
    std::advance(x, -n);
    return x;
}

//------------------------------------------------------------------------------
// algorithms

// Exchange sorts

template <class T>
void stupid_sort(T first, T last)
{
    for ( T i = first; ; )
    {
        T next = std_next(i);
        if ( next == last )
            break;

        if ( *next < *i )
        {
            std::iter_swap(i, next);
            i = first;
        }
        else ++i;
    }
}

template <class T>
void gnome_sort(T first, T last)
{
    for ( T i = first;; )
    {
        T next = std_next(i);
        if ( next == last )
            break;

        if ( *next < *i )
        {
            std::iter_swap(i, next);
            if ( i > first )
                --i;
        }
        else
            i = next;
    }
}

template <class T>
void bubble_sort(T first, T last)
{
    for ( T i = first; i != last; ++i )
    {
        T j = i;
        ++j;
        for ( ; j != last; ++j )
        {
            if ( *j < *i )
                std::iter_swap(i, j);
        }
    }
}

template <class T>
void stooge_sort(T first, T last)
{
    T end = std_prev(last);
    if ( *end < *first )
        std::iter_swap(end, first);

    typename std::iterator_traits<T>::difference_type k
            = std::distance(first, last) / 3;
    if ( k == 0 )
        return;

    T middle_1_3 = std_next(first, k);
    T middle_2_3 = std_prev(last,  k);

    stooge_sort(first,      middle_2_3);
    stooge_sort(middle_1_3, last);
    stooge_sort(first,      middle_2_3);
}

template <class T>
void quick_sort(T first, T last)
{
    typedef typename std::iterator_traits<T>::value_type value_type;

    if ( first == last )
        return;

    const value_type pivot = *std_next(first, std::distance(first, last) / 2);

    T middle1 = std::partition(first, last,
                               std::bind2nd( std::less<value_type>(), pivot));
    T middle2 = std::partition(middle1, last,
                               std::not1(std::bind1st( std::less<value_type>(), pivot)));

    quick_sort(first, middle1);
    quick_sort(middle2, last);
}

// Selection sorts

template <class T>
void selection_sort(T first, T last)
{
    for ( T i = first; i != last; ++i )
        std::iter_swap(i, std::min_element(i, last));
}

template <class T>
void heap_sort(T first, T last)
{
    std::make_heap(first, last);
    std::sort_heap(first, last);
}

// Insertion sorts

template <class T>
void insertion_sort(T first, T last)
{
    for ( T i = first; i != last; ++i )
        std::rotate(std::upper_bound(first, i, *i), i, std_next(i));
}

template <class T>
void shell_sort(T first, T last)
{
    for( typename std::iterator_traits<T>::difference_type d
            = std::distance(first, last) / 2; d != 0; d /= 2 )
        for ( T i = std_next(first, d); i != last; ++i )
            std::rotate(std::upper_bound(first, i, *i), i, std_next(i));
}

template <class T>
void tree_sort(T first, T last)
{
    std::multiset<typename std::iterator_traits<T>::value_type> tree(first, last);
    std::copy(tree.begin(), tree.end(), first);
};

// Merge sorts

template <class T>
T merge_sort(T first, T last)
{
    T middle = std_next(first, std::distance(first, last) / 2);

    if ( first != middle )
        std::inplace_merge(first, merge_sort(first, middle), merge_sort(middle, last));

    return last;
}

//------------------------------------------------------------------------------
// item

class item
{
public:
    class observer;

    item() : m_value(-1), m_observer(NULL) {}
    explicit item(int value, observer* o) : m_value(value), m_observer(o) {}

    int get() const { return m_value; }

    item(const item& other) : m_value(other.m_value), m_observer(other.m_observer)
    {
    }

#if 0
    bool operator==(const item& other) const
        { return m_value == other.m_value; }
#endif
    bool operator<(const item& other) const;
    static int cmp(const void *a, const void *b);

private:
    int m_value;

    observer* m_observer;
};

class item::observer
{
public:
    virtual ~observer() {}

    virtual void on_less(const item& item_less, const item& item_greater) = 0;
};

bool item::operator<(const item& other) const
{
    BOOST_ASSERT(m_observer);
    const bool result = m_value < other.m_value;
    m_observer->on_less(result ? *this : other,
                        result ? other : *this);
    return result;
}

int item::cmp(const void *a, const void *b)
{
    const item* item_a = static_cast<const item*>(a);
    const item* item_b = static_cast<const item*>(b);

    int result;
    if ( item_a->m_value < item_b->m_value )
        result = -1;
    else if ( item_a->m_value > item_b->m_value )
        result = 1;
    else
        result = 0;

    item_a->m_observer->on_less(result < 0 ? *item_a : *item_b,
                                result < 0 ? *item_b : *item_a);

    return result;
}

//------------------------------------------------------------------------------
// user interface

class sort_dialog : public ui::dialog, private item::observer
{
    typedef sort_dialog this_type;

public:
    sort_dialog();

private:
    void on_generate();
    void on_start();
    void on_next();
    void on_run();
    void on_close_handler(ui::close_event& e);

    void draw();

    typedef std::vector<item> array_type;
    //typedef std::list<item> array_type;
    //typedef std::forward_list<item> array_type;
    array_type m_array;
    const size_t m_max_value;
    boost::optional<size_t> m_index_less;
    boost::optional<size_t> m_index_greater;

    boost::optional<size_t> get_index(const item& i);
    void on_less(const item& item_less, const item& item_greater);

    ui::button m_generate_button;
    ui::button m_start_button;
    ui::button m_next_button;
    ui::button m_run_button;

    ui::canvas m_canvas;
    ui::event_loop m_loop;
};

sort_dialog::sort_dialog() : ui::dialog("Visualization of sorting algorithms"),
    m_max_value(10)
{
    on_close_event(boost::bind(&this_type::on_close_handler, this, _1));

    ui::hbox(*this)
        << m_canvas.create(*this)
            .on_resize(boost::bind(&this_type::draw, this))
            .layout().justify().stretch()
        << ( ui::vbox().layout().justify()
            << m_generate_button.create(*this, "&Generate")
                .on_press(&this_type::on_generate, this)
                .layout().justify()
            << m_start_button.create(*this, "&Start")
                .on_press(&this_type::on_start, this)
                .layout().justify()
            << m_next_button.create(*this, "&Next")
                .on_press(&this_type::on_next, this)
                .disable()
                .layout().justify()
            << m_run_button.create(*this, "&Run")
                .on_press(&this_type::on_run, this)
                .disable()
                .layout().justify()
           );

    on_generate();

    resize(600, 400);
}

void sort_dialog::on_generate()
{
    m_array.clear();

    for ( size_t i = 0; i < m_max_value; i++ )
    {
        const item local_item = item(std::rand() % m_max_value  + 1, this);
        //const item local_item = item(i + 1, this);
#if 1
        m_array.push_back(local_item);
#else
        m_array.push_front(local_item);
#endif
    }

    //std::random_shuffle(m_array.begin(), m_array.end());
    //std::sort(m_array.begin(), m_array.end());

    draw();
}

void sort_dialog::on_start()
{
    m_generate_button.disable();
    m_start_button.disable();
    m_next_button.enable();
    m_run_button.enable();

    //const item value = item(m_max_value / 2, this);
    //std::partition(m_array.begin(), m_array.end(),
    //               std::bind2nd(std::less<array_type::value_type>(), value));
    //std::sort(m_array.begin(), m_array.end());
    //std::binary_search(m_array.begin(), m_array.end(), value);
    //std::lower_bound(m_array.begin(), m_array.end(), value);
    //std::upper_bound(m_array.begin(), m_array.end(), value);
    //std::equal_range(m_array.begin(), m_array.end(), value);

    //std::stable_sort(m_array.begin(), m_array.end());
    //std::partial_sort(m_array.begin(), m_array.begin() + m_array.size() / 2, m_array.end());
    //std::nth_element(m_array.begin(), m_array.begin() + m_array.size() / 2, m_array.end());
    //std::qsort(&m_array[0], m_array.size(), sizeof(item), &item::cmp);
    //std::bsearch(&value, &m_array[0], m_array.size(), sizeof(item), &item::cmp);
    //m_array.sort();

    //stupid_sort(m_array.begin(), m_array.end());
    //gnome_sort(m_array.begin(), m_array.end());
    bubble_sort(m_array.begin(), m_array.end());
    //stooge_sort(m_array.begin(), m_array.end());
    //quick_sort(m_array.begin(), m_array.end());
    //selection_sort(m_array.begin(), m_array.end());
    //heap_sort(m_array.begin(), m_array.end());
    //insertion_sort(m_array.begin(), m_array.end());
    //shell_sort(m_array.begin(), m_array.end());
    //tree_sort(m_array.begin(), m_array.end());
    //merge_sort(m_array.begin(), m_array.end());

    //std::is_sorted(m_array.begin(), m_array.end());

    //std::unique(m_array.begin(), m_array.end();
    //m_array.erase(std::unique(m_array.begin(), m_array.end()), m_array.end());

    m_generate_button.enable();
    m_start_button.enable();
    m_next_button.disable();
    m_run_button.disable();

    m_index_less    = boost::none;
    m_index_greater = boost::none;

    draw();
}

void sort_dialog::on_next()
{
    m_loop.exit();
}

void sort_dialog::on_run()
{
    if ( m_loop.is_running() )
        m_loop.exit();

    if ( !m_start_button.is_enabled() )
    {
        ui::on_timeout(chrono_ns::milliseconds(100),
                       boost::bind(&this_type::on_run, this));
    }
}

void sort_dialog::on_close_handler(ui::close_event& e)
{
    if ( m_loop.is_running() )
    {
        e.veto();
        ui::error_dialog("Unable exit during algorithm execution");
    }
}

void sort_dialog::draw()
{
    ui::painter painter = m_canvas.painter();
    ui::painter::state_saver saver(painter);
    painter.clear_rect(0, 0, m_canvas.width(), m_canvas.height());

    if ( m_array.empty() )
        return;

#if 1
    const std::size_t size = m_array.size();
#else
    const std::size_t size = std::count_if(m_array.begin(), m_array.end(),
                                           [](const item&){ return true; });
#endif

    const ui::size dist(m_canvas.width()  / size,
                        m_canvas.height() / m_max_value);
    painter.translate(0, m_canvas.height()).scale(1, -1).translate(0.5, 0.5);
    painter.stroke_color(ui::color::blue);
    size_t index = 0;
    for ( array_type::const_iterator iter = m_array.begin();
         iter != m_array.end(); ++iter, index++ )
    {
        const ui::gpoint p(index * dist.width(), 0);
        const ui::grect rect(p, ui::gpoint(p.x() + dist.width() - 2,
                                           iter->get() * dist.height()));
        painter.stroke_rect(rect);
        if ( index == m_index_less )
        {
            painter.fill_color(ui::color::red).fill_rect(rect);
        }
        if ( index == m_index_greater )
        {
            painter.fill_color(ui::color::lime).fill_rect(rect);
        }
    }
}

boost::optional<size_t> sort_dialog::get_index(const item& i)
{
#if 0
    const size_t pos = &i - &m_array[0];
    if ( pos >= 0 && pos < m_array.size() )
        return pos;
    else
        return boost::none;
#else
    boost::optional<size_t> result;
    size_t index = 0;
    for ( array_type::const_iterator iter = m_array.begin();
         iter != m_array.end(); ++iter, index++ )
    {
        if ( &*iter == &i )
            return index;
    }
    return result;
#endif
}

void sort_dialog::on_less(const item& item_less, const item& item_greater)
{
    if ( m_start_button.is_enabled() )
        return;

    m_index_less    = get_index(item_less);
    m_index_greater = get_index(item_greater);

    draw();
    m_loop.run();
}

int ui_main()
{
    std::srand(static_cast<unsigned>( std::time(NULL) ));

    sort_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
