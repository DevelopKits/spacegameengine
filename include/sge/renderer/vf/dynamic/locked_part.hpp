/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED

#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class locked_part
{
public:
	SGE_SYMBOL
	locked_part(
		renderer::raw_pointer,
		renderer::size_type pos,
		renderer::size_type count,
		bool read,
		bool write
	);

	SGE_SYMBOL
	renderer::raw_pointer
	data() const;

	SGE_SYMBOL
	renderer::size_type
	pos() const;

	SGE_SYMBOL
	renderer::size_type
	count() const;

	SGE_SYMBOL
	bool
	read() const;

	SGE_SYMBOL
	bool
	write() const;
private:
	renderer::raw_pointer data_;

	renderer::size_type
		pos_,
		count_;
	
	bool
		read_,
		write_;
};

}
}
}
}

#endif