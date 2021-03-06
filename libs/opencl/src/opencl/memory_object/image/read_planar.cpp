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


#include <sge/image/raw_pointer.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/memory_object/image/read_planar.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


void
sge::opencl::memory_object::image::read_planar(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::memory_object::image::planar const &_image,
	sge::image2d::view::object const &_view,
	sge::opencl::memory_object::rect const &_rect)
{
	sge::opencl::command_queue::scoped_planar_mapping scoped_map(
		_queue,
		const_cast<opencl::memory_object::image::planar &>(
			_image),
		sge::opencl::command_queue::map_flags::read,
		_rect,
		sge::opencl::event::sequence());

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			static_cast<sge::image::raw_pointer>(
				scoped_map.ptr()),
			fcppt::math::dim::structure_cast<
				sge::image2d::dim,
				fcppt::cast::size_fun
			>(
				_rect.size()
			),
			image::opencl_color_format_to_sge(
				_image.image_format()),
			image2d::pitch(
				static_cast<image2d::pitch::value_type>(
					scoped_map.pitch()))),
		_view,
		sge::image::algorithm::may_overlap::yes,
		sge::image::algorithm::uninitialized::yes);
}
