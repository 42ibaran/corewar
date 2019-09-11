.name "EmIvDa"
.comment "GET OUTTA MAAA HOUSE"

here:
		zjmp	%:see_ya
here2:	sti		r1,	%:live, %1
		sti		r1,	%:see_ya, %1
		sti		r1,	%:see_ya2, %1
		fork	%:clone
live:	live	%42
		zjmp	%:live
		lfork	%2000
		ld		%0, r2
		zjmp	%:live
clone:
		live	%42
		st		r1, -4
		fork	%:here2
		ld		%0, r2
		zjmp	%:clone

see_ya:
		live	%42
		ldi		%1, %:live, r1
		ldi		%1, %:live, r2
		ldi		%1, %:live, r3
		ldi		%1, %:live, r4
		ldi		%1, %:live, r5
		ldi		%1, %:live, r6
		ldi		%1, %:live, r7
		ldi		%1, %:live, r8
		ldi		%1, %:live, r9
		ldi		%1, %:live, r10
		ldi		%1, %:live, r11
		ldi		%1, %:live, r12
		ldi		%1, %:live, r13
		ldi		%1, %:live, r14
		ldi		%1, %:live, r15
		ldi		%1, %:live, r16
see_ya2:
		live	%42
		ld		%0, r13
		zjmp	%511
		


#here:
#		sti		r1,	%:live, %1
#		fork	%:clone
#live:	live	%42
#		zjmp	%:live
#		lfork	%2000
#		ld		%0, r2
#		zjmp	%:live
#clone:
#		live	%42
#		st		r1, -4
#		fork	%:here
#		ld		%0, r2
#		zjmp	%:clone
