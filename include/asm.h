#ifndef ASM_H_W23GKNVE
#define ASM_H_W23GKNVE




/* ========================================================================== */
// R Format
/* -------- Arithmetic and Logical Instructions ----------------------------- */
#define INS_NEW_ADD(d, s, t)   ins_create_r("000000", s, t, d, "00000", "100000")
#define INS_NEW_ADDU(d, s, t)  ins_create_r("000000", s, t, d, "00000", "100001")
#define INS_NEW_AND(d, s, t)   ins_create_r("000000", s, t, d, "00000", "100100")
#define INS_NEW_DIV(d, s, t)   ins_create_r("000000", s, t, d, "00000", "011010")
#define INS_NEW_DIVU(d, s, t)  ins_create_r("000000", s, t, d, "00000", "011011")
#define INS_NEW_MULT(d, s, t)  ins_create_r("000000", s, t, d, "00000", "011000")
#define INS_NEW_MULTU(d, s, t) ins_create_r("000000", s, t, d, "00000", "011001")
#define INS_NEW_OR(d, s, t)    ins_create_r("000000", s, t, d, "00000", "100101")

/* -------- Constant-Manipulating Instructions ------------------------------ */

/* -------- Comparison Instructions ----------------------------------------- */

/* -------- Branch Instructions --------------------------------------------- */

/* -------- Jump Instructions ----------------------------------------------- */

/* -------- Load Instructions ----------------------------------------------- */

/* -------- Store Instructions ---------------------------------------------- */

/* -------- Data Movement Instructions -------------------------------------- */

/* -------- Exception and Interrupt Instructions ---------------------------- */


/* ========================================================================== */
// I Format
/* -------- Arithmetic and Logical Instructions ----------------------------- */
#define INS_NEW_ADDI(t, s, i)  ins_create_i("001000", s, t, i)
#define INS_NEW_ADDIU(t, s, i) ins_create_i("001001", s, t, i)
#define INS_NEW_ANDI(t, s, i)  ins_create_i("001100", s, t, i)
#define INS_NEW_ORI(t, s, i)   ins_create_i("001101", s, t, i)

/* -------- Constant-Manipulating Instructions ------------------------------ */

/* -------- Comparison Instructions ----------------------------------------- */
#define INS_NEW_SLTI(t, s, i)  ins_create_i("001010", s, t, i)
#define INS_NEW_SLTIU(t, s, i) ins_create_i("001001", s, t, i)

/* -------- Branch Instructions --------------------------------------------- */
#define INS_NEW_BEQ(s, t, i) ins_create_i("000100", s, t, i)
#define INS_NEW_BGEZ(s, i)   ins_create_i("000001", s, "00001", i)
#define INS_NEW_BGEZAL(s, i) ins_create_i("000001", s, "10001", i)
#define INS_NEW_BGTZ(s, i)   ins_create_i("000111", s, "00000", i)
#define INS_NEW_BLEZ(s, i)   ins_create_i("000110", s, "00000", i)
#define INS_NEW_BLTZ(s, i)   ins_create_i("000001", s, "00000", i)
#define INS_NEW_BLTZAL(s, i) ins_create_i("000001", s, "10000", i)
#define INS_NEW_BNE(s, t, i) ins_create_i("000101", s, t, i)

/* -------- Jump Instructions ----------------------------------------------- */
#define INS_NEW_JR(s)   ins_create_i("000000", s, "00000", "0000000000001000")

/* -------- Load Instructions ----------------------------------------------- */

/* -------- Store Instructions ---------------------------------------------- */

/* -------- Data Movement Instructions -------------------------------------- */

/* -------- Exception and Interrupt Instructions ---------------------------- */


/* ========================================================================== */
// J Format
/* -------- Arithmetic and Logical Instructions ----------------------------- */

/* -------- Constant-Manipulating Instructions ------------------------------ */

/* -------- Comparison Instructions ----------------------------------------- */

/* -------- Branch Instructions --------------------------------------------- */

/* -------- Jump Instructions ----------------------------------------------- */
#define INS_NEW_J(i)   ins_create_j("000010", i)
#define INS_NEW_JAL(i) ins_create_j("000011", i)

/* -------- Load Instructions ----------------------------------------------- */

/* -------- Store Instructions ---------------------------------------------- */

/* -------- Data Movement Instructions -------------------------------------- */

/* -------- Exception and Interrupt Instructions ---------------------------- */



/* ========================================================================== */
// Others:
/* -------- Labels and more ------------------------------------------------- */
#define INS_NEW_LABEL(x)    ins_create_label(x)



extern
const char *ins_create_r(
        const char *opcode, /* 6 bits */
        const char *s_reg,  /* 5 bits */
        const char *t_reg,  /* 5 bits */
        const char *d_reg,  /* 5 bits */
        const char *shamt,  /* 5 bits */
        const char *func    /* 6 bits */
        );

extern
const char *ins_create_i(
        const char *opcode, /*  6 bits */
        const char *s_reg,  /*  5 bits */
        const char *t_reg,  /*  5 bits */
        const char *imm     /* 16 bits */
        );

extern
const char *ins_create_j(
        const char *opcode, /*  6 bits */
        const char *imm     /* 26 bits */
        );

extern
const char *ins_create_label(const char *label);

#endif /* ASM_H_W23GKNVE */

