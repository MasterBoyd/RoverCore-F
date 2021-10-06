
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"
#include "stdio.h"
#include <string.h>
#include "stdint.h"
#include <stdbool.h>
#include "usb_serial.h"

#define PRINT(var) printf("\tRunning Test: (" #var ")\n");

using namespace cgreen;

Ensure(cgreen_is_working) {
    PRINT(cgreen_is_working);
    assert_that(true, is_equal_to(true));
}

TestSuite *Drive_Tests() {
    printf("Suite (Drive_Tests)\n");
    TestSuite *suite = create_test_suite();
    
    add_test(suite, cgreen_is_working);
    
    return suite;
}