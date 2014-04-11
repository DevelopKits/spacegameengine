/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RUCKSACK_WIDGET_MINIMUM_SIZE_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_MINIMUM_SIZE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class SGE_CLASS_SYMBOL minimum_size
:
	public sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		minimum_size
	);
public:
	SGE_RUCKSACK_SYMBOL
	explicit
	minimum_size(
		sge::rucksack::widget::base &
	);

	SGE_RUCKSACK_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	);

	SGE_RUCKSACK_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	);

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::dim const
	size() const;

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::vector const
	position() const;

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::axis_policy2 const
	axis_policy() const;

	SGE_RUCKSACK_SYMBOL
	void
	relayout();

	SGE_RUCKSACK_SYMBOL
	~minimum_size();
private:
	sge::rucksack::widget::base &child_;
};

}
}
}

#endif