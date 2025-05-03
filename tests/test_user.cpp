#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/user.h" 


TEST_CASE("User password verification works", "[user]") {
    User u("alice", "mypassword");

    REQUIRE(u.checkPassword("mypassword"));
    REQUIRE_FALSE(u.checkPassword("wrongpass"));
}


TEST_CASE("User equality is based on username", "[user]") {
    User u1("admin", "1234");
    User u2("admin", "abcd");
    User u3("guest", "1234");

    REQUIRE(u1 == u2);
    REQUIRE_FALSE(u1 == u3);
}


TEST_CASE("User active status is changeable", "[user]") {
    User u("bob", "secure");

    REQUIRE_FALSE(u.getActive());

    u.setActive(true);
    REQUIRE(u.getActive());
}


TEST_CASE("User hash is consistent for same username", "[user]") {
    User u1("john", "abc");
    User u2("john", "def");

    User::HashFunction hasher;
    REQUIRE(hasher(u1) == hasher(u2));
}

// cd "User Auth System Project"

// g++ tests/test_user.cpp tests/test_utils.cpp src/user.cpp src/utils.cpp -o tests -std=c++17
// ./tests [user]