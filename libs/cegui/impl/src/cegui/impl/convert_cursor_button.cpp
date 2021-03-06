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


#include <sge/cegui/impl/convert_cursor_button.hpp>
#include <sge/cegui/impl/optional_mouse_button.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::optional_mouse_button
sge::cegui::impl::convert_cursor_button(
	sge::input::cursor::button_code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::cursor::button_code::left:
		return
			sge::cegui::impl::optional_mouse_button{
				CEGUI::LeftButton
			};
	case sge::input::cursor::button_code::right:
		return
			sge::cegui::impl::optional_mouse_button{
				CEGUI::RightButton
			};
	case sge::input::cursor::button_code::middle:
		return
			sge::cegui::impl::optional_mouse_button{
				CEGUI::MiddleButton
			};
	case sge::input::cursor::button_code::unknown:
		return
			sge::cegui::impl::optional_mouse_button{
				CEGUI::NoButton
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
