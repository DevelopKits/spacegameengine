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


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include "buffer_base.hpp"
#include "vbo.hpp"
#include <sge/renderer/index_buffer.hpp>

namespace sge
{
namespace ogl
{
namespace detail
{
typedef buffer_base<
	renderer::index_buffer,
	index_buffer_type,
	vb_ib_vbo_impl
> index_buffer_base;
}

class index_buffer
: public detail::index_buffer_base {
public:
	index_buffer(
		const_view_type const &,
		resource_flag_type flags);
private:
	view_type const view();
	const_view_type const view() const;
};

}
}

#endif

