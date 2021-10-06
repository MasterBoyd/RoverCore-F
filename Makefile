#************************************************************************
# Make file adjustable inputs
#************************************************************************

PROJ                    ?= Pods

#************************************************************************
# Static Directories
#************************************************************************

# Stores all .o, .d files
OBJ_DIR                 = Build/Objects
OBJ_DIR_SOURCE          = Build/Objects/Source
OBJ_DIR_UNIT            = Build/Objects/Unit
# Stores all .elf and .hex files
BIN_DIR                 = Build/Binaries
# Stores all .exe Unit Test Executables
EXE_DIR                 = Build/Unit
# Directory for storing projects
PROJ_DIR                = Projects
# Directory for common files
LIB_DIR                 = Core/Core-Source
#Unit testing Universal Methods
UNIT_METH_DIR			= Core/Core-Unit
# Directory for Tests
TEST_DIR                = Tests
# path location for the arm-none-eabi compiler
COMPILERPATH 			= Tools/arm/bin
# names for the Linux compiler programs
CC_UNIT                 = gcc
CPP_UNIT                = g++

#************************************************************************
# Dynamic Directories
#************************************************************************

# Directory for Teensy Core Libraries
TEENSY_SOURCE 			= $(LIB_DIR)/Teensy

# Directory for Source Code and Source Code Tests
PROJECT_SOURCE          = $(PROJ_DIR)/$(PROJ)/Source
PROJECT_TEST 			= $(TEST_DIR)/$(PROJ)
# Directory for Utilities Source Code and Utilities Source Code Tests
UTILITIES_SOURCE        = $(LIB_DIR)/Utilities
UTILITIES_TEST   		= $(TEST_DIR)/Utilities
# names for the ARM compiler programs
CC                      = arm-none-eabi-gcc
CXX                     = arm-none-eabi-g++
OBJCOPY                 = arm-none-eabi-objcopy
SIZE                    = arm-none-eabi-size

#************************************************************************
# Flags
#************************************************************************

#--------------------Unit---------------------

UNIT_TEST_FLAGS         = -lcgreen --verbose

#Compiler options for C++ Only
CPPFLAGS_UNIT           = -std=gnu++11
#compiler options for C only
CFLAGS_UNIT             = -std=gnu11
#Compiler options for C and C++
CXXFLAGS_UNIT           = -g -Wall -lcgreen\
						-I"$(PROJECT_SOURCE)" \
						-I"$(PROJECT_SOURCE)/Source" \
						-I"$(PROJECT_TEST)" \
						-I"$(PROJECT_TEST)/Tests" \
						-I"$(PROJECT_TEST)/Stubs" \
						-I"$(UTILITIES_SOURCE)/SerialController" \
						-I"$(UTILITIES_TEST)/SerialController/Tests" \
						-I"$(UTILITIES_TEST)/SerialController/Stubs" \
						-I"$(UTILITIES_SOURCE)/Words-Test" \
						-I"$(UTILITIES_TEST)/Words-Test/Tests" \
						-I"$(UTILITIES_TEST)/Words-Test/Stubs" \
						-I"$(UTILITIES_SOURCE)/PID" \
						-I"$(UNIT_METH_DIR)" 

#--------------------Arm---------------------		

# set your MCU type here, or make command line `
# MK20DX256 for Teensy 3.2` or mk64fx512 FOR Teensy 3.5
MCU                     = MK20DX256
MCU_L                   = mk20dx256
MCU_LD 					= $(LIB_DIR)/Teensy/$(MCU_L).ld

# The name of your project (used to name the compiled .hex file)
EXECUTABLE          	= $(BIN_DIR)/$(PROJ)/$(PROJ).elf
HEX                 	= $(EXECUTABLE:.elf=.hex)

# configurable options
OPTIONS 				= -DF_CPU=48000000 -DUSB_SERIAL_HID  -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE
#-DUSB_EVERYTHING

# options needed by many Arduino libraries to configure for Teensy 3.0
OPTIONS 				+= -D__$(MCU)__ -DARDUINO=10600 -DTEENSYDUINO=121

# CPPFLAGS = compiler options for C and C++
CPPFLAGS 				= -Wall -g -Os -mcpu=cortex-m4 -mthumb -MMD $(OPTIONS) -I. \
						-I"$(LIB_DIR)/Teensy" \
						-I"$(LIB_DIR)/Teensy/avr" \
						-I"$(LIB_DIR)/FreeRTOS_ARM/src" \
						-I"$(UTILITIES_SOURCE)/SerialController" \
						-I"$(UTILITIES_SOURCE)/CommonFunctions" \
						-I"$(UTILITIES_SOURCE)/PID" \
						-I"$(TEENSY_SOURCE)/SdFat" \
						-I"$(TEENSY_SOURCE)/SdFat/FatLib" \
						-I"$(TEENSY_SOURCE)/i2c_t3-master" \
						-I"$(PROJ_DIR)/$(PROJ)" \
						-I"$(PROJ_DIR)/$(PROJ)/Source" \

