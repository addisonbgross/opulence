# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_SOURCE_DIR = /home/champ/Git/crows/opulence

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/champ/Git/crows/opulence

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/champ/Git/crows/opulence/CMakeFiles /home/champ/Git/crows/opulence/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/champ/Git/crows/opulence/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named opulence

# Build rule for target.
opulence: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 opulence
.PHONY : opulence

# fast build rule for target.
opulence/fast:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/build
.PHONY : opulence/fast

home/champ/Git/crows/main.o: home/champ/Git/crows/main.c.o
.PHONY : home/champ/Git/crows/main.o

# target to build an object file
home/champ/Git/crows/main.c.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/home/champ/Git/crows/main.c.o
.PHONY : home/champ/Git/crows/main.c.o

home/champ/Git/crows/main.i: home/champ/Git/crows/main.c.i
.PHONY : home/champ/Git/crows/main.i

# target to preprocess a source file
home/champ/Git/crows/main.c.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/home/champ/Git/crows/main.c.i
.PHONY : home/champ/Git/crows/main.c.i

home/champ/Git/crows/main.s: home/champ/Git/crows/main.c.s
.PHONY : home/champ/Git/crows/main.s

# target to generate assembly for a file
home/champ/Git/crows/main.c.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/home/champ/Git/crows/main.c.s
.PHONY : home/champ/Git/crows/main.c.s

opulence.o: opulence.cpp.o
.PHONY : opulence.o

# target to build an object file
opulence.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/opulence.cpp.o
.PHONY : opulence.cpp.o

opulence.i: opulence.cpp.i
.PHONY : opulence.i

# target to preprocess a source file
opulence.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/opulence.cpp.i
.PHONY : opulence.cpp.i

opulence.s: opulence.cpp.s
.PHONY : opulence.s

# target to generate assembly for a file
opulence.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/opulence.cpp.s
.PHONY : opulence.cpp.s

src/entity/Entity.o: src/entity/Entity.cpp.o
.PHONY : src/entity/Entity.o

# target to build an object file
src/entity/Entity.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/Entity.cpp.o
.PHONY : src/entity/Entity.cpp.o

src/entity/Entity.i: src/entity/Entity.cpp.i
.PHONY : src/entity/Entity.i

# target to preprocess a source file
src/entity/Entity.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/Entity.cpp.i
.PHONY : src/entity/Entity.cpp.i

src/entity/Entity.s: src/entity/Entity.cpp.s
.PHONY : src/entity/Entity.s

# target to generate assembly for a file
src/entity/Entity.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/Entity.cpp.s
.PHONY : src/entity/Entity.cpp.s

src/entity/camera/Camera.o: src/entity/camera/Camera.cpp.o
.PHONY : src/entity/camera/Camera.o

# target to build an object file
src/entity/camera/Camera.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/camera/Camera.cpp.o
.PHONY : src/entity/camera/Camera.cpp.o

src/entity/camera/Camera.i: src/entity/camera/Camera.cpp.i
.PHONY : src/entity/camera/Camera.i

# target to preprocess a source file
src/entity/camera/Camera.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/camera/Camera.cpp.i
.PHONY : src/entity/camera/Camera.cpp.i

src/entity/camera/Camera.s: src/entity/camera/Camera.cpp.s
.PHONY : src/entity/camera/Camera.s

# target to generate assembly for a file
src/entity/camera/Camera.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/camera/Camera.cpp.s
.PHONY : src/entity/camera/Camera.cpp.s

src/entity/model/Model.o: src/entity/model/Model.cpp.o
.PHONY : src/entity/model/Model.o

# target to build an object file
src/entity/model/Model.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/model/Model.cpp.o
.PHONY : src/entity/model/Model.cpp.o

src/entity/model/Model.i: src/entity/model/Model.cpp.i
.PHONY : src/entity/model/Model.i

# target to preprocess a source file
src/entity/model/Model.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/model/Model.cpp.i
.PHONY : src/entity/model/Model.cpp.i

src/entity/model/Model.s: src/entity/model/Model.cpp.s
.PHONY : src/entity/model/Model.s

