all: asm vm dasm

re: fclean all

fclean:
	make -C assembly/ fclean
	make -C vm/ fclean
	make -C dasm/ fclean

clean:
	make -C assembly/ clean
	make -C vm/ clean
	make -C dasm/ clean

asm:
	make -C assembly/

vm:
	make -C vm/

dasm:
	make -C dasm/

.PHONY: asm vm all fclean clean dasm
