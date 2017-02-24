		.model large
		.486

;        .386
;
;        SMART   ;Optimise all code
;
;        LOCALS  ;allow local symbols
;
;        WARN
;
;_data  	segment para public use16 'data'
;
;_data	ends
;
;
;	assume  cs:a_code,ds:_data
;
; Parameters passed as follows:
; 1st in EAX
; 2nd in EDX
; 3rd in EBX
; 4th in ECX
;
a_code	segment word public use32 'code'

	public	mul_64bit_
mul_64bit_	proc near

	imul	edx	;edx:eax = edx*eax
	shl	edx,20
	shr	eax,12
	or	eax,edx
	ret

mul_64bit_		endp


; pass (f0,0,f1) for f0/f1
	public	div_64bit_
div_64bit_	proc near
	idiv	ebx		;result in eax
	mov	ecx,eax
	; fraction = (remainder*4096)/f1
	shl	edx,12		;times 4096
	mov	eax,edx
	xor	edx,edx
	idiv	ebx
	and	eax,4095
	shl	ecx,12
	or	eax,ecx
	ret
div_64bit_	endp
	

a_code	ends


	end

