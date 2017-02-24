#
#       Watcom make file
#

wlink_options=

#wcc_options  =  /7 /d2 /5r /mf /zq /fp3 /4 /zp4 /s

#wcc_options	= /5r /7 /fp5 /zp4 /zq /s
wcc_options	= /5r /7 /fp5 /zp4 /zq /os /s /d2
#wcc_options	= /4r /7 /fp3 /zp4 /zq /d2 /s

wasm_options = -4s

# Auto included in every file.
header_files =	
#use & as a line extender
object_files =	test.obj &
		euro_gen.obj euro_spt.obj euro_dsk.obj euro_mem.obj euro_grf.obj euro_var.obj &
		euro_sqd.obj euro_fix.obj euro_sel.obj euro_inf.obj euro_cnt.obj euro_usr.obj euro_win.obj &
		euro_inp.obj euro_mod.obj euro_net.obj euro_cmd.obj euro_gdv.obj euro_mat.obj euro_rnd.obj &
		euro_int.obj euro_fxd.obj &
		menu.obj results.obj unmangle.obj intronet.obj &
		control.obj mallocx.obj gamedata.obj audio.obj

test.exe	: $(object_files)
		wlink $(wlink_options) @INFO

test.obj	: test.cpp *.h $(header_files)

mallocx.obj	: 
		  wpp386 mallocx.c $(wcc_options) 

menu.obj	: menu.cpp  

results.obj	: results.cpp  

unmangle.obj	: 
		  wpp386 unmangle.c $(wcc_options)

intronet.obj	: intronet.c *.h 

control.obj	: control.cpp 


gamedata.obj	: gamedata.cpp  
		  wpp386 gamedata.cpp $(wcc_options) 

euro_sqd.obj	: euro_sqd.cpp *.h 
euro_fix.obj	: euro_fix.cpp *.h 
euro_grf.obj	: euro_grf.cpp *.h 
euro_spt.obj	: euro_spt.cpp *.h 
euro_gen.obj	: euro_gen.cpp *.h 
euro_inf.obj	: euro_inf.cpp *.h 
euro_dsk.obj	: euro_dsk.cpp *.h 
euro_mem.obj	: euro_mem.cpp *.h 
euro_cnt.obj	: euro_cnt.cpp *.h 
euro_usr.obj	: euro_usr.cpp *.h 
euro_mat.obj	: euro_mat.cpp *.h 
euro_win.obj	: euro_win.cpp *.h 
euro_gdv.obj	: euro_gdv.cpp *.h 
euro_net.obj	: euro_net.c   *.h 
euro_mod.obj	: euro_mod.cpp *.h 
euro_rnd.obj	: euro_rnd.cpp *.h 
euro_inp.obj	: euro_inp.cpp *.h 
euro_cmd.obj	: euro_cmd.cpp *.h 
euro_var.obj	: euro_var.cpp *.h 
euro_int.obj	: euro_int.cpp *.h 
euro_fxd.obj	: euro_fxd.asm *.h 
#3deng.obj	: 3deng.c *.h

.cpp.obj:	
		wpp386 $*.cpp $(wcc_options)

3deng.obj:	
		wpp386 3deng.c $(wcc_options)

.c.obj:	
		wcc386 $*.c $(wcc_options)


.asm.obj:	
		wasm $*.asm $(wasm_options)




