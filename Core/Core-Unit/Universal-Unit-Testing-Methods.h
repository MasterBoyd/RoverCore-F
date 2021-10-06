#ifndef Universal_Unit_Testing_Methods_h
#define Universal_Unit_Testing_Methods_h

#include <stdio.h>


//fonts color
#define F_RED     "\x1b[31m"
#define F_GREEN   "\x1b[32m"
#define F_YELLOW  "\x1b[33m"
#define F_BLUE    "\x1b[34m"
#define F_MAGENTA "\x1b[35m"
#define F_CYAN    "\x1b[36m"
#define F_RESET   "\x1b[0m"

//end color
#define F_NONE        "\033[0m"

#define LOG_RED(X) printf("%s %s %s",Color_Red,X,Color_end)

//#define PRINT_LITERAL(var) printf(F_BLUE "\tRunning Test: (" #var ")" F_RESET "\n");
#define PRINT_LITERAL(var, color) printf(color "\tRunning Test: (" #var ")" F_RESET "\n");
#define PRINT_STRING(var, color)  printf(color "%s\n" F_RESET, var);
#define PRINT_UINT32(var, color)  printf(color "%d\n" F_RESET, (int)var);


#endif // Universal_Unit_Testing_Methods.h