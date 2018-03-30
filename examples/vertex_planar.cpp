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


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::core
			>,
			sge::systems::with_input
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge vertex planar example")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

	typedef sge::renderer::vf::pos<
		float,
		3
	> pos3_type;

	typedef sge::image::color::bgra8_format bgra8_format;

	typedef sge::renderer::vf::color<
		bgra8_format
	> color_type;

	typedef sge::renderer::vf::part<
		brigand::list<
			pos3_type
		>
	> pos_format_part;

	typedef sge::renderer::vf::part<
		brigand::list<
			color_type
		>
	> color_format_part;


	typedef sge::renderer::vf::format<
		brigand::list<
			pos_format_part,
			color_format_part
		>
	> format;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);

	sge::renderer::vertex::count const num_vertices(
		3u
	);

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer1(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					format,
					pos_format_part
				>(),
				num_vertices,
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer2(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					format,
					color_format_part
				>(),
				num_vertices,
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	{
		sge::renderer::vertex::scoped_lock const vblock(
			*vertex_buffer1,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			pos_format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef pos3_type::packed_type vec3;

		(*vb_it++).set<pos3_type>(
			vec3(-1.f, 1.f, 0.f)
		);

		(*vb_it++).set<pos3_type>(
			vec3(-1.f, -1.f, 0.f)
		);

		(*vb_it++).set<pos3_type>(
			vec3(1.f, 1.f, 0.f)
		);
	}

	{
		sge::renderer::vertex::scoped_lock const vblock(
			*vertex_buffer2,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			color_format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		(*vb_it++).set<color_type>(
			sge::image::color::convert<
				bgra8_format
			>(
				sge::image::color::predef::cyan()
			)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::convert<
				bgra8_format
			>(
				sge::image::color::predef::yellow()
			)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::convert<
				bgra8_format
			>(
				sge::image::color::predef::magenta()
			)
		);
	}

	fcppt::signal::auto_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	auto const draw(
		[
			num_vertices,
			&vertex_buffer1,
			&vertex_buffer2,
			&vertex_declaration,
			&sys
		]
		{
			sge::renderer::context::scoped_core const scoped_block(
				sys.renderer_device_core(),
				sys.renderer_device_core().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
				scoped_block.get(),
				*vertex_declaration,
				sge::renderer::vertex::const_buffer_ref_container{
					fcppt::make_cref(
						*vertex_buffer1
					),
					fcppt::make_cref(
						*vertex_buffer2
					)
				}
			);

			scoped_block.get().render_nonindexed(
				sge::renderer::vertex::first(
					0u
				),
				num_vertices,
				sge::renderer::primitive_type::triangle_list
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
						}
					);
				}
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
