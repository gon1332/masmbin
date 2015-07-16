/*****************************************************************************
 * Decription: Lexical Analysis for MAsmBin
 *****************************************************************************/
%top{
    #include "tok.h"
    #include "parser.h"
    #include <stdio.h>
    #include <string.h>
    #include "strdup.h"

    size_t LINENO = 1;     /* line numbering */

    int FLAG_ERROR = 0;
    char *INPUT_FILE_NAME = NULL;

}

/******************************   DEFINITIONS   ******************************/

DEC_0       [0-9]
DEC_1       [1-9]
HEX_0       [0-9A-Fa-f]
HEX_1       [1-9A-Fa-f]

PRNT_ASCII  [ -~]
DIGIT       [0-9]
LETTER      [a-zA-Z]
W           [ \t]
SPECIAL_C   [._]

LABEL_INSTR {LETTER}({LETTER}|{DIGIT}|{SPECIAL_C})*
LABEL_DEFIN {LABEL_INSTR}:

REG_NAME    $(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra)
REG_NUM     $([0-9]|1[0-9]|2[0-9]|3[0-2])
REG         {REG_NAME}|{REG_NUM}

DEC_ICONST  0|{DEC_1}{DEC_0}*
HEX_ICONST  0[Xx]{HEX_1}{HEX_0}*
NUMBER      {DEC_ICONST}|{HEX_ICONST}

DEC_RCONST  ((0|{DEC_1}{DEC_0}*)[.])|((0[.]|{DEC_1}{DEC_0}*[.]|[.])({DEC_1}{DEC_0}*|0+{DEC_1}{HEX_0}*))
HEX_RCONST  0[Xx](((0|{HEX_1}{HEX_0}*)[.])|((0[.]|{HEX_1}{HEX_0}*[.]|[.])({HEX_1}{HEX_0}*|0+{HEX_1}{HEX_0}*)))
RCONST      {DEC_RCONST}|{HEX_RCONST}

ISA         add|addi|addiu|addu|and|andi|beq|bgez|bgezal|bgtz|blez|bltz|bltzal|bne|div|divu|j|jal|jr|lb|lui|lw|mfhi|mflo|mult|multu|noop|or|ori|sb|sll|sllv|slt|slti|sltiu|sltu|sra|srl|srlv|sub|subu|sw|syscall|xor|xori

%%

.start {
    return START;
}

add {
    return ADD;
}

addi {
    return ADDI;
}

addiu {
    return ADDIU;
}

addu {
    return ADDU;
}

and {
    return AND;
}

andi {
    return ANDI;
}

beq {
    return BEQ;
}

bgez {
    return BGEZ;
}

bgezal {
    return BGEZAL;
}

bgtz {

    return BGTZ;
}

blez {

    return BLEZ;
}

bltz {

    return BLTZ;
}

bltzal {

    return BLTZAL;
}

bne {
    return  BNE;
}

div {
    return DIV;
}

divu {
    return DIVU;
}

j {
    return J;
}

jal {
    return JAL;
}

jr {
    return JR;
}

lb

lui

lw {
    return LW;
}

mfhi

mflo

mult {
    return MULT;
}

multu {
    return MULTU;
}

noop

or {
    return OR;
}

ori {
    return ORI;
}

sb

sll

sllv

slt

slti {
    return SLTI;
}

sltiu {
    return SLTIU;
}

sltu

sra

srl

srlv

sub

subu

sw

syscall

xor

xori


{REG} {
    yylval.string = strdup(yytext);
    return REG;
}

{NUMBER} {
    yylval.string = strdup(yytext);
    return NUM;
}

{LABEL_INSTR} {
    yylval.string = strdup(yytext);
    return LABEL_INSTR;
}

{LABEL_DEFIN} {
    yylval.string = strdup(yytext);
    return LABEL_DEFIN;
}

"(" {       /* LPAREN */
    return LPAREN;
}

")" {       /* RPAREN */
    return RPAREN;
}

"," {       /* COMMA */
    return COMMA;
}

"#".*\n {   /* COMMENTS */
    LINENO++;
//    puts("");
}


{W}+ {      /* WHITESPACES */
    // do nothing
}

\n {        /* NEW LINE */
    LINENO++;
//    puts("");
}

. {   /* If the lexeme is not supported */
    FLAG_ERROR = 1;
    printf("@%zd: Unknown lexeme \'%s\' found.\n", LINENO, yytext);
}

%%
