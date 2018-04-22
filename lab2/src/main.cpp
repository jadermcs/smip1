#include <stdio.h>
#include <string>
#include <stdint.h>
#include "mips.hpp"

int main(int argc, char *argv[]) {
    char mypath1[] =  "mips/text.bin";
    char mypath2[] =  "mips/data.bin";
    Mips myMips = Mips(mypath1, mypath2);
    myMips.dump_mem(0, 18, 'h');
    myMips.dump_mem(2048, 2068, 'h');
    myMips.run();
    return 0;
}