# compiler options for C++ only
CXXFLAGS 				= -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS 					=

# linker options
LDFLAGS 				= -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=cortex-m4 -mthumb -T$(MCU_LD)

# additional libraries to link
LIBS = -lm

#************************************************************************
# List Creation
#************************************************************************

#--------------------Unit---------------------

PROJECT_SOURCE_LIST     = $(shell find $(PROJECT_SOURCE) -name '*.c' -o -name '*.cpp')
PROJECT_TEST_LIST      	= $(shell find $(PROJECT_TEST) -name '*.c' -o -name '*.cpp')
UNIT_METH_DIR_LIST		= $(shell find $(UNIT_METH_DIR) -name '*.c' -o -name '*.cpp')

UTILITIES_SOURCE_LIST  	= $(shell find $(UTILITIES_SOURCE) -name '*.c' -o -name '*.cpp')
UTILITIES_TEST_LIST    	= $(shell find $(UTILITIES_TEST) -name '*.c' -o -name '*.cpp')


# List of all Utilitiy Files for individual compilation
COMPILABLES_UTIL 		= $(UTILITIES_SOURCE_LIST) $(UTILITIES_TEST_LIST)
# List of all Project Files for individual compilation
COMPILABLES_UNIT 		= $(PROJECT_SOURCE_LIST) $(PROJECT_TEST_LIST) $(UNIT_METH_DIR_LIST)

#Create lists of all compilable object files
UTIL_TEST_OBJECTS1 		= $(patsubst $(PROJ_DIR)/$(PROJ)/Source,	$(PROJ)/%,	$(COMPILABLES_UTIL)) 
UTIL_TEST_OBJECTS2 		= $(patsubst $(TEST_DIR)/%,					%,			$(UTIL_TEST_OBJECTS1)) 
UTIL_TEST_OBJECTS3 		= $(patsubst $(LIB_DIR)/%,					%,			$(UTIL_TEST_OBJECTS2)) 
UTIL_TEST_OBJECTS4 		= $(patsubst %.c,							%.o,		$(patsubst %.cpp,%.o,$(UTIL_TEST_OBJECTS3)))
UTIL_TEST_OBJECTS  		= $(addprefix  $(OBJ_DIR_UNIT)/, $(UTIL_TEST_OBJECTS4))
#Create lists of all compilable object files
UNIT_TEST_OBJECTS1 		= $(patsubst $(PROJ_DIR)/$(PROJ)/Source/%,	$(PROJ)/%,	$(COMPILABLES_UNIT)) 
UNIT_TEST_OBJECTS2 		= $(patsubst $(TEST_DIR)/%,					%,          $(UNIT_TEST_OBJECTS1)) 
UNIT_TEST_OBJECTS4 		= $(patsubst %.c,							%.o, 		$(patsubst %.cpp,%.o,$(UNIT_TEST_OBJECTS2)))
UNIT_TEST_OBJECTS  		= $(addprefix  $(OBJ_DIR_UNIT)/,                		$(UNIT_TEST_OBJECTS4))

#Crete List of All projects and create HEXNOT files as dependencies.
DIRECTORIES 			= $(shell find $(PROJ_DIR) -maxdepth 1 -type d)
DIRECTORIES_NAMES		= $(subst $(PROJ_DIR),, $(subst $(PROJ_DIR)/,, $(DIRECTORIES)))

UTILITIES 				= $(shell find $(UTILITIES_SOURCE) -maxdepth 1 -type d)
UTILITIES_NAMES 		= $(subst $(UTILITIES_SOURCE),, $(subst $(UTILITIES_SOURCE)/,, $(UTILITIES)))

HEXNOT1 				= $(subst $(PROJ_DIR),, $(subst $(PROJ_DIR)/,, $(DIRECTORIES)))
HEXNOT2 				= $(addprefix /, $(HEXNOT1))
HEXNOT3 				= $(join $(HEXNOT2), $(HEXNOT2))
HEXNOT4 				= $(addprefix $(BIN_DIR), $(HEXNOT3))
HEXUNIT 				= $(addsuffix .hexUNIT, $(HEXNOT4))

#--------------------Arm---------------------	

# List of all common files
LIBRARIES       		= $(shell find $(LIB_DIR) -name '*.c' -o -name '*.cpp')

# List of all project files
SOURCES 				= $(shell find $(PROJ_DIR)/$(PROJ) -name '*.c' -o -name '*.cpp')

# List of all project and common files
COMPILABLES     		= $(LIBRARIES) $(SOURCES)

