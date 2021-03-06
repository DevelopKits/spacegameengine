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


#ifndef SGE_GUI_WIDGET_CONTAINER_HPP_INCLUDED
#define SGE_GUI_WIDGET_CONTAINER_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/container_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/gui/widget/reference_fwd.hpp>
#include <sge/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class container
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		container
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	container(
		sge::gui::context &,
		sge::gui::widget::reference_vector const &,
		sge::rucksack::widget::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~container()
	override;

	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
protected:
	void
	push_front_widget(
		sge::gui::widget::reference
	);

	void
	pop_front_widget();

	void
	push_back_widget(
		sge::gui::widget::reference
	);

	void
	pop_back_widget();

	void
	replace_widgets(
		sge::gui::widget::reference_vector::size_type,
		sge::gui::widget::reference
	);

	void
	clear_widgets();
private:
	void
	insert_widget(
		sge::gui::widget::reference_vector::iterator,
		sge::gui::widget::reference
	);

	sge::gui::widget::reference_vector::iterator
	erase_widget(
		sge::gui::widget::reference_vector::iterator
	);

	void
	on_update(
		sge::gui::duration
	)
	override;

	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sge::gui::get_focus
	on_click(
		sge::rucksack::vector
	)
	override;

	sge::gui::widget::optional_ref
	on_tab(
		sge::gui::widget::optional_focus &
	)
	override;

	void
	unregister(
		sge::gui::widget::base const &
	)
	override;

	enum class foreach_result
	{
		abort,
		continue_
	};

	template<
		typename Function
	>
	void
	foreach_widget(
		Function const &
	);

	sge::gui::context &context_;

	sge::gui::widget::reference_vector widgets_;

	sge::rucksack::widget::base &layout_;
};

}
}
}

#endif
