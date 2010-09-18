/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/null.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("widgets_base")
	)
);

}

sge::gui::widgets::base::base(
	parent_data const &parent_data_,
	parameters const &params)
:
	parent_(
		parent_data_.parent_widget()),
	manager_(
		parent_data_.parent_manager()),
	pos_(
		point::null()),
	pos_hint_(
		params.pos()),
	size_(
		dim::null()),
	size_hint_(
		params.size()),
	z_(
		params.z()),
	size_policy_(
		params.size_policy()),
	keyboard_focus_(
		params.keyboard_focus()),
	layout_(
		params.layout()
		? params.layout()
		: layouts::base_ptr(
			fcppt::make_shared_ptr<
				layouts::null
			>()
		)
	),
	activation_(params.activation())
{
	if (size_hint())
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("widget has a size hint of ")
				<< *size_hint()
				<< FCPPT_TEXT(", has type: ")
				<< typeid(*this).name());
	}
	layout_->connected_widget(*this);
	if (has_parent())
		parent_widget().add_child(*this);
	parent_manager().add(*this);
}

sge::gui::point const sge::gui::widgets::base::screen_pos() const
{
	if (!has_parent())
		return pos_;
	return pos_ + parent_widget().screen_pos();
}

sge::gui::point const sge::gui::widgets::base::absolute_pos() const
{
	if (!has_parent())
		return point::null();
	if (!parent_widget().has_parent())
		return pos_;
	return pos_ + parent_widget().absolute_pos();
}

sge::gui::point const sge::gui::widgets::base::relative_pos() const
{
	if (!has_parent())
		return point::null();
	return pos_;
}

void sge::gui::widgets::base::pos_hint(
	point const &_pos_hint)
{
	pos_hint_ = _pos_hint;
	invalidate(
		*this,
		invalidation::position);
}

sge::gui::widgets::optional_point const
sge::gui::widgets::base::pos_hint() const
{
	return pos_hint_;
}

sge::gui::dim const sge::gui::widgets::base::size() const
{
	return size_;
}

void sge::gui::widgets::base::size_hint(
	dim const &_size_hint)
{
	size_hint_ = _size_hint;
	invalidate(
		*this,
		invalidation::size);
}

sge::gui::widgets::optional_dim const
sge::gui::widgets::base::size_hint() const
{
	return size_hint_;
}

void sge::gui::widgets::base::z(depth_type const _z)
{
	z_ = _z;
	parent_manager().z(
		*this,
		z_);
}

sge::gui::depth_type sge::gui::widgets::base::z() const
{
	return z_;
}

sge::gui::image &sge::gui::widgets::base::buffer() const
{
	return buffer_;
}

sge::gui::manager &sge::gui::widgets::base::parent_manager()
{
	return manager_;
}

sge::gui::manager const &sge::gui::widgets::base::parent_manager() const
{
	return manager_;
}

sge::gui::widgets::base &sge::gui::widgets::base::parent_widget()
{
	return *parent_;
}

sge::gui::widgets::base const &sge::gui::widgets::base::parent_widget() const
{
	return *parent_;
}

bool sge::gui::widgets::base::has_parent() const
{
	return parent_ != 0;
}

sge::gui::widgets::base &sge::gui::widgets::base::oldest_parent()
{
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
}

sge::gui::widgets::base const &sge::gui::widgets::base::oldest_parent() const
{
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
}

sge::gui::size_policy const &sge::gui::widgets::base::size_policy() const
{
	return size_policy_;
}

void sge::gui::widgets::base::size_policy(sge::gui::size_policy const &s)
{
	size_policy_ = s;
}

sge::gui::keyboard_focus::type sge::gui::widgets::base::keyboard_focus() const
{
	return keyboard_focus_;
}

void sge::gui::widgets::base::keyboard_focus(keyboard_focus::type const n)
{
	parent_manager().keyboard_focus(
		*this,
		keyboard_focus_ = n);
}

sge::gui::widgets::base::child_container &sge::gui::widgets::base::children()
{
	return children_;
}

sge::gui::widgets::base::child_container const &sge::gui::widgets::base::children() const
{
	return children_;
}

void sge::gui::widgets::base::add_child(widgets::base &w)
{
	children_.push_back(&w);
}

