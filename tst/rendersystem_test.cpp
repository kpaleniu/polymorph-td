#ifndef POLYMORPH_TESTS_COMMON_CPP
#define POLYMORPH_TESTS_COMMON_CPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "RenderSystem.hpp"

/**
 * This shall be a boiler-plate example of how to create unit
 * tests in cppunit. You need the following:
 *
 * 1) The test should be in a class that inherits from
 *    CppUnit::TestFixture. Naming of the class is important,
 *    it should postfixed by Test, e.g. FooTest
 *
 * 2) Class has to declare using CPPUNIT_TEST_SUITE() and
 *    CPPUNIT_TEST() macros what tests are registered to the
 *    test registry. All registered tests are run by the
 *    testrunner binary.
 *
 * 3) Test class must implement public methods void setUp()
 *    and void tearDown().
 *
 * 4) Tests themselves should be in a protected section in of
 *    the class and are in the form of void foo().
 *
 * 5) End of the file must contain call to
 *    CPPUNIT_TEST_SUITE_REGISTRATION(FooTest) macro. That
 *    registers the class itself to the test registry.
 *
 * This file will be compiled to an object file and linked with
 * the testrunner binary.
 *
 * For more information, see cppunit documentation.
 */

using namespace PolyMorph;

class MockRenderData : public RenderData
{
public:
	MockRenderData() {}
	void render() {}
};

class RenderSystemTest : public CppUnit::TestFixture
{
	/* Add tests to test suite */
	CPPUNIT_TEST_SUITE(RenderSystemTest);
	CPPUNIT_TEST(CanAddAndRemoveRenderData);
	CPPUNIT_TEST_SUITE_END();

	RenderSystem _rs;

	public:
		void setUp() {}
		void tearDown() {}

	protected:
		/* Tests itself */

		/**
		 * Simple test that verifies that RenderData can be added
		 * and removed successfully.
		 */
		void CanAddAndRemoveRenderData() {
			RenderData::ptr data(new MockRenderData);

			_rs.addToRendering(data);

			CPPUNIT_ASSERT(_rs.isRendering(data));

			_rs.removeFromRendering(data);

			CPPUNIT_ASSERT(!_rs.isRendering(data));
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(RenderSystemTest);

#endif /* POLYMORPH_TESTS_COMMON_CPP */
