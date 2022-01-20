# @author Patrick Fan {@literal fany218@wfu.edu}
# @date Apr. 30, 2021
# @assignment Lab 8
# @file print_max.s
# @course CSC 250
#
# This program reads a sequence of integers until a negative
# value is entered and displays the current maximum
#
# Compile and run (Linux)
#   gcc -no-pie print_max.s && ./a.out


.text
   .global main               # use main if using C library


main:
   push %rbp                  # save the old frame
   mov  %rsp, %rbp            # create a new frame  
   
   sub  $16, %rsp             # make some space on the stack (stack alignment)
   
   movl $0, 8(%rsp)           # local variable storing the current maximum, 
                              # initialized to be 0

.L1:
   # prompt the user
   movl  $prompt_format, %edi # first printf argument, format string  
   xorl  %eax, %eax           # zero out rax  
   call printf                # printf

   # read the value
   movl $read_format, %edi    # first scanf argument, format string 
   leaq 12(%rsp), %rsi        # second scanf argument, memory address
   xorl  %eax, %eax           # zero out rax
   call scanf                 # scanf
   
   # conditional jump to ending the loop
   cmpl  $0, 12(%rsp)         # compare the entered integer with 0
   jl   .L3
   

   # determine current max
   movl  12(%rsp), %eax       # move the current value into rax for comparison
   cmpl  %eax, 8(%rsp)        # compare eax with current max
   jge .L2                    # skip the following segments if 
                              # the current value is smaller
   mov  %eax, 8(%rsp)         # otherwise store the current value as max
   
.L2:
   # print to the screen
   movl  $write_format, %edi  # first printf argument, format string  
   movl 8(%rsp), %esi         # second printf argument, the current max
   xorl  %eax, %eax           # zero out rax  
   call printf                # printf
   jmp .L1

.L3:
   add  $16, %rsp             # release stack space
   pop  %rbp                  # restore old frame
   ret                        # return to C library to end


.data

read_format:
   .asciz  "%d"

prompt_format:
   .asciz  "Enter an integer (negative to quit) -> "

write_format:
   .asciz  "Current max is %d \n"
