
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"
#include "stdio.h"
#include <string.h>
#include "stdint.h"
#include <stdbool.h>
#include "usb_serial.h"
#include "Universal-Unit-Testing-Methods.h"
#include "Methods.h"

#define PRINT(var) printf("\tRunning Test: (" #var ")\n");

using namespace cgreen;

Ensure(cgreen_is_working) {
    PRINT_LITERAL(cgreen_is_working, F_CYAN);
    assert_that(true, is_equal_to(true));
}

Ensure(SHOULDER_CONTROL_LOOP) {
    PRINT_LITERAL(SHOULDER_CONTROL_LOOP,F_CYAN);
    significant_figures_for_assert_double_are(6);
    double Output = 0;
    Feedback_t Feedback; 
    Feedback.Shoulder = 50;
    Commands_t Command;
    Command.Shoulder = 180;

    for(int i =0; i < 20; i++)
    {
    	Output = ShoulderControlSystem(&Command, &Feedback);
    }


	// Command.Shoulder = 20;
 //    Feedback.Shoulder = 20;

 //    for(int i =0; i < 20; i++)
 //    {
 //    	Output = ShoulderControlSystem(&Command, &Feedback);
 //    	printf("Target: %f, Feedback: %f, Controlled: %f \n", 
 //    		Command.Shoulder, Feedback.Shoulder, Output);
 //    }

    assert_that(true, is_equal_to(true));
}

TestSuite *Arm_Tests() {
    printf("Suite (Arm_Tests)\n");
    TestSuite *suite = create_test_suite();
    
    add_test(suite, cgreen_is_working);
    add_test(suite, SHOULDER_CONTROL_LOOP);
    
    return suite;
}