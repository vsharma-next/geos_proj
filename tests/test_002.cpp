#include <gtest/gtest.h>
#include "feanor.hpp" // Adjust the include path according to your project setup

TEST(FeanorTest, TestTransformed)
{
    geos_wrapper dummy;
    int result = dummy.return_transformed();
    EXPECT_EQ(result, 2) << "Expected 2, got " << result;
}
