OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o Cluster.o Espera.o
	g++ -o program.exe program.o Proceso.o Procesador.o Cluster.o Espera.o

Proceso.o:  Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

Procesador.o:  Procesador.cc Procesador.hh
	g++ -c Procesador.cc $(OPCIONS)

Cluster.o:  Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS)

Espera.o: Espera.cc Espera.hh
	g++ -c Espera.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

practica.tar: program.cc Cluster.cc Cluster.hh Espera.cc Espera.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh Makefile
	tar -cvf practica.tar program.cc Cluster.cc Cluster.hh Espera.cc Espera.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh Makefile

clean:
	rm *.o
	rm *.exe