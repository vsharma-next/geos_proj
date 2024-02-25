cmake_minimum_required(VERSION 3.10)

# Set the default install prefix to the build directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")

# Setup the Project
project(FEANOR VERSION 0.1 LANGUAGES CXX)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Set the directory for external libraries
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/external_libs/build")

# Retrieve compilation flags from gdal-config and geos-config
execute_process(COMMAND ${LIBS_DIR}/bin/geos-config --cflags OUTPUT_VARIABLE GEOS_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LIBS_DIR}/bin/gdal-config --cflags OUTPUT_VARIABLE GDAL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

# Retrieve linker flags from gdal-config and geos-config
execute_process(COMMAND ${LIBS_DIR}/bin/geos-config --static-cclibs OUTPUT_VARIABLE GEOS_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LIBS_DIR}/bin/gdal-config --libs OUTPUT_VARIABLE GDAL_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

# Additional linker flags
set(ADDITIONAL_LDFLAGS "-lsqlite3 -ldl")

# Combine flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ${GEOS_CFLAGS} ${GDAL_CFLAGS}")
set(CUSTOM_LDFLAGS "${GEOS_LDFLAGS} ${GDAL_LDFLAGS} ${ADDITIONAL_LDFLAGS}")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CUSTOM_LDFLAGS: ${CUSTOM_LDFLAGS}")


# Include subdirectories
add_subdirectory(src)

# add_subdirectory(examples)
add_subdirectory(tests)

# Install the library
install(TARGETS feanor
        EXPORT feanorTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# Install the header files
install(FILES "${CMAKE_SOURCE_DIR}/src/feanor.hpp" DESTINATION include)