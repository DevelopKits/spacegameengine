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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_STATIC_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_STATIC_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_may_overlap.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <sge/image/impl/traits/static_converter.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/image/algorithm/copy_and_convert.hpp>
#include <fcppt/variant/apply_binary.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace algorithm
{

template<
	typename Tag
>
void
copy_and_convert_static(
	sge::image::view::const_object<
		Tag
	> const &_src,
	sge::image::view::object<
		Tag
	> const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	fcppt::variant::apply_binary(
		[
			_overlap,
			_uninitialized
		](
			auto const &_src_inner,
			auto const &_dest_inner
		)
		{
			return
				mizuiro::image::algorithm::copy_and_convert<
					sge::image::impl::traits::static_converter<
						sge::image::traits::image::color_tag<
							Tag
						>
					>
				>(
					_src_inner,
					_dest_inner,
					sge::image::impl::algorithm::convert_may_overlap(
						_overlap
					),
					sge::image::impl::algorithm::convert_uninitialized(
						_uninitialized
					)
				);
		},
		_src.get(),
		_dest.get()
	);
}

}
}
}
}

#endif
