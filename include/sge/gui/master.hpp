/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_GUI_MASTER_HPP_INCLUDED
#define SGE_GUI_MASTER_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/master_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace gui
{

class master
{
	FCPPT_NONCOPYABLE(
		master
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	master(
		sge::input::focus::object &,
		sge::input::cursor::object &,
		sge::gui::context &,
		sge::gui::main_area::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~master();

	SGE_GUI_DETAIL_SYMBOL
	void
	draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::gui::background::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	draw_with_states(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::gui::background::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	update(
		sge::gui::duration
	);
private:
	void
	key_event(
		sge::input::focus::key_event const &
	);

	void
	key_repeat_event(
		sge::input::focus::key_repeat_event const &
	);

	void
	char_event(
		sge::input::focus::char_event const &
	);

	void
	button_event(
		sge::input::cursor::button_event const &
	);

	void
	handle_key(
		sge::input::key::code
	);

	sge::gui::widget::optional_ref const
	try_focus(
		sge::gui::widget::optional_focus
	);

	sge::gui::widget::base &
	widget();

	sge::input::cursor::object &cursor_;

	sge::gui::context &context_;

	sge::gui::main_area::base &main_area_;

	fcppt::signal::auto_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		button_connection_;
};

}
}

#endif
