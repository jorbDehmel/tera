STEM = clang++ -pedantic -Wall -Werror
OBJECTS = trit.o

tritcpu.out:	src/trit.cpp src/tritcpu.cpp src/tryteMath.cpp
	$(STEM) -o tritcpu.out src/trit.cpp src/tritcpu.cpp src/tryteMath.cpp

pclean:
	rm *.o *.out