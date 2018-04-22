/* #define CATCH_CONFIG_MAIN */
/* #include "catch.hpp" */
#include "mips.hpp"
#include <string>

/* TEST_CASE("Byte memory test") { */
/*     /1* sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01); *1/ */
/*     /1* sb(4, 0, 0xFF); sb(4, 1, 0xFE); sb(4, 2, 0xFD); sb(4, 3, 0xFC); *1/ */
/*     std::string mypath1 =  "mips/text.bin"; */
/*     std::string mypath2 =  "mips/data.bin"; */
/*     const char* ftext = mypath1.c_str(); */
/*     const char* fdata = mypath2.c_str(); */
/*     Mips myMips = Mips(ftext, fdata); */
/*     printf("%x", myMips.mem[0]); */
/*     /1* REQUIRE(myMips.mem[0] == 0x01020304); *1/ */
/*     /1* REQUIRE(myMips.mem[1] == 0xfcfdfeff); *1/ */
/* } */

int main(int argc, char *argv[]) {
    std::string mypath1 =  "mips/text.bin";
    std::string mypath2 =  "mips/data.bin";
    Mips myMips = Mips(mypath1.c_str(), mypath2.c_str());
    /* printf("%x", myMips.mem[0]); */
    return 0;
}
