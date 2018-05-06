.data
n1: .asciiz "Digite o primeiro numero "
n2: .asciiz "Digite o segundo numero "
op: .asciiz "Digite a operacao(+/*) "

.text
main: # IMPRIME E OBTEM DADOS, OPERANDOS E OPERADOR.
li $v0 4
la $a0 n1
syscall
li $v0 6
syscall
mfc1 $s0, $f0

li $v0 4
la $a0 n2
syscall
li $v0 6
syscall
mfc1 $s1, $f0

li $v0 4
la $a0 op
syscall
li $v0 12
syscall
# PASSA DADOS PARA VARIAVEIS APROPRIADAS.
add $a0 $s0 $zero # n1
add $a1 $s1 $zero # n2
add $s2 $v0 $zero # op

some:
jal norm_single
add $t7 $t2 $t3 # soma mantissas
j exit

exit:
li $v0, 10
syscall

get_s:
srl $v0, $a0, 31
jr $ra

get_exp:
srl $v0 $a0 23
andi $v0 $v0 0xff
jr $ra

get_man:
andi $v0 $a0 0x7fffff
jr $ra

norm_single:
jal get_exp
ori $t0 $v0 0 # exp n1
jal get_exp
ori $t1 $v0 0 # exp n2
jal get_man
ori $t2 $v0 0 # mantissa n1
jal get_man
ori $t3 $v0 0 # mantissa n2
not_equal:
bgt $t0 $t1 t0_gt
bgt $t1 $t0 t1_gt
jr $ra
t0_gt:
sub $t7 $t0 $t1
srlv $t3 $t3 $t7
add $t1 $t0 $zero
j not_equal
t1_gt:
sub $t7 $t1 $t0
srlv $t2 $t2 $t7
add $t0 $t1 $zero
j not_equal