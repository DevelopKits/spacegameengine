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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_SIZE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_SIZE_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <fcppt/algorithm/fold.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{
namespace detail
{

template<
	typename Order,
	typename Choices
>
inline
sge::sprite::count
range_size(
	sge::sprite::intrusive::ordered::detail::map<
		Order,
		Choices
	> const &_ordered_map
)
{
	return
		fcppt::algorithm::fold(
			_ordered_map,
			sge::sprite::count{
				0u
			},
			[](
				auto const &_element,
				sge::sprite::count const _value
			)
			{
				return
					_value
					+
					_element.second->range().size();
			}
		);
}

}
}
}
}
}

#endif
