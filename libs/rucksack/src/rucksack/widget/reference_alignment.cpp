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


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment.hpp>


sge::rucksack::widget::reference_alignment::reference_alignment(
	sge::rucksack::widget::reference const _reference,
	sge::rucksack::alignment const _alignment
)
:
	reference_{
		_reference
	},
	alignment_{
		_alignment
	}
{
}

sge::rucksack::widget::reference
sge::rucksack::widget::reference_alignment::reference() const
{
	return
		reference_;
}

sge::rucksack::alignment
sge::rucksack::widget::reference_alignment::alignment() const
{
	return
		alignment_;
}
