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


#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/projectile/debug_drawer.hpp>
#include <sge/projectile/dim2.hpp>
#include <sge/projectile/duration.hpp>
#include <sge/projectile/log.hpp>
#include <sge/projectile/log_location.hpp>
#include <sge/projectile/rect.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/collision.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/position_change.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/static.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/ghost/body_enter.hpp>
#include <sge/projectile/ghost/body_exit.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/scoped.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <sge/projectile/shape/circle.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/math/vector/input.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <chrono>
#include <example_main.hpp>
#include <exception>
#include <functional>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Container,
	typename Ch,
	typename Traits
>
Container
container_from_stream(
	std::basic_istream<
		Ch,
		Traits
	> &s
)
{
	Ch c;

	s >> c;

	if(
		c != s.widen('(')
	)
	{
		s.setstate(
			std::ios_base::failbit
		);

		return
			Container();
	}

	s >> c;

	Container result;

	while(
		c != s.widen(')')
	)
	{
		s.putback(
			c
		);

		typename
		Container::value_type new_value{
			fcppt::no_init()
		};

		s >> new_value;

		if(
			!s
		)
			return
				Container();

		result.insert(
			result.end(),
			new_value
		);

		s >> c;

		s >> c;
	}

	return
		result;
}

class body
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	body(
		sge::projectile::log const &_log,
		sge::projectile::world &_world,
		sge::projectile::group::object &_group,
		sge::projectile::shape::shared_base_ptr const _shape,
		sge::projectile::body::solidity::variant const &_solidity,
		sge::projectile::rect const _rect
	)
	:
		body_{
			sge::projectile::body::parameters{
				_log,
				sge::projectile::body::position(
					fcppt::math::box::center(
						_rect
					)
				),
				sge::projectile::body::linear_velocity(
					fcppt::math::vector::null<
						sge::projectile::vector2
					>()
				),
				sge::projectile::body::angular_velocity(
					fcppt::literal<
						sge::projectile::scalar
					>(
						0
					)
				),
				_shape,
				sge::projectile::body::rotation(
					fcppt::literal<
						sge::projectile::scalar
					>(
						0
					)
				),
				_solidity,
				sge::projectile::body::user_data()
			}
		},
		body_scope_{
			_world,
			body_,
			sge::projectile::group::sequence{
				fcppt::make_ref(
					_group
				)
			}
		}
	{
	}
FCPPT_PP_POP_WARNING

	~body()
	{
	}

	sge::projectile::body::object &
	get()
	{
		return
			body_;
	}
private:
	sge::projectile::body::object body_;

	sge::projectile::body::scoped body_scope_;
};

class body_keyboard_mover
{
	FCPPT_NONCOPYABLE(
		body_keyboard_mover
	);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	body_keyboard_mover(
		sge::projectile::world &_world,
		sge::projectile::body::object &_body
	)
	:
		body_(
			_body
		),
		body_collision_connection_(
			_world.body_collision(
				sge::projectile::body::collision{
					std::bind(
						&body_keyboard_mover::body_collision,
						this,
						std::placeholders::_1,
						std::placeholders::_2
					)
				}
			)
		),
		velocity_(
			fcppt::math::vector::null<
				sge::projectile::vector2
			>()
		)
	{
	}
FCPPT_PP_POP_WARNING

	~body_keyboard_mover()
	{
	}

	void
	key_event(
		sge::input::keyboard::event::key const &_event
	)
	{
		velocity_ =
			body_.linear_velocity()
			+
			fcppt::literal<
				sge::projectile::scalar
			>(
				30
			)
			*
			this->key_event_to_vector(
				_event
			);

		body_.linear_velocity(
			velocity_
		);
	}
private:
	sge::projectile::body::object &body_;

	fcppt::signal::auto_connection const body_collision_connection_;

	sge::projectile::vector2 velocity_;

	void
	body_collision(
		sge::projectile::body::object const &_body1,
		sge::projectile::body::object const &_body2
	)
	{
		if(
			&_body1 == &body_
			||
			&_body2 == &body_
		)
		{
			body_.linear_velocity(
				velocity_
			);

			body_.angular_velocity(
				fcppt::literal<
					sge::projectile::scalar
				>(
					0
				)
			);
		}
	}

