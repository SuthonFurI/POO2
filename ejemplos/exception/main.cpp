#include <iostream>
#include "Alumno.h"

int main() {
    try {
        // Caso OK
        Alumno a1("Julieta", 123, 8.5f);
        std::cout << a1.getNombre() << " (" << a1.getLegajo()
                  << ") promedio: " << a1.getPromedio() << "\n";

        // Forzamos un error de validación
        Alumno a2("Carlos", 456, 12.0f); // 12 es inválido -> lanza excepción
        std::cout << a2.getNombre() << " promedio: " << a2.getPromedio() << "\n";
    }
    catch (const ValidacionError& e) {        // nuestra excepción
        std::cout << "Error de validacion: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e) {   // respaldo para errores en tiempo de ejecución
        std::cout << "Excepcion runtime: " << e.what() << "\n";
    }
    catch (const std::exception& e) {         // respaldo general (std::bad_alloc, etc.)
        std::cout << "Excepcion std: " << e.what() << "\n";
    }
    catch (...) {                              // último recurso
        std::cout << "Excepcion desconocida\n";
    }
    //Las cadenas de catch van desde el mas especifico al mas generico
    //en nuestro caso validaciónError es derivado de std::exception

    // El programa sigue vivo
    std::cout << "Fin del programa\n";
    return 0;
}
