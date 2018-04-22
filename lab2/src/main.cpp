#include <stdio.h>
#include <string>
#include <stdint.h>
#include "mips.hpp"

int main(int argc, char *argv[]) {
    char mypath1[] =  "mips/text.bin";
    char mypath2[] =  "mips/data.bin";
    Mips myMips = Mips(mypath1, mypath2);
    /* printf("%x\n", myMips.mem[0]); */
    /* printf("%x\n", myMips.mem[1]); */
    myMips.run();
    return 0;
}
