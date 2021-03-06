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


#ifndef SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_unique_ptr.hpp>
#include <sge/dinput/device/object_fwd.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	awl::event::container
	dispatch();

	virtual
	~object() = 0;

	void
	acquire();

	void
	unacquire();
protected:
	object(
		sge::dinput::device::parameters const &,
		DIDATAFORMAT const &
	);

	IDirectInputDevice8 &
	get();

	sge::window::object &
	sge_window() const;
private:
	bool
	acquire_impl();

	void
	set_data_format(
		DIDATAFORMAT const &
	);

	void
	set_property(
		REFGUID,
		LPCDIPROPHEADER
	);

	void
	set_event_handle(
		HANDLE
	);

	virtual
	awl::event::optional_base_unique_ptr
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	) = 0;

	sge::window::object &window_;

	sge::dinput::dinput_device_unique_ptr const device_;
};

}
}
}

#endif
