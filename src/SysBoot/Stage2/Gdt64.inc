;*************************************************
;	Gdt64.inc
;		-GDT64 Routines
;
;*************************************************
 
%ifndef __GDT_64_INC_INCLUDED__
%define __GDT_64_INC_INCLUDED__
 
bits	32
 
;*******************************************
; InstallGDT64()
;	- Install our GDT64
;*******************************************

InstallGDT64:
  lgdt [GDT64.Pointer]         ; Load the 64-bit global descriptor table.
  ret

;*******************************************
; Global Descriptor Table (GDT 64)
;*******************************************

GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.

    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).

    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.

%endif ;__GDT_64_INC_INCLUDED__