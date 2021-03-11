#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

extern "C"
{
#include "max.h"
#include "swap.h"
#include "max_sum.h"
}

// See Catch2's documentation: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#scaling-up

TEST_CASE("max")
{
    REQUIRE(max(0, 0) == 0);
    REQUIRE(max(1, 2) == 2);
    REQUIRE(max(0, -1) == -1);
    REQUIRE(max(-2, -1) == -1);
}

TEST_CASE("swap")
{
    int a = 1;
    int b = 2;
    swap(&a, &b);
    REQUIRE(a == 2);
    REQUIRE(b == 1);
    swap(&a, &b);
    REQUIRE(a == 1);
    REQUIRE(b == 2);
}

TEST_CASE("max_sum")
{
    REQUIRE(max_sum(1, 2, 3) == 6);
    REQUIRE(max_sum(1, 2, -3) == 3);
    REQUIRE(max_sum(0, 0, 0) == 0);
    REQUIRE(max_sum(-10, 20, 30) == 50);
}
