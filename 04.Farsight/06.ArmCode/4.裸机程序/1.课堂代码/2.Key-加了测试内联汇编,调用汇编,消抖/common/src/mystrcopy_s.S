
.global mystrcopy
mystrcopy:
  LDRB r2, [r1], #1
  STRB r2, [r0], #1
  CMP r2, #0
  BNE mystrcopy



