#ifndef POLYMORPH_TESTS_ANIMATION_SYSTEM_CPP
#define POLYMORPH_TESTS_ANIMATION_SYSTEM_CPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "animationSystem.hpp"

using namespace PolyMorph;

class MockAnimationData : public AnimationData
{
public:
	MockAnimationData() {}
	void animate() {}
};

class AnimationSystemTest : public CppUnit::TestFixture
{
	/* Add tests to test suite */
	CPPUNIT_TEST_SUITE(AnimationSystemTest);
	CPPUNIT_TEST(CanAddAndRemoveAnimationData);
	CPPUNIT_TEST_SUITE_END();

	AnimationSystem _rs;

	public:
		void setUp() {}
		void tearDown() {}

	protected:
		/* Tests itself */

		/**
		 * Simple test that verifies that AnimationData can be added
		 * and removed successfully.
		 */
		void CanAddAndRemoveAnimationData()
		{
			AnimationData::ptr_type data(new MockAnimationData);

			_rs.addToAnimating(data);

			CPPUNIT_ASSERT(_rs.isAnimating(data));

			_rs.removeFromAnimating(data);

			CPPUNIT_ASSERT(!_rs.isAnimating(data));
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AnimationSystemTest);

#endif /* POLYMORPH_TESTS_COMMON_CPP */
