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


#ifndef SGE_X11INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_X11INPUT_PROCESSOR_HPP_INCLUDED

#include "device_fwd.hpp"
#include <X11/Xlib.h>
#include <sge/x11/window_ptr.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/callback.hpp>
#include <sge/input/repeat_callback.hpp>
#include <sge/input/key_pair_function.hpp>
#include <sge/input/key_type_function.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_type_fwd.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace x11input
{

class processor
:
	public input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	)
public:
	explicit processor(
		x11::window_ptr wnd
	);

	~processor();
private:
	fcppt::signal::auto_connection
	register_callback(
		input::callback const &c
	);

	fcppt::signal::auto_connection
	register_repeat_callback(
		input::repeat_callback const &c
	);

	fcppt::signal::auto_connection
	keyboard_discover_callback(
		input::keyboard::discover_callback const &
	);

	fcppt::signal::auto_connection
	keyboard_remove_callback(
		input::keyboard::remove_callback const &
	);

	input::keyboard::device_vector const
	keyboards() const;

	fcppt::signal::auto_connection
	mouse_discover_callback(
		input::mouse::discover_callback const &
	);

	fcppt::signal::auto_connection
	mouse_remove_callback(
		input::mouse::remove_callback const &
	);

	input::mouse::device_vector const
	mice() const;

	void
	dispatch();

	window::instance_ptr const
	window() const;

	void
	emit_callback(
		input::key_pair const &
	);

	void
	emit_repeat_callback(
		input::key_type const &
	);

	void
	on_key_event(
		XEvent const &
	);

	void
	on_acquire(
		XEvent const &
	);

	void
	on_release(
		XEvent const &
	);

	x11::window_ptr const wnd;

	bool acquired;

	typedef boost::ptr_vector<
		device
	> device_vector;

	device_vector devices;

	fcppt::signal::connection_manager connections;

	typedef fcppt::signal::object<
		input::key_pair_function
	> signal_type;

	typedef fcppt::signal::object<
		input::key_type_function
	> repeat_signal_type;

	signal_type        sig;

	repeat_signal_type repeat_sig;
};

}
}

#endif

