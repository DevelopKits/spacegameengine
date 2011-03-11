/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_RENDER_ONE_ADVANCED_HPP_INCLUDED
#define SGE_SPRITE_RENDER_ONE_ADVANCED_HPP_INCLUDED

#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/dont_sort.hpp>
#include <sge/sprite/default_equal.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
void
render_one_advanced(
	external_system<
		Choices
	> &_system,
	object<
		Choices
	> const &_sprite
)
{
	_system.render_advanced(
		&_sprite,
		&_sprite + 1u,
		sprite::dont_sort(),
		sprite::default_equal()
	);
}

}
}

#endif