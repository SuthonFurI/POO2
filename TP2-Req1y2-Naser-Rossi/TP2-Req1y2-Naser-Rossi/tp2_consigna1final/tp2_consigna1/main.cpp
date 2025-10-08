#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <getopt.h>
#include <filesystem>
#include <exception>

#include "Archivo_318.h"
#include "Controlador_318.h"
#include "Interfaz_318.h"
#include "Formato_318.h"
#include "FormatoCSV_318.h"
#include "FormatoJSON_318.h"
#include "FormatoXML_318.h"

// Directorio específico donde se almacenarán los archivos
const std::string DIRECTORIO_DATOS = "./datos/";
const std::string EXTENSION_ARCHIVO = ".csv";

void mostrarAyuda() {
    std::cout << "Uso: programa [opciones]\n\n";
    std::cout << "Opciones:\n";
    std::cout << "  -h, --help                 Mostrar esta ayuda\n";
    std::cout << "  -r, --read <archivo>       Modo lectura: leer archivo existente\n";
    std::cout << "  -w, --write <archivo>      Modo escritura: crear archivo con datos de Arduino\n";
    std::cout << "  -f, --format <c|j|x>       Formato de salida (c=CSV, j=JSON, x=XML) [default: c]\n";
    std::cout << "  -n, --count <numero>       Cantidad de lecturas a realizar [default: 5]\n";
    std::cout << "  -p, --port <puerto>        Puerto serie para Arduino [default: /dev/ttyUSB0]\n";
    std::cout << "  -t, --type <c|j|x>         Tipo de formato de recepción desde Arduino [default: c]\n";
    std::cout << "\nEjemplos:\n";
    std::cout << "  programa -r datos_sensor   # Leer archivo datos_sensor.csv\n";
    std::cout << "  programa -w mediciones -n 10 -f j -t c  # Escribir 10 lecturas en JSON\n";
}

