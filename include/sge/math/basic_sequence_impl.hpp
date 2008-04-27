/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED
#define SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED

#include "basic_sequence.hpp"
#include "compare.hpp"
#include "../array_facade_impl.hpp" // TODO: do we want this here?
#include <boost/static_assert.hpp>
#include <algorithm>

template<
	typename T,
	sge::math::detail::dim_type Dim>
template<typename... Args>
sge::math::basic_sequence<T, Dim>::basic_sequence(
	Args... args)
{
#ifdef SGE_HAVE_STATIC_ASSERT
	static_assert(sizeof... (args) == Dim, "Invalid number of arguments supplied to sequence!");
#else
	BOOST_STATIC_ASSERT(sizeof... (args) == Dim);
#endif
	init(args...);	
}

#define SGE_MATH_BINARY_OP_ASSIGN(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> & \
sge::math::basic_sequence<T, Dim>::operator x( \
	basic_sequence<T, Dim> const &r) \
{ \
	for(detail::dim_type i(0); i < Dim; ++i) \
		(*this)[i] x r[i]; \
	return *this; \
}

SGE_MATH_BINARY_OP_ASSIGN(+=)
SGE_MATH_BINARY_OP_ASSIGN(-=)
SGE_MATH_BINARY_OP_ASSIGN(*=)
SGE_MATH_BINARY_OP_ASSIGN(/=)
SGE_MATH_BINARY_OP_ASSIGN(%=)

#undef SGE_MATH_BINARY_OP_ASSIGN

#define SGE_MATH_UNARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x( \
	basic_sequence<T, Dim> l) \
{ \
	for(unsigned i = 0; i < Dim; ++i) \
		l[i] = x l[i]; \
	return l; \
}

SGE_MATH_UNARY_OP(+)
SGE_MATH_UNARY_OP(-)

#undef SGE_MATH_UNARY_OP

#define SGE_MATH_BINARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x( \
	basic_sequence<T, Dim> l, \
	basic_sequence<T, Dim> const &r) \
{ \
	return l x##= r; \
}

SGE_MATH_BINARY_OP(+)
SGE_MATH_BINARY_OP(-)
SGE_MATH_BINARY_OP(*)
SGE_MATH_BINARY_OP(/)
SGE_MATH_BINARY_OP(%)

#undef SGE_MATH_BINARY_OP

#define SGE_MATH_BINARY_OP_SCALAR(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x ( \
	basic_sequence<T, Dim> l, \
	typename basic_sequence<T, Dim>::const_reference r) \
{  \
	return l x##= r; \
}

SGE_MATH_BINARY_OP_SCALAR(+)
SGE_MATH_BINARY_OP_SCALAR(-)
SGE_MATH_BINARY_OP_SCALAR(/)
SGE_MATH_BINARY_OP_SCALAR(*)
SGE_MATH_BINARY_OP_SCALAR(%)

#define SGE_MATH_BINARY_OP_SCALAR_LEFT(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x ( \
	typename basic_sequence<T, Dim>::const_reference l, \
	basic_sequence<T, Dim> r) \
{ \
	return r x##= l; \
}

SGE_MATH_BINARY_OP_SCALAR_LEFT(+)
SGE_MATH_BINARY_OP_SCALAR_LEFT(-)
SGE_MATH_BINARY_OP_SCALAR_LEFT(*)

#undef SGE_MATH_BINARY_OP_SCALAR_LEFT

template<typename T,
	sge::math::detail::dim_type Dim>
typename sge::math::basic_sequence<T, Dim>::pointer
sge::math::basic_sequence<T, Dim>::data()
{
	return data_.c_array();
}

template<typename T,
	sge::math::detail::dim_type Dim>
typename sge::math::basic_sequence<T, Dim>::const_pointer
sge::math::basic_sequence<T, Dim>::data() const
{
	return data_.data();
}

template<typename T,
	sge::math::detail::dim_type Dim>
typename sge::math::basic_sequence<T, Dim>::size_type
sge::math::basic_sequence<T, Dim>::size() const
{
	return Dim;
}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
template<
	typename T,
	sge::math::detail::dim_type Dim>
template<typename... Args>
void sge::math::basic_sequence<T, Dim>::init(
	const_reference arg1,
	Args... args)
{
	init_where(0, arg1, args...);
}

template<
	typename T,
	sge::math::detail::dim_type Dim>
template<typename... Args>
void sge::math::basic_sequence<T, Dim>::init_where(
	size_type pos,
	const_reference arg1,
	Args... args)
{
	(*this)[pos] = arg1;
	init_where(++pos, args...);
}

template<
	typename T,
	sge::math::detail::dim_type Dim>
void sge::math::basic_sequence<T, Dim>::init_where(
	const size_type pos,
	const_reference arg)
{
	(*this)[pos] = arg;
}
#endif

template<
	typename T,
	sge::math::detail::dim_type Dim>
bool sge::math::operator==(
	basic_sequence<T, Dim> const &a,
	basic_sequence<T, Dim> const &b)
{
	return std::equal(
		a.begin(),
		a.end(),
		b.begin(),
		sge::math::compare<T>);
}

template<
	typename T,
	sge::math::detail::dim_type Dim>
bool sge::math::operator!=(
	basic_sequence<T, Dim> const &a,
	basic_sequence<T, Dim> const &b)
{
	return !(a == b);
}

template<
	typename D,
	typename S,
	sge::math::detail::dim_type Dim>
sge::math::basic_sequence<D, Dim>
sge::math::structure_cast(basic_sequence<S, Dim> const &s)
{
	typedef basic_sequence<D, Dim> ret_type;
	ret_type ret = ret_type(no_initialization_tag());
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(s[i]);
	return ret;
}

#endif
