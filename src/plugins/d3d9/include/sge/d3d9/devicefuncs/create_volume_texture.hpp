/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_VOLUME_TEXTURE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_volume_texture_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

sge::d3d9::texture::d3d_volume_texture_unique_ptr
create_volume_texture(
	IDirect3DDevice9 &,
	sge::renderer::texture::volume_parameters const &,
	D3DFORMAT,
	D3DPOOL,
	sge::d3d9::usage
);

}
}
}

#endif