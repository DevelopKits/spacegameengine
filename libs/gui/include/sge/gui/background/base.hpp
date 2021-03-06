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


#ifndef SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED
#define SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED

#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace background
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	explicit
	base(
		sge::gui::main_area::base &
	);
public:
	virtual
	~base() = 0;

	void
	draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	);

	sge::gui::widget::base &
	widget();
private:
	virtual
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) = 0;

	sge::gui::main_area::base &main_area_;
};

}
}
}

#endif
