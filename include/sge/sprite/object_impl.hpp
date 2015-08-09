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


#ifndef SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/sprite/color.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/is_normal_size.hpp>
#include <sge/sprite/detail/assign_post.hpp>
#include <sge/sprite/detail/assign_pre.hpp>
#include <sge/sprite/detail/destroy.hpp>
#include <sge/sprite/detail/get_center.hpp>
#include <sge/sprite/detail/get_pos.hpp>
#include <sge/sprite/detail/get_size.hpp>
#include <sge/sprite/detail/set_center.hpp>
#include <sge/sprite/detail/set_pos.hpp>
#include <sge/sprite/detail/set_size.hpp>
#include <sge/sprite/detail/unlink.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/roles/texture_point_pos.hpp>
#include <sge/sprite/roles/texture_point_size.hpp>
#include <sge/sprite/types/center.hpp>
#include <sge/sprite/types/pos.hpp>
#include <sge/sprite/types/basic/dim_impl.hpp>
#include <sge/sprite/types/basic/homogenous_pair_impl.hpp>
#include <sge/sprite/types/basic/vector_impl.hpp>
#include <majutsu/get.hpp>
#include <majutsu/role_return_type.hpp>
#include <majutsu/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Choices
>
template<
	typename... Args
>
sge::sprite::object<
	Choices
