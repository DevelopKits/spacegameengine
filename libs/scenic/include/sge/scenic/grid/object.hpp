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


#ifndef SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/grid/depth_test.hpp>
#include <sge/scenic/grid/distance_to_origin.hpp>
#include <sge/scenic/grid/orientation_fwd.hpp>
#include <sge/scenic/grid/rect.hpp>
#include <sge/scenic/grid/spacing.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace grid
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::renderer::device::ffp &,
		sge::camera::base const &,
		sge::scenic::grid::orientation,
		sge::scenic::grid::rect const &,
		sge::scenic::grid::spacing const &,
		sge::scenic::grid::distance_to_origin const &,
		sge::image::color::any::object const &);

	SGE_SCENIC_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &,
		sge::scenic::grid::depth_test const &);

	SGE_SCENIC_DETAIL_SYMBOL
	~object();
private:
	sge::renderer::device::ffp &renderer_;
	sge::camera::base const &camera_;
	sge::line_drawer::object line_drawer_;
};
}
}
}

#endif
