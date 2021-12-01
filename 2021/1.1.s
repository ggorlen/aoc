.data  
fin: .asciiz "1.txt"
buffer: .space 1
line: .space 1024
.globl main
.text
main:
    la $s1 buffer
    la $s2 line
    li $s3 0      # current line length
    li $s6 2147483 # last line
    li $s7 0      # count of lines where line[i] > line[i-1]

    # open file
    li $v0 13     # syscall for open file
    la $a0 fin    # input file name
    li $a1 0      # read flag
    li $a2 0      # ignore mode 
    syscall       # open file 
    move $s0 $v0  # save the file descriptor 

read_loop:

    # read byte from file
    li $v0 14     # syscall for read file
    move $a0 $s0  # file descriptor 
    move $a1 $s1  # address of dest buffer
    li $a2 1      # buffer length
    syscall       # read byte from file

    # keep reading until bytes read <= 0
    blez $v0 read_done

    # naively handle exceeding line size by exiting
    slti $t0 $s3 1024
    beqz $t0 read_done

    # if current byte is a newline, consume line
    lb $s4 ($s1)
    li $t0 10
    beq $s4 $t0 consume_line

    # otherwise, append byte to line
    add $s5 $s3 $s2
    sb $s4 ($s5)

    # increment line length
    addi $s3 $s3 1

    b read_loop

consume_line:

    # null terminate line
    add $s5 $s3 $s2
    sb $zero ($s5)

    # reset bytes read
    li $s3 0

    # convert chunk to number
    move $a0 $s2
    jal atoi

    # result++ if current line > last line
    bgt $s6 $v0 post_increment
    addi $s7 $s7 1

post_increment:

    # set the current line as the last line
    move $s6 $v0

    b read_loop

read_done:

    # print the result
    move $a0 $s7
    li $v0 1
    syscall

    # print newline
    li $a0 10
    li $v0 11
    syscall

    # close file
    li $v0 16     # syscall for close file
    move $a0 $s0  # file descriptor to close
    syscall       # close file

    # exit the program
    li $v0 10
    syscall

atoi:
    addi $sp $sp -20
    sw $s0 ($sp)
    sw $s1 4($sp)
    sw $s2 8($sp)
    sw $s3 12($sp)
    sw $s4 16($sp)
    move $s0 $a0  # addr of string number
    li $s1 0      # index
    li $s2 0      # result

atoi_loop:
    # load s[i]
    add $s4 $s1 $s0
    lb $s3 ($s4)

    # break if null
    beqz $s3 atoi_done

    # convert ascii to digit
    addi $s3 $s3 -48

    # result *= 10
    li $s4 10
    mul $s2 $s2 $s4

    # result += digit
    add $s2 $s2 $s3

    # index++
    addi $s1 $s1 1

    j atoi_loop

atoi_done:
    move $v0 $s2
    lw $s0 ($sp)
    lw $s1 4($sp)
    lw $s2 8($sp)
    lw $s3 12($sp)
    lw $s4 16($sp)
    addi $sp $sp 20
    jr $ra

