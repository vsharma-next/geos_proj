# Find all example source files
file(GLOB EXAMPLE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(example_source ${EXAMPLE_SOURCES})
    # Get file name without the extension
    get_filename_component(example_name ${example_source} NAME_WE)

    # Create an executable for each source file
    add_executable(${example_name} ${example_source})

    # Link the executable with the header-only library
    target_link_libraries(${example_name} PRIVATE libfeanor)
endforeach()
