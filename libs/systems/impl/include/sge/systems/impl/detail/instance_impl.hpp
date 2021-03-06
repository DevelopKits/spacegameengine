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


#ifndef SGE_SYSTEMS_IMPL_DETAIL_INSTANCE_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_DETAIL_INSTANCE_IMPL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/plugin/cache.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/optional_log_context_ref_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/log_context.hpp>
#include <sge/systems/impl/audio/loader_unique_ptr.hpp>
#include <sge/systems/impl/audio/player_unique_ptr.hpp>
#include <sge/systems/impl/font/object_unique_ptr.hpp>
#include <sge/systems/impl/image2d/object_unique_ptr.hpp>
#include <sge/systems/impl/input/object_unique_ptr.hpp>
#include <sge/systems/impl/renderer/device_unique_ptr.hpp>
#include <sge/systems/impl/renderer/system_unique_ptr.hpp>
#include <sge/systems/impl/window/object_unique_ptr.hpp>
#include <sge/systems/impl/window/system_unique_ptr.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class instance_impl
{
	FCPPT_NONCOPYABLE(
		instance_impl
	);
public:
	instance_impl(
		sge::systems::plugin_path const &,
		sge::systems::optional_log_context_ref const &
	);

	~instance_impl();

	void
	init_window_system(
		sge::systems::window const &
	);

	void
	init_renderer_system(
		sge::systems::detail::renderer const &,
		sge::parse::ini::optional_start const &
	);

	void
	init_window_object(
		sge::systems::window const &
	);

	void
	init_renderer(
		sge::systems::detail::renderer const &
	);

	void
	init_input(
		sge::systems::input const &
	);

	void
	init_image2d(
		sge::systems::image2d const &
	);

	void
	init_audio_loader(
		sge::systems::audio_loader const &
	);

	void
	init_audio_player(
		sge::systems::audio_player const &
	);

	void
	init_font(
		sge::systems::font const &
	);

	void
	post_init();

	fcppt::log::context &
	log_context();

	fcppt::log::object &
	log();

	sge::plugin::manager &
	plugin_manager();

	sge::renderer::core &
	renderer_core() const;

	sge::renderer::system &
	renderer_system() const;

	sge::renderer::device::ffp &
	renderer_device_ffp() const;

	sge::renderer::device::core &
	renderer_device_core() const;

	sge::input::system &
	input_system() const;

	sge::input::processor &
	input_processor() const;

	sge::image2d::system &
	image_system() const;

	sge::audio::loader &
	audio_loader() const;

	sge::audio::player &
	audio_player() const;

	sge::font::system &
	font_system() const;

	sge::window::system &
	window_system() const;

	sge::window::object &
	window() const;

	sge::viewport::manager &
	viewport_manager() const;
private:
	sge::systems::impl::log_context log_context_;

	fcppt::log::object log_;

	// Almost all plugins need to be unloaded last. If, for example,
	// libGL.so is unloaded before the X window will be destroyed, then the
	// unloading will crash.
	sge::plugin::cache plugin_cache_;

	sge::plugin::manager plugin_manager_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::window::system_unique_ptr
	>
	optional_window_system;

	optional_window_system window_system_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::renderer::system_unique_ptr
	>
	optional_renderer_system;

	optional_renderer_system renderer_system_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::window::object_unique_ptr
	>
	optional_window_object;

	optional_window_object window_object_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::renderer::device_unique_ptr
	>
	optional_renderer_device;

	optional_renderer_device renderer_device_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::input::object_unique_ptr
	>
	optional_input;

	optional_input input_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::audio::loader_unique_ptr
	>
	optional_audio_loader;

	optional_audio_loader audio_loader_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::audio::player_unique_ptr
	>
	optional_audio_player;

	optional_audio_player audio_player_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::image2d::object_unique_ptr
	>
	optional_image2d;

	optional_image2d image2d_;

	typedef
	fcppt::optional::object<
		sge::systems::impl::font::object_unique_ptr
	>
	optional_font;

	optional_font font_;
};

}
}
}

#endif
