# Create libfeanor library
add_library(libfeanor STATIC feanor.cpp) # or SHARED

# Include directories for libfeanor
target_include_directories(libfeanor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Assuming external libraries are installed under external_libs/build
link_directories(${CMAKE_SOURCE_DIR}/external_libs/build/lib)

# Link against the static libraries you've built
target_link_libraries(libfeanor PRIVATE geos gdal proj)

# Specify include directories for external libraries
target_include_directories(libfeanor PRIVATE ${CMAKE_SOURCE_DIR}/external_libs/build/include)
