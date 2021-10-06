#include "cgreen/cgreen.h"
#include <cgreen/mocks.h>

TestSuite *Common_Functions_Tests();
TestSuite *Serial_Controller_Tests();

using namespace cgreen;

int main(int argc, char **argv) {
  TestSuite *suite = create_test_suite();
  // add_suite(suite, Common_Functions_Tests());
  add_suite(suite, Serial_Controller_Tests());
  if (argc > 1) {
    return run_single_test(suite, argv[1], create_text_reporter());
  }
  return run_test_suite(suite, create_text_reporter());
}