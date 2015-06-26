#include "asm.h"
#include <stdio.h>

const char *ins_create_r(
        const char *opcode,
        const char *s_reg,
        const char *t_reg,
        const char *d_reg,
        const char *shamt,
        const char *func
        )
{
    fprintf(stdout, "%s_%s_%s_%s_%s_%s\n", opcode, s_reg, t_reg, d_reg, shamt, func);
    return NULL;
}

const char *ins_create_i(
        const char *opcode,
        const char *s_reg,
        const char *t_reg,
        const char *imm
        )
{
    fprintf(stdout, "%s_%s_%s_%s\n", opcode, s_reg, t_reg, imm);
    return NULL;
}

const char *ins_create_j(
        const char *opcode,
        const char *imm
        )
{
    fprintf(stdout, "%s_%s\n", opcode, imm);
    return NULL;
}