# creates a list of all compilable files with a .o end and adds the proper prefix.
OBJECTS 	    		= $(addprefix  $(OBJ_DIR_SOURCE)/, $(patsubst $(PROJ_DIR)/%,%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(COMPILABLES)))))

# creates a list of all project files with a proper path name.
TARGET          		= $(BIN_DIR)/$(PROJ)/$(PROJ)

# create a list of the individual projects and adds a proper prefix to be able to compile all projects at the same time.
HEXNOT 					= $(addsuffix .hexNOT, $(HEXNOT4))


#************************************************************************
# Recipes for the entire process
#************************************************************************

#--------------------Unit---------------------

#Location of the output Unit testing executables.
UTIL_TARGET 			= $(BIN_DIR)/Utilities/Utilities
UTIL_HEXUNIT 			= $(addsuffix .hexUNIT, $(UTIL_TARGET))

# turns recipes into procedures
.PHONY: unit_test all_unit_test clean spotless
help:
	@echo -e 'Projects Found: \n$(DIRECTORIES_NAMES)\n'
	@echo -e 'Utilities Found: \n$(UTILITIES_NAMES)\n'
	@echo -e '------------------------------------'
	@echo -e '------------COMMANDS----------------'
	@echo -e '------------------------------------'
	@echo 'Build  All Projects:'
	@echo '		make all_projects'
	@echo 'Build  All Unit Tests:'
	@echo '		make all_unit_test'
	@echo 'Delete All Project Build Files:'
	@echo '		make spotless'
	@echo 'Build  Individual Projects:'
	@echo '		make project PROJ=Project'
	@echo 'Build  Individual Unit Test:'
	@echo '		make unit_test PROJ=Project'
	@echo 'Delete Individual Project Build Files:'
	@echo '		make clean PROJ=Project'

all:
	$(MAKE) spotless 
	$(MAKE) all_unit_test 
	$(MAKE) all_projects 

unit:
	$(MAKE) spotless 
	$(MAKE) all_unit_test 
	./Build/Binaries/Arm/Arm.exe

it:
	$(MAKE) spotless 
	$(MAKE) project PROJ=Arm 

proj:
	$(MAKE) spotless 
	$(MAKE) all_projects 

print:
	@echo -e 'COMPILABLES_UNIT: \n$(COMPILABLES_UNIT)\n\n'
	@echo -e 'UNIT_TEST_OBJECTS1  \n$(UNIT_TEST_OBJECTS1)\n\n'
	@echo -e 'UNIT_TEST_OBJECTS2  \n$(UNIT_TEST_OBJECTS2)\n\n'
	@echo -e 'UNIT_TEST_OBJECTS4  \n$(UNIT_TEST_OBJECTS4)\n\n'
	@echo -e 'UNIT_TEST_OBJECTS   \n$(UNIT_TEST_OBJECTS)\n\n' 
	@echo -e 'UNIT_METH_DIR 	  \n$(UNIT_METH_DIR)\n\n'
	@echo -e 'PROJECT_SOURCE 	  \n$(PROJECT_SOURCE)\n\n'

	
test:
	@echo -e 'HEXNOT1: \n$(HEXNOT1)\n\n'
	@echo -e 'HEXNOT2: \n$(HEXNOT2)\n\n'
	@echo -e 'HEXNOT3: \n$(HEXNOT3)\n\n'
	@echo -e 'HEXNOT4: \n$(HEXNOT4)\n\n'
	@echo -e 'HEXUNIT: \n$(HEXUNIT)\n\n'

	@echo -e 'UTIL_TEST_OBJECTS1  \n$(UTIL_TEST_OBJECTS1)\n\n'
	@echo -e 'UTIL_TEST_OBJECTS2  \n$(UTIL_TEST_OBJECTS2)\n\n'
	@echo -e 'UTIL_TEST_OBJECTS3  \n$(UTIL_TEST_OBJECTS3)\n\n'
	@echo -e 'UTIL_TEST_OBJECTS4  \n$(UTIL_TEST_OBJECTS4)\n\n'
	@echo -e 'UTIL_TEST_OBJECTS   \n$(UTIL_TEST_OBJECTS)\n\n' 

	@echo -e 'COMPILABLES_UTIL: 	\n$(COMPILABLES_UTIL)\n'
	@echo -e 'UTIL_TEST_OBJECTS1: 	\n$(UTIL_TEST_OBJECTS1)\n'
	@echo -e 'UTIL_TEST_OBJECTS2: 	\n$(UTIL_TEST_OBJECTS2)\n'
	@echo -e 'UTIL_TEST_OBJECTS4: 	\n$(UTIL_TEST_OBJECTS4)\n'
	@echo -e 'UTIL_TEST_OBJECTS:  	\n$(UTIL_TEST_OBJECTS)\n'

	@echo -e 'COMPILABLES_UNIT: 	\n$(COMPILABLES_UNIT)\n'
	@echo -e 'UNIT_TEST_OBJECTS1: 	\n$(UNIT_TEST_OBJECTS1)\n'
	@echo -e 'UNIT_TEST_OBJECTS2: 	\n$(UNIT_TEST_OBJECTS2)\n'
	@echo -e 'UNIT_TEST_OBJECTS4: 	\n$(UNIT_TEST_OBJECTS4)\n'
	@echo -e 'UNIT_TEST_OBJECTS:  	\n$(UNIT_TEST_OBJECTS)\n'


