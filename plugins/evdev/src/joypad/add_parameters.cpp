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


#include <sge/evdev/joypad/add_parameters.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <awl/backends/posix/processor_fwd.hpp>


sge::evdev::joypad::add_parameters::add_parameters(
	awl::backends::posix::processor &_processor,
	sge::evdev::joypad::map &_map,
	sge::input::joypad::discover_signal &_discover_signal
)
:
	processor_(
		_processor
	),
	map_(
		_map
	),
	discover_signal_(
		_discover_signal
	)
{
}

awl::backends::posix::processor &
sge::evdev::joypad::add_parameters::processor() const
{
	return
		processor_;
}

sge::evdev::joypad::map &
sge::evdev::joypad::add_parameters::map() const
{
	return
		map_;
}

sge::input::joypad::discover_signal &
sge::evdev::joypad::add_parameters::discover_signal() const
{
	return
		discover_signal_;
}
