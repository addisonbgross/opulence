# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

SET(CMAKE_SYSROOT ~/home/champ/Git/crows/opulence)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# here is the target environment located
#SET(CMAKE_FIND_ROOT_PATH /usr/include /usr/include/SDL /x86_64-w64-mingw32)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