void sge::gui::widgets::base::remove_child(widgets::base &w)
{
	fcppt::algorithm::ptr_container_erase(
		children_,
		&w
	);
}

void sge::gui::widgets::base::activation(
	activation_state::type _activation)
{
	if (_activation == activation())
		return;
	activation_ = _activation;
	parent_manager().activation(*this,activation_);
}

sge::gui::activation_state::type sge::gui::widgets::base::activation() const
{
	return activation_;
}

void sge::gui::widgets::base::layout(
	layouts::base_ptr n)
{
	layout_ = n;
	layout_->connected_widget(*this);
	invalidate(
		*this,
		invalidation::all);
}

sge::gui::layouts::base &sge::gui::widgets::base::layout()
{
	return *layout_;
}

sge::gui::layouts::base const &sge::gui::widgets::base::layout() const
{
	return *layout_;
}

bool sge::gui::widgets::base::has_child(widgets::base const &w) const
{
	BOOST_FOREACH(widgets::base const &child,children())
	{
		if (&w == &child)
			return true;

		if (child.has_child(w))
			return true;
	}

	return false;
}

sge::gui::rect const sge::gui::widgets::base::absolute_area() const
{
	return rect(
		absolute_pos(),
		size());
}

sge::gui::rect const sge::gui::widgets::base::screen_area() const
{
	return rect(
		screen_pos(),
		size());
}

void sge::gui::widgets::base::compile(
	invalidation::type const &i)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("in compile"));
	layout().compile(
		i);
}

void sge::gui::widgets::base::compile_static()
{
	layout().compile_static();
}

sge::gui::dim const sge::gui::widgets::base::optimal_size() const
{
	if (size_hint())
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("Widget has a size hint, so returning: ")
				<< *size_hint());
		return *size_hint();
	}
	return layout().optimal_size();
}

void sge::gui::widgets::base::invalidate(
	widgets::base &w,
	invalidation::type const &i)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("in invalidate"));
	layout().invalidate(
		w,
		i);
}

void sge::gui::widgets::base::process_invalid_area(
	events::invalid_area const &e)
{
	// draw itself, then draw children
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("redrawing myself, region ")
		        << e.area());
	parent_manager().skin().draw(*this,e);

	BOOST_FOREACH(widgets::base &w,children())
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("checking if ")
				<< w.absolute_area()
				<< FCPPT_TEXT(" intersects with ")
				<< e.area()
				<< FCPPT_TEXT(": ")
				<< intersects(w.absolute_area(),e.area()));

		if (intersects(w.absolute_area(),e.area()))
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_
					<< FCPPT_TEXT("sending widgets::base ")
					<< fcppt::type_name(typeid(w))
					<< FCPPT_TEXT(" an invalid area event"));
			w.process_invalid_area(e);
		}
	}
}

void sge::gui::widgets::base::process_mouse_enter(events::mouse_enter const &) {}
void sge::gui::widgets::base::process_mouse_leave(events::mouse_leave const &) {}
void sge::gui::widgets::base::process_mouse_move(events::mouse_move const &) {}
void sge::gui::widgets::base::process_mouse_click(events::mouse_click const &) {}

sge::gui::key_handling::type sge::gui::widgets::base::process_key(
	events::key const &)
{
	return key_handling::process;
}

void sge::gui::widgets::base::process_keyboard_enter(
	events::keyboard_enter const &)
{
	FCPPT_LOG_DEBUG(mylogger,fcppt::log::_ << FCPPT_TEXT("got keyboard_enter"));
}

void sge::gui::widgets::base::process_keyboard_leave(
	events::keyboard_leave const &)
{
	FCPPT_LOG_DEBUG(mylogger,fcppt::log::_ << FCPPT_TEXT("got keyboard_leave"));
}

sge::gui::widgets::base::~base()
{
	if (has_parent())
		parent_widget().remove_child(
			*this);
	parent_manager().remove(
		*this);
}

void sge::gui::widgets::base::size(
	dim const &_size)
{
	size_ = _size;
	parent_manager().resize(
		*this,
		size_);
}

void sge::gui::widgets::base::pos(
	point const &p)
{
	pos_ = p;
	parent_manager().reposition(
		*this,
		p);
}
