#include "../include/user/admin.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Admin can add grades") {
    unor_map_vec data;
    Admin admin("test", "pass", data, ...);
    
    REQUIRE(admin.addGrade("math", 5) == true);
}
