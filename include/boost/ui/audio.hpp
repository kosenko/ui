// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file audio.hpp Audio

#ifndef BOOST_UI_AUDIO_HPP
#define BOOST_UI_AUDIO_HPP

#include <boost/ui/config.hpp>

namespace boost {
namespace ui    {

/// @brief Rings the system bell
/// @see <a href="http://en.wikipedia.org/wiki/Beep_(sound)">Beep (Wikipedia)</a>
/// @ingroup audio
BOOST_UI_DECL void beep();

} // namespace ui
} // namespace boost

#endif // BOOST_UI_AUDIO_HPP
