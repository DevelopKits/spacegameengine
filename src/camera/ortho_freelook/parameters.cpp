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


#include <sge/camera/ortho_freelook/parameters.hpp>

sge::camera::ortho_freelook::parameters::parameters(
	input::mouse::device &_mouse,
	input::keyboard::device &_keyboard)
:
	mouse_(
		_mouse),
	keyboard_(
		_keyboard),
	rect_(),
	near_(
		0.0f),
	far_(
		10.0f),
	zoom_to_zooming_speed_factor_(
		renderer::vector2(
			0.05f,
			0.05f)),
	zoom_to_panning_speed_factor_(
		renderer::vector2(
			0.005f,
			0.005f)),
	active_(
		true)
{
}

sge::input::mouse::device &
sge::camera::ortho_freelook::parameters::mouse() const
{
	return mouse_;
}

sge::input::keyboard::device &
sge::camera::ortho_freelook::parameters::keyboard() const
{
	return keyboard_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::projection_rect(
	sge::renderer::projection::rect const &_rect)
{
	rect_ =
		_rect;
	return *this;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::near(
	renderer::scalar const _near)
{
	near_ =
		renderer::projection::near(
				_near);
	return *this;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::far(
	renderer::scalar const _far)
{
	far_ =
		renderer::projection::far(
			_far);
	return *this;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::zoom_to_zooming_speed_factor(
	renderer::vector2 const &_zoom_to_zooming_speed_factor)
{
	zoom_to_zooming_speed_factor_ =
		_zoom_to_zooming_speed_factor;
	return *this;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::zoom_to_panning_speed_factor(
	renderer::vector2 const &_zoom_to_panning_speed_factor)
{
	zoom_to_panning_speed_factor_ =
		_zoom_to_panning_speed_factor;
	return *this;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::active(
	bool const _active)
{
	active_ =
		_active;
	return *this;
}

sge::camera::ortho_freelook::optional_projection_rect const
sge::camera::ortho_freelook::parameters::projection_rect() const
{
	return
		rect_;
}

sge::renderer::projection::near const
sge::camera::ortho_freelook::parameters::near() const
{
	return near_;
}

sge::renderer::projection::far const
sge::camera::ortho_freelook::parameters::far() const
{
	return far_;
}

sge::renderer::vector2 const &
sge::camera::ortho_freelook::parameters::zoom_to_zooming_speed_factor() const
{
	return
		zoom_to_zooming_speed_factor_;
}

sge::renderer::vector2 const &
sge::camera::ortho_freelook::parameters::zoom_to_panning_speed_factor() const
{
	return
		zoom_to_panning_speed_factor_;
}

bool
sge::camera::ortho_freelook::parameters::active() const
{
	return active_;
}
