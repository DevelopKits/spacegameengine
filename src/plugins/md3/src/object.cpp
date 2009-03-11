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


#include "../object.hpp"
#include <sge/math/pi.hpp>
#include <sge/log/headers.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/istream_util.hpp>
#include <cmath>
#include <algorithm>

namespace
{

unsigned const max_qpath = 64;

// TODO: replace float here!
float const MD3_XYZ_SCALE = static_cast<float>(1) / static_cast<float>(64);

}

sge::md3::object::object(
	model::istream &is)
:
	vertices_(0),
	indices_(0)
{
	model::istream::off_type const start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(SGE_TEXT("Invalid md3 format!"));

	s32 const version = read<s32>(is);
	if(version != 15)
		SGE_LOG_WARNING(
			log::global(),
			log::_1 << SGE_TEXT("md3 version is not 15 but continuing anyway.")
		);

	name_ = read_string<max_qpath>(is);

	read<s32>(is); // flags

	s32 const
		num_frames = read<s32>(is),
		num_tags     = read<s32>(is),
		num_surfaces = read<s32>(is);
	
	read<s32>(is); // num_skins
	
	s32 const
		ofs_frames   = read<s32>(is),
		ofs_tags     = read<s32>(is),
		ofs_surfaces = read<s32>(is),
		ofs_eof      = read<s32>(is);

	is.seekg(start + ofs_frames, std::ios_base::beg);
	for(s32 i = 0; i < num_frames; ++i)
		frames.push_back(frame(is));

	is.seekg(start + ofs_tags, std::ios_base::beg);
	for(s32 i = 0; i < num_tags; ++i)
		tags.push_back(tag(is));

	is.seekg(start + ofs_surfaces, std::ios_base::beg);
	for(s32 i = 0; i < num_surfaces; ++i)
	{
		surfaces.push_back(surface(is, num_frames));
		surface const &s = surfaces.back();
		indices_ += s.triangles.size();
		vertices_ += s.transformed_vertices.size();
	}
	indices_ *= 3;

	is.seekg(start + ofs_eof);
}

sge::renderer::size_type
sge::md3::object::vertices() const
{
	return vertices_;
}

sge::renderer::size_type
sge::md3::object::indices() const
{
	return indices_;
}

void
sge::md3::object::copy_vertices(
	renderer::vf::dynamic_view const &view)
{
	/*
	if(offset + vertices() > vb->size())
		throw exception(SGE_TEXT("md3::object::fill_vertices(): vertex buffer out of range!"));

	renderer::vertex_buffer::iterator vbit = vb->begin() + offset;
	for(surface_vector::const_iterator surf_it = surfaces.begin(); surf_it != surfaces.end(); ++surf_it)
	{
		const surface& surf = *surf_it;

		const renderer::vertex_buffer::iterator vbold = vbit;
		for(surface::transformed_vertex_vector::size_type sz = 0; sz < surf.transformed_vertices.size(); ++sz)
		{
			const surface::transformed_vertex& v = surf.transformed_vertices.at(sz);

			(vbit  )->pos()    = v.pos;
			(vbit  )->normal() = v.normal;
			(vbit++)->tex()    = surf.st.at(sz).tex;
		}	
	}
	*/
}

void
sge::md3::object::copy_indices(
	renderer::index::view const &)
{
	/*
	if(offset + indices() > ib->size())
		throw exception(SGE_TEXT("md3::object::fill_indices(): index buffer out of range!"));

	renderer::index_buffer::value_type ib_offset(0);
	renderer::index_buffer::iterator ibit = ib->begin() + offset;
	for(surface_vector::const_iterator surf_it = surfaces.begin(); surf_it != surfaces.end(); ++surf_it)
	{
		const surface& surf = *surf_it;
		for(surface::triangle_vector::const_iterator it = surf.triangles.begin(); it != surf.triangles.end(); ++it)
		{
			*ibit++ = it->indices[0] + ib_offset;
			*ibit++ = it->indices[1] + ib_offset;
			*ibit++ = it->indices[2] + ib_offset;
		}
		ib_offset += static_cast<renderer::index_buffer::value_type>(surf.transformed_vertices.size());
	}
	*/
}


bool sge::md3::object::read_and_check_id3p(model::istream& is)
{
	typedef std::tr1::array<u8, 4> id3p_array;
	id3p_array id3p,
	           to_check = { { 0x49, 0x44, 0x50, 0x33 } };
	for(id3p_array::iterator i = id3p.begin(); i != id3p.end(); ++i)
		*i = read<u8>(is);
	return std::equal(id3p.begin(), id3p.end(), to_check.begin());
}

