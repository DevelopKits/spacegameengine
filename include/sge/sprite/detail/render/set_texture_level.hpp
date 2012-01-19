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


#ifndef SGE_SPRITE_DETAIL_RENDER_SET_TEXTURE_LEVEL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SET_TEXTURE_LEVEL_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices
>
class set_texture_level
{
	FCPPT_NONASSIGNABLE(
		set_texture_level
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	set_texture_level(
		object const &_object,
		sge::renderer::device &_renderer
	)
	:
		object_(
			_object
		),
		renderer_(
			_renderer
		)
	{
	}

	template<
		typename Level
	>
	void
	operator()(
		Level const &
	) const
	{
		sge::texture::const_part_ptr const vtex(
			object_. template texture_level<
				Level::value
			>()
		);

		renderer_.texture(
			vtex
			?
				sge::renderer::texture::const_optional_base(
					*vtex->texture()
				)
			:
				sge::renderer::texture::const_optional_base()
			,
			sge::renderer::texture::stage(
				Level::value
			)
		);
	}
private:
	object const &object_;

	sge::renderer::device &renderer_;
};

}
}
}
}

#endif