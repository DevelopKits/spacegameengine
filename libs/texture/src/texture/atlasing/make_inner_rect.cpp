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


#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/atlasing/make_inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>
#include <fcppt/math/box/shrink.hpp>
#include <fcppt/math/vector/fill.hpp>


sge::texture::atlasing::inner_rect
sge::texture::atlasing::make_inner_rect(
	sge::texture::atlasing::outer_rect const &_outer
)
{
	return
		sge::texture::atlasing::inner_rect(
			fcppt::math::box::shrink(
				_outer.get(),
				fcppt::math::vector::fill<
					sge::renderer::lock_rect::vector
				>(
					1u
				)
			)
		);
}
