/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_VERTEX_FORMAT_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include "types.hpp"
#include "color.hpp"

namespace sge
{

namespace vertex_usage
{
	enum type {
		pos,
		normal,
		tex,
		diffuse,
		num_elements
	};
}

template<vertex_usage::type> struct vertex_traits;
template<> struct vertex_traits<vertex_usage::pos> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,3> packed_type;
};
template<> struct vertex_traits<vertex_usage::normal> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,3> packed_type;
};
template<> struct vertex_traits<vertex_usage::tex> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,2> packed_type;
};
template<> struct vertex_traits<vertex_usage::diffuse> {
	typedef color        element_type;
	typedef element_type packed_type;
};

typedef std::size_t vertex_size;
typedef std::ptrdiff_t vertex_difference;

const vertex_size vertex_element_size[] = {
	3*sizeof(vertex_traits<vertex_usage::pos>::element_type),
	3*sizeof(vertex_traits<vertex_usage::normal>::element_type),
	2*sizeof(vertex_traits<vertex_usage::tex>::element_type),
	1*sizeof(vertex_traits<vertex_usage::diffuse>::element_type)
};

typedef vertex_size offset_info[vertex_usage::num_elements];

class vertex_element {
public:
	vertex_element(vertex_usage::type usage, vertex_size count);
	vertex_usage::type usage() const;
	vertex_size size() const;
	vertex_size count() const;
	vertex_size stride() const;
private:
	vertex_usage::type _usage;
	vertex_size        _count;
	vertex_size        _size;
};

class vertex_format {
public:
	typedef std::vector<vertex_element> usage_list;

	vertex_format();
	const usage_list& elements() const;
	vertex_size stride() const;
	vertex_format& add(vertex_usage::type u, vertex_size count = 1);
	const offset_info& offsets() const;
	bool uses(vertex_usage::type e) const;
private:
	offset_info oi;
	usage_list  ulist;
	vertex_size _stride;
};

}

#endif
