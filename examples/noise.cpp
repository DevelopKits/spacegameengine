/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/channel8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/store/l8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <sge/noise/perlin/object.hpp>
#include <sge/noise/simplex/object.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/default_parameters.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/defaults/defaults.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <mizuiro/color/channel/luminance.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/interpolation/perlin_fifth_degree_functor.hpp>
#include <fcppt/math/interpolation/trigonometric_functor.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


namespace
{

void
fill_texture(
	sge::image2d::store::l8::view_type _view)
{
	typedef sge::image2d::store::l8::view_type::dim dim_type;
	typedef dim_type::value_type dim_value_type;

	/*
	typedef
	sge::noise::simplex::object<double,2>
	noise_type;
	*/
	typedef
	//sge::noise::perlin::object<double,2,fcppt::math::interpolation::trigonometric_functor>
	sge::noise::perlin::object<double,2,fcppt::math::interpolation::perlin_fifth_degree_functor>
	noise_type;

	typedef
	sge::noise::sample_parameters<noise_type>
	param_type;

	fcppt::random::generator::minstd_rand rng(
		fcppt::random::generator::seed_from_chrono<fcppt::random::generator::minstd_rand::seed>());

	/*
	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));
			*/
	noise_type noise_generator(
		noise_type::dim(
			_view.size()[0]/100,
			_view.size()[1]/100),
		rng);

	for (dim_value_type y = 0; y < _view.size()[1]; ++y)
		for (dim_value_type x = 0; x < _view.size()[0]; ++x)
		{
			_view[
				sge::image2d::store::l8::view_type::dim(
					x,
					y
				)
			].set(
				mizuiro::color::channel::luminance(),
				static_cast<sge::image::channel8>(
					256.0 *
					(0.5 + 0.5 *
					sge::noise::sample(
						noise_generator,
						param_type(
							param_type::position_type(
								noise_type::vector_type(
									static_cast<noise_type::value_type>(
										x),
									static_cast<noise_type::value_type>(
										y))),
							param_type::amplitude_type(
								0.8),
							param_type::frequency_type(
								.005),
							param_type::octaves_type(
								6u))))
				)
			);
		}
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	typedef
	sge::noise::simplex::object<double,2>
	noise_type;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));

	fcppt::io::cout()
		<< FCPPT_TEXT("raw noise generator spit out: ")
		<< noise_generator.sample(
				noise_type::vector_type(
					23.0,
					42.0))
		<< FCPPT_TEXT('\n');

	sge::systems::instance<
		boost::mpl::vector2<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("noisetest")
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	);

	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::shared
			>
		>
	> sprite_choices;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	sprite_buffers_type sprite_buffers(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic);

	typedef sge::sprite::state::all_choices sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state_object;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	sprite_state_object sprite_state(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sge::image2d::store::l8 const store{
		fcppt::math::dim::fill<
			sge::image2d::dim
		>(
			1024
		),
		&fill_texture
	};

	sge::renderer::texture::planar_unique_ptr const noise_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer_device_ffp(),
			sge::image2d::view::const_object(
				store.const_wrapped_view()
			),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		)
	);

	sprite_object const spr(
		sge::sprite::default_parameters<
			sprite_choices
		>()
		.texture_size()
		.texture(
			sprite_object::texture_type{
				fcppt::make_shared_ptr<
					sge::texture::part_raw_ref
				>(
					*noise_texture
				)
			}
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
			)
		);

		sge::sprite::process::one(
			scoped_block.get(),
			spr,
			sprite_buffers,
			sprite_state
		);
	}

	return sys.window_system().exit_code();
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr() << e.string() << FCPPT_TEXT("\n");
	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr << _error.what() << '\n';
	return awl::main::exit_failure();
}
