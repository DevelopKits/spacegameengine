/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_CURSOR_CONFINE_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_CONFINE_HPP_INCLUDED

#include "confine_fwd.hpp"
#include "../device/id.hpp"
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/noncopyable.hpp>
//#include <X11/extensions/XInput2.h>

namespace sge
{
namespace x11input
{
namespace cursor
{

class confine
{
	FCPPT_NONCOPYABLE(
		confine
	)
public:
	confine(
		awl::backends::x11::window::instance_ptr,
		device::id const &
	);

	~confine();
private:
	awl::backends::x11::window::instance_ptr const window_;
#if 0
	device::id const id_;

	int num_modifiers_;

	XIGrabModifiers modifiers_;
#endif
};

}
}
}

#endif