section .data
  number: dd 0
  string: times 100 db 0
  inputn: db "Enter a number: ", 0
  inputs: db "Enter a string: ", 0
  outputn: db "Entered number was: %d", 10, 0
  outputs: db "Entered string was: %s", 10, 0
  ifmtn db "%d", 0
  ifmts db "%s", 0

section .text
  global main
  extern scanf
  extern printf
  default rel

main:
  push rbp

  lea rdi, [inputn]
  xor rax, rax
  call printf

  lea rdi, [ifmtn]
  lea rsi, [number]
  xor rax, rax
  call scanf

  lea rdi, [inputs]
  xor rax, rax
  call printf

  lea rdi, [ifmts]
  lea rsi, [string]
  xor rax, rax
  call scanf

  lea rdi, [outputn]
  mov rsi, [number]
  xor rax, rax
  call printf

  lea rdi, [outputs]
  lea rsi, [string]
  xor rax, rax
  call printf

  pop rbp
  xor rax, rax
  ret
