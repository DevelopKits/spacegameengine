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


#ifndef SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	object();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~object() = 0;

	virtual
	sge::window::object &
	window() const = 0;

	virtual
	sge::input::cursor::optional_position
	position() const = 0;

	virtual
	void
	mode(
		sge::input::cursor::mode
	) = 0;
};

}
}
}

#endif
