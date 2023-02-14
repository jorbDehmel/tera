##################################

STEM = clang++ -pedantic -Wall -Werror

##################################

all: bin/tritcpu.out bin/assembler.out bin/tricat.out

##################################

bin/tritcpu.out:	bin tritcpuMain.cpp build/trit.o build/tritcpu.o build/tryteMath.o
	$(STEM) -o bin/tritcpu.out tritcpuMain.cpp build/trit.o build/tryteMath.o build/tritcpu.o

bin/assembler.out:	bin assemblerMain.cpp build/assembler.o build/trit.o build/tryteMath.o
	$(STEM) -o bin/assembler.out assemblerMain.cpp build/assembler.o build/trit.o build/tryteMath.o

bin/tricat.out:	bin tricat.cpp build/trit.o build/tryteMath.o
	$(STEM) -o bin/tricat.out tricat.cpp build/trit.o build/tryteMath.o

##################################

build/trit.o:	build src/trit.cpp src/trit.hpp
	$(STEM) -c -o build/trit.o src/trit.cpp

build/tritcpu.o:	build src/tritcpu.cpp src/tritcpu.hpp
	$(STEM) -c -o build/tritcpu.o src/tritcpu.cpp

build/assembler.o:	build src/assembler.cpp src/assembler.hpp
	$(STEM) -c -o build/assembler.o src/assembler.cpp

build/tryteMath.o:	build src/tryteMath.cpp src/tryteMath.hpp
	$(STEM) -c -o build/tryteMath.o src/tryteMath.cpp

##################################

bin:
	mkdir bin

build:
	mkdir build

##################################

pclean:
	rm bin/* build/*

##################################