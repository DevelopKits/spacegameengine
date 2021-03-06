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


#include <sge/input/focus/char_type.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/event/char.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/wininput/focus/key_repeated.hpp>
#include <sge/wininput/focus/object.hpp>
#include <sge/wininput/focus/translate_key_code.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::focus::object::object(
	sge::window::object &_window
)
:
	sge::input::focus::object{},
	fcppt::enable_shared_from_this<
		sge::wininput::focus::object
	>{},
	window_{
		_window
	},
	event_connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::wininput::focus::object::~object()
{
}

sge::window::object &
sge::wininput::focus::object::window() const
{
	return
		window_;
}

awl::event::container
sge::wininput::focus::object::on_event(
	awl::window::event::base const &_event
)
{
	return
		fcppt::optional::to_container<
			awl::event::container
		>(
			fcppt::optional::bind(
				fcppt::cast::dynamic<
					awl::backends::windows::window::event::generic const
				>(
					_event
				),
				[
					this
				](
					fcppt::reference<
						awl::backends::windows::window::event::generic const
					> const _window_event
				)
				{
					return
						this->on_window_event(
							_window_event.get()
						);
				}
			)
		);
}

awl::event::optional_base_unique_ptr
sge::wininput::focus::object::on_window_event(
	awl::backends::windows::window::event::generic const &_event
)
{
	switch(
		_event.type().get()
	)
	{
	case WM_CHAR:
		return
			awl::event::optional_base_unique_ptr{
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::focus::event::char_
					>(
						this->fcppt_shared_from_this(),
						// TODO: Conversion function
						static_cast<
							sge::input::focus::char_type
						>(
							_event.wparam().get()
						)
					)
				)
			};
	case WM_KEYDOWN:
		return
			awl::event::optional_base_unique_ptr{
				this->on_key(
					_event,
					sge::input::key::pressed{
						true
					}
				)
			};
	case WM_KEYUP:
		return
			awl::event::optional_base_unique_ptr{
				this->on_key(
					_event,
					sge::input::key::pressed{
						false
					}
				)
			};
	case WM_SETFOCUS:
		return
			awl::event::optional_base_unique_ptr{
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::focus::event::in
					>(
						this->fcppt_shared_from_this()
					)
				)
			};
	case WM_KILLFOCUS:
		return
			awl::event::optional_base_unique_ptr{
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::focus::event::out
					>(
						this->fcppt_shared_from_this()
					)
				)
			};
	}

	return
		awl::event::optional_base_unique_ptr{};
}

awl::event::base_unique_ptr
sge::wininput::focus::object::on_key(
	awl::backends::windows::window::event::generic const &_event,
	sge::input::key::pressed const _pressed
)
{
	sge::input::focus::key const key(
		sge::wininput::focus::translate_key_code(
			_event.wparam()
		)
	);

	return
		_pressed.get()
		&&
		sge::wininput::focus::key_repeated(
			_event.lparam()
		)
		?
			fcppt::unique_ptr_to_base<
				awl::event::base
			>(
				fcppt::make_unique_ptr<
					sge::input::focus::event::key_repeat
				>(
					this->fcppt_shared_from_this(),
					key
				)
			)
		:
			fcppt::unique_ptr_to_base<
				awl::event::base
			>(
				fcppt::make_unique_ptr<
					sge::input::focus::event::key
				>(
					this->fcppt_shared_from_this(),
					key,
					_pressed
				)
			)
		;
}
