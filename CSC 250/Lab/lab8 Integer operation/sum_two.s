# @author Patrick Fan {@literal fany218@wfu.edu}
# @date Apr.30, 2021
# @assignment Lab 8
# @file sum_two.s
# @course CSC 250
#
# This program reads two integers and displays the sum
#
# Compile and run (Linux)
#   gcc -no-pie sum_two.s && ./a.out


.text
   .global main               # use main if using C library

sum:
   push %rbp                  # save the old frame
   mov  %rsp, %rbp            # create a new frame
   mov  (%rdi), %rax          # store the first integer in rax
   add  (%rsi), %rax          # sum the two integers and store the result in rax
   pop  %rbp                  # restore old frame
   ret                        # return to C library to end


main:
   push %rbp                  # save the old frame
   mov  %rsp, %rbp            # create a new frame  

   sub  $16, %rsp             # make some space on the stack (stack alignment)

   # prompt the user
   mov  $prompt_format, %rdi  # first printf argument, format string  
   xor  %rax, %rax            # zero out rax  
   call printf                # printf

   # read the value
   mov  $read_format, %rdi    # first scanf argument, format string 
   lea  -12(%rbp), %rsi       # second scanf argument, first memory address
   lea  -8(%rbp), %rdx        # third scanf argument, second memory address
   xor  %rax, %rax            # zero out rax
   call scanf                 # scanf
   
   #calculate the sum
   lea  -12(%rbp), %rdi       # put first integer as first parameter
   lea  -8(%rbp), %rsi        # put second integer as second parameter
   xor  %rax, %rax            # zero out rax
   call sum                   # sum
   
   
   
   
   
   # print to the screen
   mov  $write_format, %rdi   # first printf argument, format string  
   mov  -12(%rbp), %rsi        # second printf argument, the first integer  
   mov  -8(%rbp), %rdx       # third printf argument, the second integer
   mov  %rax, %rcx            # fourth printf argument, the sum result
   xor  %rax, %rax            # zero out rax  
   call printf                # printf

   add  $16, %rsp             # release stack space
   pop  %rbp                  # restore old frame
   ret                        # return to C library to end


.data

read_format:
   .asciz  "%d %d"

prompt_format:
   .asciz  "Enter two integers -> "

write_format:
   .asciz  "%d + %d = %d \n"