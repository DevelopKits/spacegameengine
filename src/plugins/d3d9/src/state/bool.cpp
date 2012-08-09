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


#include <sge/d3d9/state/bool.hpp>
#include <sge/d3d9/state/parameters.hpp>
#include <sge/d3d9/state/set_render_state_bool.hpp>
#include <sge/d3d9/state/convert/bool.hpp>
#include <sge/d3d9/state/deferred/bundle.hpp>
#include <sge/d3d9/state/deferred/object.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/bool/available_states.hpp>
#include <sge/renderer/state/bool/type.hpp>

void
sge::d3d9::state::bool_(
	sge::d3d9::state::parameters const &_parameters,
	sge::renderer::state::bool_::type const &_state
)
{
	switch(
		_state.state()
	)
	{
	case sge::renderer::state::bool_::available_states::write_alpha:
	case sge::renderer::state::bool_::available_states::write_blue:
	case sge::renderer::state::bool_::available_states::write_green:
	case sge::renderer::state::bool_::available_states::write_red:
		_parameters.deferred().add(
			deferred::bundle::color_write
		);
		return;
	case sge::renderer::state::bool_::available_states::enable_alpha_blending:
	case sge::renderer::state::bool_::available_states::enable_lighting:
	case sge::renderer::state::bool_::available_states::enable_point_sprites:
	case sge::renderer::state::bool_::available_states::enable_scissor_test:
	case sge::renderer::state::bool_::available_states::local_viewer:
	case sge::renderer::state::bool_::available_states::normalize_normals:
	case sge::renderer::state::bool_::available_states::write_to_depth_buffer:
		break;
	}

	sge::d3d9::state::set_render_state_bool(
		_parameters.device(),
		sge::d3d9::state::convert::bool_(
			_state.state()
		),
		_state.value()
	);
}
