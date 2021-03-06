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


#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/index.hpp>
#include <sge/gui/index_callback.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::gui::widget::choices::choices(
	sge::gui::context &_context,
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::gui::string_container const &_strings,
	sge::gui::optional_index const _opt_index
)
:
	sge::gui::widget::box_container(
		_context,
		sge::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::x
	),
	strings_(
		_strings
	),
	left_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("<"),
		sge::gui::optional_needed_width()
	),
	middle_text_(
		_style,
		_renderer,
		_font,
		fcppt::optional::maybe(
			_opt_index,
			[]{
				return
					sge::font::string();
			},
			[
				&_strings
			](
				sge::gui::index const _index
			)
			{
				return
					_strings[
						_index.get()
					];
			}
		),
		_style.text_color(),
		sge::gui::optional_needed_width(
			sge::gui::needed_width_from_strings(
				_font,
				_strings
			)
		)
	),
	right_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT(">"),
		sge::gui::optional_needed_width()
	),
	index_{
		_opt_index
	},
	left_connection_{
		left_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sge::gui::widget::choices::left_clicked,
					this
				)
			}
		)
	},
	right_connection_{
		right_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sge::gui::widget::choices::right_clicked,
					this
				)
			}
		)
	},
	index_changed_()
{
	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				left_button_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				middle_text_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				right_button_
			),
			sge::rucksack::alignment::center
		)
	);
}

sge::gui::widget::choices::~choices()
{
}

fcppt::signal::auto_connection
sge::gui::widget::choices::change(
	sge::gui::index_callback const &_callback
)
{
	return
		index_changed_.connect(
			_callback
		);
}

sge::gui::optional_index
sge::gui::widget::choices::index() const
{
	return
		index_;
}

void
sge::gui::widget::choices::left_clicked()
{
	this->update_index(
		[
			this
		](
			sge::gui::index const _index
		)
		{
			return
				_index.get()
				==
				0u
				?
					index_
				:
					sge::gui::optional_index(
						sge::gui::index(
							_index.get()
							-
							1u
						)
					)
				;
		}
	);
}

void
sge::gui::widget::choices::right_clicked()
{
	this->update_index(
		[
			this
		](
			sge::gui::index const _index
		)
		{
			return
				_index.get()
				==
				strings_.size() - 1u
				?
					index_
				:
					sge::gui::optional_index(
						sge::gui::index(
							_index.get()
							+
							1u
						)
					)
				;
		}
	);
}

template<
	typename Func
>
void
sge::gui::widget::choices::update_index(
	Func const &_func
)
{
	index_ =
		fcppt::optional::bind(
			index_,
			_func
		);

	fcppt::optional::maybe_void(
		index_,
		[
			this
		](
			sge::gui::index const _index
		)
		{
			middle_text_.value(
				strings_[
					_index.get()
				]
			);

			index_changed_(
				_index
			);
		}
	);
}
