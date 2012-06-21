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
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/keyboard/enumerator.hpp>
#include <sge/dinput/keyboard/info.hpp>
#include <sge/dinput/keyboard/key_converter_fwd.hpp>
#include <sge/dinput/keyboard/make_info.hpp>


sge::dinput::keyboard::info const
sge::dinput::keyboard::make_info(
	IDirectInputDevice8 &_device,
	sge::dinput::keyboard::key_converter const &_key_converter
)
{
	sge::dinput::keyboard::enumerator object(
		_key_converter
	);

	sge::dinput::device::enumerate_objects(
		_device,
		object,
		DIDFT_ALL
	);

	return
		sge::dinput::keyboard::info(
			object.key_map()
		);
}