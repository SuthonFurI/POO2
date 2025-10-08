CXX = g++
CXXFLAGS = -Wall -std=c++17

OBJS = main.o Archivo_318.o Controlador_318.o Interfaz_318.o \
       FormatoCSV_318.o FormatoJSON_318.o FormatoXML_318.o

all: programa

programa: $(OBJS)
	$(CXX) $(CXXFLAGS) -o programa $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o programa


	