	static
	sge::projectile::vector2
	key_code_to_vector(
		sge::input::key::code const _key_code
	)
	{
		switch(
			_key_code
		)
		{
		case sge::input::key::code::left:
			return
				sge::projectile::vector2{
					-1.f,
					0.f
				};
		case sge::input::key::code::right:
			return
				sge::projectile::vector2{
					1.f,
					0.f
				};
		case sge::input::key::code::up:
			return
				sge::projectile::vector2{
					0.f,
					-1.f
				};
		case sge::input::key::code::down:
			return
				sge::projectile::vector2{
					0.f,
					1.f
				};
		default:
			return
				fcppt::math::vector::null<
					sge::projectile::vector2
				>();
		}
	}

	static
	sge::projectile::vector2
	key_event_to_vector(
		sge::input::keyboard::event::key const &_event
	)
	{
		sge::projectile::vector2 const result{
			key_code_to_vector(
				_event.get().code()
			)
		};

		return
			_event.pressed()
			?
				result
			:
				-result
			;
	}

};

void
body_collision(
	sge::projectile::body::object const &,
	sge::projectile::body::object const &
)
{
	static unsigned ticker{
		1u
	};

	std::cout
		<<
		ticker++
		<<
		": body collision!\n";
}

class body_following_ghost
{
	FCPPT_NONCOPYABLE(
		body_following_ghost
	);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	body_following_ghost(
		sge::projectile::log const &_log,
		sge::projectile::world &_world,
		sge::projectile::body::object &_body,
		sge::projectile::ghost::size const &_size,
		sge::projectile::group::sequence const &_groups
	)
	:
		ghost_(
			sge::projectile::ghost::parameters(
				_log,
				sge::projectile::ghost::position(
					_body.position()
				),
				_size
			)
		),
		ghost_scope_(
			_world,
			ghost_,
			_groups
		),
		body_position_change_connection_(
			_body.position_change(
				sge::projectile::body::position_change{
					std::bind(
						&body_following_ghost::body_position_change,
						this,
						std::placeholders::_1
					)
				}
			)
		),
		body_enter_connection_(
			ghost_.body_enter(
				sge::projectile::ghost::body_enter{
					std::bind(
						&body_following_ghost::body_enter,
						this,
						std::placeholders::_1
					)
				}
			)
		),
		body_exit_connection_(
			ghost_.body_exit(
				sge::projectile::ghost::body_exit{
					std::bind(
						&body_following_ghost::body_exit,
						this,
						std::placeholders::_1
					)
				}
			)
		)
	{
	}
FCPPT_PP_POP_WARNING

	~body_following_ghost()
	{
	}
private:
	sge::projectile::ghost::object ghost_;

	sge::projectile::ghost::scoped ghost_scope_;

	fcppt::signal::auto_connection const
		body_position_change_connection_,
		body_enter_connection_,
		body_exit_connection_;

	void
	body_position_change(
		sge::projectile::body::position const &_pos
	)
	{
		ghost_.position(
			_pos.get()
		);
	}

	void
	body_enter(
		sge::projectile::body::object const &
	)
	{
		std::cout
			<< "Body enter!\n";
	}

