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


#ifndef SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED

#include <sge/noise/perlin/object_decl.hpp>
#include <fcppt/container/grid/interpolate.hpp>
#include <fcppt/math/mod.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


template
<
	typename Float,
	std::size_t N,
	typename Interpolator
>
template
<
	typename Rng
>
sge::noise::perlin::object<Float,N,Interpolator>::object(
	dim const &_size,
	Rng &_random_generator)
:
	gradients_(
		_size)
{
	typedef
	fcppt::random::distribution::uniform_real<value_type>
	uniform_real_distribution;

	typedef
	fcppt::random::variate<Rng,uniform_real_distribution>
	variate;

	variate v(
		_random_generator,
		uniform_real_distribution(
			typename uniform_real_distribution::min(
				static_cast<value_type>(
					-1)),
			typename uniform_real_distribution::sup(
				static_cast<value_type>(
					1))));

	for(
		typename grid_type::iterator it =
			gradients_.begin();
		it != gradients_.end();
		++it)
		*it = v();
}

template
<
	typename Float,
	std::size_t N,
	typename Interpolator
>
typename
sge::noise::perlin::object<Float,N,Interpolator>::value_type
sge::noise::perlin::object<Float,N,Interpolator>::sample(
	vector_type v) const
{
	for(std::size_t i = 0u; i < N; ++i)
	{
		value_type const current_dimension =
			static_cast<value_type>(
				gradients_.size()[static_cast<typename grid_type::dim::size_type>(i)]);

		v[static_cast<typename vector_type::size_type>(i)] =
			fcppt::math::mod(
				fcppt::math::mod(
					v[static_cast<typename vector_type::size_type>(i)],
					current_dimension) +
				current_dimension,
				current_dimension);
	}

	return
		fcppt::container::grid::interpolate(
			gradients_,
			v,
			Interpolator());
}

#endif
