#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

extern "C"
{
#include "linked_list.h"
#include "btree.h"
}

// See Catch2's documentation: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#scaling-up

TEST_CASE("linked_list")
{
    //exercise 2
    int sum;
    node *ns = make_node (1,
			make_node (2,
				   make_node (3,
					      make_node (4,
							 make_node (5,
								    &SENTINEL)))));
  sum = sum_squares (ns);	/* sum should equal 55 */

  assert (sum == 55);
    REQUIRE(sum==55);
}

TEST_CASE("btree")
{
    // Add your tests here you can use the REQUIRE() statement 
    REQUIRE(1==1);
}
