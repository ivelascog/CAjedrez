# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/alserrano/Documentos/clion-2017.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/alserrano/Documentos/clion-2017.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alserrano/CLionProjects/CAjedrez

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alserrano/CLionProjects/CAjedrez/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proyecto.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proyecto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proyecto.dir/flags.make

CMakeFiles/proyecto.dir/main.cpp.o: CMakeFiles/proyecto.dir/flags.make
CMakeFiles/proyecto.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proyecto.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto.dir/main.cpp.o -c /home/alserrano/CLionProjects/CAjedrez/main.cpp

CMakeFiles/proyecto.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alserrano/CLionProjects/CAjedrez/main.cpp > CMakeFiles/proyecto.dir/main.cpp.i

CMakeFiles/proyecto.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alserrano/CLionProjects/CAjedrez/main.cpp -o CMakeFiles/proyecto.dir/main.cpp.s

CMakeFiles/proyecto.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/proyecto.dir/main.cpp.o.requires

CMakeFiles/proyecto.dir/main.cpp.o.provides: CMakeFiles/proyecto.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/proyecto.dir/build.make CMakeFiles/proyecto.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/proyecto.dir/main.cpp.o.provides

CMakeFiles/proyecto.dir/main.cpp.o.provides.build: CMakeFiles/proyecto.dir/main.cpp.o


CMakeFiles/proyecto.dir/Board.cpp.o: CMakeFiles/proyecto.dir/flags.make
CMakeFiles/proyecto.dir/Board.cpp.o: ../Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/proyecto.dir/Board.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto.dir/Board.cpp.o -c /home/alserrano/CLionProjects/CAjedrez/Board.cpp

CMakeFiles/proyecto.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto.dir/Board.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alserrano/CLionProjects/CAjedrez/Board.cpp > CMakeFiles/proyecto.dir/Board.cpp.i

CMakeFiles/proyecto.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto.dir/Board.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alserrano/CLionProjects/CAjedrez/Board.cpp -o CMakeFiles/proyecto.dir/Board.cpp.s

CMakeFiles/proyecto.dir/Board.cpp.o.requires:

.PHONY : CMakeFiles/proyecto.dir/Board.cpp.o.requires

CMakeFiles/proyecto.dir/Board.cpp.o.provides: CMakeFiles/proyecto.dir/Board.cpp.o.requires
	$(MAKE) -f CMakeFiles/proyecto.dir/build.make CMakeFiles/proyecto.dir/Board.cpp.o.provides.build
.PHONY : CMakeFiles/proyecto.dir/Board.cpp.o.provides

CMakeFiles/proyecto.dir/Board.cpp.o.provides.build: CMakeFiles/proyecto.dir/Board.cpp.o


CMakeFiles/proyecto.dir/Archer.cpp.o: CMakeFiles/proyecto.dir/flags.make
CMakeFiles/proyecto.dir/Archer.cpp.o: ../Archer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/proyecto.dir/Archer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto.dir/Archer.cpp.o -c /home/alserrano/CLionProjects/CAjedrez/Archer.cpp

CMakeFiles/proyecto.dir/Archer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto.dir/Archer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alserrano/CLionProjects/CAjedrez/Archer.cpp > CMakeFiles/proyecto.dir/Archer.cpp.i

CMakeFiles/proyecto.dir/Archer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto.dir/Archer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alserrano/CLionProjects/CAjedrez/Archer.cpp -o CMakeFiles/proyecto.dir/Archer.cpp.s

CMakeFiles/proyecto.dir/Archer.cpp.o.requires:

.PHONY : CMakeFiles/proyecto.dir/Archer.cpp.o.requires

CMakeFiles/proyecto.dir/Archer.cpp.o.provides: CMakeFiles/proyecto.dir/Archer.cpp.o.requires
	$(MAKE) -f CMakeFiles/proyecto.dir/build.make CMakeFiles/proyecto.dir/Archer.cpp.o.provides.build
.PHONY : CMakeFiles/proyecto.dir/Archer.cpp.o.provides

CMakeFiles/proyecto.dir/Archer.cpp.o.provides.build: CMakeFiles/proyecto.dir/Archer.cpp.o


CMakeFiles/proyecto.dir/Unit.cpp.o: CMakeFiles/proyecto.dir/flags.make
CMakeFiles/proyecto.dir/Unit.cpp.o: ../Unit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/proyecto.dir/Unit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto.dir/Unit.cpp.o -c /home/alserrano/CLionProjects/CAjedrez/Unit.cpp

CMakeFiles/proyecto.dir/Unit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto.dir/Unit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alserrano/CLionProjects/CAjedrez/Unit.cpp > CMakeFiles/proyecto.dir/Unit.cpp.i

