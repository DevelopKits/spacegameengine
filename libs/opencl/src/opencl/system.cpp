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


#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/platform/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/buffer/object.hpp>


sge::opencl::system::system()
:
	// TODO: Direct initialization
	platforms_()
{
	cl_uint number_of_platforms;

	// First, query the total number of platforms
	cl_int error_code =
		clGetPlatformIDs(
			// maximum number of entries
			0,
			// pointer to the entries array
			nullptr,
			&number_of_platforms);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetplatformIDs"));

	if(!number_of_platforms)
		return;

	typedef
	fcppt::container::buffer::object<cl_platform_id>
	platform_id_sequence;

	platform_id_sequence platform_ids(
		static_cast<platform_id_sequence::size_type>(
			number_of_platforms));

	// First, query the total number of platforms
	error_code =
		clGetPlatformIDs(
			number_of_platforms,
			platform_ids.write_data(),
			// pointer to the number of platforms
			nullptr);

	platform_ids.written(
		platform_ids.write_size()
	);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetplatformIDs"));

	// TODO: map
	for(
		auto const &platform
		:
		platform_ids
	)
	{
		platforms_.push_back(
			opencl::platform::object(
				platform));
	}
}

sge::opencl::platform::object_sequence &
sge::opencl::system::platforms()
{
	return platforms_;
}

sge::opencl::platform::object_sequence const &
sge::opencl::system::platforms() const
{
	return platforms_;
}

sge::opencl::system::~system()
{
}
