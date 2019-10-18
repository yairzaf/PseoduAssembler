# assembler for a ficitional 14 - bit machine
 ##### this is a summary, for the full assignment look at assignment.pdf (hebrew)

## architecture:

### memory:
256X14bit-word

cann't reference an address directly, can reference a label in the instruction segement or the data segment.

### registers:
8 14-bit registers.

refernce in code:

r0,r1,r3 . . .  r7

### flags:
zero flag.

## syntax:

### labels:
first letter can't be a number.

can contain only letters and numbers (lower and uppercase).

will end with ':'.

max size of 32 characters.

examples:
```
START: mov r1,r2
HelloWorld123:
.string "hello world"
EOF:
```
### direct data for instructions:

begins with '#'.

must contain only numbers, can't be empty.

examples:

mov #4567,r5

add #11,NUM



### instructions:
```
mov source operand,destination operand

cmp operand,operand

add operand to add,added operand

sub operand to subtract,subtracted operand

lea address operand,destination operand

not operand

clr operand

inc operand

dec operand

jmp address operand(optional operand as argument,optional operand as argument)

bne address operand(optional operand as argument,optional operand as argument)

red operand

prn operand

jsr address operand(optional operand as argument,optional operand as argument)

rts

stop
```

examples:

START:

lea START(r2,#84)

mov #1,r2

add NUM,NUM2


### specifcations for the assembler.

.data number array

.string "string"

this will add the specified data to the data segment

examples:
 
.data -56,84,911,23
 
.string "hello world"
 
 ### comment:
 comment will start with ';' at the begining of a line.
 
 the assembler will ignore those lines.
 
 examples:
 
 ; my program
 
 ; insert routine here
 
 
 #### for the inner workings of the assembler, look at ASSEMBLER_DESC.pdf
 
