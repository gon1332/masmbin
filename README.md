MAsmBin
===

A MIPS assembler built to assist the students in the labs part of Computer
System Organization lesson taken place in University of Thessaly, Electrical
and Computer Engineering Department.


Use cases
---

1. Evaluation tool of the binary representation of MIPS assembly. Students can
   use it to see how an assembly program can be repesented in binary format.

2. Helping tool for giving large inputs in the MIPS simulator that they will be
   called to implement in labs. MAsmBin outputs binary to be out-of-the-box
   compatible with the `$readmemb()` command found in Verilog.


Supported instructions (under construction)
---

| Opcodes | Format | Syntax |
|:-------:|:------:|--------|
| ADD     |   R    |        |
| ADDI    |   I    |        |
| ADDIU   |   I    |        |
| ADDU    |   R    |        |
| AND     |   R    |        |
| ANDI    |   I    |        |
| BEQ     |   I    |        |
| BGEZ    |       |        |
| BGEZAL  |       |        |
| BGTZ    |       |        |
| BLEZ    |       |        |
| BLTZ    |       |        |
| BLTZAL  |       |        |
| BNE     |       |        |
| DIV     |       |        |
| DIVU    |       |        |
| J       |       |        |
| JAL     |       |        |
| JR      |       |        |
| MULT    |       |        |
| MULTU   |       |        |
| OR      |       |        |
| ORI     |       |        |
| SLTI    |       |        |
| SLTIU   |       |        |

