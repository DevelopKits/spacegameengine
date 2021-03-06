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
#include <sge/opengl/occlusion_query/context.hpp>
#include <sge/opengl/occlusion_query/create.hpp>
#include <sge/opengl/occlusion_query/object.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::renderer::occlusion_query::object_unique_ptr
sge::opengl::occlusion_query::create(
	sge::opengl::context::object &_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::occlusion_query::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::occlusion_query::object
			>(
				fcppt::optional::to_exception(
					sge::opengl::context::use<
						sge::opengl::occlusion_query::context
					>(
						_context,
						_context.info()
					).config(),
					[]{
						return
							sge::renderer::unsupported(
								FCPPT_TEXT("occlusion queries"),
								FCPPT_TEXT("1.5"),
								FCPPT_TEXT("")
							);
					}
				)
			)
		);
}