	void
	body_exit(
		sge::projectile::body::object const &
	)
	{
		std::cout
			<< "Body exit!\n";
	}
};

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("projectile")
						)
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
				sge::viewport::optional_resize_callback{
					sge::viewport::center_on_resize(
						sge::window::dim{
							1024u,
							768u
						}
					)
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::projectile::log_location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	);

	sge::projectile::log log{
		sys.log_context()
	};

	sge::projectile::world world{
		log
	};

	fcppt::signal::auto_connection const body_collision_world(
		world.body_collision(
			sge::projectile::body::collision{
				&body_collision
			}
		)
	);

	sge::projectile::debug_drawer debug_drawer(
		sys.log_context(),
		world,
		sys.renderer_device_ffp());
	sge::projectile::group::object
		first_group(
			world),
		second_group(
			world);
	world.make_groups_collide(
		first_group,
		second_group);

	debug_drawer.active(
		true);

	body first_body(
		log,
		world,
		first_group,
		fcppt::make_shared_ptr<
			sge::projectile::shape::circle
		>(
			fcppt::literal<
				sge::projectile::scalar
			>(
				5
			)
		),
		sge::projectile::body::solidity::variant{
			sge::projectile::body::solidity::solid(
				sge::projectile::body::mass(
					fcppt::literal<
						sge::projectile::scalar
					>(
						1
					)
				)
			)
		},
		sge::projectile::rect(
			sge::projectile::vector2(
				10.f,
				10.f
			),
			sge::projectile::dim2(
				10.f,
				10.f
			)
		)
	);

	std::istringstream polygon_stream(
		"((42,296),(253,162),(12,23),(420,22),(420,310))");

	body second_body(
		log,
		world,
		second_group,
		fcppt::make_shared_ptr<
			sge::projectile::shape::triangle_mesh
		>(
			log,
			sge::projectile::triangulation::triangulate<
				sge::projectile::triangulation::default_tag,
				sge::projectile::shape::triangle_sequence
			>(
				container_from_stream<
					std::vector<
						sge::projectile::vector2
					>
				>(
					polygon_stream
				),
				fcppt::literal<
					sge::projectile::scalar
				>(
					0.00001
				)
			)
		),
		sge::projectile::body::solidity::variant{
			sge::projectile::body::solidity::static_()
		},
		sge::projectile::rect(
			sge::projectile::vector2(
				100.f,
				100.f
			),
			sge::projectile::dim2(
				20.f,
				20.f
			)
		)
	);

	body_following_ghost first_ghost{
		log,
		world,
		first_body.get(),
		sge::projectile::ghost::size(
			sge::projectile::dim2(
				100.f,
				100.f
			)
		),
		sge::projectile::group::sequence{
			fcppt::make_ref(
				first_group
			)
		}
	};

	body_keyboard_mover keyboard_mover{
		world,
		first_body.get()
	};

	fcppt::signal::auto_connection const escape_connection{
		sge::systems::quit_on_escape(
			sys
		)
	};

	sge::timer::basic<
		sge::timer::clocks::standard
	> frame_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	auto const draw(
		[
			&debug_drawer,
			&frame_timer,
			&sys,
			&world
		]{
			world.update_continuous(
				sge::projectile::time_increment(
					std::chrono::duration_cast<
						sge::projectile::duration
					>(
						sge::timer::elapsed(
							frame_timer
						)
					)
				)
			);

			frame_timer.reset();

			debug_drawer.update();

			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			fcppt::optional::maybe_void(
				sge::renderer::projection::orthogonal_viewport(
					scoped_block.get().target().viewport(),
					sge::renderer::projection::near(
						0.f
					),
					sge::renderer::projection::far(
						10.f
					)
				),
				[
					&scoped_block,
					&debug_drawer,
					&sys
				](
					sge::renderer::matrix4 const &_projection
				)
				{
					scoped_block.get().clear(
						sge::renderer::clear::parameters()
						.back_buffer(
							sge::image::color::any::object{
								sge::image::color::predef::black()
							}
						)
					);

					sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
						sys.renderer_device_ffp().create_transform_state(
							sge::renderer::state::ffp::transform::parameters(
								_projection
							)
						)
					);

					sge::renderer::state::ffp::transform::scoped const scoped_transform(
						scoped_block.get(),
						sge::renderer::state::ffp::transform::mode::projection,
						*transform_state
					);

					debug_drawer.render(
						scoped_block.get()
					);
				}
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&keyboard_mover,
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							brigand::list<
								sge::input::keyboard::event::key const,
								sge::renderer::event::render const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&keyboard_mover,
							&draw
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&keyboard_mover
								](
									fcppt::reference<
										sge::input::keyboard::event::key const
									> const _key_event
								)
								{
									keyboard_mover.key_event(
										_key_event.get()
									);
								},
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								}
							);
						}
					);
				}
			}
		);

}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
