#ifndef POLYMORPH_TESTS_RENDER_SYSTEM_CPP
#define POLYMORPH_TESTS_RENDER_SYSTEM_CPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "RenderSystem.hpp"

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
