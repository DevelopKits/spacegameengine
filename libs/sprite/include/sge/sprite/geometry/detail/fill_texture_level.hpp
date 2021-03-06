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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_HPP_INCLUDED

#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/geometry/detail/fill_texture_level_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/tag_type.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
class fill_texture_level
{
	FCPPT_NONASSIGNABLE(
		fill_texture_level
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	fill_texture_level(
		Iterator const &_iterator,
		object const &_object
	)
	:
		iterator_(
			_iterator
		),
		object_(
			_object
		)
	{
	}

	template<
		typename Level
	>
	void
	operator()(
		Level const &
	) const
	{
		typedef
		fcppt::tag_type<
			Level
		>
		level;

		sge::sprite::geometry::detail::fill_texture_level_impl<
			level
		>(
			iterator_,
			object_,
			sge::sprite::deref_texture(
				object_. template texture_level<
					level::value
				>()
			)
		);
	}
private:
	Iterator const iterator_;

	object const &object_;
};

}
}
}
}

#endif
