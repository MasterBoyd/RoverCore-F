
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"
#include "stdio.h"
#include <string.h>
#include "stdint.h"
#include <stdbool.h>
#include "usb_serial.h"
#include "Universal-Unit-Testing-Methods.h"
#include "CommonFunctions.h"

using namespace cgreen;

////////////////////////////////////////////////////////////////////////
//Send
////////////////////////////////////////////////////////////////////////

////SetToSend////

Ensure(TEST_CGREEN) {
    PRINT_LITERAL(TEST_CGREEN, F_GREEN);

    assert_that(true, is_equal_to(true));
}


//drv8870MotorControl() Tests

Ensure(TEST_MOTOR_CONTROL_BRAKE) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_BRAKE, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, 0);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm1, is_equal_to(255));

}

Ensure(TEST_MOTOR_CONTROL_FULL_SPEED_FORWARD) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_FULL_SPEED_FORWARD, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, 1);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm2, is_equal_to(0));
}

Ensure(TEST_MOTOR_CONTROL_FULL_SPEED_REVERSE) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_FULL_SPEED_REVERSE, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, -1);
    assert_that(result.pwm1, is_equal_to(0));
    assert_that(result.pwm2, is_equal_to(255));
}

Ensure(TEST_MOTOR_CONTROL_HALF_SPEED) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_HALF_SPEED, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, 0.5);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm2, is_equal_to(128));
}

Ensure(TEST_MOTOR_CONTROL_QUARTER_SPEED) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_QUARTER_SPEED, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, 0.25);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm2, is_equal_to(192));
}

Ensure(TEST_MOTOR_CONTROL_TOO_MUCH_SPEED) {
    PRINT_LITERAL(TEST_MOTOR_CONTROL_TOO_MUCH_SPEED, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 10, 2.0);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm2, is_equal_to(0));
}

Ensure(TEST_MOTOR_VOLTAGE_MISMATCH) {
    PRINT_LITERAL(TEST_MOTOR_VOLTAGE_MISMATCH, F_GREEN);
    MimicAnalogPrecision(8);
    motorControl_t result = drv8870MotorControl(10, 5, 1.0);
    assert_that(result.pwm1, is_equal_to(255));
    assert_that(result.pwm2, is_equal_to(128));
}

//dutyCycleVoltageTransfer() tests

Ensure(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_HALF) {
    PRINT_LITERAL(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_HALF, F_GREEN);

    //Defualt set to 12
    MimicAnalogPrecision(10);
    // dutyCycleVoltageTransfer();
    assert_that(dutyCycleVoltageTransfer(24, 12), is_equal_to(511));
}
Ensure(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_QUARTER) {
    PRINT_LITERAL(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_QUARTER, F_GREEN);

    //Defualt set to 12
    MimicAnalogPrecision(10);
    // dutyCycleVoltageTransfer();
    assert_that(dutyCycleVoltageTransfer(48, 12), is_equal_to(255));
}
Ensure(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_HALF) {
    PRINT_LITERAL(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_HALF, F_GREEN);

    //Defualt set to 12
    MimicAnalogPrecision(8);
    // dutyCycleVoltageTransfer();
    assert_that(dutyCycleVoltageTransfer(24, 12), is_equal_to(127));
}
Ensure(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_QUARTER) {
    PRINT_LITERAL(TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_QUARTER, F_GREEN);

    //Defualt set to 12
    MimicAnalogPrecision(8);
    // dutyCycleVoltageTransfer();
    assert_that(dutyCycleVoltageTransfer(48, 12), is_equal_to(63));
}


TestSuite *Common_Functions_Tests() {
    printf("Suite (Serial_Controller_Tests)\n");
    TestSuite *suite = create_test_suite();

    add_test(suite, TEST_CGREEN);
    add_test(suite, TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_HALF);
    add_test(suite, TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_8BIT_QUARTER);
    add_test(suite, TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_HALF);
    add_test(suite, TEST_DUTY_CYCLE_VOLTAGE_TRANSFER_10BIT_QUARTER);

    return suite;
}
