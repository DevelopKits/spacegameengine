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


#ifndef SGE_RENDERER_TEXTURE_SCOPED_VOLUME_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SCOPED_VOLUME_LOCK_HPP_INCLUDED

#include <sge/image3d/view/object.hpp>
#include <sge/renderer/color_buffer/volume.hpp>
#include <sge/renderer/texture/basic_scoped_lock.hpp>
#include <sge/renderer/texture/volume.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

typedef sge::renderer::texture::basic_scoped_lock<
	sge::renderer::texture::volume
> scoped_volume_lock;

}
}
}

#endif
