.data  
fin: .asciiz "2.1.txt"
lo: .word 0
hi: .word 0
line: .space 128
chunk: .space 16
buffer: .space 1
char: .space 1
.globl main
.text
main:
    # open file
    li $v0 13     # syscall for open file
    la $a0 fin    # input file name
    li $a1 0      # read flag
    li $a2 0      # ignore mode 
    syscall       # open a file 
    move $s0 $v0  # save the file descriptor 

    la $s2 buffer
    la $s3 line
    la $s7 chunk
    li $s4 0  # bytes read
    li $t5 0  # total valid passwords

read_loop:
    # read byte from file
    li $v0 14     # syscall for reading from file
    move $a0 $s0  # file descriptor 
    move $a1 $s2  # address of dest buffer
    li $a2 1      # buffer length
    syscall       # read byte from file

    # save number of bytes read
    move $s1 $v0

    # keep reading until bytes read <= 0
    blez $s1 read_done

    # if byte is a newline, start a new line
    lb $s5 ($s2)
    beq $s5 10 consume_line

    # otherwise, append byte to line
    lb $s5 ($s2)
    add $s6 $s4 $s3
    sb $s5 ($s6)

    # increment total number of bytes read
    addi $s4 $s4 1

    j read_loop

consume_line:
    # null terminate line
    addi $s6 $s6 1
    sb $0 ($s6)

    li $t0 0  # line index = 0
    li $t3 0  # chunk index = 0

lo_loop:
    add $t1 $s3 $t0
    lb $t1 ($t1)
    beq $t1 45 lo_loop_end

    add $t2 $s7 $t0
    sb $t1 ($t2)

    addi $t0 $t0 1  # i++
    
    j lo_loop

lo_loop_end:
    # null terminate chunk
    addi $t2 $t2 1
    sb $zero ($t2)

    addi $t0 $t0 1  # i++

    # convert chunk to number
    move $a0 $s7
    jal atoi
    la $t1 lo
    sw $v0 ($t1)

    li $t3 0  # chunk index = 0

hi_loop:
    add $t1 $s3 $t0
    lb $t1 ($t1)
    beq $t1 32 hi_loop_end

    add $t2 $s7 $t3
    sb $t1 ($t2)

    addi $t0 $t0 1  # line i++
    addi $t3 $t3 1  # chunk i++
    
    j hi_loop

hi_loop_end:
    # null terminate chunk
    addi $t2 $t2 1
    sb $zero ($t2)

    # get char
    addi $t0 $t0 1  # i++
    add $t1 $s3 $t0
    lb $t1 ($t1)
    sb $t1 char($0)

    # convert chunk to number
    move $a0 $s7
    jal atoi
    la $t1 hi
    sw $v0 ($t1)

    addi $t0 $t0 3  # i += 2
    li $t4 0        # count of matching chars

pw_loop:
    add $t1 $s3 $t0
    lb $t1 ($t1)
    beqz $t1 pw_loop_end

    # if the char matches with target, count++
    lb $t6 char($0)
    bne $t1 $t6 pw_loop_increment
    addi $t4 1      # count++

pw_loop_increment:
    addi $t0 $t0 1  # i++
    j pw_loop

pw_loop_end:
    # reset bytes read for the next line
    li $s4 0

    # if lo <= count <= hi, it's a valid pw
    lw $t1 lo
    lw $t6 hi
    blt $t4 $t1 read_loop
    sub $t6 $t6 $t4
    bltz $t6 read_loop

    addi $t5 1  # total_valid_passwords++
    j read_loop

read_done:
    # print total count of valid pws
    move $a0 $t5
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

