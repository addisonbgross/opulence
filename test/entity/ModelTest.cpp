#ifndef OPULENCE_MODELTEST_H
#define OPULENCE_MODELTEST_H

#include "gtest/gtest.h"

TEST(ModelTest, MethodBarDoesAbc) {
    int answer = 1+ 3;
    EXPECT_EQ(4, answer);
}

#endif
