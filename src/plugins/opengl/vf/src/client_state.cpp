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


#include "../client_state.hpp"
#include <sge/log/global.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/container/linear_set_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <ostream>

namespace
{

template<
	typename Set
>
void
insert_checked(
	Set &,
	typename Set::value_type
);

template<
	typename Set
>
void
erase_checked(
	Set &,
	typename Set::value_type
);

}

void
sge::opengl::vf::client_state::enable(
	GLenum const e
)
{
	insert_checked(
		normal_states_,
		e
	);
}

void
sge::opengl::vf::client_state::disable(
	GLenum const e
)
{
	erase_checked(
		normal_states_,
		e
	);
}

void
sge::opengl::vf::client_state::enable_attribute(
	GLuint const i
)
{
	insert_checked(
		attribute_states_,
		i
	);
}

void
sge::opengl::vf::client_state::disable_attribute(
	GLuint const i
)
{
	erase_checked(
		attribute_states_,
		i
	);
}

sge::opengl::vf::client_state::normal_state_set const &
sge::opengl::vf::client_state::normal_states() const
{
	return normal_states_;
}

sge::opengl::vf::client_state::index_state_set const &
sge::opengl::vf::client_state::attribute_states() const
{
	return attribute_states_;
}

namespace
{

fcppt::string const common_error(
	FCPPT_TEXT(" This usually happens if you forget to call renderer::device::unset_vertex_buffer() before setting a new one.")
);

template<
	typename Set
>
void
insert_checked(
	Set &s,
	typename Set::value_type const v
)
{
	if(
		!s.insert(v).second
	)
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate state inserted in opengl::vf!")
				<< common_error
		);
}

template<
	typename Set
>
void
erase_checked(
	Set &s,
	typename Set::value_type const v
)
{
	if(
		!s.erase(v)
	)
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("State erased in opengl::vf that was not there!")
				<< common_error
		);
}

}