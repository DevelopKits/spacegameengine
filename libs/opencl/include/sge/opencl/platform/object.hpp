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


#ifndef SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/device/object_sequence.hpp>
#include <sge/opencl/platform/extension_sequence.hpp>
#include <sge/opencl/platform/profile_type_fwd.hpp>
#include <sge/opencl/platform/version.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace platform
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_DETAIL_SYMBOL cl_platform_id
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object_sequence &
	devices();

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object_sequence const &
	devices() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::profile_type
	profile() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::version
	version() const;

	SGE_OPENCL_DETAIL_SYMBOL std::string
	name() const;

	SGE_OPENCL_DETAIL_SYMBOL std::string
	vendor() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::extension_sequence
	extensions() const;

	SGE_OPENCL_DETAIL_SYMBOL bool
	supports_memory_sharing_with(
		renderer::device::core const &) const;

	SGE_OPENCL_DETAIL_SYMBOL bool
	has_gpu() const;

	SGE_OPENCL_DETAIL_SYMBOL
	~object();

	object(
		object &&
	);

	object &
	operator=(
		object &&
	);
private:
	friend class opencl::system;
	friend class opencl::context::object;

	cl_platform_id platform_id_;

	opencl::device::object_sequence devices_;

	explicit
	object(
		cl_platform_id const &);
};
}
}
}

#endif
