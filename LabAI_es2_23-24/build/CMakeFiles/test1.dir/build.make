# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build

# Include any dependencies generated for this target.
include CMakeFiles/test1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test1.dir/flags.make

CMakeFiles/test1.dir/codegen:
.PHONY : CMakeFiles/test1.dir/codegen

CMakeFiles/test1.dir/src/test/test1.cpp.o: CMakeFiles/test1.dir/flags.make
CMakeFiles/test1.dir/src/test/test1.cpp.o: /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/src/test/test1.cpp
CMakeFiles/test1.dir/src/test/test1.cpp.o: CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test1.dir/src/test/test1.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test1.dir/src/test/test1.cpp.o -MF CMakeFiles/test1.dir/src/test/test1.cpp.o.d -o CMakeFiles/test1.dir/src/test/test1.cpp.o -c /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/src/test/test1.cpp

CMakeFiles/test1.dir/src/test/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test1.dir/src/test/test1.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/src/test/test1.cpp > CMakeFiles/test1.dir/src/test/test1.cpp.i

CMakeFiles/test1.dir/src/test/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test1.dir/src/test/test1.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/src/test/test1.cpp -o CMakeFiles/test1.dir/src/test/test1.cpp.s

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/src/test/test1.cpp.o"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1: CMakeFiles/test1.dir/src/test/test1.cpp.o
/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1: CMakeFiles/test1.dir/build.make
/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1: libuwimg++.dylib
/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1: CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test1.dir/build: /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/test1
.PHONY : CMakeFiles/test1.dir/build

CMakeFiles/test1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test1.dir/clean

CMakeFiles/test1.dir/depend:
	cd /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24 /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24 /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build /Users/alessandropaolantonio/Desktop/UNI/LAB_IA/LabAI-esercitazioni/LabAI_es2_23-24/build/CMakeFiles/test1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test1.dir/depend