template<
	sge::md3::object::string::size_type Max
>
inline sge::md3::object::string const
sge::md3::object::read_string(model::istream& is)
{
	std::tr1::array<u8, Max> tmp_name;
	is.read(reinterpret_cast<char*>(tmp_name.c_array()), tmp_name.size());

	if(!std::count(tmp_name.begin(), tmp_name.end(), 0))
		throw exception(SGE_TEXT("String in md3 file not ended with a 0!"));

	return tmp_name.data();
}

inline sge::md3::object::vec3 sge::md3::object::convert_normal(const s16 normal)
{
	using std::sin;
	using std::cos;

	f32 const
		lat = static_cast<f32>((normal >> 8) & 255) * (2 * math::pi<f32>()) / 255,
		lng = static_cast<f32>(normal & 255) * (2 * math::pi<f32>()) / 255;

	return vec3(cos(lat) * sin(lng),
	            sin(lat) * sin(lng),
	            cos(lng));
}

inline sge::md3::object::vec3
sge::md3::object::read_vec3(model::istream& is)
{
	return vec3(read<f32>(is), read<f32>(is), read<f32>(is));
}

inline sge::md3::object::frame::frame(model::istream& is)
: min_bounds(read_vec3(is)),
  max_bounds(read_vec3(is)),
  local_origin(read_vec3(is)),
  radius(read<f32>(is)),
  name(read_string<16>(is))
{}

inline sge::md3::object::tag::tag(model::istream& is)
: name(read_string<max_qpath>(is)),
  origin(read_vec3(is))
{
	for(axis_array::iterator i = axis.begin(); i != axis.end(); ++i)
		*i = read_vec3(is);
}

inline sge::md3::object::surface::surface(model::istream& is, const s32 num_frames_head)
{
	const model::istream::off_type start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(SGE_TEXT("Invalid md3 surface!"));

	name = read_string<max_qpath>(is);
	read<s32>(is); // flags

	const s32 num_frames    = read<s32>(is);

	if(num_frames != num_frames_head)
		throw exception(SGE_TEXT("num_frames mismatch in md3::object::surface!"));

	const s32 num_shaders   = read<s32>(is);
	const s32 num_verts     = read<s32>(is);
	const s32 num_triangles = read<s32>(is);
	const s32 ofs_triangles = read<s32>(is);
	const s32 ofs_shaders   = read<s32>(is);
	const s32 ofs_st        = read<s32>(is);
	const s32 ofs_xyznormal = read<s32>(is);
	const s32 ofs_end       = read<s32>(is);

	is.seekg(start + ofs_triangles, std::ios_base::beg);
	for(s32 i = 0; i < num_triangles; ++i)
		triangles.push_back(triangle(is));

	is.seekg(start + ofs_shaders, std::ios_base::beg);
	for(s32 i = 0; i < num_shaders; ++i)
		shaders.push_back(shader(is));
	
	is.seekg(start + ofs_st, std::ios_base::beg);
	for(s32 i = 0; i < num_verts; ++i)
		st.push_back(texcoord(is));

	is.seekg(start + ofs_xyznormal, std::ios_base::beg);
	for(s32 i = 0; i < num_verts; ++i)
		transformed_vertices.push_back(
			transformed_vertex(
				vertex(is)
			)
		);

	is.seekg(start + ofs_end, std::ios_base::beg);
}

sge::md3::object::surface::shader::shader(model::istream& is)
: name(read_string<max_qpath>(is)),
  shader_index(read<s32>(is))
{}

sge::md3::object::surface::triangle::triangle(model::istream& is)
{
	for(index_array::iterator i = indices.begin(); i != indices.end(); ++i)
		*i = read<s32>(is);
}

sge::md3::object::surface::texcoord::texcoord(model::istream& is)
: tex(read<f32>(is), read<f32>(is))
{}

sge::md3::object::surface::vertex::vertex(model::istream& is)
: x(read<s16>(is)),
  y(read<s16>(is)),
  z(read<s16>(is)),
  normal(read<s16>(is))
{}

sge::md3::object::surface::transformed_vertex::transformed_vertex(
	vertex const &v)
:
	pos(
		static_cast<f32>(v.x) * MD3_XYZ_SCALE,
		static_cast<f32>(v.y) * MD3_XYZ_SCALE,
		static_cast<f32>(v.z) * MD3_XYZ_SCALE
	),
	normal(
		convert_normal(
			v.normal
		)
	)
{}
