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


#ifndef SGE_FONT_TEXT_SIZE_HPP_INCLUDED
#define SGE_FONT_TEXT_SIZE_HPP_INCLUDED

#include <sge/font/text/flags_field.hpp>
#include <sge/font/text/part_fwd.hpp>
#include <sge/font/text/string.hpp>
#include <sge/font/text/symbol.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/dim.hpp>

namespace sge
{
namespace font
{
namespace text
{

SGE_FONT_TEXT_SYMBOL
font::text::part const
size(
	metrics_ptr,
	text::string::const_iterator beg,
	text::string::const_iterator end,
	dim const &max_size,
	flags_field const &
);

SGE_FONT_TEXT_SYMBOL
font::text::part const
size(
	metrics_ptr,
	text::string const &,
	dim const &max_size,
	flags_field const &
);

}
}
}

#endif