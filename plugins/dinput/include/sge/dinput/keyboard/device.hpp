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


#ifndef SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/keyboard/device_fwd.hpp>
#include <sge/dinput/keyboard/info.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>



namespace sge
{
namespace dinput
{
namespace keyboard
{

class device
:
	public
		sge::input::keyboard::device,
	public
		sge::dinput::device::object,
	public
		fcppt::enable_shared_from_this<
			sge::dinput::keyboard::device
		>
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit
	device(
		sge::dinput::device::parameters const &
	);

	~device()
	override;
private:
	sge::window::object &
	window() const
	override;

	awl::event::optional_base_unique_ptr
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	)
	override;

	sge::dinput::keyboard::info const info_;
};

}
}
}

#endif
