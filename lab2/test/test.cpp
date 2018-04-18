#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mips.hpp"
#include <string>

TEST_CASE("Byte memory test") {
    /* sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01); */
    /* sb(4, 0, 0xFF); sb(4, 1, 0xFE); sb(4, 2, 0xFD); sb(4, 3, 0xFC); */
    std::string mypath =  "path";
    const char* ftext = mypath.c_str();
    const char* fdata = mypath.c_str();
    Mips myMips = Mips(ftext, fdata);
    REQUIRE(myMips.mem[0] == 0x01020304);
    REQUIRE(myMips.mem[1] == 0xfcfdfeff);
}
