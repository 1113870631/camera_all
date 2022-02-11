# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/share/cmake-3.22.1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/share/cmake-3.22.1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ww/opencv/camera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ww/opencv/camera/build

# Include any dependencies generated for this target.
include CMakeFiles/camera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/camera.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camera.dir/flags.make

CMakeFiles/camera.dir/main.cpp.o: CMakeFiles/camera.dir/flags.make
CMakeFiles/camera.dir/main.cpp.o: ../main.cpp
CMakeFiles/camera.dir/main.cpp.o: CMakeFiles/camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camera.dir/main.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera.dir/main.cpp.o -MF CMakeFiles/camera.dir/main.cpp.o.d -o CMakeFiles/camera.dir/main.cpp.o -c /home/ww/opencv/camera/main.cpp

CMakeFiles/camera.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera.dir/main.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/camera/main.cpp > CMakeFiles/camera.dir/main.cpp.i

CMakeFiles/camera.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera.dir/main.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/camera/main.cpp -o CMakeFiles/camera.dir/main.cpp.s

CMakeFiles/camera.dir/picture_ex.cpp.o: CMakeFiles/camera.dir/flags.make
CMakeFiles/camera.dir/picture_ex.cpp.o: ../picture_ex.cpp
CMakeFiles/camera.dir/picture_ex.cpp.o: CMakeFiles/camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/camera.dir/picture_ex.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera.dir/picture_ex.cpp.o -MF CMakeFiles/camera.dir/picture_ex.cpp.o.d -o CMakeFiles/camera.dir/picture_ex.cpp.o -c /home/ww/opencv/camera/picture_ex.cpp

CMakeFiles/camera.dir/picture_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera.dir/picture_ex.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/camera/picture_ex.cpp > CMakeFiles/camera.dir/picture_ex.cpp.i

CMakeFiles/camera.dir/picture_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera.dir/picture_ex.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/camera/picture_ex.cpp -o CMakeFiles/camera.dir/picture_ex.cpp.s

CMakeFiles/camera.dir/jibian.cpp.o: CMakeFiles/camera.dir/flags.make
CMakeFiles/camera.dir/jibian.cpp.o: ../jibian.cpp
CMakeFiles/camera.dir/jibian.cpp.o: CMakeFiles/camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/camera.dir/jibian.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera.dir/jibian.cpp.o -MF CMakeFiles/camera.dir/jibian.cpp.o.d -o CMakeFiles/camera.dir/jibian.cpp.o -c /home/ww/opencv/camera/jibian.cpp

CMakeFiles/camera.dir/jibian.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera.dir/jibian.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/camera/jibian.cpp > CMakeFiles/camera.dir/jibian.cpp.i

CMakeFiles/camera.dir/jibian.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera.dir/jibian.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/camera/jibian.cpp -o CMakeFiles/camera.dir/jibian.cpp.s

# Object files for target camera
camera_OBJECTS = \
"CMakeFiles/camera.dir/main.cpp.o" \
"CMakeFiles/camera.dir/picture_ex.cpp.o" \
"CMakeFiles/camera.dir/jibian.cpp.o"

# External object files for target camera
camera_EXTERNAL_OBJECTS =

camera: CMakeFiles/camera.dir/main.cpp.o
camera: CMakeFiles/camera.dir/picture_ex.cpp.o
camera: CMakeFiles/camera.dir/jibian.cpp.o
camera: CMakeFiles/camera.dir/build.make
camera: /usr/local/lib/libopencv_gapi.so.4.5.5
camera: /usr/local/lib/libopencv_highgui.so.4.5.5
camera: /usr/local/lib/libopencv_ml.so.4.5.5
camera: /usr/local/lib/libopencv_objdetect.so.4.5.5
camera: /usr/local/lib/libopencv_photo.so.4.5.5
camera: /usr/local/lib/libopencv_stitching.so.4.5.5
camera: /usr/local/lib/libopencv_video.so.4.5.5
camera: /usr/local/lib/libopencv_videoio.so.4.5.5
camera: /usr/local/lib/libopencv_imgcodecs.so.4.5.5
camera: /usr/local/lib/libopencv_dnn.so.4.5.5
camera: /usr/local/lib/libopencv_calib3d.so.4.5.5
camera: /usr/local/lib/libopencv_features2d.so.4.5.5
camera: /usr/local/lib/libopencv_flann.so.4.5.5
camera: /usr/local/lib/libopencv_imgproc.so.4.5.5
camera: /usr/local/lib/libopencv_core.so.4.5.5
camera: CMakeFiles/camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ww/opencv/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camera.dir/build: camera
.PHONY : CMakeFiles/camera.dir/build

CMakeFiles/camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camera.dir/clean

CMakeFiles/camera.dir/depend:
	cd /home/ww/opencv/camera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ww/opencv/camera /home/ww/opencv/camera /home/ww/opencv/camera/build /home/ww/opencv/camera/build /home/ww/opencv/camera/build/CMakeFiles/camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camera.dir/depend

