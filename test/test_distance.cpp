
#include "gtest/gtest.h"
#include "obstacle.hpp"
#include <cmath>

TEST(obstacle, distance1)
{
    Obstacle obst{0,0};
    
    EXPECT_FLOAT_EQ(2.f,obst.getDistance(2.f,0.f,90.f));

    EXPECT_FLOAT_EQ(0.f,obst.getDistance(2.f,0.f,0.f));
    EXPECT_FLOAT_EQ(0.f,obst.getDistance(0.f,0.f,0.f));
}

TEST(obstacle, distance2)
{
    Obstacle obst{1,1};
    EXPECT_FLOAT_EQ(1.f,obst.getDistance(0.f,0.f,0.f));
    EXPECT_FLOAT_EQ(0.f,obst.getDistance(0.f,0.f,45.f));
    EXPECT_FLOAT_EQ(sqrt(2.f),obst.getDistance(0.f,0.f,135.f));
    EXPECT_FLOAT_EQ(1,obst.getDistance(0.f,0.f,180.f));
    EXPECT_FLOAT_EQ(0,obst.getDistance(0.f,0.f,225.f));
    EXPECT_FLOAT_EQ(1,obst.getDistance(0.f,0.f,270.f));    
    EXPECT_FLOAT_EQ(sqrt(2.f),obst.getDistance(0.f,0.f,315.f));    
}

TEST(obstacle, distance3)
{
    Obstacle obst{0,0};
    EXPECT_FLOAT_EQ(1.f,obst.getDistance(1345.f,811.f,-135.f));
}