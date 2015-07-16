%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "asm.h"
    #include "parser.h"
    #include "hash.h"
    #include "globals.h"


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
             | ADD    REG COMMA REG COMMA REG     { check_ret( INS_NEW_ADD($2, $4, $6) );   }
             | ADDI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ADDI($2, $4, $6) );  }
             | ADDIU  REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ADDIU($2, $4, $6) ); }
             | ADDU   REG COMMA REG COMMA REG     { check_ret( INS_NEW_ADDU($2, $4, $6) );  }
             | AND    REG COMMA REG COMMA REG     { check_ret( INS_NEW_AND($2, $4, $6) );   }
             | ANDI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ANDI($2, $4, $6) );  }
             | BEQ    REG COMMA REG COMMA address { check_ret( INS_NEW_BEQ($2, $4, $6) );   }
             | BGEZ   REG COMMA address           { check_ret( INS_NEW_BGEZ($2, $4) );      }
             | BGEZAL REG COMMA address           { check_ret( INS_NEW_BGEZAL($2, $4) );    }
             | BGTZ   REG COMMA address           { check_ret( INS_NEW_BGTZ($2, $4) );      }
             | BLEZ   REG COMMA address           { check_ret( INS_NEW_BLEZ($2, $4) );      }
             | BLTZ   REG COMMA address           { check_ret( INS_NEW_BLTZ($2, $4) );      }
             | BLTZAL REG COMMA address           { check_ret( INS_NEW_BLTZAL($2, $4) );    }
             | BNE    REG COMMA REG COMMA address { check_ret( INS_NEW_BNE($2, $4, $6) );   }
             | DIV    REG COMMA REG COMMA REG     { check_ret( INS_NEW_DIV($2, $4, $6) );   }
             | DIVU   REG COMMA REG COMMA REG     { check_ret( INS_NEW_DIVU($2, $4, $6) );  }
             | J      address                     { check_ret( INS_NEW_J($2) );             }
             | JAL    address                     { check_ret( INS_NEW_JAL($2) );           }
             | JR     REG                         { check_ret( INS_NEW_JR($2) );            }
             | MULT   REG COMMA REG COMMA REG     { check_ret( INS_NEW_MULT($2, $4, $6) );  }
             | MULTU  REG COMMA REG COMMA REG     { check_ret( INS_NEW_MULTU($2, $4, $6) ); }
             | OR     REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ORI($2, $4, $6) );   }
             | ORI    REG COMMA REG COMMA NUM     { check_ret( INS_NEW_ORI($2, $4, $6) );   }
             | SLTI   REG COMMA REG COMMA NUM     { check_ret( INS_NEW_SLTI($2, $4, $6) );  }
             | SLTIU  REG COMMA REG COMMA NUM     { check_ret( INS_NEW_SLTIU($2, $4, $6) ); }
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
