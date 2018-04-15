#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "funcs.h"

TEST_CASE("Byte memory test") {
    sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01);
    sb(4, 0, 0xFF); sb(4, 1, 0xFE); sb(4, 2, 0xFD); sb(4, 3, 0xFC);
    REQUIRE(mem[0] == 0x01020304);
    REQUIRE((int32_t)mem[1] == 0xfcfdfeff);
}

TEST_CASE("Half-Word memory test") {
    sh(8, 0, 0xFFF0); sh(8, 2, 0x8C);
    REQUIRE((int32_t)mem[2] == 0x008cfff0);
}

TEST_CASE("Word memory test") {
    sw(12, 0, 0xFF);
    sw(16, 0, 0xFFFF);
    sw(20, 0, 0xFFFFFFFF);
    sw(24, 0, 0x80000000);
    REQUIRE((int32_t)mem[3] == (int32_t)0x000000FF);
    REQUIRE((int32_t)mem[4] == (int32_t)0x0000FFFF);
    REQUIRE((int32_t)mem[5] == (int32_t)0xFFFFFFFF);
    REQUIRE((int32_t)mem[6] == (int32_t)0x80000000);
}

TEST_CASE("Load byte sig-unsig test") {
    sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01);
    sb(4, 0, 0xFF); sb(4, 1, 0xFE); sb(4, 2, 0xFD); sb(4, 3, 0xFC);
    REQUIRE((int32_t)lb(0, 3) == 0x01);
    REQUIRE((int32_t)lbu(4, 2) == 0xfd);
}

TEST_CASE("Load half-word sig-unsig test") {
    sh(8, 0, 0xFFF0); sh(8, 2, 0x8C);
    REQUIRE(lb(0, 3) == 0x01);
    REQUIRE(lbu(4, 2) == 0xfd);
}

TEST_CASE("Load word test") {
    sw(12, 0, 0xFF);
    sw(16, 0, 0xFFFF);
    sw(20, 0, 0xFFFFFFFF);
    sw(24, 0, 0x80000000);
    REQUIRE(lw(16, 0) == 0xFFFF);
    REQUIRE(lw(24, 0) == (int32_t)0x80000000);
}
