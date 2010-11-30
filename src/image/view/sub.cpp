/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/view/sub.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <mizuiro/image/sub_view.hpp>

namespace
{

template<
	typename View
>
View const
sub_impl(
	View const &,
	sge::image::rect const &
);

template<
	typename Result
>
class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	)
public:
	typedef Result result_type;

	explicit visitor(
		sge::image::rect const &
	);

	template<
		typename T
	>
	result_type const
	operator()(
		T const &
	) const;
private:
	sge::image::rect const rect_;
};

}

sge::image::view::object const
sge::image::view::sub(
	object const &_src,
	rect const &_rect
)
{
	return
		::sub_impl(
			_src,
			_rect
		);
}

sge::image::view::const_object const
sge::image::view::sub(
	const_object const &_src,
	rect const &_rect
)
{
	return
		::sub_impl(
			_src,
			_rect
		);
}

namespace
{

template<
	typename View
>
View const
sub_impl(
	View const &_view,
	sge::image::rect const &_rect
)
{
	return
		fcppt::variant::apply_unary(
			::visitor<
				View
			>(
				_rect
			),
			_view
		);
}

template<
	typename Result
>
visitor<Result>::visitor(
	sge::image::rect const &_rect
)
:
	rect_(_rect)
{}

template<
	typename Result
>
template<
	typename T
>
typename visitor<Result>::result_type const
visitor<Result>::operator()(
	T const &_value
) const
{
	// TODO: make this more generic!

	return
		mizuiro::image::sub_view(
			_value,
			typename T::bound_type(
				typename T::dim_type(
					rect_.left(),
					rect_.top()
				),
				typename T::dim_type(
					rect_.w(),
					rect_.h()
				)
			)
		);
}

}
