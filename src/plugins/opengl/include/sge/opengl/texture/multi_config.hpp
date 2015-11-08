/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/texture/multi_config_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class multi_config
{
	FCPPT_NONASSIGNABLE(
		multi_config
	);
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLACTIVETEXTUREPROC
	>
	gl_active_texture;

	typedef
	sge::opengl::fun_ref<
		// FIXME
		PFNGLACTIVETEXTUREPROC
		//PFNGLCLIENTACTIVETEXTUREPROC
	>
	gl_client_active_texture;

	multi_config(
		gl_active_texture,
		gl_client_active_texture,
		sge::renderer::caps::texture_stages
	);

	gl_active_texture
	active_texture() const;

	gl_client_active_texture
	client_active_texture() const;

	sge::renderer::caps::texture_stages
	max_level() const;
private:
	gl_active_texture active_texture_;

	gl_client_active_texture client_active_texture_;

	sge::renderer::caps::texture_stages const max_level_;
};

}
}
}

#endif