CMakeFiles/proyecto.dir/Unit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto.dir/Unit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alserrano/CLionProjects/CAjedrez/Unit.cpp -o CMakeFiles/proyecto.dir/Unit.cpp.s

CMakeFiles/proyecto.dir/Unit.cpp.o.requires:

.PHONY : CMakeFiles/proyecto.dir/Unit.cpp.o.requires

CMakeFiles/proyecto.dir/Unit.cpp.o.provides: CMakeFiles/proyecto.dir/Unit.cpp.o.requires
	$(MAKE) -f CMakeFiles/proyecto.dir/build.make CMakeFiles/proyecto.dir/Unit.cpp.o.provides.build
.PHONY : CMakeFiles/proyecto.dir/Unit.cpp.o.provides

CMakeFiles/proyecto.dir/Unit.cpp.o.provides.build: CMakeFiles/proyecto.dir/Unit.cpp.o


CMakeFiles/proyecto.dir/King.cpp.o: CMakeFiles/proyecto.dir/flags.make
CMakeFiles/proyecto.dir/King.cpp.o: ../King.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/proyecto.dir/King.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto.dir/King.cpp.o -c /home/alserrano/CLionProjects/CAjedrez/King.cpp

CMakeFiles/proyecto.dir/King.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto.dir/King.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alserrano/CLionProjects/CAjedrez/King.cpp > CMakeFiles/proyecto.dir/King.cpp.i

CMakeFiles/proyecto.dir/King.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto.dir/King.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alserrano/CLionProjects/CAjedrez/King.cpp -o CMakeFiles/proyecto.dir/King.cpp.s

CMakeFiles/proyecto.dir/King.cpp.o.requires:

.PHONY : CMakeFiles/proyecto.dir/King.cpp.o.requires

CMakeFiles/proyecto.dir/King.cpp.o.provides: CMakeFiles/proyecto.dir/King.cpp.o.requires
	$(MAKE) -f CMakeFiles/proyecto.dir/build.make CMakeFiles/proyecto.dir/King.cpp.o.provides.build
.PHONY : CMakeFiles/proyecto.dir/King.cpp.o.provides

CMakeFiles/proyecto.dir/King.cpp.o.provides.build: CMakeFiles/proyecto.dir/King.cpp.o


# Object files for target proyecto
proyecto_OBJECTS = \
"CMakeFiles/proyecto.dir/main.cpp.o" \
"CMakeFiles/proyecto.dir/Board.cpp.o" \
"CMakeFiles/proyecto.dir/Archer.cpp.o" \
"CMakeFiles/proyecto.dir/Unit.cpp.o" \
"CMakeFiles/proyecto.dir/King.cpp.o"

# External object files for target proyecto
proyecto_EXTERNAL_OBJECTS =

proyecto: CMakeFiles/proyecto.dir/main.cpp.o
proyecto: CMakeFiles/proyecto.dir/Board.cpp.o
proyecto: CMakeFiles/proyecto.dir/Archer.cpp.o
proyecto: CMakeFiles/proyecto.dir/Unit.cpp.o
proyecto: CMakeFiles/proyecto.dir/King.cpp.o
proyecto: CMakeFiles/proyecto.dir/build.make
proyecto: CMakeFiles/proyecto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable proyecto"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proyecto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proyecto.dir/build: proyecto

.PHONY : CMakeFiles/proyecto.dir/build

CMakeFiles/proyecto.dir/requires: CMakeFiles/proyecto.dir/main.cpp.o.requires
CMakeFiles/proyecto.dir/requires: CMakeFiles/proyecto.dir/Board.cpp.o.requires
CMakeFiles/proyecto.dir/requires: CMakeFiles/proyecto.dir/Archer.cpp.o.requires
CMakeFiles/proyecto.dir/requires: CMakeFiles/proyecto.dir/Unit.cpp.o.requires
CMakeFiles/proyecto.dir/requires: CMakeFiles/proyecto.dir/King.cpp.o.requires

.PHONY : CMakeFiles/proyecto.dir/requires

CMakeFiles/proyecto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proyecto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proyecto.dir/clean

CMakeFiles/proyecto.dir/depend:
	cd /home/alserrano/CLionProjects/CAjedrez/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alserrano/CLionProjects/CAjedrez /home/alserrano/CLionProjects/CAjedrez /home/alserrano/CLionProjects/CAjedrez/cmake-build-debug /home/alserrano/CLionProjects/CAjedrez/cmake-build-debug /home/alserrano/CLionProjects/CAjedrez/cmake-build-debug/CMakeFiles/proyecto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proyecto.dir/depend

