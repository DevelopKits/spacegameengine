/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace
{

XIDeviceInfo const *
search_info(
	sge::x11input::device::id,
	sge::x11input::device::info::multi const &
);

}

sge::x11input::device::info::single::single(
	awl::backends::x11::display &_display,
	x11input::device::id const _id
)
:
	info_base_(
		_display
	),
	info_(
		::search_info(
			_id,
			info_base_
		)
	)
{
}

sge::x11input::device::info::single::~single()
{
}

XIDeviceInfo const *
sge::x11input::device::info::single::get() const
{
	return
		info_;
}

namespace
{

XIDeviceInfo const *
search_info(
	sge::x11input::device::id const _id,
	sge::x11input::device::info::multi const &_multi
)
{
	for(
		sge::x11input::device::info::multi::size_type index(
			0u
		);
		index < _multi.size();
		++index
	)
	{
		XIDeviceInfo const &info(
			_multi[
				index
			]
		);

		if(
			info.deviceid
			==
			_id.get()
		)
			return
				&info;
	}

	return
		fcppt::null_ptr();
}

}
