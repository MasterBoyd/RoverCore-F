#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"
#include "Universal-Unit-Testing-Methods.h"
#include <string.h>
#include "words.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace cgreen;

Ensure(these_should_be_true){
    PRINT_LITERAL(these_should_be_true, F_BLUE); 
    assert_true(1);
    assert_false(1);
}

Ensure(these_should_be_false) {
    PRINT_LITERAL(these_should_be_false, F_BLUE);
    assert_true(0);
    assert_false(0);
}

Ensure(these_should_be_equal) {
    PRINT_LITERAL(these_should_be_equal, F_BLUE);
    assert_equal(1, 1);
    assert_not_equal(1, 1);
}

Ensure(these_should_not_be_equal) {
    PRINT_LITERAL(these_should_not_be_equal, F_BLUE);
    assert_equal(0, 1);
    assert_not_equal(0, 1);
}

Ensure(these_strings_should_match) {
    PRINT_LITERAL(these_strings_should_match, F_BLUE);
    assert_string_equal("Hello", "Hello");
    assert_string_not_equal("Hello", "Hello");
}

Ensure(these_strings_should_not_match) {
    PRINT_LITERAL(these_strings_should_not_match, F_BLUE);
    assert_string_equal("Hello", "hello");
    assert_string_not_equal("Hello", "hello");
}

TestSuite *assertion_tests() {
    TestSuite *suite = create_test_suite();
    add_test(suite, these_should_be_true);
    add_test(suite, these_should_be_false);
    add_test(suite, these_should_be_equal);
    add_test(suite, these_should_not_be_equal);
    add_test(suite, these_strings_should_match);
    add_test(suite, these_strings_should_not_match);
    return suite;
}

static int an_integer = 0;

void set_up_an_integer() {
    an_integer = 1;
}

Ensure(confirm_integer_is_set_up) {
    PRINT_LITERAL(confirm_integer_is_set_up, F_BLUE);
    assert_equal_with_message(an_integer, 1, "Could not set up the integer");
    an_integer = 2;
}

Ensure(check_again_during_teardown) {
    PRINT_LITERAL(check_again_during_teardown, F_BLUE);
    assert_equal_with_message(an_integer, 1, "Integer was changed from 1 to %d", an_integer);
}

TestSuite *fixture_tests() {
    TestSuite *suite = create_test_suite();
    set_setup(suite, set_up_an_integer);
    set_teardown(suite, check_again_during_teardown);
    add_test(suite, confirm_integer_is_set_up);
    return suite;
}

static void print_something_during_setup() {
    printf("\tI was called during setup\n");
}

Ensure(print_something_during_a_test) {
    PRINT_LITERAL(print_something_during_a_test, F_BLUE);
    printf("\tI am a test\n");
}

static void print_something_during_teardown() {
    printf("\tI was called during teardown\n");
}

TestSuite *visible_test() {
    TestSuite *suite = create_test_suite();
    set_setup(suite, print_something_during_setup);
    add_test(suite, print_something_during_a_test);
    set_teardown(suite, print_something_during_teardown);
    return suite;
}

static void print_something_during_suite_setup() {
    printf("I was called during suite setup\n");
}

static void print_something_during_suite_teardown() {
    printf("I was called during suite teardown\n");
}

TestSuite *visible_fixtures() {
    TestSuite *suite = create_test_suite();
    set_setup(suite, print_something_during_suite_setup);
    add_suite(suite, visible_test());
    add_suite(suite, visible_test());
    set_teardown(suite, print_something_during_suite_teardown);
    return suite;
}

int interference = 0;

Ensure(create_test_interference) {
    PRINT_LITERAL(create_test_interference, F_BLUE);
    interference = 1;
}

Ensure(prove_there_is_no_test_interference) {
    PRINT_LITERAL(prove_there_is_no_test_interference, F_BLUE);
    assert_equal(interference, 0);
}

Ensure(seg_fault) {
    PRINT_LITERAL(seg_fault, F_BLUE);
    int *p = NULL;
    (*p)++;
}

Ensure(time_out_in_only_one_second) {
    PRINT_LITERAL(time_out_in_only_one_second, F_BLUE);
    die_in(1);
    sleep(10);
}

TestSuite *isolation_tests() {
    TestSuite *suite = create_test_suite();
    add_test(suite, create_test_interference);
    add_test(suite, prove_there_is_no_test_interference);
    add_test(suite, seg_fault);
    add_test(suite, time_out_in_only_one_second);
    return suite;
}

static void takes_integer(int i) {
    mock(i);
}

Ensure(expectation_confirmed) {
    PRINT_LITERAL(expectation_confirmed, F_BLUE);
    expect(takes_integer, when(i, is_equal_to(3)));
    takes_integer(3);
}

Ensure(expectation_dashed) {
    PRINT_LITERAL(expectation_dashed, F_BLUE);
    expect(takes_integer, when(i, is_equal_to(3)));
    takes_integer(4);
}

static void mixed_parameters(int i, char *s) {
    mock(i, s);
}

Ensure(confirming_multiple_parameters_multiple_times) {
    PRINT_LITERAL(confirming_multiple_parameters_multiple_times, F_BLUE);
    expect(mixed_parameters, when(i, is_equal_to(1)), when(s, is_equal_to_string("Hello")));
    expect(mixed_parameters, when(i, is_equal_to(2)), when(s, is_equal_to_string("Goodbye")));
    mixed_parameters(1, "Hello");
    mixed_parameters(2, "Goodbye");
}

Ensure(breaking_multiple_parameters_multiple_times) {
    PRINT_LITERAL(breaking_multiple_parameters_multiple_times, F_BLUE);
    expect(mixed_parameters, when(i, is_equal_to(1)), when(s, is_equal_to_string("Hello")));
    expect(mixed_parameters, when(i, is_equal_to(2)), when(s, is_equal_to_string("Goodbye")));
    mixed_parameters(10, "Helloo");
    mixed_parameters(20, "Gooodbye");
}

Ensure(uncalled_expectations_should_throw_errors) {
    PRINT_LITERAL(uncalled_expectations_should_throw_errors, F_BLUE);
    expect(mixed_parameters, when(i, is_equal_to(1)), when(s, is_equal_to_string("Hello")));
}

Ensure(unexpected_call_should_throw_error) {
    PRINT_LITERAL(unexpected_call_should_throw_error, F_BLUE);
    never_expect(mixed_parameters);
    mixed_parameters(10, "Helloo");
}

TestSuite *mock_tests() {
    TestSuite *suite = create_test_suite();
    add_test(suite, expectation_confirmed);
    add_test(suite, expectation_dashed);
    add_test(suite, confirming_multiple_parameters_multiple_times);
    add_test(suite, breaking_multiple_parameters_multiple_times);
    add_test(suite, uncalled_expectations_should_throw_errors);
    add_test(suite, unexpected_call_should_throw_error);
    return suite;
}

Ensure(take_so_long_that_ctrl_c_is_needed) {
    PRINT_LITERAL(take_so_long_that_ctrl_c_is_needed, F_BLUE);
    sleep(10);
}