all_unit_test: $(HEXUNIT) $(UTIL_HEXUNIT)

unit_test: $(OBJ_DIR_UNIT) $(BIN_DIR) $(TARGET).exe

%.hexUNIT:
	@echo 'Building Project: $@'
	$(MAKE) unit_test PROJ=$(basename $(notdir $@))
	touch $@
	@echo -e '\n\nSuccessfully Compiled All Unit Tests \n\n'
	

$(TARGET).exe: $(UNIT_TEST_OBJECTS)
	@echo -e '\n\n$(TARGET)\n\n'
	@echo 'Building file: $<'
	@echo 'Creating Executable'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(UNIT_TEST_OBJECTS) $(UNIT_TEST_FLAGS) $(LIBS) -o "$@"
	@echo 'Finished building: $@'
	@echo ' '


$(UTIL_TARGET).exe: $(UTIL_TEST_OBJECTS)
	@echo -e '\n\n$(TARGET)\n\n'
	@echo 'Building file: $<'
	@echo 'Creating Executable'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(UTIL_TEST_OBJECTS) $(UNIT_TEST_FLAGS) $(LIBS) -o "$@"
	@echo 'Finished building: $@'
	@echo ' '

#--------------------Arm---------------------

all_projects: $(HEXNOT)

%.hexNOT:
	@echo 'Building Project: $@'
	$(MAKE) project PROJ=$(basename $(notdir $@))
	touch $@z
	@echo -e '\n\nSuccessfully Compiled all Hex Files\n\n'

project: $(OBJ_DIR_SOURCE) $(BIN_DIR) $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).elf: $(MCU_LD) $(OBJECTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Linker'
	mkdir -p "$(dir $@)"
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '
#************************************************************************
# Rules for ARM Object Files
#************************************************************************

$(OBJ_DIR_SOURCE)/$(PROJ)/%.o: $(PROJ_DIR)/$(PROJ)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_SOURCE)/$(PROJ)/%.o: $(PROJ_DIR)/$(PROJ)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_SOURCE)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_SOURCE)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#************************************************************************
# Rules for Unit Testing Utilities
#************************************************************************


$(OBJ_DIR_UNIT)/Utilities/%.o: $(UTILITIES_SOURCE)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/Utilities/%.o: $(UTILITIES_SOURCE)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
$(OBJ_DIR_UNIT)/Utilities/%.o: $(UTILITIES_TEST)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/Utilities/%.o: $(UTILITIES_TEST)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#************************************************************************
# Rules for Unit testing Projects
#************************************************************************
$(OBJ_DIR_UNIT)/$(UNIT_METH_DIR)/%.o: $(UNIT_METH_DIR)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/$(PROJ)/%.o: $(PROJECT_SOURCE)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/$(PROJ)/%.o: $(PROJECT_SOURCE)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/$(PROJ)/%.o: $(PROJECT_TEST)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJ_DIR_UNIT)/$(PROJ)/%.o: $(PROJECT_TEST)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	mkdir -p "$(dir $@)"
	$(CPP_UNIT) $(CXXFLAGS_UNIT) $(CPPFLAGS_UNIT) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#************************************************************************
# Commands for Creating Directories
#************************************************************************


$(OBJ_DIR_SOURCE):
	@echo 'Creating Objects Folder for Unit Tests: $<'
	mkdir -p $(OBJ_DIR_SOURCE)

$(OBJ_DIR_UNIT):
	@echo 'Creating Objects Folder for Unit Tests: $<'
	mkdir -p $(OBJ_DIR_UNIT)

$(OBJ_DIR):
	@echo 'Creating Objects Folder for Unit Tests: $<'
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@echo 'Creating Binary Folder: $<'
	mkdir -p $(BIN_DIR)/$(PROJ)

$(EXE_DIR):
	@echo 'Creating Unit Test Executable Folder: $<'
	mkdir -p $(EXE_DIR)

#************************************************************************
# Cleaning Commands
#************************************************************************

clean:
	rm -rf *.o *.d $(BIN_DIR)/$(PROJ) $(OBJ_DIR)/$(PROJ)

spotless:
	rm -rf *.o *.d $(BIN_DIR)/* $(OBJ_DIR)/*