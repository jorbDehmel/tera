STEM = clang++ -pedantic -Wall -Werror
OBJECTS = trit.o

demo.out:	demo.cpp trit.o tritcpu.o tryteMath.o
	$(STEM) -o demo.out demo.cpp trit.o tritcpu.o tryteMath.o

trit.o:	src/trit.cpp src/trit.hpp
	$(STEM) -c -o trit.o src/trit.cpp

tritcpu.o:	src/tritcpu.cpp src/tritcpu.hpp
	$(STEM) -c -o tritcpu.o src/tritcpu.cpp

tryteMath.o:	src/tryteMath.cpp src/tryteMath.hpp
	$(STEM) -c -o tryteMath.o src/tryteMath.cpp

pclean:
	rm *.o *.out