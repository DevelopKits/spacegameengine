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


#include <sge/input/keyboard/key_code.hpp>
#include <sge/src/cegui/keyboard_code_map.hpp>
#include <sge/src/cegui/keyboard_code_translation.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


// TODO: Turn this into a switch
namespace
{

sge::cegui::keyboard_code_map const codes(
	fcppt::assign::make_container<
		sge::cegui::keyboard_code_map::map_type
	>(
		std::make_pair(
			sge::input::keyboard::key_code::escape,
			CEGUI::Key::Escape
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::return_,
			CEGUI::Key::Return
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::lshift,
			CEGUI::Key::LeftShift
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::rshift,
			CEGUI::Key::RightShift
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::tab,
			CEGUI::Key::Tab
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::backspace,
			CEGUI::Key::Backspace
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::lctrl,
			CEGUI::Key::LeftControl
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::rctrl,
			CEGUI::Key::RightControl
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::alt,
			CEGUI::Key::LeftAlt
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::altgr,
			CEGUI::Key::RightAlt
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::space,
			CEGUI::Key::Space
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::insert,
			CEGUI::Key::Insert
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::home,
			CEGUI::Key::Home
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::pageup,
			CEGUI::Key::PageUp
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::delete_,
			CEGUI::Key::Delete
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::end,
			CEGUI::Key::End
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::pagedown,
			CEGUI::Key::PageDown
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::left,
			CEGUI::Key::ArrowLeft
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::right,
			CEGUI::Key::ArrowRight
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::up,
			CEGUI::Key::ArrowUp
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::down,
			CEGUI::Key::ArrowDown
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::a,
			CEGUI::Key::A
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::b,
			CEGUI::Key::B
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::c,
			CEGUI::Key::C
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::d,
			CEGUI::Key::D
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::e,
			CEGUI::Key::E
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f,
			CEGUI::Key::F
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::g,
			CEGUI::Key::G
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::h,
			CEGUI::Key::H
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::i,
			CEGUI::Key::I
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::j,
			CEGUI::Key::J
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::k,
			CEGUI::Key::K
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::l,
			CEGUI::Key::L
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::m,
			CEGUI::Key::M
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::n,
			CEGUI::Key::N
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::o,
			CEGUI::Key::O
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::p,
			CEGUI::Key::P
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::q,
			CEGUI::Key::Q
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::r,
			CEGUI::Key::R
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::s,
			CEGUI::Key::S
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::t,
			CEGUI::Key::T
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::u,
			CEGUI::Key::U
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::v,
			CEGUI::Key::V
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::w,
			CEGUI::Key::W
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::x,
			CEGUI::Key::X
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::y,
			CEGUI::Key::Y
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::z,
			CEGUI::Key::Z
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_0,
			CEGUI::Key::Zero
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_1,
			CEGUI::Key::One
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_2,
			CEGUI::Key::Two
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_3,
			CEGUI::Key::Three
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_4,
			CEGUI::Key::Four
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_5,
			CEGUI::Key::Five
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_6,
			CEGUI::Key::Six
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_7,
			CEGUI::Key::Seven
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_8,
			CEGUI::Key::Eight
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::_9,
			CEGUI::Key::Nine
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f1,
			CEGUI::Key::F1
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f2,
			CEGUI::Key::F2
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f3,
			CEGUI::Key::F3
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f4,
			CEGUI::Key::F4
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f5,
			CEGUI::Key::F5
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f6,
			CEGUI::Key::F6
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f7,
			CEGUI::Key::F7
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f8,
			CEGUI::Key::F8
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f9,
			CEGUI::Key::F9
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f10,
			CEGUI::Key::F10
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f11,
			CEGUI::Key::F11
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f12,
			CEGUI::Key::F12
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f13,
			CEGUI::Key::F13
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f14,
			CEGUI::Key::F14
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::f15,
			CEGUI::Key::F15
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::comma,
			CEGUI::Key::Comma
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::colon,
			CEGUI::Key::Colon
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::apostrophe,
			CEGUI::Key::Apostrophe
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::backslash,
			CEGUI::Key::Backslash
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::grave,
			CEGUI::Key::Grave
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::substract,
			CEGUI::Key::Subtract
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::lbracket,
			CEGUI::Key::LeftBracket
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::rbracket,
			CEGUI::Key::RightBracket
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::semicolon,
			CEGUI::Key::Semicolon
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::slash,
			CEGUI::Key::Slash
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::underline,
			CEGUI::Key::Underline
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::print,
			CEGUI::Key::SysRq
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::scroll,
			CEGUI::Key::ScrollLock
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::pause,
			CEGUI::Key::Pause
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::lwin,
			CEGUI::Key::LeftWindows
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::rwin,
			CEGUI::Key::RightWindows
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num0,
			CEGUI::Key::Numpad0
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num1,
			CEGUI::Key::Numpad1
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num2,
			CEGUI::Key::Numpad2
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num3,
			CEGUI::Key::Numpad3
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num4,
			CEGUI::Key::Numpad4
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num5,
			CEGUI::Key::Numpad5
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num6,
			CEGUI::Key::Numpad6
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num7,
			CEGUI::Key::Numpad7
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num8,
			CEGUI::Key::Numpad8
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::num9,
			CEGUI::Key::Numpad9
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::numcomma,
			CEGUI::Key::NumpadComma
		)
	)(
		//std::make_pair(
		//	sge::input::keyboard::key_code::numenter,
		//	CEGUI::Key::Numpadenter
		std::make_pair(
			sge::input::keyboard::key_code::numlock,
			CEGUI::Key::NumLock
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::add,
			CEGUI::Key::Add
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::minus,
			CEGUI::Key::Minus
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::multiply,
			CEGUI::Key::Multiply
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::divide,
			CEGUI::Key::Divide
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::equals,
			CEGUI::Key::Equals
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::kana,
			CEGUI::Key::Kana
		)
	)(
		std::make_pair(
			sge::input::keyboard::key_code::kanji,
			CEGUI::Key::Kanji
		)
	)(
		//std::make_pair(
		//	sge::input::keyboard::key_code::next,
		//	CEGUI::Key::Next
		std::make_pair(
			sge::input::keyboard::key_code::numequals,
			CEGUI::Key::NumpadEquals
		)
	)(
		//std::make_pair(
		//	sge::input::keyboard::key_code::period,
		//	CEGUI::Key::period
		std::make_pair(
			sge::input::keyboard::key_code::yen,
			CEGUI::Key::Yen
		)
	)
);

}

sge::cegui::keyboard_code_map const &
sge::cegui::keyboard_code_translation()
{
	return codes;
}
