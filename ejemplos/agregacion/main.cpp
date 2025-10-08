#include <iostream>
#include "Libro.h"
#include "Estudiante.h"

int main() {
    // Creamos libros (existen independientemente)
    Libro libro1("Cien años de soledad", "Gabriel García Márquez");
    Libro libro2("El principito", "Antoine de Saint-Exupéry");
    Libro libro3("1984", "George Orwell");
    
    std::cout << "=== LIBROS DISPONIBLES ===" << std::endl;
    libro1.mostrarInfo();
    libro2.mostrarInfo();
    libro3.mostrarInfo();
    
    std::cout << "\n=== ESTUDIANTES ===" << std::endl;
    // Creamos estudiantes
    Estudiante juan("Juan");
    Estudiante maria("María");
    
    // Los estudiantes USAN los libros (agregación)
    std::cout << "\n=== PRÉSTAMOS ===" << std::endl;
    juan.prestarLibro(&libro1);
    juan.prestarLibro(&libro3);
    maria.prestarLibro(&libro2);
    
    // Mostramos qué tiene cada estudiante
    juan.mostrarLibrosPrestados();
    maria.mostrarLibrosPrestados();
    
    // Juan devuelve un libro
    std::cout << "\n=== DEVOLUCIÓN ===" << std::endl;
    juan.devolverLibro(&libro1);
    
    juan.mostrarLibrosPrestados();
    
    std::cout << "\n=== LOS LIBROS SIGUEN EXISTIENDO ===" << std::endl;
    std::cout << "Incluso si los estudiantes ya no los tienen:" << std::endl;
    libro1.mostrarInfo();
    
    return 0;
    // Al salir del main:
    // - Los libros se destruyen
    // - Los estudiantes se destruyen
    // - Pero ninguno depende del otro para su existencia
}