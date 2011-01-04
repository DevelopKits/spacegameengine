/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_HPP_INCLUDED

#include <sge/sprite/detail/fill_tex_coordinates_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/texture/part.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_texture
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	void
>::type
fill_tex_coordinates(
	Iterator const &_iterator,
	object<
		Choices
	> const &_sprite
)
{
	if(
		!_sprite.texture()
		|| !_sprite.texture()->texture()
	)
		return;
	
	detail::fill_tex_coordinates_impl(
		_iterator,
		_sprite
	);
}

template<
	typename Iterator,
	typename Choices
>
typename boost::disable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_texture
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	void
>::type
fill_tex_coordinates(
	Iterator const &,
	object<
		Choices
	> const &
)
{
}

}
}
}

#endif
