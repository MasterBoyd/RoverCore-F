#include "cgreen/cgreen.h"
#include <cgreen/mocks.h>

////Example Tests////
TestSuite *assertion_tests();
TestSuite *fixture_tests();
TestSuite *visible_fixtures();
TestSuite *isolation_tests();
TestSuite *mock_tests();

////Development Tests////
TestSuite *Tracker_Tests();

using namespace cgreen;

int main(int argc, char **argv) {
  TestSuite *suite = create_test_suite();

  ////Example Tests////
  	add_suite(suite, assertion_tests());
    add_suite(suite, fixture_tests());
    add_suite(suite, visible_fixtures());
    add_suite(suite, isolation_tests());
	add_suite(suite, mock_tests());

	////Development Tests////
  	add_suite(suite, Tracker_Tests());

  if (argc > 1) {
    return run_single_test(suite, argv[1], create_text_reporter());
  }
  return run_test_suite(suite, create_text_reporter());
}