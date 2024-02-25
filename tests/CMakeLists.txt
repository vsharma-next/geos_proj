find_package(GTest REQUIRED)
include(GoogleTest)


# Add test executable
# add_executable(feanor_test test_001.cpp test_002.cpp) # Add your test source files here
# target_link_libraries(feanor_test PRIVATE feanor ${CUSTOM_LDFLAGS})
# target_link_libraries(feanor_test PRIVATE gtest gtest_main)

# gtest_discover_tests(feanor_test)

# add_test(NAME feanor_test COMMAND feanor_test)

# Automatically populate TEST_SOURCES with all files matching the pattern
file(GLOB TEST_SOURCES "test_*.cpp")

# Loop through each test source file and create an executable
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Extract the filename without the extension to use as the executable name
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Create an executable for each test source file
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE feanor ${CUSTOM_LDFLAGS})
    target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main)
    set_target_properties(${TEST_NAME} PROPERTIES SUFFIX ".exe")
   
    # Add the test to CTest
    gtest_discover_tests(${TEST_NAME})
endforeach()