void crearDirectorioSiNoExiste() {
    try {
        if (!std::filesystem::exists(DIRECTORIO_DATOS)) {
            std::filesystem::create_directories(DIRECTORIO_DATOS);
            std::cout << "Directorio creado: " << DIRECTORIO_DATOS << std::endl;
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al crear directorio: " + std::string(e.what()));
    }
}

void mostrarInfoArchivo(const Archivo_318& archivo) {
    std::cout << "\n=== INFORMACIÓN DEL ARCHIVO ===\n";
    std::cout << std::left << std::setw(20) << "Propiedad" << "Valor\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << std::left << std::setw(20) << "Nombre:" << archivo.getName() << "\n";
    std::cout << std::left << std::setw(20) << "Propietario:" << archivo.getOwner() << "\n";
    std::cout << std::left << std::setw(20) << "Fecha mod.:" << archivo.getDatetime();
    std::cout << std::left << std::setw(20) << "Tamaño:" << archivo.getDimension() << " bytes\n";
    std::cout << std::string(50, '=') << "\n";
}

void mostrarDatosEnTabla(const std::vector<std::string>& datos, const std::string& formato) {
    if (datos.empty()) {
        std::cout << "No hay datos para mostrar.\n";
        return;
    }

    std::cout << "\n=== CONTENIDO DEL ARCHIVO ===\n";
    std::cout << "Formato de salida: " << (formato == "c" ? "CSV" : formato == "j" ? "JSON" : "XML") << "\n";
    std::cout << std::string(50, '-') << "\n";

    // Crear el formateador apropiado
    std::unique_ptr<Formato_318> formateador;
    
    if (formato == "j") {
        formateador = std::make_unique<FormatoJSON_318>();
    } else if (formato == "x") {
        formateador = std::make_unique<FormatoXML_318>();
    } else {
        formateador = std::make_unique<FormatoCSV_318>();
    }

    // Mostrar datos formateados
    std::string salidaFormateada = formateador->convertirDeCsv(datos);
    std::cout << salidaFormateada << std::endl;
}

std::string construirRutaCompleta(const std::string& nombreArchivo) {
    std::string rutaCompleta = DIRECTORIO_DATOS + nombreArchivo;
    if (rutaCompleta.find(EXTENSION_ARCHIVO) == std::string::npos) {
        rutaCompleta += EXTENSION_ARCHIVO;
    }
    return rutaCompleta;
}

void modoLectura(const std::string& nombreArchivo, const std::string& formatoSalida) {
    try {
        std::string rutaCompleta = construirRutaCompleta(nombreArchivo);
        Archivo_318 archivo(rutaCompleta);
        
        if (!archivo.exists()) {
            throw std::runtime_error("El archivo '" + rutaCompleta + "' no existe.");
        }

        // Mostrar información del archivo
        mostrarInfoArchivo(archivo);

        // Leer contenido del archivo
        if (!archivo.open(std::ios::in)) {
            throw std::runtime_error("No se pudo abrir el archivo para lectura.");
        }

        std::vector<std::string> datosLeidos;
        std::string linea;
        while (!(linea = archivo.getLine()).empty()) {
            datosLeidos.push_back(linea);
        }
        archivo.close();

        // Mostrar datos en el formato solicitado
        mostrarDatosEnTabla(datosLeidos, formatoSalida);

    } catch (const std::exception& e) {
        std::cerr << "Error en modo lectura: " << e.what() << std::endl;
        throw;
    }
}

void modoEscritura(const std::string& nombreArchivo, const std::string& puertoSerie, 
                   int cantidadLecturas, char tipoRecepcion, const std::string& formatoSalida) {
    try {
        crearDirectorioSiNoExiste();
        
        std::cout << "Iniciando adquisición de datos desde Arduino...\n";
        std::cout << "Puerto: " << puertoSerie << std::endl;
        std::cout << "Cantidad de lecturas: " << cantidadLecturas << std::endl;
        std::cout << "Formato de recepción: " << tipoRecepcion << std::endl;

        // Crear controlador y recibir datos
        Controlador_318 controlador(puertoSerie);
        std::vector<std::string> datosRecibidos = controlador.recibirDatos(cantidadLecturas, tipoRecepcion);
        
        if (datosRecibidos.empty()) {
            throw std::runtime_error("No se recibieron datos del Arduino.");
        }

        std::cout << "Datos recibidos: " << datosRecibidos.size() << " líneas\n";

        // Convertir a CSV (formato interno de almacenamiento)
        std::unique_ptr<Formato_318> formateador;
        if (tipoRecepcion == 'j') {
            formateador = std::make_unique<FormatoJSON_318>();
        } else if (tipoRecepcion == 'x') {
            formateador = std::make_unique<FormatoXML_318>();
        } else {
            formateador = std::make_unique<FormatoCSV_318>();
        }

        std::vector<std::string> datosCSV = formateador->convertirACsv(datosRecibidos);

        // Guardar en archivo
        std::string rutaCompleta = construirRutaCompleta(nombreArchivo);
        Archivo_318 archivo(rutaCompleta);
        
        if (!archivo.open(std::ios::out)) {
            throw std::runtime_error("No se pudo crear el archivo '" + rutaCompleta + "'.");
        }

        for (const auto& linea : datosCSV) {
            archivo.write(linea + "\n");
        }
        archivo.close();

        std::cout << "Archivo guardado exitosamente: " << rutaCompleta << std::endl;

        // Mostrar información del archivo creado
        Archivo_318 archivoCreado(rutaCompleta);
        mostrarInfoArchivo(archivoCreado);

        // Mostrar datos en el formato solicitado
        mostrarDatosEnTabla(datosCSV, formatoSalida);

    } catch (const std::exception& e) {
        std::cerr << "Error en modo escritura: " << e.what() << std::endl;
        throw;
    }
}

int main(int argc, char* argv[]) {
    try {
        // Variables para opciones
        std::string nombreArchivo;
        std::string formatoSalida = "c";  // CSV por defecto
        std::string puertoSerie = "/dev/ttyUSB0";
        char tipoRecepcion = 'c';  // CSV por defecto
        int cantidadLecturas = 5;
        bool modoLec = false;
        bool modoEsc = false;

        // Definir opciones largas
        static struct option opciones_largas[] = {
            {"help",   no_argument,       0, 'h'},
            {"read",   required_argument, 0, 'r'},
            {"write",  required_argument, 0, 'w'},
            {"format", required_argument, 0, 'f'},
            {"count",  required_argument, 0, 'n'},
            {"port",   required_argument, 0, 'p'},
            {"type",   required_argument, 0, 't'},
            {0, 0, 0, 0}
        };

        int opcion;
        int indice_opcion = 0;
        
        while ((opcion = getopt_long(argc, argv, "hr:w:f:n:p:t:", opciones_largas, &indice_opcion)) != -1) {
            switch (opcion) {
                case 'h':
                    mostrarAyuda();
                    return 0;
                    
                case 'r':
                    if (modoEsc) {
                        throw std::runtime_error("No se pueden usar -r y -w simultáneamente.");
                    }
                    modoLec = true;
                    nombreArchivo = optarg;
                    break;
                    
                case 'w':
                    if (modoLec) {
                        throw std::runtime_error("No se pueden usar -r y -w simultáneamente.");
                    }
                    modoEsc = true;
                    nombreArchivo = optarg;
                    break;
                    
                case 'f':
                    formatoSalida = optarg;
                    if (formatoSalida != "c" && formatoSalida != "j" && formatoSalida != "x") {
                        throw std::runtime_error("Formato de salida inválido. Use: c, j, o x");
                    }
                    break;
                    
                case 'n':
                    cantidadLecturas = std::stoi(optarg);
                    if (cantidadLecturas <= 0) {
                        throw std::runtime_error("La cantidad de lecturas debe ser mayor a 0.");
                    }
                    break;
                    
                case 'p':
                    puertoSerie = optarg;
                    break;
                    
                case 't':
                    tipoRecepcion = optarg[0];
                    if (tipoRecepcion != 'c' && tipoRecepcion != 'j' && tipoRecepcion != 'x') {
                        throw std::runtime_error("Tipo de recepción inválido. Use: c, j, o x");
                    }
                    break;
                    
                case '?':
                    std::cerr << "Opción desconocida. Use -h para ayuda.\n";
                    return 1;
                    
                default:
                    mostrarAyuda();
                    return 1;
            }
        }

        // Verificar que se especificó un modo
        if (!modoLec && !modoEsc) {
            std::cerr << "Debe especificar modo de lectura (-r) o escritura (-w).\n";
            mostrarAyuda();
            return 1;
        }

        // Verificar que se especificó un nombre de archivo
        if (nombreArchivo.empty()) {
            throw std::runtime_error("Debe especificar un nombre de archivo.");
        }

        std::cout << "=== HERRAMIENTA DE DATOS ARDUINO ===\n";
        std::cout << "Modo: " << (modoLec ? "LECTURA" : "ESCRITURA") << std::endl;
        std::cout << "Archivo: " << nombreArchivo << std::endl;
        std::cout << std::string(40, '=') << "\n";

        // Ejecutar el modo correspondiente
        if (modoLec) {
            modoLectura(nombreArchivo, formatoSalida);
        } else {
            modoEscritura(nombreArchivo, puertoSerie, cantidadLecturas, tipoRecepcion, formatoSalida);
        }

        std::cout << "\nProceso completado exitosamente.\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
        std::cerr << "Use -h para obtener ayuda.\n";
        return 1;
    } catch (...) {
        std::cerr << "\nError inesperado durante la ejecución.\n";
        return 1;
    }
}

