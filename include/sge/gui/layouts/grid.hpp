#ifndef SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	
#define SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL grid : public base
{
public:
	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL dim const optimal_size() const;
private:
	typedef boost::multi_array<widgets::base*,2> child_container;
	typedef boost::multi_array<widget::base const *,2> const_child_container;
	typedef boost::multi_array<widget::base const *,1> const_child_row;
	typedef std::vector<
		std::pair<
			widgets::base*,
			dim>
			> sizes_map;

	sizes_map sizes;

	dim const dimensions() const;
	child_container const children();
	const_child_container const children() const;
};
}
}
}

#endif
