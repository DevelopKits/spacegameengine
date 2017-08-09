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


#ifndef SGE_INPUT_FOCUS_EVENT_KEY_REPEAT_HPP_INCLUDED
#define SGE_INPUT_FOCUS_EVENT_KEY_REPEAT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace focus
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL key_repeat
:
	public sge::input::focus::event::base
{
	FCPPT_NONCOPYABLE(
		key_repeat
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	key_repeat(
		sge::input::focus::shared_ptr,
		sge::input::focus::key const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~key_repeat()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::focus::key const &
	key() const;
private:
	sge::input::focus::key const key_;
};

}
}
}
}

#endif
