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


#ifndef SGE_IMAGE_IMPL_VIEW_FORMAT_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_FORMAT_ANY_HPP_INCLUDED

#include <sge/image/impl/view/format_type.hpp>
#include <sge/image/traits/format_fwd.hpp>
#include <sge/image/traits/format_static.hpp>
#include <fcppt/use.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace view
{

template<
	typename ColorTag,
	typename View
>
typename
sge::image::traits::format<
	ColorTag
>::type
format_any(
	View const &_view
)
{
	return
		fcppt::variant::apply_unary(
			[](
				auto const &_src
			)
			{
				FCPPT_USE(
					_src
				);

				return
					sge::image::traits::format_static<
						ColorTag
					>:: template apply<
						typename
						sge::image::impl::view::format_type<
							typename
							std::decay<
								decltype(
									_src
								)
							>::type
						>::color_format
					>::value;
			},
			_view.get()
		);
}

}
}
}
}

#endif