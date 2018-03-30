#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#define MEM_SIZE 4096

int32_t mem[MEM_SIZE];

void dump_mem(uint32_t add, uint32_t size) {
    for (int i = add/4; i < size/4; ++i) {
        printf("mem[%d]\t= %08x\n", i, mem[i]);
    }
}

int32_t lw(uint32_t address, int16_t kte) {
    // => lê um inteiro alinhado - endereços múltiplos de 4
    int32_t dado = mem[address/4];
    return dado;
}

int32_t lh(uint32_t address, int16_t kte) {
    // => lê meia palavra, 16 bits - retorna inteiro com sinal
    int32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF;
    return dado;
}

uint32_t lhu(uint32_t address, int16_t kte) {
    // => lê meia palavra, 16 bits formato inteiro sem sinal
    uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF;
    return dado;
}

int32_t lb(uint32_t address, int16_t kte) {
    // => lê um byte - retorna inteiro com sinal
    int32_t dado = (mem[address/4] >> (kte*8)) & 0xFF;
    return dado;
}

uint32_t lbu(uint32_t address, int16_t kte) {
    // => lê um byte - 8 bits formato inteiro sem sinal
    uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFF;
    return dado;
}

void sw(uint32_t address, int16_t kte, int32_t dado) {
    // => escreve um inteiro alinhado na memória - endereços múltiplos de 4
    mem[address/4] = dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado) {
    // => escreve meia palavra, 16 bits - endereços múltiplos de 2
    uint32_t shifter = kte * 8;
    uint32_t mask = ~(0xffff << shifter);
    mem[address/4] = (mem[address/4] & mask) | (dado << shifter);
}

void sb(uint32_t address, int16_t kte, int8_t dado) {
    // => escreve um byte na memória
    uint32_t shifter = kte * 8;
    uint32_t mask = ~(0xff << shifter);
    mem[address/4] = (mem[address/4] & mask) | (dado << shifter);
}

#endif
