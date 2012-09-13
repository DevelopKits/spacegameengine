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


#ifndef SGE_RENDERER_STATE_FFP_TRANSFORM_MODE_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_TRANSFORM_MODE_HPP_INCLUDED


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace transform
{

namespace mode
{
enum type
{
	/**
	\brief The world matrix

	The world matrix describes the transformation of the scene.
	*/
	world,
	/**
	\brief The projection matrix

	The projection matrix describes how the transformed scene is mapped
	onto the screen.
	*/
	projection,
	/**
	\brief The texture matrix

	The texture matrix describes how texture coordinates are transformed.
	*/
	texture
};
}

}
}
}
}
}

#endif