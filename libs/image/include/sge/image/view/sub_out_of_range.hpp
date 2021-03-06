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


#ifndef SGE_IMAGE_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/box.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/sub_out_of_range_fwd.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL sub_out_of_range
:
	public sge::image::exception
{
public:
	typedef
	sge::image::box<
		Tag
	>
	box;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range(
		box const &outer,
		box const &inner
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	box const &
	outer() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	box const &
	inner() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~sub_out_of_range() throw()
	override;
private:
	box
		outer_,
		inner_;
};

}
}
}

#endif
