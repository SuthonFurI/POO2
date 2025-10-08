# Compilador
CXX = g++
# Flags de compilación
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Archivos fuente y objetos
SRCS = main.cpp Mensaje.cpp MensajeEmisor.cpp MensajeReceptor.cpp
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
TARGET = programa2

# Regla por defecto
all: $(TARGET)

# Linkeo final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa (compilar + correr)
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos intermedios y binarios
clean:
	rm -f $(OBJS) $(TARGET)
