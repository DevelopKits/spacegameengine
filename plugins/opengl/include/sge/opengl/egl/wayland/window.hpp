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


#ifndef SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#define SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_EGL_CORE_ON_TOP
#include <sge/opengl/egl/wayland/window_holder.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace wayland
{

class window
{
	FCPPT_NONCOPYABLE(
		window
	);
public:
	explicit
	window(
		sge::window::object &
	);

	~window();

	wl_egl_window *
	get() const;
private:
	sge::opengl::egl::wayland::window_holder const holder_;

	fcppt::signal::auto_connection const resize_connection_;
};

}
}
}
}

#endif
