#ifndef POLYMORPH_TESTS_COMMON_CPP
#define POLYMORPH_TESTS_COMMON_CPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <common.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

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

class CommonTest : public CppUnit::TestFixture
{
	/* Add tests to test suite */
	CPPUNIT_TEST_SUITE(CommonTest);
	CPPUNIT_TEST(OpenServerSocket);
	CPPUNIT_TEST(OpenClientSocket);
	CPPUNIT_TEST(ClientAndServerCanCommunicate);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp() {}
		void tearDown() {}

	protected:
		/* Tests itself */

		/**
		 * Test that a server socket can be opened without errors.
		 */
		void OpenServerSocket() {
		   	CPPUNIT_ASSERT_NO_THROW(
					Socket sock = Socket::openServerSocket(6789));
		}

		/**
		 * Test that a client socket can be created an can connect to
		 * a listening server socket.
		 */
		void OpenClientSocket() {
		   	CPPUNIT_ASSERT_NO_THROW(
					Socket serv = Socket::openServerSocket(6789));
			CPPUNIT_ASSERT_NO_THROW(
					Socket client1 = Socket::openClientSocket("localhost", 6789));
		}

		/**
		 * Test that a client and server sockets can correctly connect,
		 * send and receive data.
		 */
		void ClientAndServerCanCommunicate() {
			/* Easiest way to test this is to fork a process for
			 * either the server or client and try communication.
			 */
			int ret = fork();

			CPPUNIT_ASSERT(ret >= 0);

			/* Server */
			if (ret > 0)
			{
				char a = 0, b = 'b';
				Socket serv = Socket::openServerSocket(6789);
				Socket cli = serv.accept();
				cli.recv(&a, sizeof(a), 0);
				CPPUNIT_ASSERT(a == 'a');
				cli.send(&b, sizeof(b), 0);
			}

			/* Client (the forked process) */
			if (ret == 0)
			{
				char a = 'a', b = 0;
				Socket cli = Socket::openClientSocket("localhost", 6789);
				cli.send(&a, sizeof(a), 0);
				cli.recv(&b, sizeof(b), 0);
				CPPUNIT_ASSERT(b == 'b');
				_exit(0);
			}
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CommonTest);

#endif /* POLYMORPH_TESTS_COMMON_CPP */
