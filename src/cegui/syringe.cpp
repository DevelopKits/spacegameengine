#include "declare_local_logger.hpp"
#include "keyboard_code_translation.hpp"
#include "cursor_button_translation.hpp"
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/system.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIInputEvent.h>
#include <fcppt/assert.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>
#include <string>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("syringe"))

sge::cegui::syringe::syringe(
	system &_system)
:
	system_(
		_system),
	charconv_system_(
		system_.charconv_system())
{
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_event const &k)
{
	if (keyboard_code_translation().find(k.key_code()) == keyboard_code_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_ 
				<< FCPPT_TEXT("Warning: got a key which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(k.key_code()) 
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	if (k.pressed())
	{
		CEGUI::System::getSingleton().injectKeyDown(
			keyboard_code_translation()[k.key_code()]);
	}
	else
	{
		CEGUI::System::getSingleton().injectKeyUp(
			keyboard_code_translation()[k.key_code()]);
	}
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_repeat_event const &k)
{
	if (keyboard_code_translation().find(k.key_code()) == keyboard_code_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_ 
				<< FCPPT_TEXT("Warning: got a key which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(k.key_code()) 
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	CEGUI::System::getSingleton().injectKeyDown(
		keyboard_code_translation()[k.key_code()]);
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::char_event const &k)
{
	typedef 
	sge::charconv::string_type<sge::charconv::encoding::utf32>::type 
	utf32_string;

	utf32_string const converted_string(
		sge::charconv::convert
		<
			sge::charconv::encoding::utf32, 
			sge::charconv::encoding::wchar
		>(
			charconv_system_,
			std::basic_string<sge::input::keyboard::char_type>(
				1u,
				k.character())));

	FCPPT_ASSERT(
		converted_string.size() == 1);

	CEGUI::System::getSingleton().injectChar(
		converted_string[0]);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::button_event const &e)
{
	if (cursor_button_translation().find(e.button_code()) == cursor_button_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_ 
				<< FCPPT_TEXT("Warning: got a button which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(e.button_code()) 
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	if (e.pressed())
		CEGUI::System::getSingleton().injectMouseButtonDown(
			cursor_button_translation()[e.button_code()]);
	else
		CEGUI::System::getSingleton().injectMouseButtonUp(
			cursor_button_translation()[e.button_code()]);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::move_event const &e)
{
	inject(
		e.position());
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::position const &cursor_position)
{
	CEGUI::System::getSingleton().injectMousePosition(
		static_cast<unit>(
			cursor_position.x()),
		static_cast<unit>(
			cursor_position.y()));
}