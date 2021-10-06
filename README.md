# README #



### Framework ###

##### General #####
* The framework make commands ONLY work in Linux. If you have a windows computer. Please install a VM of Linux using VM Workstation. If your computer is not fast enough for a VM then you will have to duel boot. Also, for VM's make sure you use a 32 bit version of Linux.

##### Hierarchy #####
* Build - The folder where all the files used in the build process are dumped. Also contains the final hex files for the Teensy and executables for unit testing.
* Core - Contains the Teensy Drivers, FreeRTOS files, and any utility classes.
* Projects - Holds the source code for the different user projects. 
* Tests - Holds the Tests and Stubs for each user project.
* Tools - Contains the Arm compiler that compiles all the source code into hex files.

##### Creating a New Project #####
1. Create a new project folder in the **Project directory** by copying the ProtoNeuron folder with a different name.
2. Create a new project folder in the **Test directory** by copying the ProtoNeuron folder with the same name as the previously created name from step 1.

### Unit Testing ###

##### Basics #####

* The framework that is apart of Rovercore-F is **Cgreen** https://github.com/cgreen-devs/cgreen 
* It is organized into two levels, Suites and Tests.

##### Suites #####
* A Test Suite is a system of tests around a specific feature. An example is a Test Suite for the SerialController class.
* To Create a new Suite you first create a file in your test location rovercore-f/Tests/YourProject/Tests
* Inside the file that was created put the following:
```C++
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"

using namespace cgreen;

TestSuite *Serial_Controller_Tests() {
    TestSuite *suite = create_test_suite();

    return suite;
}
```
* With the Suite File Created, you then need to add the suite to the main for it to be run. 
* In the main file which is in the same file location as the Tests folder and Stubs folder, You need to create the Test Suite Object and add it to be run.
* By removing the comments in the following snippets of code is how you add the Test Suite to the main file.
```C++
#include "cgreen/cgreen.h"
#include <cgreen/mocks.h>

//TestSuite *Serial_Controller_Tests();

using namespace cgreen;

int main(int argc, char **argv) {
  TestSuite *suite = create_test_suite();

  //add_suite(suite, Serial_Controller_Tests());
  
  if (argc > 1) {
    return run_single_test(suite, argv[1], create_text_reporter());
  }
  return run_test_suite(suite, create_text_reporter());
}
```
##### Tests #####
* Inside of your suite of tests, you add a test by adding the following sections that are commented out.
```C++
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"

using namespace cgreen;

//Ensure(NAME_OF_YOUR_TEST)
//{

//}
TestSuite *Serial_Controller_Tests() {
    TestSuite *suite = create_test_suite();
    //add_test(suite, NAME_OF_YOUR_TEST);
    return suite;
}
```
* In side of your test case you will be comparing your expected outputs with your actual outputs.
* To do the actual comparison, Cgreen has a function called assert_that(Value, Comparison Macro);
* The assert_that() call is the primary part of an assertion, which is complemented with a constraint, in this case is_equal_to(), as a parameter. This makes a very fluent interface to the asserts, that actually reads like English.
* Below is a list of all the comparision macros that can be used with Cgreen.

```
is_true  //evaluates to true

is_false //evaluates to false

is_null  //equals null

is_non_null // is a non null value

is_equal_to(value) //'== value'

is_not_equal_to(value) //'!= value'

is_greater_than(value) //'> value'

is_less_than(value) //'< value'
    
is_equal_to_contents_of(pointer, size) //matches the data pointed to by pointer to a size of size bytes

is_not_equal_to_contents_of(pointer, size) //does not match the data pointed to by pointer to a size of size bytes   

is_equal_to_string(value) //are equal when compared using strcmp()

is_not_equal_to_string(value) //are not equal when compared using strcmp()

contains_string(value) //contains value when evaluated using strstr()

does_not_contain_string(value) //does not contain value when evaluated using strstr()

begins_with_string(value) //starts with the string value

is_equal_to_double(value) //are equal to value within the number of significant digits (which you can set with a call to significant_figures_for_assert_double_are(int figures))

is_not_equal_to_double(value) //are not equal to value within the number of significant digits

is_less_than_double(value) //< value withing the number of significant digits

is_greater_than_double(value) //> value within the number of significant digits
```
* In the case of comparisons with doubles, the number of significant digits that actually get compared can be selected with the below function call.
```
significant_figures_for_assert_double_are(6); // In this case, the comparison is set to 6 significant figures.
```
* Below is an example of what a full Unit test could look like:
```
Ensure(Validate_DecodeAndApply_float_Data_Edit) {
    //Prints a variable's name to the console in a specific color.
    PRINT_LITERAL(Validate_DecodeAndApply_float_Data_Edit, F_CYAN);

    //Compares 6 significant figures in all asserts for doubles.
    significant_figures_for_assert_double_are(6);
    
    //Setup and function calls to get the function under test set up.
    float Value1 = 0;
    usb_serial_class serial;
    serial.SetToReceive(10, &Value1);
    
    //The function under test
    serial.DecodeAndApply("@10,666.433\r\n");

    //The assert that compares the actual output to the expected output
    assert_that_double((double)Value1, is_equal_to_double(666.432));
}
```
##### Stubs #####



### Setting Up Teensy Loader ###

##### For Linux #####

1. Install "Teensy Program" for your OS from https://www.pjrc.com/teensy/loader.html
2. Create a folder named "Loader" in rovercore-f.
3. Unzip the download and put in the Loader folder.
4. leave the Rovercore-F project directory.
5. Create a file called 49-teensy.rules
6. In this file copy the text at https://www.pjrc.com/teensy/49-teensy.rules and put in the file you just made.
7. Execute the command: `sudo cp 49-teensy.rules /etc/udev/rules.d/`

##### For Windows #####

1. Download and install tinsyduino at https://www.pjrc.com/teensy/td_download.html
2. In your Ardunio folder, find an application named teensy.exe. Its found at: C:\Program Files (x86)\Arduino\hardware\tools
3. Create a folder named "Loader" in rovercore-f.
4. Move that application to the Loader folder that you previously created in rovercore-f.
5. To use the loader, simply launch the teensy application.


### Make Commands ###

* `make help` - Lists out the makefile commands.
* `make all_projects` - Creates a hex file for all projects.
* `make all_unit_test` - Creates all unit test executables.
* `make project PROJ=Project` - Creates a .hex for only the target project.
* `make unit_test PROJ=Project` - Creates a the unit test executable for only the target project.
* `make clean PPROJ=Project` - Cleans the target project.
* `make spotless` - Cleans the entire repo.