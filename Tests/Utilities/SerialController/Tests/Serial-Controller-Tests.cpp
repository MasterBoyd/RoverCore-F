
#include "cgreen/cgreen.h"
#include "cgreen/mocks.h"
#include "stdio.h"
#include <string.h>
#include "stdint.h"
#include <stdbool.h>
#include "usb_serial.h"
#include "Universal-Unit-Testing-Methods.h"

using namespace cgreen;

Describe(SerialController);
BeforeEach(SerialController) {}
AfterEach(SerialController) {}
////////////////////////////////////////////////////////////////////////
//Send
////////////////////////////////////////////////////////////////////////

////SetToSend////

Ensure(SetToSend_Uint8_t) {
    PRINT_LITERAL(SetToSend_Uint8_t, F_CYAN);
    usb_serial_class serial;
    uint8_t Value = 255;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
Ensure(SetToSend_Uint16_t) {
    PRINT_LITERAL(SetToSend_Uint16_t, F_CYAN);
    usb_serial_class serial;
    uint16_t Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
Ensure(SetToSend_Uint32_t) {
    PRINT_LITERAL(SetToSend_Uint32_t, F_CYAN);
    usb_serial_class serial;
    uint32_t Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
// Ensure(SetToSend_Uint64_t) {
//     PRINT_LITERAL(SetToSend_Uint64_t, F_CYAN);
//     usb_serial_class serial;
//     uint64_t Value = 20000;

//     assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
//     assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
// }
Ensure(SetToSend_Int8_t) {
    PRINT_LITERAL(SetToSend_Int8_t, F_CYAN);
    usb_serial_class serial;
    int8_t Value = 100;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
Ensure(SetToSend_Int16_t) {
    PRINT_LITERAL(SetToSend_Int16_t, F_CYAN);
    usb_serial_class serial;
    int16_t Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
Ensure(SetToSend_Int32_t) {
    PRINT_LITERAL(SetToSend_Int32_t, F_CYAN);
    usb_serial_class serial;
    int32_t Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
// Ensure(SetToSend_Int64_t) {
//     PRINT_LITERAL(SetToSend_Int64_t, F_CYAN);
//     usb_serial_class serial;
//     int64_t Value = 20000;

//     assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
//     assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
// }
Ensure(SetToSend_Float) {
    PRINT_LITERAL(SetToSend_Float, F_CYAN);
    usb_serial_class serial;
    float Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}
Ensure(SetToSend_Double) {
    PRINT_LITERAL(SetToSend_Double, F_CYAN);
    usb_serial_class serial;
    double Value = 20000;

    assert_that(serial.SetToSend(20, &Value), is_equal_to(true));
    assert_that(serial.SetToSend(20, &Value), is_equal_to(false));
}

////CheckIfNew////

Ensure(CheckIfNew_Uint8_t) {
    PRINT_LITERAL(CheckIfNew_Uint8_t, F_CYAN);

    usb_serial_class serial;
    uint8_t Value = 255;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
Ensure(CheckIfNew_Uint16_t) {
    PRINT_LITERAL(CheckIfNew_Uint16_t, F_CYAN);

    usb_serial_class serial;
    uint16_t Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
Ensure(CheckIfNew_Uint32_t) {
    PRINT_LITERAL(CheckIfNew_Uint32_t, F_CYAN);

    usb_serial_class serial;
    uint32_t Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
// Ensure(CheckIfNew_Uint64_t) {
//     PRINT_LITERAL(CheckIfNew_Uint64_t, F_CYAN);

//     usb_serial_class serial;
//     uint64_t Value = 20000;
//     serial.SetToSend(20, &Value);

//     assert_that(serial.CheckIfNew(20), is_equal_to(true));
//     assert_that(serial.CheckIfNew(40), is_equal_to(false));
// }
Ensure(CheckIfNew_Int8_t) {
    PRINT_LITERAL(CheckIfNew_Int8_t, F_CYAN);

    usb_serial_class serial;
    int8_t Value = 100;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
Ensure(CheckIfNew_Int16_t) {
    PRINT_LITERAL(CheckIfNew_Int16_t, F_CYAN);

    usb_serial_class serial;
    int16_t Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
Ensure(CheckIfNew_Int32_t) {
    PRINT_LITERAL(CheckIfNew_Int32_t, F_CYAN);

    usb_serial_class serial;
    int32_t Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
// Ensure(CheckIfNew_Int64_t) {
//     PRINT_LITERAL(CheckIfNew_Int64_t, F_CYAN);

//     usb_serial_class serial;
//     int64_t Value = 20000;
//     serial.SetToSend(20, &Value);

//     assert_that(serial.CheckIfNew(20), is_equal_to(true));
//     assert_that(serial.CheckIfNew(40), is_equal_to(false));
// }
Ensure(CheckIfNew_Float) {
    PRINT_LITERAL(CheckIfNew_Float, F_CYAN);

    usb_serial_class serial;
    float Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}
Ensure(CheckIfNew_Double) {
    PRINT_LITERAL(CheckIfNew_Double, F_CYAN);

    usb_serial_class serial;
    double Value = 20000;
    serial.SetToSend(20, &Value);

    assert_that(serial.CheckIfNew(20), is_equal_to(true));
    assert_that(serial.CheckIfNew(40), is_equal_to(false));
}

////SerialSend////

Ensure(SerialSend_For_Uint8_t) {
    PRINT_LITERAL(SerialSend_For_Uint8_t, F_CYAN);

    usb_serial_class serial;
    uint8_t Value = 255;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,255\r\n"));
}
Ensure(SerialSend_For_Uint16_t) {
    PRINT_LITERAL(SerialSend_For_Uint16_t, F_CYAN);

    usb_serial_class serial;
    uint16_t Value = 20000;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
}
Ensure(SerialSend_For_Uint32_t) {
    PRINT_LITERAL(SerialSend_For_Uint32_t, F_CYAN);

    usb_serial_class serial;
    uint32_t Value = 20000;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
}
// Ensure(SerialSend_For_Uint64_t) {
//     PRINT_LITERAL(SerialSend_For_Uint64_t, F_CYAN);

//     usb_serial_class serial;
//     uint64_t Value = 20000;

//     serial.SetToSend('a', &Value);
//     serial.SerialSend('a');
//     serial.SerialSend('a');

//     assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
// }

Ensure(SerialSend_For_Int8_t) {
    PRINT_LITERAL(SerialSend_For_Int8_t, F_CYAN);

    usb_serial_class serial;
    int8_t Value = 127;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,127\r\n"));
}
Ensure(SerialSend_For_Int16_t) {
    PRINT_LITERAL(SerialSend_For_Int16_t, F_CYAN);

    usb_serial_class serial;
    int16_t Value = 20000;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
}
Ensure(SerialSend_For_Int32_t) {
    PRINT_LITERAL(SerialSend_For_Int32_t, F_CYAN);

    usb_serial_class serial;
    int32_t Value = 20000;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
}
// Ensure(SerialSend_For_Int64_t) {
//     PRINT_LITERAL(SerialSend_For_Int64_t, F_CYAN);

//     usb_serial_class serial;
//     int64_t Value = 20000;

//     serial.SetToSend('a', &Value);
//     serial.SerialSend('a');
//     serial.SerialSend('a');

//     assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000\r\n"));
// }

Ensure(SerialSend_For_Float) {
    PRINT_LITERAL(SerialSend_For_Float, F_CYAN);

    usb_serial_class serial;
    float Value = 20000.544;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000.544\r\n"));
}

Ensure(SerialSend_For_Double) {
    PRINT_LITERAL(SerialSend_For_Double, F_CYAN);

    usb_serial_class serial;
    double Value = 20000.54677892;

    serial.SetToSend('a', &Value);
    serial.SerialSend('a');

    assert_that(serial.ReturnCapture(), is_equal_to_string("@a,20000.54677892\r\n"));
}
////MovePointedToCopied////

Ensure(MovePointedToCopied) {
    PRINT_LITERAL(MovePointedToCopied, F_CYAN);

    usb_serial_class serial;
    uint32_t Value = 20000;
    serial.SetToSend('a', &Value);

    assert_that(serial.CheckIfNew('a'), is_equal_to(true));
    serial.MovePointedToCopied('a');

    Value = 400;
    assert_that(serial.CheckIfNew('a'), is_equal_to(true));
    serial.MovePointedToCopied('a');

    assert_that(serial.CheckIfNew('a'), is_equal_to(false));
}

Ensure(SerialAll) {
    PRINT_LITERAL(SerialAll, F_CYAN);

    usb_serial_class serial;
    float Value1 = 20000.547;
    uint32_t Value2 = 3452;
    uint32_t Value3 = 777;

    serial.SetToSend('a', &Value1);
    serial.SetToSend('b', &Value2);
    serial.SetToSend('c', &Value3);
    serial.SerialSendAll();
    //serial.SerialSendAll();

    assert_that(serial.ReturnCapture(), is_equal_to_string(
        "@a,20000.546\r\n@b,3452\r\n@c,777\r\n"));

    serial.ClearString();

    Value2 = 44444;
    serial.SerialSendAll();

    assert_that(serial.ReturnCapture(), is_equal_to_string(
        "@b,44444\r\n"));
}

// ////////////////////////////////////////////////////////////////////////
// //Receive
// ////////////////////////////////////////////////////////////////////////

////SetToReceive////

Ensure(SetToReceive_Uint8) {
    PRINT_LITERAL(SetToReceive_Uint8, F_CYAN);
    uint8_t Value1 = 200;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
Ensure(SetToReceive_Uint16) {
    PRINT_LITERAL(SetToReceive_Uint16, F_CYAN);
    uint16_t Value1 = 20000;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
Ensure(SetToReceive_Uint32) {
    PRINT_LITERAL(SetToReceive_Uint32, F_CYAN);
    uint32_t Value1 = 20000;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
// Ensure(SetToReceive_Uint64) {
//     PRINT_LITERAL(SetToReceive_Uint64, F_CYAN);
//     uint64_t Value1 = 20000;
//     usb_serial_class serial;

//     assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
//     assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
// }
Ensure(SetToReceive_Int8) {
    PRINT_LITERAL(SetToReceive_Int8, F_CYAN);
    int8_t Value1 = 100;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
Ensure(SetToReceive_Int16) {
    PRINT_LITERAL(SetToReceive_Int16, F_CYAN);
    int16_t Value1 = 20000;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
Ensure(SetToReceive_Int32) {
    PRINT_LITERAL(SetToReceive_Int32, F_CYAN);
    int32_t Value1 = 20000;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
// Ensure(SetToReceive_Int64) {
//     PRINT_LITERAL(SetToReceive_Int64, F_CYAN);
//     int64_t Value1 = 20000;
//     usb_serial_class serial;

//     assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
//     assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
// }
Ensure(SetToReceive_Float) {
    PRINT_LITERAL(SetToReceive_Float, F_CYAN);
    float Value1 = 20000.678;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
Ensure(SetToReceive_Double) {
    PRINT_LITERAL(SetToReceive_Double, F_CYAN);
    double Value1 = 20000.678;
    usb_serial_class serial;

    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(true));
    assert_that(serial.SetToReceive(10, &Value1), is_equal_to(false));
}
////DecodeAndApply////

Ensure(DecodeAndApply_Return_Uint8) {
    PRINT_LITERAL(DecodeAndApply_Return_Uint8, F_CYAN);
    uint8_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Return_Uint16) {
    PRINT_LITERAL(DecodeAndApply_Return_Uint16, F_CYAN);
    uint16_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Return_Uint32) {
    PRINT_LITERAL(DecodeAndApply_Return_Uint32, F_CYAN);
    uint32_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
// Ensure(DecodeAndApply_Return_Uint64) {
//     PRINT_LITERAL(DecodeAndApply_Return_Uint64, F_CYAN);
//     uint64_t Value1 = 0;
//     usb_serial_class serial;

//     serial.SetToReceive('a', &Value1);
//     assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
//     assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
//     assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
// }
Ensure(DecodeAndApply_Return_Int8) {
    PRINT_LITERAL(DecodeAndApply_Return_Int8, F_CYAN);
    int8_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Return_Int16) {
    PRINT_LITERAL(DecodeAndApply_Return_Int16, F_CYAN);
    int16_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Return_Int32) {
    PRINT_LITERAL(DecodeAndApply_Return_Int32, F_CYAN);
    int32_t Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
}
// Ensure(DecodeAndApply_Return_Int64) {
//     PRINT_LITERAL(DecodeAndApply_Return_Int64, F_CYAN);
//     int64_t Value1 = 0;
//     usb_serial_class serial;

//     serial.SetToReceive('a', &Value1);
//     assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
//     assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
//     assert_that(serial.DecodeAndApply("@a,555\r\n"), is_equal_to(true));
// }
Ensure(DecodeAndApply_Return_Float) {
    PRINT_LITERAL(DecodeAndApply_Return_Float,F_CYAN);
    float Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555.543\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Return_Double) {
    PRINT_LITERAL(DecodeAndApply_Return_Double,F_CYAN);
    double Value1 = 0;
    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    assert_that(serial.DecodeAndApply("a"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,"), is_equal_to(false));
    assert_that(serial.DecodeAndApply("@a,555.543345\r\n"), is_equal_to(true));
}
Ensure(DecodeAndApply_Data_Uint8) {
    PRINT_LITERAL(DecodeAndApply_Data_Uint8,F_CYAN);
    uint8_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,255\r\n");
    assert_that(Value1, is_equal_to(255));
}
Ensure(DecodeAndApply_Data_Uint16) {
    PRINT_LITERAL(DecodeAndApply_Data_Uint16,F_CYAN);
    uint16_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,65535\r\n");
    assert_that(Value1, is_equal_to(65535));
}
Ensure(DecodeAndApply_Data_Uint32) {
    PRINT_LITERAL(DecodeAndApply_Data_Uint32,F_CYAN);
    uint32_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,2147483646\r\n");
    assert_that(Value1, is_equal_to(2147483646));
}
// Ensure(DecodeAndApply_Data_Uint64) {
//     PRINT_LITERAL(DecodeAndApply_Data_Uint64,F_CYAN);
//     uint64_t Value1 = 0;

//     usb_serial_class serial;

//     serial.SetToReceive('a', &Value1);

//     serial.DecodeAndApply("@a,9223372036854775806\r\n");
//     assert_that(Value1, is_equal_to(9223372036854775806));
// }
Ensure(DecodeAndApply_Data_Int8) {
    PRINT_LITERAL(DecodeAndApply_Data_Int8,F_CYAN);
    int8_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,100\r\n");
    assert_that(Value1, is_equal_to(100));
}
Ensure(DecodeAndApply_Data_Int16) {
    PRINT_LITERAL(DecodeAndApply_Data_Int16,F_CYAN);
    int16_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,32767\r\n");
    assert_that(Value1, is_equal_to(32767));
}
Ensure(DecodeAndApply_Data_Int32) {
    PRINT_LITERAL(DecodeAndApply_Data_Int32,F_CYAN);
    int32_t Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);

    serial.DecodeAndApply("@a,2147483646\r\n");
    assert_that(Value1, is_equal_to(2147483646));
}
// Ensure(DecodeAndApply_Data_Int64) {
//     PRINT_LITERAL(DecodeAndApply_Data_Int64,F_CYAN);
//     int64_t Value1 = 0;

//     usb_serial_class serial;

//     serial.SetToReceive('a', &Value1);

//     serial.DecodeAndApply("@a,9223372036854775806\r\n");
//     assert_that(Value1, is_equal_to(9223372036854775806));
// }

Ensure(DecodeAndApply_Data_Float) {
    PRINT_LITERAL(DecodeAndApply_Data_Float,F_CYAN);
    significant_figures_for_assert_double_are(6);
    float Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    serial.DecodeAndApply("@a,666.433\r\n");
    assert_that_double((double)Value1, is_equal_to_double(666.432));
}

Ensure(DecodeAndApply_Data_Double) {
    PRINT_LITERAL(DecodeAndApply_Data_Double,F_CYAN);
    significant_figures_for_assert_double_are(6);
    double Value1 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    serial.DecodeAndApply("@a,666.433\r\n");
    assert_that_double((double)Value1, is_equal_to_double(666.432));
}

////CollectIncomming////

Ensure(CollectIncomming_Return) {
    PRINT_LITERAL(CollectIncomming, F_CYAN);
    usb_serial_class serial;

    assert_that(serial.CollectIncomming(), is_equal_to(false));

    serial.InsertDummySerial("@a,111|\r\n");

    assert_that(serial.CollectIncomming(), is_equal_to(true));
}

Ensure(CollectIncomming_Data_Uint8) {
    PRINT_LITERAL(CollectIncomming_Data_Uint8,F_CYAN);
    uint8_t Value1 = 0;
    uint8_t Value2 = 0;
    uint8_t Value3 = 0;
    uint8_t Value4 = 0;

    usb_serial_class serial;
    serial.SetToReceive('a' ,&Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);
    serial.InsertDummySerial(
        "@a,255|\r\n@b,255|\r\n@c,255|\r\n@d,255|\r\n");
    printf("%s", serial.GetIt());
    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(255));
    assert_that(Value2, is_equal_to(255));
    assert_that(Value3, is_equal_to(255));
    assert_that(Value4, is_equal_to(255));
}

Ensure(CollectIncomming_Data_Uint16) {
    PRINT_LITERAL(CollectIncomming_Data_Uint16,F_CYAN);
    uint16_t Value1 = 0;
    uint16_t Value2 = 0;
    uint16_t Value3 = 0;
    uint16_t Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a' , &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,65535|\r\n@b,65535|\r\n@c,65535|\r\n@d,65535|\r\n");

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(65535));
    assert_that(Value2, is_equal_to(65535));
    assert_that(Value3, is_equal_to(65535));
    assert_that(Value4, is_equal_to(65535));
}

Ensure(CollectIncomming_Data_Uint32) {
    PRINT_LITERAL(CollectIncomming_Data_Uint32,F_CYAN);
    uint32_t Value1 = 0;
    uint32_t Value2 = 0;
    uint32_t Value3 = 0;
    uint32_t Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a' , &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,777|\r\n@b,4444|\r\n@c,12345|\r\n@d,9876|\r\n");

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(777));
    assert_that(Value2, is_equal_to(4444));
    assert_that(Value3, is_equal_to(12345));
    assert_that(Value4, is_equal_to(9876));
}

// Ensure(CollectIncomming_Data_Uint64) {
//     PRINT_LITERAL(CollectIncomming_Data_Uint64,F_CYAN);
//     uint64_t Value1 = 0;
//     uint64_t Value2 = 0;
//     uint64_t Value3 = 0;
//     uint64_t Value4 = 0;

//     usb_serial_class serial;

//     serial.SetToReceive('a' , &Value1);
//     serial.SetToReceive('b', &Value2);
//     serial.SetToReceive('c', &Value3);
//     serial.SetToReceive('d', &Value4);

//     serial.InsertDummySerial(
//         "@a,777|\r\n@b,4444|\r\n@c,12345|\r\n@d,9876|\r\n");

//     serial.CollectIncomming();
//     assert_that(Value1, is_equal_to(777));
//     assert_that(Value2, is_equal_to(4444));
//     assert_that(Value3, is_equal_to(12345));
//     assert_that(Value4, is_equal_to(9876));
// }
Ensure(CollectIncomming_Data_Int8) {
    PRINT_LITERAL(CollectIncomming_Data_Int8,F_CYAN);
    int8_t Value1 = 0;
    int8_t Value2 = 0;
    int8_t Value3 = 0;
    int8_t Value4 = 0;

    usb_serial_class serial;
    serial.SetToReceive('a', &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,127|\r\n@b,127|\r\n@c,127|\r\n@d,127|\r\n");

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(127));
    assert_that(Value2, is_equal_to(127));
    assert_that(Value3, is_equal_to(127));
    assert_that(Value4, is_equal_to(127));
}

Ensure(CollectIncomming_Data_Int16) {
    PRINT_LITERAL(CollectIncomming_Data_Int16,F_CYAN);
    int16_t Value1 = 0;
    int16_t Value2 = 0;
    int16_t Value3 = 0;
    int16_t Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,32767|\r\n@b,32767|\r\n@c,32767|\r\n@d,32767|\r\n");

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(32767));
    assert_that(Value2, is_equal_to(32767));
    assert_that(Value3, is_equal_to(32767));
    assert_that(Value4, is_equal_to(32767));
}

Ensure(CollectIncomming_Data_Int32) {
    PRINT_LITERAL(CollectIncomming_Data_Int32,F_CYAN);
    int32_t Value1 = 0;
    int32_t Value2 = 0;
    int32_t Value3 = 0;
    int32_t Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a' , &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,777|\r\n@b,4444|\r\n@c,12345|\r\n@d,9876|\r\n");

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(777));
    assert_that(Value2, is_equal_to(4444));
    assert_that(Value3, is_equal_to(12345));
    assert_that(Value4, is_equal_to(9876));
}

// Ensure(CollectIncomming_Data_Int64) {
//     PRINT_LITERAL(CollectIncomming_Data_Int64,F_CYAN);
//     int64_t Value1 = 0;
//     int64_t Value2 = 0;
//     int64_t Value3 = 0;
//     int64_t Value4 = 0;

//     usb_serial_class serial;

//     serial.SetToReceive('a' , &Value1);
//     serial.SetToReceive('b', &Value2);
//     serial.SetToReceive('c', &Value3);
//     serial.SetToReceive('d', &Value4);

//     serial.InsertDummySerial(
//         "@a,777|\r\n@b,4444|\r\n@c,12345|\r\n@d,9876|\r\n");

//     serial.CollectIncomming();
//     assert_that(Value1, is_equal_to(777));
//     assert_that(Value2, is_equal_to(4444));
//     assert_that(Value3, is_equal_to(12345));
//     assert_that(Value4, is_equal_to(9876));
// }

// Ensure(CollectIncomming_Data_Multiple_Int64) {
//     PRINT_LITERAL(CollectIncomming_Data_Multiple_Int64,F_CYAN);
//     int64_t Value1 = 0;
//     int64_t Value2 = 0;

//     usb_serial_class serial;

//     serial.SetToReceive('a' , &Value1);
//     serial.SetToReceive('b', &Value2);

//     serial.InsertDummySerial(
//         "@a,777|\r\n@b,4444|\r\n");
//     serial.CollectIncomming();

//     assert_that(Value1, is_equal_to(777));
//     assert_that(Value2, is_equal_to(4444));

//     serial.InsertDummySerial(
//         "@a,454800|\r\n@b,45454444|\r\n");
//     serial.CollectIncomming();

//     assert_that(Value1, is_equal_to(454800));
//     assert_that(Value2, is_equal_to(45454444));

//     serial.InsertDummySerial(
//         "@a,3554800|\r\n@b,25477444|\r\n");
//     serial.CollectIncomming();

//     assert_that(Value1, is_equal_to(3554800));
//     assert_that(Value2, is_equal_to(25477444));
// }

Ensure(CollectIncomming_Data_Float) {
    PRINT_LITERAL(CollectIncomming_Data_Float,F_CYAN);
    significant_figures_for_assert_double_are(6);
    float Value1 = 0;
    float Value2 = 0;
    float Value3 = 0;
    float Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,777.7007|\r\n@b,4444.4004|\r\n@c,12345.6006|\r\n@d,9876.5005|\r\n");

    serial.CollectIncomming();
    assert_that_double((double)Value1, is_equal_to_double(777.7007));
    assert_that_double((double)Value2, is_equal_to_double(4444.4004));
    assert_that_double((double)Value3, is_equal_to_double(12345.6006));
    assert_that_double((double)Value4, is_equal_to_double(9876.5005));
}

Ensure(CollectIncomming_Data_Double) {
    PRINT_LITERAL(CollectIncomming_Data_Double,F_CYAN);
    significant_figures_for_assert_double_are(6);
    double Value1 = 0;
    double Value2 = 0;
    double Value3 = 0;
    double Value4 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a', &Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    serial.SetToReceive('d', &Value4);

    serial.InsertDummySerial(
        "@a,777.7007|\r\n@b,4444.4004|\r\n@34234|\r@@@@|\r@|\n@c,12345.6006|\r\n@d,9876.5005|\r\n");

    serial.CollectIncomming();
    assert_that_double((double)Value1, is_equal_to_double(777.7007));
    assert_that_double((double)Value2, is_equal_to_double(4444.4004));
    assert_that_double((double)Value3, is_equal_to_double(12345.6006));
    assert_that_double((double)Value4, is_equal_to_double(9876.5005));
}

Ensure(CollectIncomming_Data_All) {
    PRINT_LITERAL(CollectIncomming_Data_All,F_CYAN);
    significant_figures_for_assert_double_are(6);
    uint8_t     Value1 = 0;
    uint16_t    Value2 = 0;
    uint32_t    Value3 = 0;
    //uint64_t    Value4 = 0;
    int8_t      Value5 = 0;
    int16_t     Value6 = 0;
    int32_t     Value7 = 0;
    //int64_t     Value8 = 0;
    float       Value9 = 0;
    double      Value10 = 0;

    usb_serial_class serial;

    serial.SetToReceive('a' ,&Value1);
    serial.SetToReceive('b', &Value2);
    serial.SetToReceive('c', &Value3);
    //serial.SetToReceive('d', &Value4);
    serial.SetToReceive('e' ,&Value5);
    serial.SetToReceive('f', &Value6);
    serial.SetToReceive('g', &Value7);
    //serial.SetToReceive('h', &Value8);
    serial.SetToReceive('i', &Value9);
    serial.SetToReceive('j', &Value10);

    serial.InsertDummySerial(
        "@a,255|\r\n@b,65535|\r\n@c,2147483646|\r\n@e,-127|\r\n@f,-32768|\r\n@g,-2147483646|\r\n@i,4444.4004|\r\n@j,9876.5005|\r\n");

    //@d,9223372036854775806|\r\n
    //@h,-9223372036854775806|\r\n

    serial.CollectIncomming();
    assert_that(Value1, is_equal_to(255));
    assert_that(Value2, is_equal_to(65535));
    assert_that(Value3, is_equal_to(2147483646));
    //assert_that(Value4, is_equal_to(9223372036854775806));
    assert_that(Value5, is_equal_to(-127));
    assert_that(Value6, is_equal_to(-32768));
    assert_that(Value7, is_equal_to(-2147483646));
    //assert_that(Value8, is_equal_to(-9223372036854775806));
    assert_that_double((double)Value9, is_equal_to_double(4444.4004));
    assert_that_double((double)Value10, is_equal_to_double(9876.5005));
}


Ensure(Connection_Status) {
    PRINT_LITERAL(Connection_Status,F_CYAN);

    usb_serial_class serial;

    serial.InitiateConnMonitor(100, 200);

    assert_that(serial.CheckConnStatus(), is_equal_to(false));
    
    serial.InsertDummySerial("@~,0|\r\n");
    serial.CollectIncomming();
    serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(false));

     serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(false));


    serial.InsertDummySerial("@~,1|\r\n");
    serial.CollectIncomming();
    serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(true));

    serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(true));

    serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(false));

    serial.InsertDummySerial("@~,2|\r\n");
    serial.CollectIncomming();
    serial.HandelConnMonitor();
    assert_that(serial.CheckConnStatus(), is_equal_to(true));

    // for(int i = 0; i < 10; i++)
    // {
    //     serial.HandelConnMonitor();
    //     assert_that(serial.CheckConnStatus(), is_equal_to(true));
    // }
    // serial.HandelConnMonitor();
    // assert_that(serial.CheckConnStatus(), is_equal_to(false));
    // serial.HandelConnMonitor();
    // assert_that(serial.CheckConnStatus(), is_equal_to(false));
    // serial.InsertDummySerial("@~,1\r\n");
    // serial.CollectIncomming();
    // for(int i = 0; i < 10; i++)
    // {
    //     serial.HandelConnMonitor();
    //     assert_that(serial.CheckConnStatus(), is_equal_to(true));
    // }
    // serial.HandelConnMonitor();
    // assert_that(serial.CheckConnStatus(), is_equal_to(false));


    // for(int i = 0; i < 10; i++)
    // {
    //     status = serial.CheckConnection(100, 1000);
    //     assert_that(status, is_equal_to(true));
    // }


}


TestSuite *Serial_Controller_Tests() {
    printf("Suite (Serial_Controller_Tests)\n");
    TestSuite *suite = create_test_suite();

    add_test(suite, Connection_Status);
    add_test(suite, CollectIncomming_Data_All);
    add_test(suite, SetToSend_Uint8_t);
    add_test(suite, SetToSend_Uint16_t);
    add_test(suite, SetToSend_Uint32_t);
    //add_test(suite, SetToSend_Uint64_t);
    add_test(suite, SetToSend_Int8_t);
    add_test(suite, SetToSend_Int16_t);
    add_test(suite, SetToSend_Int32_t);
    //add_test(suite, SetToSend_Int64_t);
    add_test(suite, SetToSend_Float);
    add_test(suite, SetToSend_Double);

    add_test(suite, CheckIfNew_Uint8_t);
    add_test(suite, CheckIfNew_Uint16_t);
    add_test(suite, CheckIfNew_Uint32_t);
   //add_test(suite, CheckIfNew_Uint64_t);
    add_test(suite, CheckIfNew_Int8_t);
    add_test(suite, CheckIfNew_Int16_t);
    add_test(suite, CheckIfNew_Int32_t);
   // add_test(suite, CheckIfNew_Int64_t);
    add_test(suite, CheckIfNew_Float);
    add_test(suite, CheckIfNew_Double);

    add_test(suite, SerialSend_For_Uint8_t);
    add_test(suite, SerialSend_For_Uint16_t);
    add_test(suite, SerialSend_For_Uint32_t);
    //add_test(suite, SerialSend_For_Uint64_t);
    add_test(suite, SerialSend_For_Int8_t);
    add_test(suite, SerialSend_For_Int16_t);
    add_test(suite, SerialSend_For_Int32_t);
    //add_test(suite, SerialSend_For_Int64_t);
    add_test(suite, SerialSend_For_Float);
    add_test(suite, SerialSend_For_Double);

    add_test(suite, MovePointedToCopied);

    add_test(suite, SerialAll);

    add_test(suite, SetToReceive_Uint8);
    add_test(suite, SetToReceive_Uint16);
    add_test(suite, SetToReceive_Uint32);
    //add_test(suite, SetToReceive_Uint64);
    add_test(suite, SetToReceive_Int8);
    add_test(suite, SetToReceive_Int16);
    add_test(suite, SetToReceive_Int32);
    //add_test(suite, SetToReceive_Int64);
    add_test(suite, SetToReceive_Float);
    add_test(suite, SetToReceive_Double);

    add_test(suite, DecodeAndApply_Return_Uint8);
    add_test(suite, DecodeAndApply_Return_Uint16);
    add_test(suite, DecodeAndApply_Return_Uint32);
   //add_test(suite, DecodeAndApply_Return_Uint64);
    add_test(suite, DecodeAndApply_Return_Int8);
    add_test(suite, DecodeAndApply_Return_Int16);
    add_test(suite, DecodeAndApply_Return_Int32);
    //add_test(suite, DecodeAndApply_Return_Int64);
    add_test(suite, DecodeAndApply_Return_Float);
    add_test(suite, DecodeAndApply_Return_Double);

    add_test(suite, DecodeAndApply_Data_Uint8);
    add_test(suite, DecodeAndApply_Data_Uint16);
    add_test(suite, DecodeAndApply_Data_Uint32);
    //add_test(suite, DecodeAndApply_Data_Uint64);
    add_test(suite, DecodeAndApply_Data_Int8);
    add_test(suite, DecodeAndApply_Data_Int16);
    add_test(suite, DecodeAndApply_Data_Int32);
    //add_test(suite, DecodeAndApply_Data_Int64);
    add_test(suite, DecodeAndApply_Data_Float);
    add_test(suite, DecodeAndApply_Data_Double);

    add_test(suite, CollectIncomming_Return);

    add_test(suite, CollectIncomming_Data_Uint8);
    add_test(suite, CollectIncomming_Data_Uint16);
    add_test(suite, CollectIncomming_Data_Uint32);
    //add_test(suite, CollectIncomming_Data_Uint64);
    add_test(suite, CollectIncomming_Data_Int8);
    add_test(suite, CollectIncomming_Data_Int16);
    add_test(suite, CollectIncomming_Data_Int32);
    //add_test(suite, CollectIncomming_Data_Int64);
    //add_test(suite, CollectIncomming_Data_Multiple_Int64);
    add_test(suite, CollectIncomming_Data_Float);
    add_test(suite, CollectIncomming_Data_Double);


    return suite;
}