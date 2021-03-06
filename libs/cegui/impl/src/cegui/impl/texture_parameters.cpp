/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>


sge::cegui::impl::texture_parameters::texture_parameters(
	sge::cegui::impl::prefix const &_prefix,
	sge::image2d::system &_image_system,
	sge::renderer::device::ffp &_renderer,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	prefix_(
		_prefix
	),
	image_system_(
		_image_system
	),
	renderer_(
		_renderer
	),
	emulate_srgb_(
		_emulate_srgb
	)
{
}

sge::cegui::impl::prefix const &
sge::cegui::impl::texture_parameters::prefix() const
{
	return
		prefix_;
}

sge::image2d::system &
sge::cegui::impl::texture_parameters::image_system() const
{
	return
		image_system_;
}

sge::renderer::device::ffp &
sge::cegui::impl::texture_parameters::renderer() const
{
	return
		renderer_;
}

sge::renderer::texture::emulate_srgb
sge::cegui::impl::texture_parameters::emulate_srgb() const
{
	return
		emulate_srgb_;
}
