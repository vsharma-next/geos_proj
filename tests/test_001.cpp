#include <gtest/gtest.h>
#include "feanor.hpp" // Adjust the include path according to your project setup

TEST(FeanorTest, TestOriginal)
{
    geos_wrapper dummy;
    int result = dummy.return_original();
    EXPECT_EQ(result, 1) << "Expected 1, got " << result;
}
