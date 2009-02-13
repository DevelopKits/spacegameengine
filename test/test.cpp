/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/any_color_print.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/input/system.hpp>
#include <sge/input/plugin.hpp>
#include <sge/input/action.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/plugin.hpp>
#include <sge/image/object.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/window/parameters.hpp>
#include <sge/media.hpp>
#include <sge/endianness.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/iostream.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/renderer/color.hpp>
#include <sge/log/global.hpp>
#include <sge/log/logger.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);
	
	bool running = true;
	sge::plugin::manager pm;

	const sge::plugin::plugin<sge::renderer::system>::ptr_type renderer_plugin = pm.plugin<sge::renderer::system>().load();
	const sge::plugin::plugin<sge::input::system>::ptr_type input_plugin = pm.plugin<sge::input::system>().load();

	const sge::renderer::system_ptr rs(renderer_plugin->get()());
	const sge::renderer::parameters param(
		sge::renderer::display_mode(
			sge::renderer::screen_size_t(1280, 1024),
			sge::renderer::bit_depth::depth32,
			sge::renderer::refresh_rate_dont_care),
		sge::renderer::depth_buffer::off,
		sge::renderer::stencil_buffer::off,
		sge::renderer::window_mode::windowed,
		sge::renderer::vsync::on);
	
	sge::window::instance_ptr const wnd(
		rs->create_window(
			sge::window::parameters(
				SGE_TEXT("sgetest"),
				sge::window::dim_type(
					1280,
					1024)
			),
			param));

	const sge::renderer::device_ptr rend = rs->create_renderer(
		param,
		static_cast<sge::renderer::adapter_type>(0),
		wnd);

	const sge::input::system_ptr is(input_plugin->get()(rend->window()));

	const sge::plugin::plugin<sge::image::loader>::ptr_type image_plugin = pm.plugin<sge::image::loader>().load();
	const sge::image::loader_ptr image_loader(image_plugin->get()());

	sge::signals::scoped_connection const cb(
		is->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::renderer::texture_ptr const testtex(
		rend->create_texture(
			sge::renderer::texture::dim_type(256, 256),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::readable));
	{
		sge::renderer::scoped_texture_lock const lock_(
			testtex,
			sge::renderer::lock_rect(
				100,
				100,
				200,
				200),
			sge::renderer::lock_flags::readwrite);

		sge::renderer::fill_pixels(
			sge::renderer::subimage_view(
				lock_.value(),
				sge::renderer::lock_rect(0, 0, 50, 50)),
			sge::renderer::rgba8_color(255, 0, 0, 255));


		image_loader->create(
			sge::renderer::make_const_image_view(lock_.value()))->save(
				SGE_TEXT("sge_test.png"));
	}

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::rgba8_color(255, 255, 0, 255))
			(sge::renderer::state::cull_mode::off)
		);
	sge::string const some_text(SGE_TEXT("de\nEFygY\ngyhgh"));
	while(running)
	{
		sge::mainloop::dispatch();

		sge::renderer::state::scoped const states_(
			rend,
			sge::renderer::state::list
				(sge::renderer::state::color_::clear_color
				= sge::renderer::rgba8_color(255, 0, 0, 255))
				(sge::renderer::state::bool_::clear_backbuffer = true)
			);

		sge::renderer::scoped_block const block_(rend);
	}
	return EXIT_SUCCESS;
}
catch(const sge::exception& e)
{
	sge::cerr << "Program terminated (sge::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(const std::exception& e)
{
	sge::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	sge::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}
