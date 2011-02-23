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


#ifndef SGE_D3D9_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_D3D9_VERTEX_FORMAT_HPP_INCLUDED

#include "d3d_device_ptr.hpp"
#include "d3d_vertex_declaration_ptr.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{

class vertex_format
{
	FCPPT_NONCOPYABLE(
		vertex_format
	);
public:
	vertex_format(
		d3d9::d3d_device_ptr,
		sge::renderer::vf::dynamic::format const &
	);

	~vertex_format();

	d3d9::d3d_vertex_declaration_ptr const
	vertex_declaration() const;

	sge::renderer::vf::dynamic::format const &
	format() const;

	DWORD
	fvf() const;

	renderer::size_type
	stride() const;
private:
	sge::renderer::vf::dynamic::format const format_;

	d3d9::d3d_vertex_declaration_ptr const vertex_declaration_;

	DWORD const fvf_;
};

}
}

#endif
