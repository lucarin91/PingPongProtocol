# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luca/PingPongProtocol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luca/PingPongProtocol

# Include any dependencies generated for this target.
include CMakeFiles/PingPongProtocol_v1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PingPongProtocol_v1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PingPongProtocol_v1.dir/flags.make

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o: src/Helper/ArgsParser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o -c /home/luca/PingPongProtocol/src/Helper/ArgsParser.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Helper/ArgsParser.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Helper/ArgsParser.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o: src/Helper/Logger.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o -c /home/luca/PingPongProtocol/src/Helper/Logger.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Helper/Logger.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Helper/Logger.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o: src/Message.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o -c /home/luca/PingPongProtocol/src/Message.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Message.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Message.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o: src/Peer/Peer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o -c /home/luca/PingPongProtocol/src/Peer/Peer.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Peer/Peer.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Peer/Peer.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o: src/Peer/Peer_p.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o -c /home/luca/PingPongProtocol/src/Peer/Peer_p.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Peer/Peer_p.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Peer/Peer_p.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o: src/Peer/Peer_pp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o -c /home/luca/PingPongProtocol/src/Peer/Peer_pp.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/Peer/Peer_pp.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/Peer/Peer_pp.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o: src/TopologyGen.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o -c /home/luca/PingPongProtocol/src/TopologyGen.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/TopologyGen.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/TopologyGen.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o: CMakeFiles/PingPongProtocol_v1.dir/flags.make
CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/luca/PingPongProtocol/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o -c /home/luca/PingPongProtocol/src/main.cpp

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/luca/PingPongProtocol/src/main.cpp > CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.i

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/luca/PingPongProtocol/src/main.cpp -o CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.s

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.requires

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.provides: CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/PingPongProtocol_v1.dir/build.make CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.provides

CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.provides.build: CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o

# Object files for target PingPongProtocol_v1
PingPongProtocol_v1_OBJECTS = \
"CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o" \
"CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o"

# External object files for target PingPongProtocol_v1
PingPongProtocol_v1_EXTERNAL_OBJECTS =

bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/build.make
bin/PingPongProtocol_v1: /usr/lib/x86_64-linux-gnu/libconfig++.so
bin/PingPongProtocol_v1: CMakeFiles/PingPongProtocol_v1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/PingPongProtocol_v1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PingPongProtocol_v1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PingPongProtocol_v1.dir/build: bin/PingPongProtocol_v1
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/build

CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/ArgsParser.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Helper/Logger.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Message.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_p.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/Peer/Peer_pp.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/TopologyGen.cpp.o.requires
CMakeFiles/PingPongProtocol_v1.dir/requires: CMakeFiles/PingPongProtocol_v1.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/requires

CMakeFiles/PingPongProtocol_v1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PingPongProtocol_v1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/clean

CMakeFiles/PingPongProtocol_v1.dir/depend:
	cd /home/luca/PingPongProtocol && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luca/PingPongProtocol /home/luca/PingPongProtocol /home/luca/PingPongProtocol /home/luca/PingPongProtocol /home/luca/PingPongProtocol/CMakeFiles/PingPongProtocol_v1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PingPongProtocol_v1.dir/depend

