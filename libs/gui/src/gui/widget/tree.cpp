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


#include <sge/gui/context_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_tree.hpp>
#include <sge/gui/widget/reference_tree_vector.hpp>
#include <sge/gui/widget/tree.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/tree/level.hpp>
#include <fcppt/container/tree/pre_order.hpp>


sge::gui::widget::tree::tree(
	sge::gui::context &_context,
	sge::gui::widget::reference_tree_vector const &_widgets
)
:
	sge::gui::widget::box_container(
		_context,
		sge::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::y
	),
	boxes_(
		fcppt::algorithm::map_concat<
			sge::gui::widget::unique_ptr_vector
		>(
			_widgets,
			[
				&_context
			](
				sge::gui::widget::reference_tree const &_tree
			)
			{
				return
					fcppt::algorithm::map<
						sge::gui::widget::unique_ptr_vector
					>(
						fcppt::container::tree::pre_order<
							sge::gui::widget::reference_tree const
						>(
							_tree
						),
						[
							&_context
						](
							sge::gui::widget::reference_tree const &_widget
						)
						{
							class indented_widget
							:
								public sge::gui::widget::box_container
							{
								FCPPT_NONCOPYABLE(
									indented_widget
								);
							public:
								indented_widget(
									sge::rucksack::scalar const _indent,
									sge::gui::context &_new_context,
									sge::gui::widget::base &_new_widget
								)
								:
									sge::gui::widget::box_container(
										_new_context,
										sge::gui::widget::reference_alignment_vector{
											sge::gui::widget::reference_alignment_pair(
												sge::gui::widget::reference(
													_new_widget
												),
												sge::rucksack::alignment::left_or_top
											)
										},
										sge::rucksack::axis::x
									),
									padding_{
										sge::rucksack::axis_policy2{
											sge::rucksack::axis_policy{
												sge::rucksack::preferred_size{
													_indent
												}
											},
											sge::rucksack::axis_policy{
												sge::rucksack::minimum_size{
													fcppt::literal<
														sge::rucksack::scalar
													>(
														0
													)
												}
											}
										}
									}
								{
									this->box_layout().push_front_child(
										padding_,
										sge::rucksack::alignment::left_or_top
									);
								}

								~indented_widget()
								{
								}
							private:
								sge::rucksack::widget::dummy padding_;
							};

							return
								fcppt::unique_ptr_to_base<
									sge::gui::widget::base
								>(
									fcppt::make_unique_ptr<
										indented_widget
									>(
										fcppt::cast::size<
											sge::rucksack::scalar
										>(
											fcppt::cast::to_signed(
												fcppt::container::tree::level(
													_widget
												)
											)
										)
										*
										fcppt::literal<
											sge::rucksack::scalar
										>(
											20
										),
										_context,
										_widget.value().get()
									)
								);
						}
					);
			}
		)
	)
{
	for(
		auto &box
		:
		boxes_
	)
		this->push_back(
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					*box
				),
				sge::rucksack::alignment::left_or_top
			)
		);
}

sge::gui::widget::tree::~tree()
{
}
