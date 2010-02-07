#include "../overlap_filter.hpp"
#include "../shapes/base.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>

namespace
{
sge::bullet::shapes::base &
proxy_to_shape(
	btBroadphaseProxy &b)
{
	return 
		*static_cast<sge::bullet::shapes::base *>(
			static_cast<btRigidBody *>(
				b.m_clientObject)->getUserPointer());
}

fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("overlap_filter")));
}

fcppt::signal::auto_connection
sge::bullet::overlap_filter::register_callback(
	collision::test_callback const &f)
{
	return 
		test_callback_.connect(
			f);
}

void
sge::bullet::overlap_filter::combiner(
	collision::test_callback_combiner const &f)
{
	test_callback_.combiner(
		f);
}

bool 
sge::bullet::overlap_filter::needBroadphaseCollision(
	btBroadphaseProxy* const a,
	btBroadphaseProxy* const b
) const
{
	// This is taken from the bullet user's manual. Turns out that needBroadphaseCollision
	// is responsible for the group handling by default. It does the following stuff. We could
	// circumvent the whole group system by defining our own masks and collides (which shouldn't be
	// short values), but I'm too lazy for that.
	bool const group_collides = 
		(a->m_collisionFilterGroup & b->m_collisionFilterMask) != 0 &&
		(b->m_collisionFilterGroup & a->m_collisionFilterMask) != 0;
	
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("a: ")
			<< a
			<< FCPPT_TEXT(", b: ")
			<< b
			<< FCPPT_TEXT(", group(a): ")
			<< a->m_collisionFilterGroup
			<< FCPPT_TEXT(", group(b): ")
			<< b->m_collisionFilterGroup
			<< FCPPT_TEXT(", mask(a): ")
			<< a->m_collisionFilterMask
			<< FCPPT_TEXT(", mask(b): ")
			<< b->m_collisionFilterMask
			<< FCPPT_TEXT(", result: ")
			<< group_collides);
		
	if (!group_collides)
		return false;
		
	shapes::base const
		&sa = 
			proxy_to_shape(
				*a),
		&sb = 
			proxy_to_shape(
				*b);
	
	// no "inner body" collisions
	//if (sa.has_meta_body() && sb.has_meta_body() && &(sa.meta_body()) == &(sb.meta_body()))
	//	return false;
	return
		test_callback_(
			sa.satellite(),
			sb.satellite()
		);
}
