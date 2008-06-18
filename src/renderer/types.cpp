/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/types.hpp>
#include <sge/exception.hpp>

unsigned sge::renderer::bit_depth_bit_count(const bit_depth::type d)
{
	return static_cast<unsigned>(d);
}

bool sge::renderer::lock_flag_write(const lock_flag_t mode)
{
	switch(mode) {
	case lock_flags::readonly:
		return false;
	default:
		return true;
	}
}

bool sge::renderer::lock_flag_read(const lock_flag_t mode)
{
	switch(mode) {
	case lock_flags::writeonly:
		return false;
	default:
		return true;
	}
}
