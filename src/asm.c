#include "asm.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>



/* TODO: gon1332 Hash the hell out of it. Τρι 14 Ιούλ 2015 05:07:01 μμ EEST */
/*
 * Check for legal registers and return the binary representation.
 *
 */
const char *which_reg(const char *reg)
{
    if (NULL == reg) return NULL;

    if (!strcmp(reg, "$0") || !strcmp(reg, "$zero")) return REG0;
    else if (!strcmp(reg, "$1") || !strcmp(reg, "$at")) return REG1;
    else if (!strcmp(reg, "$2") || !strcmp(reg, "$v0")) return REG2;
    else if (!strcmp(reg, "$3") || !strcmp(reg, "$v1")) return REG3;
    else if (!strcmp(reg, "$4") || !strcmp(reg, "$a0")) return REG4;
    else if (!strcmp(reg, "$5") || !strcmp(reg, "$a1")) return REG5;
    else if (!strcmp(reg, "$6") || !strcmp(reg, "$a2")) return REG6;
    else if (!strcmp(reg, "$7") || !strcmp(reg, "$a3")) return REG7;
    else if (!strcmp(reg, "$8") || !strcmp(reg, "$t0")) return REG8;
    else if (!strcmp(reg, "$9") || !strcmp(reg, "$t1")) return REG9;
    else if (!strcmp(reg, "$10") || !strcmp(reg, "$t2")) return REG10;
    else if (!strcmp(reg, "$11") || !strcmp(reg, "$t3")) return REG11;
    else if (!strcmp(reg, "$12") || !strcmp(reg, "$t4")) return REG12;
    else if (!strcmp(reg, "$13") || !strcmp(reg, "$t5")) return REG13;
    else if (!strcmp(reg, "$14") || !strcmp(reg, "$t6")) return REG14;
    else if (!strcmp(reg, "$15") || !strcmp(reg, "$t7")) return REG15;
    else if (!strcmp(reg, "$16") || !strcmp(reg, "$s0")) return REG16;
    else if (!strcmp(reg, "$17") || !strcmp(reg, "$s1")) return REG17;
    else if (!strcmp(reg, "$18") || !strcmp(reg, "$s2")) return REG18;
    else if (!strcmp(reg, "$19") || !strcmp(reg, "$s3")) return REG19;
    else if (!strcmp(reg, "$20") || !strcmp(reg, "$s4")) return REG20;
    else if (!strcmp(reg, "$21") || !strcmp(reg, "$s5")) return REG21;
    else if (!strcmp(reg, "$22") || !strcmp(reg, "$s6")) return REG22;
    else if (!strcmp(reg, "$23") || !strcmp(reg, "$s7")) return REG23;
    else if (!strcmp(reg, "$24") || !strcmp(reg, "$t8")) return REG24;
    else if (!strcmp(reg, "$25") || !strcmp(reg, "$t9")) return REG25;
    else if (!strcmp(reg, "$26") || !strcmp(reg, "$k0")) return REG26;
    else if (!strcmp(reg, "$27") || !strcmp(reg, "$k1")) return REG27;
    else if (!strcmp(reg, "$28") || !strcmp(reg, "$gp")) return REG28;
    else if (!strcmp(reg, "$29") || !strcmp(reg, "$sp")) return REG29;
    else if (!strcmp(reg, "$30") || !strcmp(reg, "$fp")) return REG30;
    else if (!strcmp(reg, "$31") || !strcmp(reg, "$ra")) return REG31;
    return NULL;
}


/*
 * Return values for the below functions:
 *
 * 0 -> success
 * 1 -> error on s reg
 * 2 -> error on t reg
 * 3 -> error on d reg
 * */

int ins_create_r(
        const unsigned instr_addr,
        const char *opcode,
        const char *s_reg,
        const char *t_reg,
        const char *d_reg,
        const char *shamt,
        const char *func
        )
{
    const char *s_bin = which_reg(s_reg);
    if (!s_bin) {
        return 1;   // error on s register
    }

    const char *t_bin = which_reg(t_reg);
    if (!t_bin) {
        return 2;   // error on t register
    }

    const char *d_bin = which_reg(d_reg);
    if (!d_bin) {
        return 3;   // error on d register
    }
    fprintf(fout, "@%x\t%s_%s_%s_%s_%s_%s\n", instr_addr, opcode, s_bin, t_bin, d_bin, shamt, func);
    return 0;
}

int ins_create_i(
        const unsigned instr_addr,
        const char *opcode,
        const char *s_reg,
        const char *t_reg,
        const char *imm
        )
{
    const char *s_bin = which_reg(s_reg);
    if (!s_bin) {
        return 1;   // error on s register
    }

    const char *t_bin = which_reg(t_reg);
    if (!t_bin) {
        return 2;   // error on t register
    }

    fprintf(fout, "@%x\t%s_%s_%s_%s\n", instr_addr,  opcode, s_bin, t_bin, imm);
    return 0;
}

int ins_create_j(
        const unsigned instr_addr,
        const char *opcode,
        const char *imm
        )
{
    fprintf(fout, "@%x\t%s_%s\n", instr_addr,  opcode, imm);
    return 0;
}

int ins_create_label(const char *label)
{
    (void)label;
    //fprintf(fout, "%s\n", label);
    return 0;
}
