#ifndef SGE_THREAD_FUTURE_UNINITIALIZED_HPP_INCLUDED
#define SGE_THREAD_FUTURE_UNINITIALIZED_HPP_INCLUDED

#include <sge/exception.hpp>

namespace sge
{
namespace thread
{
namespace future
{
class SGE_CLASS_SYMBOL uninitialized
:
	public exception
{
public:
	SGE_SYMBOL uninitialized();
};
}
}
}

#endif // SGE_THREAD_FUTURE_UNINITIALIZED_HPP_INCLUDED
