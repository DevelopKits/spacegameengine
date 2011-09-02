/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENAL_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_CONTEXT_HPP_INCLUDED

#include "openal.hpp"
#include "device_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace openal
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef
	std::vector
	<
		std::pair<ALCint,ALCint>
	>
	attribute_container;

	explicit
	context(
		openal::device &,
		attribute_container const & = attribute_container());

	ALCcontext *
	alcontext();

	void
	make_current();

	~context();
private:
	ALCcontext *context_;
	openal::device &device_;
};
}
}

#endif
