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


#include <sge/opencl/impl/memory_object/to_opencl_mem_flags.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>


cl_mem_flags
sge::opencl::impl::memory_object::to_opencl_mem_flags(
	sge::opencl::memory_object::flags_field const &f)
{
	cl_mem_flags result = 0;

	if(f & sge::opencl::memory_object::flags::read && f & sge::opencl::memory_object::flags::write)
		result = CL_MEM_READ_WRITE;
	else if(f & sge::opencl::memory_object::flags::read)
		result = CL_MEM_READ_ONLY;
	else if(f & sge::opencl::memory_object::flags::write)
		result = CL_MEM_WRITE_ONLY;

	if(f & sge::opencl::memory_object::flags::alloc_host_ptr)
		result |= CL_MEM_ALLOC_HOST_PTR;

	return result;
}
