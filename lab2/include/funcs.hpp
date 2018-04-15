#ifndef FUNCS_H
#define FUNCS_H

#include <stdint.h>
#include <stdlib.h>
#define MEM_SIZE 4096

uint32_t* load_binary(const char* input){
    FILE* inlet = fopen(input, "rb");
    uint32_t* outlet = NULL;

    outlet = (uint32_t*) malloc(sizeof(uint32_t) * 0x4000);
    fread(outlet, sizeof(uint32_t), 0x4000, inlet);
    outlet[4096] = 0;
    fclose(inlet);

    return outlet;
}

uint32_t lw(uint32_t *bin, uint32_t rs, uint32_t imm) {
  	return bin[(rs - 0x2000) / 4];
}

/* int32_t lh(uint32_t address, int16_t kte) { */
/*     // => lê meia palavra, 16 bits - retorna inteiro com sinal */
/*     int32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF; */
/*     return dado; */
/* } */

/* uint32_t lhu(uint32_t address, int16_t kte) { */
/*     // => lê meia palavra, 16 bits formato inteiro sem sinal */
/*     uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF; */
/*     return dado; */
/* } */

/* int32_t lb(uint32_t address, int16_t kte) { */
/*     // => lê um byte - retorna inteiro com sinal */
/*     int32_t dado = (mem[address/4] >> (kte*8)) & 0xFF; */
/*     return dado; */
/* } */

/* uint32_t lbu(uint32_t address, int16_t kte) { */
/*     // => lê um byte - 8 bits formato inteiro sem sinal */
/*     uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFF; */
/*     return dado; */
/* } */

/* void sw(uint32_t address, int16_t kte, int32_t dado) { */
/*     // => escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
/*     mem[address/4] = dado; */
/* } */

/* void sh(uint32_t address, int16_t kte, int16_t dado) { */
/*     // => escreve meia palavra, 16 bits - endereços múltiplos de 2 */
/*     uint32_t shifter = kte * 8; */
/*     uint32_t mask = ~(0xffff << shifter); */
/*     mem[address/4] = (mem[address/4] & mask) | (dado << shifter); */
/* } */

/* void sb(uint32_t address, int16_t kte, int8_t dado) { */
/*     // => escreve um byte na memória */
/*     uint32_t shifter = kte * 8; */
/*     uint32_t mask = ~(0xff << shifter); */
/*     mem[address/4] = (mem[address/4] & mask) | (dado << shifter); */
/* } */

#endif
