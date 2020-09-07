%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "asm.h"
    #include "parser.h"
    #include "hash.h"
    #include "globals.h"

    #define GET_NEXT_ADDR(x) x+=4

    static unsigned instr_addr = 0;

    void yyerror  (const char *msg);
    void check_ret(int code);


%}

%union{
    char *string;
}

%start assembly_code

%type<string> address

%token START
%token<string> NUM
%token<string> LABEL_DEFIN
%token<string> LABEL_INSTR
%token<string> REG

%token COMMA
%token RPAREN
%token LPAREN

%token ADD
%token ADDI
%token ADDIU
%token ADDU
%token AND
%token ANDI
%token BEQ
%token BNE
%token BGEZ
%token BGEZAL
%token BGTZ
%token BLEZ
%token BLTZ
%token BLTZAL
%token DIV
%token DIVU
%token J
%token JAL
%token JR
%token MULT
%token MULTU
%token SLTI
%token SLTIU
%token OR
%token ORI

%token LUI

%token LW
%token SW
%%

assembly_code : START NUM instructions
              | instructions
              ;

instructions : instructions instruction
             | /* empty */
             ;

instruction  : LABEL_DEFIN                        { check_ret( INS_NEW_LABEL($1) );         }
             | ADD    REG COMMA REG COMMA REG     { check_ret( INS_NEW_ADD(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | ADDI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ADDI(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | ADDIU  REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ADDIU(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr); }
             | ADDU   REG COMMA REG COMMA REG     { check_ret( INS_NEW_ADDU(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | AND    REG COMMA REG COMMA REG     { check_ret( INS_NEW_AND(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | ANDI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ANDI(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | BEQ    REG COMMA REG COMMA address { check_ret( INS_NEW_BEQ(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | BGEZ   REG COMMA address           { check_ret( INS_NEW_BGEZ(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);      }
             | BGEZAL REG COMMA address           { check_ret( INS_NEW_BGEZAL(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);    }
             | BGTZ   REG COMMA address           { check_ret( INS_NEW_BGTZ(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);      }
             | BLEZ   REG COMMA address           { check_ret( INS_NEW_BLEZ(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);      }
             | BLTZ   REG COMMA address           { check_ret( INS_NEW_BLTZ(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);      }
             | BLTZAL REG COMMA address           { check_ret( INS_NEW_BLTZAL(instr_addr, $2, $4) ); GET_NEXT_ADDR(instr_addr);    }
             | BNE    REG COMMA REG COMMA address { check_ret( INS_NEW_BNE(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | DIV    REG COMMA REG COMMA REG     { check_ret( INS_NEW_DIV(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | DIVU   REG COMMA REG COMMA REG     { check_ret( INS_NEW_DIVU(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | J      address                     { check_ret( INS_NEW_J(instr_addr, $2) ); GET_NEXT_ADDR(instr_addr);             }
             | JAL    address                     { check_ret( INS_NEW_JAL(instr_addr, $2) ); GET_NEXT_ADDR(instr_addr);           }
             | JR     REG                         { check_ret( INS_NEW_JR(instr_addr, $2) ); GET_NEXT_ADDR(instr_addr);            }
             | MULT   REG COMMA REG COMMA REG     { check_ret( INS_NEW_MULT(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | MULTU  REG COMMA REG COMMA REG     { check_ret( INS_NEW_MULTU(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr); }
             | OR     REG COMMA REG COMMA REG     { check_ret( INS_NEW_OR(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | ORI    REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ORI(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);   }
             | SLTI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_SLTI(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr);  }
             | SLTIU  REG COMMA REG COMMA NUM     { check_ret( INS_NEW_SLTIU(instr_addr, $2, $4, $6) ); GET_NEXT_ADDR(instr_addr); }
/*------------------------------------------------------------------------*/
             | LUI   REG COMMA NUM
             | LW    REG COMMA NUM LPAREN REG RPAREN
             | SW    REG COMMA NUM LPAREN REG RPAREN
             ;

address      : LABEL_INSTR
                {
                    int address;
                    if (-1 == (address = map_lookup(lbl_map, $1))) {
                        check_ret(-1);
                    }
                    sprintf($$, "%d", address); // Convert integer to ascii.
                }
             | NUM   { $$ = $1; }
             ;
%%

void yyerror(const char *msg)
{
    printf("@%zd: %s\n", LINENO, msg);
}

/*
 * 0 -> success
 * 1 -> error on s reg
 * 2 -> error on t reg
 * 3 -> error on d reg
 * */
void check_ret(int code)
{
    switch (code) {
    case 0: goto L_SUCC;
    case 1: yyerror("s_reg is not valid."); break;
    case 2: yyerror("t_reg is not valid."); break;
    case 3: yyerror("d_reg is not valid."); break;
    case -1: yyerror("Undefined reference to label."); break;
    default: yyerror("Unknown error occured."); break;
    }

    map_free(lbl_map);
    exit(EXIT_FAILURE);

L_SUCC:
    return;
}
