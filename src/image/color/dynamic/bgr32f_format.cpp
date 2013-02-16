/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format.hpp>
#include <sge/src/image/color/dynamic/available_channels.hpp>
#include <sge/src/image/color/dynamic/available_layouts.hpp>
#include <sge/src/image/color/dynamic/bgr32f_format.hpp>
#include <sge/src/image/color/dynamic/c32f_3_format.hpp>
#include <sge/src/image/color/dynamic/format_object_impl.hpp>


namespace
{

sge::image::color::dynamic::c32f_3_format::channel_array const channels{{
	sge::image::color::dynamic::available_channels::blue,
	sge::image::color::dynamic::available_channels::green,
	sge::image::color::dynamic::available_channels::red
}};

}

sge::image::color::dynamic::c32f_3_format const
sge::image::color::dynamic::bgr32f_format(
	channels,
	sge::image::color::dynamic::available_layouts::rgb,
	sge::image::color::format::bgr32f
);