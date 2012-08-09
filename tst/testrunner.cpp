#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

/**
 * This is basically a boiler-plate code for creating a runnable testsuite
 * using cppunit. This is compiled and linked with other individual testsuites
 * which creates a binary what executes all available unit tests.
 *
 * This is basically adapted from cppunit documentation. I'll add commenting
 * later.
 */

using namespace CPPUNIT_NS;

int main ()
{
	    // informs test-listener about testresults
		TestResult testresult;
		
		// register listener for collecting the test-results
		TestResultCollector collectedresults;
		testresult.addListener (&collectedresults);
		
		// register listener for per-test progress output
		BriefTestProgressListener progress;
		testresult.addListener(&progress);
		
		// insert test-suite at test-runner by registry
		TestRunner testrunner;
		testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
		testrunner.run (testresult);
		
        // output results in compiler-format
        CompilerOutputter compileroutputter(&collectedresults, std::cerr);
        compileroutputter.write ();

        // return 0 if tests were successful
        return collectedresults.wasSuccessful () ? 0 : 1;
}
