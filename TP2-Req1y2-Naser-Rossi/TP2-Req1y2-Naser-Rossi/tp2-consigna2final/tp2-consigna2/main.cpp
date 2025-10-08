#include <iostream>
#include <variant>
#include <type_traits>
#include <string>
#include "MensajeReceptor.h" // Mensaje simple
#include "MensajeEmisor.h"   // Mensaje extendido

// Alias para el tipo de datos variante (del archivo Mensaje.h)
using Valor = std::variant<int, double, std::string>;

// Función helper para mostrar un dato y su tipo
void mostrar_valor(const std::string& clave, const Valor& valor) {
    std::cout << "  Dato '" << clave << "': ";
    std::visit([](auto&& arg) { 
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "\"" << arg << "\" (string)";
        } else if constexpr (std::is_same_v<T, int>) {
            std::cout << arg << " (int)";
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << arg << " (double)";
        } else {
            std::cout << "(Tipo no encontrado)";
        }
    }, valor);
    std::cout << "\n";
}

int main() {
    // Nombre del archivo que simula la transmisión
    const std::string ARCHIVO_MENSAJE = "transmision_simulada.txt";

    std::cout << "================================================\n";
    std::cout << "== SIMULACION: FLUJO EMISOR -> RECEPTOR ==\n";
    std::cout << "================================================\n\n";

    // ----------------------------------------------------
    // 1. Lado del EMISOR (Clase MensajeEmisor - Extendido)
    // ----------------------------------------------------
    std::cout << "--- 1. MensajeEmisor (Envia) ---\n";
    MensajeEmisor emisor(201); // Código de 'Creación exitosa'
    emisor.setUsuario("Rossi-Naser");
    emisor.setDispositivo("467-318");
    emisor.agregarDato("Temperatura", 25.6); // Dato genérico (double)
    emisor.agregarDato("Status", std::string("Listo")); // Dato genérico (string)
    
    // El EMISOR SERIALIZA y GUARDA el mensaje completo (incluyendo IDs)
    if (emisor.guardarEnArchivo(ARCHIVO_MENSAJE)) {
        std::cout << "EMISOR: Mensaje serializado y guardado en '" << ARCHIVO_MENSAJE << "'.\n";
        std::cout << "   Serializado completo:\n   " << emisor.serializar() << "\n\n";
    } else {
        std::cerr << "EMISOR: ERROR al guardar.\n";
        return 1;
    }

    // ----------------------------------------------------
    // 2. Lado del RECEPTOR (Clase MensajeReceptor - Simple)
    // ----------------------------------------------------
    std::cout << "--- 2. MensajeReceptor (Recibe) ---\n";
    MensajeReceptor receptor; // Instancia vacía

    // El RECEPTOR CARGA el archivo. Usa el deserializador heredado que IGNOORA IDs.
    if (receptor.cargarDesdeArchivo(ARCHIVO_MENSAJE)) {
        std::cout << "RECEPTOR: Archivo cargado exitosamente.\n";
        
        // Comprobar datos recibidos:
        std::cout << "   -> Codigo de Operacion: " << receptor.getCodigoOperacion() << "\n";
        
        // El RECEPTOR SÍ recibe los datos genéricos:
        std::cout << "   -> Datos recibidos:\n";
        mostrar_valor("Temperatura", receptor.obtenerDato("Temperatura"));
        mostrar_valor("Status", receptor.obtenerDato("Status"));
        
        // El RECEPTOR INTENTA obtener un dato específico del Emisor (NO DEBE EXISTIR en el objeto):
        //std::cout << "\n   -> Intentando acceder a datos de Emisor (debería retornar vacío):\n";
        //mostrar_valor("Usuario:", receptor.obtenerDato("Usuario:"));
        
    } else {
        std::cerr << "RECEPTOR: ERROR al cargar el mensaje.\n";
        return 1;
    }

    // ----------------------------------------------------
    // 3. Demostración del MensajeEmisor guardando/cargando por sí mismo (Nota)
    // ----------------------------------------------------
    //std::cout << "\n--- 3. Demostración de Persistencia propia del Emisor (Nota) ---\n";
    //MensajeEmisor emisor_check;
    //if (emisor_check.cargarDesdeArchivo(ARCHIVO_MENSAJE)) {
        //std::cout << "EMISOR CHECK: Archivo cargado (con toda la información).\n";
        //std::cout << "   -> ID Usuario: " << emisor_check.getUsuario() << " (OK)\n";
    //}

    return 0;
}