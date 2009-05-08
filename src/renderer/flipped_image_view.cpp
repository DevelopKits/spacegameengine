/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/flipped_image_view.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/gil/image_view_factory.hpp>

namespace
{

template<
	typename View 
>
class visitor {
public:
	typedef View const result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T const &) const;
};

}

sge::renderer::image_view const
sge::renderer::flipped_image_view(
	image_view const &v)
{
	return variant::apply_unary(
		visitor<image_view>(),
		v
	);
}

sge::renderer::const_image_view const
sge::renderer::flipped_image_view(
	const_image_view const &v)
{
	return variant::apply_unary(
		visitor<const_image_view>(),
		v
	);
}

namespace
{

template<
	typename View
>
template<
	typename T
>
typename visitor<View>::result_type
visitor<View>::operator()(
	T const &v) const
{
	return typename visitor<View>::result_type(
		boost::gil::flipped_up_down_view(
			v
		)
	);
}

}
