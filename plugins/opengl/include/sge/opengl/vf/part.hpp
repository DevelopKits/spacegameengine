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


#ifndef SGE_OPENGL_VF_PART_HPP_INCLUDED
#define SGE_OPENGL_VF_PART_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class part
{
	FCPPT_NONCOPYABLE(
		part
	);
public:
	part(
		fcppt::log::object &,
		sge::opengl::context::object &,
		sge::renderer::vf::dynamic::part const &
	);

	~part();

	sge::renderer::vf::dynamic::part const &
	get() const;

	void
	use_me(
		sge::opengl::vf::pointer
	) const;

	void
	unuse_me() const;
private:
	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	sge::renderer::vf::dynamic::part const part_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::vf::actor
	>
	actor_unique_ptr;

	typedef
	std::vector<
		actor_unique_ptr
	>
	actor_container;

	actor_container const actors_;
};

}
}
}

#endif
