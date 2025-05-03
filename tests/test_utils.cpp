#include "catch.hpp"
#include "../include/utils.h" 

TEST_CASE("Input validation", "[utils]") {
    REQUIRE(isValidInput("ValidInput") == true);
    REQUIRE(isValidInput("Has space") == false);
    REQUIRE(isValidInput("") == false);
}
 
// ./tests [utils]