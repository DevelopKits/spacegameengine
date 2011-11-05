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


#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_CREATE_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_CREATE_HPP_INCLUDED

#include <sge/d3d9/surface/depth_stencil_create_fwd.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil_create
{
	FCPPT_NONCOPYABLE(
		depth_stencil_create
	);
protected:
	depth_stencil_create();
public:
	virtual ~depth_stencil_create();

	virtual surface::d3d_unique_ptr
	create() const = 0;
};

}
}
}

#endif