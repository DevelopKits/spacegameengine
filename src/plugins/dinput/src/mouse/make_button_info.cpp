/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/element_name.hpp>
#include <sge/dinput/mouse/button_code.hpp>
#include <sge/dinput/mouse/make_button_info.hpp>
#include <sge/input/info/optional_string.hpp>
#include <sge/input/mouse/button_info.hpp>


sge::input::mouse::button_info const
sge::dinput::mouse::make_button_info(
	DIDEVICEOBJECTINSTANCE const &_data
)
{
	return
			sge::input::mouse::button_info(
				sge::dinput::mouse::button_code(
					_data.dwOfs
				),
				sge::dinput::device::element_name(
					_data
				)
			);
}