# target to generate assembly for a file
src/entity/model/Model.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/entity/model/Model.cpp.s
.PHONY : src/entity/model/Model.cpp.s

src/loaders/ObjLoader.o: src/loaders/ObjLoader.cpp.o
.PHONY : src/loaders/ObjLoader.o

# target to build an object file
src/loaders/ObjLoader.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ObjLoader.cpp.o
.PHONY : src/loaders/ObjLoader.cpp.o

src/loaders/ObjLoader.i: src/loaders/ObjLoader.cpp.i
.PHONY : src/loaders/ObjLoader.i

# target to preprocess a source file
src/loaders/ObjLoader.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ObjLoader.cpp.i
.PHONY : src/loaders/ObjLoader.cpp.i

src/loaders/ObjLoader.s: src/loaders/ObjLoader.cpp.s
.PHONY : src/loaders/ObjLoader.s

# target to generate assembly for a file
src/loaders/ObjLoader.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ObjLoader.cpp.s
.PHONY : src/loaders/ObjLoader.cpp.s

src/loaders/ShaderLoader.o: src/loaders/ShaderLoader.cpp.o
.PHONY : src/loaders/ShaderLoader.o

# target to build an object file
src/loaders/ShaderLoader.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ShaderLoader.cpp.o
.PHONY : src/loaders/ShaderLoader.cpp.o

src/loaders/ShaderLoader.i: src/loaders/ShaderLoader.cpp.i
.PHONY : src/loaders/ShaderLoader.i

# target to preprocess a source file
src/loaders/ShaderLoader.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ShaderLoader.cpp.i
.PHONY : src/loaders/ShaderLoader.cpp.i

src/loaders/ShaderLoader.s: src/loaders/ShaderLoader.cpp.s
.PHONY : src/loaders/ShaderLoader.s

# target to generate assembly for a file
src/loaders/ShaderLoader.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/loaders/ShaderLoader.cpp.s
.PHONY : src/loaders/ShaderLoader.cpp.s

src/service/Courier.o: src/service/Courier.cpp.o
.PHONY : src/service/Courier.o

# target to build an object file
src/service/Courier.cpp.o:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/service/Courier.cpp.o
.PHONY : src/service/Courier.cpp.o

src/service/Courier.i: src/service/Courier.cpp.i
.PHONY : src/service/Courier.i

# target to preprocess a source file
src/service/Courier.cpp.i:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/service/Courier.cpp.i
.PHONY : src/service/Courier.cpp.i

src/service/Courier.s: src/service/Courier.cpp.s
.PHONY : src/service/Courier.s

# target to generate assembly for a file
src/service/Courier.cpp.s:
	$(MAKE) -f CMakeFiles/opulence.dir/build.make CMakeFiles/opulence.dir/src/service/Courier.cpp.s
.PHONY : src/service/Courier.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... opulence"
	@echo "... rebuild_cache"
	@echo "... home/champ/Git/crows/main.o"
	@echo "... home/champ/Git/crows/main.i"
	@echo "... home/champ/Git/crows/main.s"
	@echo "... opulence.o"
	@echo "... opulence.i"
	@echo "... opulence.s"
	@echo "... src/entity/Entity.o"
	@echo "... src/entity/Entity.i"
	@echo "... src/entity/Entity.s"
	@echo "... src/entity/camera/Camera.o"
	@echo "... src/entity/camera/Camera.i"
	@echo "... src/entity/camera/Camera.s"
	@echo "... src/entity/model/Model.o"
	@echo "... src/entity/model/Model.i"
	@echo "... src/entity/model/Model.s"
	@echo "... src/loaders/ObjLoader.o"
	@echo "... src/loaders/ObjLoader.i"
	@echo "... src/loaders/ObjLoader.s"
	@echo "... src/loaders/ShaderLoader.o"
	@echo "... src/loaders/ShaderLoader.i"
	@echo "... src/loaders/ShaderLoader.s"
	@echo "... src/service/Courier.o"
	@echo "... src/service/Courier.i"
	@echo "... src/service/Courier.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

