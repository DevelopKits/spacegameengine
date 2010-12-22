/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_MOUSE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_HPP_INCLUDED

#include "mouse_fwd.hpp"
#include "device/object.hpp"
#include "device/event_fwd.hpp"
#include "device/parameters_fwd.hpp"
#include "mouse_coordinate.hpp"
#include "mouse_grab_fwd.hpp"
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_function.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_function.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace x11input
{

class mouse
:
	public sge::input::mouse::device,
	public x11input::device::object
{
	FCPPT_NONCOPYABLE(
		mouse
	)
public:
	explicit mouse(
		x11input::device::parameters const &
	);

	~mouse();

	void
	grab();

	void
	ungrab();
private:
	fcppt::signal::auto_connection
	button_callback(
		input::mouse::button_callback const &
	);

	fcppt::signal::auto_connection
	axis_callback(
		input::mouse::axis_callback const &
	);

	void
	on_motion(
		x11input::device::event const &
	);

	void
	on_button_down(
		x11input::device::event const &
	);

	void
	on_button_up(
		x11input::device::event const &
	);

	void
	button_event(
		x11input::device::event const &,
		bool pressed
	);

	void
	private_mouse_motion(
		mouse_coordinate deltax,
		mouse_coordinate deltay
	);

	awl::backends::x11::window::instance_ptr const window_;

	fcppt::signal::connection_manager const connections_;

	fcppt::scoped_ptr<
		mouse_grab
	> grab_;

	fcppt::signal::object<
		sge::input::mouse::button_function
	> button_signal_;

	fcppt::signal::object<
		sge::input::mouse::axis_function
	> axis_signal_;
};

}
}

#endif
