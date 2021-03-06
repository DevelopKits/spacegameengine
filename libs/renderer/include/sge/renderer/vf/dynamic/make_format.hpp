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


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/detail/make_part.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/algorithm/map.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Format
>
sge::renderer::vf::dynamic::format
make_format()
{
	return
		sge::renderer::vf::dynamic::format{
			fcppt::algorithm::map<
				sge::renderer::vf::dynamic::part_list
			>(
				typename
				Format::parts{},
				[](
					auto const &_tag
				)
				{
					FCPPT_USE(
						_tag
					);

					return
						sge::renderer::vf::dynamic::detail::make_part<
							fcppt::tag_type<
								decltype(
									_tag
								)
							>
						>();
				}
			)
		};
}

}
}
}
}

#endif
