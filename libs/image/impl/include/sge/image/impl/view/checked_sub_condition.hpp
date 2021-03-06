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


#ifndef SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED

#include <sge/image/box.hpp>
#include <sge/image/view/size.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/vector/null.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace view
{

template<
	typename Tag,
	typename View
>
void
checked_sub_condition(
	View const &_src,
	sge::image::box<
		Tag
	> const &_box
)
noexcept(
	false
)
{
	typedef
	sge::image::box<
		Tag
	>
	box;

	box const outer(
		fcppt::math::vector::null<
			typename
			box::vector
		>(),
		sge::image::view::size<
			Tag
		>(
			_src
		)
	);

	if(
		!fcppt::math::box::contains(
			outer,
			_box
		)
	)
		throw
			sge::image::view::sub_out_of_range<
				Tag
			>{
				outer,
				_box
			};
}

}
}
}
}

#endif
