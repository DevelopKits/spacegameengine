/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_FONT_DRAW_COLOR_FORMAT_HPP_INCLUDED
#define SGE_FONT_DRAW_COLOR_FORMAT_HPP_INCLUDED

#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/optional_format_fwd.hpp>


namespace sge
{
namespace font
{
namespace draw
{

SGE_FONT_DRAW_DETAIL_SYMBOL
sge::image::color::format
color_format(
	sge::image::color::optional_format const &
);

}
}
}

#endif
