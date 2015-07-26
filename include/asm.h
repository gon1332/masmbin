#ifndef ASM_H_W23GKNVE
#define ASM_H_W23GKNVE

/* ========================================================================== */
// Instruction Fields in bits */
/* -------- Opcode ---------------------------------------------------------- */
#define OP_RFMT     "000000"
#define OP_LW       "100011"
#define OP_SW       "101011"
#define OP_BEQ      "000100"
#define OP_BNE      "000101"

/* -------- Function codes -------------------------------------------------- */
#define ADD_func    "100000"
#define SUB_func    "100010"
#define AND_func    "100100"
#define OR_func     "100101"
#define SLT_func    "101010"

/* -------- Registers ------------------------------------------------------- */
#define REG0        "00000"
#define REG1        "00001"
#define REG2        "00010"
#define REG3        "00011"
#define REG4        "00100"
#define REG5        "00101"
#define REG6        "00110"
#define REG7        "00111"
#define REG8        "01000"
#define REG9        "01001"
#define REG10       "01010"
#define REG11       "01011"
#define REG12       "01100"
#define REG13       "01101"
#define REG14       "01110"
#define REG15       "01111"
#define REG16       "10000"
#define REG17       "10001"
#define REG18       "10010"
#define REG19       "10011"
#define REG20       "10100"
#define REG21       "10101"
#define REG22       "10110"
#define REG23       "10111"
#define REG24       "11000"
#define REG25       "11001"
#define REG26       "11010"
#define REG27       "11011"
#define REG28       "11100"
#define REG29       "11101"
#define REG30       "11110"
#define REG31       "11111"



/* ========================================================================== */
// R Format
/* -------- Arithmetic and Logical Instructions ----------------------------- */
#define INS_NEW_ADD(a, d, s, t)   ins_create_r(a, OP_RFMT, s, t, d, "00000", "100000")
#define INS_NEW_ADDU(a, d, s, t)  ins_create_r(a, OP_RFMT, s, t, d, "00000", "100001")
#define INS_NEW_AND(a, d, s, t)   ins_create_r(a, OP_RFMT, s, t, d, "00000", "100100")
#define INS_NEW_DIV(a, d, s, t)   ins_create_r(a, OP_RFMT, s, t, d, "00000", "011010")
#define INS_NEW_DIVU(a, d, s, t)  ins_create_r(a, OP_RFMT, s, t, d, "00000", "011011")
#define INS_NEW_MULT(a, d, s, t)  ins_create_r(a, OP_RFMT, s, t, d, "00000", "011000")
#define INS_NEW_MULTU(a, d, s, t) ins_create_r(a, OP_RFMT, s, t, d, "00000", "011001")
#define INS_NEW_OR(a, d, s, t)    ins_create_r(a, OP_RFMT, s, t, d, "00000", "100101")

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
#define INS_NEW_ADDI(a, t, s, i)  ins_create_i(a, "001000", s, t, i)
#define INS_NEW_ADDIU(a, t, s, i) ins_create_i(a, "001001", s, t, i)
#define INS_NEW_ANDI(a, t, s, i)  ins_create_i(a, "001100", s, t, i)
#define INS_NEW_ORI(a, t, s, i)   ins_create_i(a, "001101", s, t, i)

/* -------- Constant-Manipulating Instructions ------------------------------ */

/* -------- Comparison Instructions ----------------------------------------- */
#define INS_NEW_SLTI(a, t, s, i)  ins_create_i(a, "001010", s, t, i)
#define INS_NEW_SLTIU(a, t, s, i) ins_create_i(a, "001001", s, t, i)

/* -------- Branch Instructions --------------------------------------------- */
#define INS_NEW_BEQ(a, s, t, i) ins_create_i(a, "000100", s, t, i)
#define INS_NEW_BGEZ(a, s, i)   ins_create_i(a, "000001", s, "00001", i)
#define INS_NEW_BGEZAL(a, s, i) ins_create_i(a, "000001", s, "10001", i)
#define INS_NEW_BGTZ(a, s, i)   ins_create_i(a, "000111", s, "00000", i)
#define INS_NEW_BLEZ(a, s, i)   ins_create_i(a, "000110", s, "00000", i)
#define INS_NEW_BLTZ(a, s, i)   ins_create_i(a, "000001", s, "00000", i)
#define INS_NEW_BLTZAL(a, s, i) ins_create_i(a, "000001", s, "10000", i)
#define INS_NEW_BNE(a, s, t, i) ins_create_i(a, "000101", s, t, i)

/* -------- Jump Instructions ----------------------------------------------- */
#define INS_NEW_JR(a, s)   ins_create_i(a, "000000", s, "00000", "0000000000001000")

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
#define INS_NEW_J(a, i)   ins_create_j(a, "000010", i)
#define INS_NEW_JAL(a, i) ins_create_j(a, "000011", i)

/* -------- Load Instructions ----------------------------------------------- */

/* -------- Store Instructions ---------------------------------------------- */

/* -------- Data Movement Instructions -------------------------------------- */

/* -------- Exception and Interrupt Instructions ---------------------------- */



/* ========================================================================== */
// Others:
/* -------- Labels and more ------------------------------------------------- */
#define INS_NEW_LABEL(x)    ins_create_label(x)


extern
const char *which_reg(const char *reg);

extern
int ins_create_r(
        const unsigned instr_addr,
        const char *opcode, /* 6 bits */
        const char *s_reg,  /* 5 bits */
        const char *t_reg,  /* 5 bits */
        const char *d_reg,  /* 5 bits */
        const char *shamt,  /* 5 bits */
        const char *func    /* 6 bits */
        );

extern
int ins_create_i(
        const unsigned instr_addr,
        const char *opcode, /*  6 bits */
        const char *s_reg,  /*  5 bits */
        const char *t_reg,  /*  5 bits */
        const char *imm     /* 16 bits */
        );

extern
int ins_create_j(
        const unsigned instr_addr,
        const char *opcode, /*  6 bits */
        const char *imm     /* 26 bits */
        );

extern
int ins_create_label(const char *label);

#endif /* ASM_H_W23GKNVE */

