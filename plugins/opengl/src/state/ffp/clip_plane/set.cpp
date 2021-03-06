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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/set_array.hpp>
#include <sge/opengl/state/convert/clip_plane_index.hpp>
#include <sge/opengl/state/ffp/clip_plane/context.hpp>
#include <sge/opengl/state/ffp/clip_plane/object.hpp>
#include <sge/opengl/state/ffp/clip_plane/set.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>


void
sge::opengl::state::ffp::clip_plane::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_planes
)
{
	sge::opengl::state::set_array<
		sge::opengl::state::ffp::clip_plane::object
	>(
		sge::opengl::context::use<
			sge::opengl::state::ffp::clip_plane::context
		>(
			_context
		),
		_planes,
		sge::opengl::state::convert::clip_plane_index
	);
}
