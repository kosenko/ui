// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_USE_GEOMETRY

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <fstream>

namespace ui = boost::ui;

template <class Geometry, class Box>
bool read_wkt_file(const std::string& filename, std::vector<Geometry>& geometries, Box& box)
{
    std::ifstream file(filename.c_str());
    if ( !file.is_open() )
        return false;

    while ( !file.eof() )
    {
        std::string line;
        std::getline(file, line);
        if ( !line.empty() )
        {
            Geometry geometry;
            boost::geometry::read_wkt(line, geometry);
            geometries.push_back(geometry);
            boost::geometry::expand(box, boost::geometry::return_envelope<Box>(geometry));
        }
    }

    return true;
}

class geometry_dialog : public ui::dialog
{
    typedef geometry_dialog this_type;

public:
    geometry_dialog(const std::string& filename);

private:
    void draw();

    ui::canvas m_canvas;

    typedef double value_type;
    typedef boost::geometry::model::d2::point_xy<value_type> point_type;
    typedef boost::geometry::model::polygon<point_type> polygon_type;
    typedef boost::geometry::model::multi_polygon<polygon_type> country_type;
    typedef std::vector<country_type> countries_type;

    countries_type m_countries;

    typedef boost::geometry::model::box<point_type> box_type;
    box_type m_box;
};

geometry_dialog::geometry_dialog(const std::string& filename)
    : ui::dialog("Boost.Geometry + Boost.UI example")
{
    boost::geometry::assign_inverse(m_box);
    if ( !filename.empty() && !read_wkt_file(filename, m_countries, m_box) )
        ui::error_dlg("File not found: " + filename);

    if ( m_countries.empty() )
    {
        country_type geometry;
        boost::geometry::read_wkt("MULTIPOLYGON(((0 0,0 70,40 20,20 0,0 0)))", geometry);
        m_countries.push_back(geometry);
        boost::geometry::expand(m_box, boost::geometry::return_envelope<box_type>(geometry));
    }

    m_canvas.create(*this).on_resize(boost::bind(&this_type::draw, this));
}

void geometry_dialog::draw()
{
    ui::painter painter = m_canvas.painter();

    boost::geometry::strategy::transform::map_transformer<value_type, 2, 2, true, true>
        transformer(m_box, m_canvas.width(), m_canvas.height());

    for ( countries_type::const_iterator country = m_countries.begin();
          country != m_countries.end(); ++country )
    {
        for ( country_type::const_iterator polygon = country->begin();
              polygon != country->end(); ++polygon )
        {
            painter.begin_path();
            for ( polygon_type::ring_type::const_iterator point = polygon->outer().begin();
                  point != polygon->outer().end(); ++point )
            {
                point_type transformed_point = *point;
                boost::geometry::transform(*point, transformed_point, transformer);

                if ( point == polygon->outer().begin() )
                    painter.move_to(ui::gpoint(transformed_point));
                else
                    painter.line_to(ui::gpoint(transformed_point));
            }
            painter.stroke();
        }
    }
}

int ui_main(int argc, char* argv[])
{
    // filename: boost/libs/geometry/example/data/world.wkt

    geometry_dialog(argc == 2 ? argv[1] : "").show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
