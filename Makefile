##################################

STEM = clang++ -pedantic -Wall -Werror

##################################

all: bin/tera.out bin/assembler.out bin/tricat.out bin/deco.out bin/benchmark.out

##################################

bin/tera.out:	build/tera.o build/trit.o build/tritcpu.o build/tryteMath.o
	$(STEM) -o bin/tera.out build/tera.o build/trit.o build/tryteMath.o build/tritcpu.o

bin/assembler.out:	build/assemblerMain.o build/assembler.o build/trit.o build/tryteMath.o build/stdmac.o
	$(STEM) -o bin/assembler.out build/assemblerMain.o build/assembler.o build/trit.o build/tryteMath.o build/stdmac.o

bin/tricat.out:	build/tricat.o build/trit.o build/tryteMath.o
	$(STEM) -o bin/tricat.out build/tricat.o build/trit.o build/tryteMath.o

bin/deco.out:	build/deco.o build/assembler.o build/trit.o build/tryteMath.o build/stdmac.o
	$(STEM) -o bin/deco.out build/deco.o build/assembler.o build/trit.o build/tryteMath.o build/stdmac.o

bin/benchmark.out:	benchmark.cpp
	$(STEM) -o bin/benchmark.out benchmark.cpp

##################################

build/tera.o:	tritcpuMain.cpp
	$(STEM) -c -o build/tera.o tritcpuMain.cpp

build/assemblerMain.o:	assemblerMain.cpp
	$(STEM) -c -o build/assemblerMain.o assemblerMain.cpp

build/tricat.o: tricat.cpp
	$(STEM) -c -o build/tricat.o tricat.cpp

build/trit.o:	src/trit.cpp src/trit.hpp
	$(STEM) -c -o build/trit.o src/trit.cpp

build/tritcpu.o:	src/tritcpu.cpp src/tritcpu.hpp
	$(STEM) -c -o build/tritcpu.o src/tritcpu.cpp

build/assembler.o:	src/assembler.cpp src/assembler.hpp
	$(STEM) -c -o build/assembler.o src/assembler.cpp

build/tryteMath.o:	src/tryteMath.cpp src/tryteMath.hpp
	$(STEM) -c -o build/tryteMath.o src/tryteMath.cpp

build/deco.o:	src/decompiler.cpp src/assembler.hpp
	$(STEM) -c -o build/deco.o src/decompiler.cpp

build/stdmac.o:	src/stdMacros.cpp src/stdMacros.hpp
	$(STEM) -c -o build/stdmac.o src/stdMacros.cpp

##################################

pclean:
	rm bin/* build/*

##################################