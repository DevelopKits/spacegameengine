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


#ifndef SGE_MEDIA_MUXER_PARAMETERS_HPP_INCLUDED
#define SGE_MEDIA_MUXER_PARAMETERS_HPP_INCLUDED

#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/media/detail/instantiate/symbol.hpp>
#include <sge/plugin/collection.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sge
{
namespace media
{

template<
	typename System
>
class muxer_parameters
{
	FCPPT_NONASSIGNABLE(
		muxer_parameters
	);
public:
	typedef
	sge::plugin::collection<
		System
	>
	collection_type;

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	muxer_parameters(
		fcppt::log::context &,
		collection_type const &,
		sge::media::optional_extension_set const &
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	fcppt::log::context &
	log_context() const;

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	collection_type const &
	collection() const;

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	sge::media::optional_extension_set const &
	extensions() const;
private:
	fcppt::log::context &log_context_;

	collection_type const collection_;

	sge::media::optional_extension_set const extensions_;
};

}
}

#endif