>::object(
	Args &&..._args
)
:
	elements_{
		std::forward<
			Args
		>(
			_args
		)...
	}
{
	sge::sprite::detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
>::object(
	object const &_other
)
:
	elements_(
		_other.elements_
	)
{
	sge::sprite::detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
>::object(
	object &_other
)
:
	elements_(
		_other.elements_
	)
{
	sge::sprite::detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
>::object(
	object &&_other
)
:
	elements_(
		std::move(
			_other.elements_
		)
	)
{
	sge::sprite::detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
>::object(
	object const &&_other
)
:
	elements_(
		_other.elements_
	)
{
	sge::sprite::detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
> &
sge::sprite::object<
	Choices
>::operator=(
	object const &_other
)
{
	sge::sprite::detail::assign_pre(
		*this,
		_other
	);

	elements_ =
		_other.elements_;

	sge::sprite::detail::assign_post(
		*this
	);

	return
		*this;
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
> &
sge::sprite::object<
	Choices
>::operator=(
	object &&_other
)
{
	sge::sprite::detail::assign_pre(
		*this,
		_other
	);

	elements_ =
		std::move(
			_other.elements_
		);

	sge::sprite::detail::assign_post(
		*this
	);

	return
		*this;
}

template<
	typename Choices
>
sge::sprite::object<
	Choices
>::~object()
{
	sge::sprite::detail::destroy(
		*this
	);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::unit
sge::sprite::object<
	Choices
>::x() const
{
	return
		this->pos().x();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::unit
sge::sprite::object<
	Choices
>::y() const
{
	return
		this->pos().y();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::vector const
sge::sprite::object<
	Choices
>::pos() const
{
	return
		sge::sprite::detail::get_pos<
			Choices
		>(
			elements_
		);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::vector const
sge::sprite::object<
	Choices
>::center() const
{
	return
		sge::sprite::detail::get_center<
			Choices
		>(
			elements_
		);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::unit
sge::sprite::object<
	Choices
>::w() const
{
	return
		this->size().w();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::unit
sge::sprite::object<
	Choices
>::h() const
{
	return
		this->size().h();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::dim const
sge::sprite::object<
	Choices
>::size() const
{
	static_assert(
		sge::sprite::config::is_normal_size<
			typename
			Choices::size_choice
		>::value,
		"This can only be used with config::normal_size"
	);

	return
		sge::sprite::detail::get_size<
			Choices
		>(
			elements_
		);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::point_size_type
sge::sprite::object<
	Choices
>::point_size() const
{
	return
		this->get<
			sge::sprite::roles::point_size
		>(
			elements_
		);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::texture_point_pos_type
sge::sprite::object<
	Choices
>::texture_point_pos() const
{
	return
		this->texture_point_pos_level<
			0
		>();
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
typename sge::sprite::object<
	Choices
>::texture_point_pos_type
sge::sprite::object<
	Choices
>::texture_point_pos_level() const
{
	return
		this->get<
			sge::sprite::roles::texture_point_pos<
				Level
			>
		>(
			elements_
		);
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::texture_point_size_type
sge::sprite::object<
	Choices
>::texture_point_size() const
{
	return
		this->texture_point_size_level<
			0
		>();
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
typename sge::sprite::object<
	Choices
>::texture_point_size_type
sge::sprite::object<
	Choices
>::texture_point_size_level() const
{
	return
		this->get<
			sge::sprite::roles::texture_point_size<
				Level
			>
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::depth_type
sge::sprite::object<
	Choices
>::z() const
{
	return
		this->get<
			sge::sprite::roles::depth
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::rotation_type
sge::sprite::object<
	Choices
>::rotation() const
{
	return
		this->get<
			sge::sprite::roles::rotation
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::repetition_type
sge::sprite::object<
	Choices
>::repetition() const
{
	return
		this->get<
			sge::sprite::roles::repetition
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::texture_coordinates_type const
sge::sprite::object<
	Choices
>::texture_coordinates() const
{
	return
		this->texture_coordinates_level<
			0
		>();
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
typename sge::sprite::object<
	Choices
>::texture_coordinates_type const
sge::sprite::object<
	Choices
>::texture_coordinates_level() const
{
	return
		this->get<
			sge::sprite::roles::texture_coordinates<
				Level
			>
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::color_type  const
sge::sprite::object<
	Choices
>::color() const
{
	return
		this->get<
			sge::sprite::roles::color
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<
	Choices
>::texture_type const
sge::sprite::object<
	Choices
>::texture() const
{
	return
		this->texture_level<
			0
		>();
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
typename sge::sprite::object<
	Choices
>::texture_type const &
sge::sprite::object<
	Choices
>::texture_level() const
{
	return
		this->get<
			sge::sprite::roles::texture<
				Level
			>
		>();
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::x(
	unit const _x
)
{
	this->pos(
		vector(
			_x,
			this->y()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::y(
	unit const _y
)
{
	this->pos(
		vector(
			this->x(),
			_y
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::z(
	depth_type const _depth
)
{
	this->set<
		sge::sprite::roles::depth
	>(
		_depth
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::pos(
	vector const _pos
)
{
	sge::sprite::detail::set_pos<
		Choices
	>(
		elements_,
		pos_type(
			_pos
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::center(
	vector const _center
)
{
	sge::sprite::detail::set_center<
		Choices
	>(
		elements_,
		center_type(
			_center
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::w(
	unit const _w
)
{
	this->size(
		dim(
			_w,
			this->h()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::h(
	unit const _h
)
{
	this->size(
		dim(
			this->w(),
			_h
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::size(
	dim const _dim
)
{
	sge::sprite::detail::set_size<
		Choices
	>(
		elements_,
		_dim
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::point_size(
	point_size_type const _point_size
)
{
	this->set<
		sge::sprite::roles::point_size
	>(
		_point_size
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::texture_point_pos(
	texture_point_pos_type const _point_pos
)
{
	this->texture_point_pos_level<
		0
	>(
		_point_pos
	);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
void
sge::sprite::object<
	Choices
>::texture_point_pos_level(
	texture_point_pos_type const _point_pos
)
{
	this->set<
		sge::sprite::roles::texture_point_pos<
			Level
		>
	>(
		_point_pos
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::texture_point_size(
	texture_point_size_type const _point_size
)
{
	this->texture_point_size_level<
		0
	>(
		_point_size
	);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
void
sge::sprite::object<
	Choices
>::texture_point_size_level(
	texture_point_size_type const _point_size
)
{
	this->set<
		sge::sprite::roles::texture_point_size<
			Level
		>
	>(
		_point_size
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::texture(
	texture_type const _texture
)
{
	this->texture_level<
		0
	>(
		_texture
	);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
void
sge::sprite::object<
	Choices
>::texture_level(
	texture_type const _texture
)
{
	this->set<
		sge::sprite::roles::texture<
			Level
		>
	>(
		_texture
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::rotation(
	rotation_type const _rotation
)
{
	this->set<
		sge::sprite::roles::rotation
	>(
		_rotation
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::repeat(
	repetition_type const _repeat
)
{
	this->set<
		sge::sprite::roles::repetition
	>(
		_repeat
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::texture_coordinates(
	texture_coordinates_type const &_coordinates
)
{
	this->texture_coordinates_level<
		0
	>(
		_coordinates
	);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
void
sge::sprite::object<
	Choices
>::texture_coordinates_level(
	texture_coordinates_type const &_coordinates
)
{
	this->set<
		sge::sprite::roles::texture_coordinates<
			Level
		>
	>(
		_coordinates
	);
}

template<
	typename Choices
>
void
sge::sprite::object<
	Choices
>::color(
	color_type const &_color
)
{
	this->set<
		sge::sprite::roles::color
	>(
		_color
	);
}

template<
	typename Choices
>
template<
	typename Role
>
inline
majutsu::role_return_type<
	typename
	sge::sprite::object<
		Choices
	>::element_type,
	Role
>
sge::sprite::object<
	Choices
>::get() const
{
	return
		majutsu::get<
			Role
		>(
			elements_
		);
}

template<
	typename Choices
>
template<
	typename Role
>
inline
void
sge::sprite::object<
	Choices
>::set(
	majutsu::role_return_type<
		element_type,
		Role
	> _value
)
{
	majutsu::set<
		Role
	>(
		elements_,
		_value
	);
}

#endif
