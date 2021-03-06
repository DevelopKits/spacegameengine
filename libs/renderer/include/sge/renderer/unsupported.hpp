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


#ifndef SGE_RENDERER_UNSUPPORTED_HPP_INCLUDED
#define SGE_RENDERER_UNSUPPORTED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace renderer
{

/**
\brief An exception that is thrown when unsupported features are used

\ingroup sge_renderer
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL unsupported
:
	public sge::renderer::exception
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	unsupported(
		fcppt::string const &feature,
		fcppt::string const &minimum_version_required,
		fcppt::string const &possible_extensions
	);

	/**
	\brief Returns the name of the missing feature
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	fcppt::string const &
	feature() const;

	/**
	\brief Returns the minimum version that is required to get the feature
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	fcppt::string const &
	minimum_version_required() const;

	/**
	\brief Returns possible extensions that could provide the feature
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	fcppt::string const &
	possible_extensions() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~unsupported() throw()
	override;
private:
	fcppt::string
		feature_,
		minimum_version_required_,
		possible_extensions_;
};

}
}

#endif
