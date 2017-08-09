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


#ifndef SGE_X11INPUT_EVENT_STATIC_TYPE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_STATIC_TYPE_HPP_INCLUDED

#include <sge/x11input/event/is_device.hpp>
#include <sge/x11input/event/is_hierarchy.hpp>
#include <sge/x11input/event/is_raw.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/mpl/if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Value
>
struct static_type
:
boost::mpl::if_<
	sge::x11input::event::is_raw<
		Value
	>,
	XIRawEvent,
	typename
	boost::mpl::if_<
		sge::x11input::event::is_device<
			Value
		>,
		XIDeviceEvent,
		typename
		boost::mpl::if_<
			sge::x11input::event::is_hierarchy<
				Value
			>,
			XIHierarchyEvent,
			fcppt::unit
		>::type
	>::type
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
