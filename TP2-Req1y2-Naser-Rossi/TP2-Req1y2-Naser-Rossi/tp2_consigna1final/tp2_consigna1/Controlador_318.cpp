
#include "Controlador_318.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdexcept>
#include <iostream>

Controlador_318::Controlador_318(const std::string& puerto) : puertoSerie(puerto) {}

std::vector<std::string> Controlador_318::recibirDatos(int cantidad, char formato) {
    std::vector<std::string> datos;

    int fd = open(puertoSerie.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) throw std::runtime_error("No se pudo abrir el puerto serie");

    struct termios tty{};
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B19200);
    cfsetispeed(&tty, B19200);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag &= ~IGNBRK;
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 5;
    tcsetattr(fd, TCSANOW, &tty);

    // Limpiar buffer inicial del Arduino
    std::cout << "Limpiando buffer inicial..." << std::endl;
    sleep(2);
    tcflush(fd, TCIFLUSH);

    for (int i = 0; i < cantidad; i++) {
        std::cout << "Solicitando dato " << (i+1) << "/" << cantidad << " (formato: " << formato << ")" << std::endl;
        
        // Enviar comando
        write(fd, &formato, 1);
        fsync(fd);
        
        // Esperar respuesta adecuada según el formato
        if (formato == 'c') {
            // CSV: una línea simple
            usleep(200000); // 200ms
            std::string linea;
            char buf;
            int timeout = 0;
            while (timeout < 50) { // 5 segundos máximo
                int n = read(fd, &buf, 1);
                if (n > 0) {
                    if (buf == '\n') break;
                    if (buf != '\r') linea.push_back(buf);
                } else {
                    usleep(100000); // 100ms
                    timeout++;
                }
            }
            if (!linea.empty()) {
                datos.push_back(linea);
                std::cout << "CSV recibido: " << linea << std::endl;
            }
        } 
        else if (formato == 'j') {
            // JSON: leer todo hasta encontrar el final
            usleep(300000); // 300ms - JSON es más lento
            std::string json_completo;
            char buf;
            int timeout = 0;
            int llaves_abiertas = 0;
            bool iniciado = false;
            
            while (timeout < 100) { // 10 segundos máximo para JSON
                int n = read(fd, &buf, 1);
                if (n > 0) {
                    json_completo.push_back(buf);
                    
                    if (buf == '{') {
                        llaves_abiertas++;
                        iniciado = true;
                    } else if (buf == '}') {
                        llaves_abiertas--;
                        if (iniciado && llaves_abiertas == 0) {
                            // JSON completo
                            break;
                        }
                    }
                    timeout = 0; // Reset timeout si recibimos datos
                } else {
                    usleep(100000); // 100ms
                    timeout++;
                }
            }
            
            if (!json_completo.empty()) {
                // Limpiar el JSON: quitar saltos de línea y espacios extras
                std::string json_limpio;
                for (char c : json_completo) {
                    if (c != '\n' && c != '\r' && c != '\t') {
                        json_limpio += c;
                    }
                }
                datos.push_back(json_limpio);
                std::cout << "JSON recibido: " << json_limpio.substr(0, 50) << "..." << std::endl;
            }
        }
        else if (formato == 'x') {
            // XML: leer hasta </registro>
            usleep(300000); // 300ms
            std::string xml_completo;
            char buf;
            int timeout = 0;
            
            while (timeout < 100) { // 10 segundos máximo
                int n = read(fd, &buf, 1);
                if (n > 0) {
                    xml_completo.push_back(buf);
                    
                    // Verificar si terminó el registro XML
                    if (xml_completo.size() >= 11) { // longitud mínima de "</registro>"
                        if (xml_completo.find("</registro>") != std::string::npos) {
                            break;
                        }
                    }
                    timeout = 0;
                } else {
                    usleep(100000);
                    timeout++;
                }
            }
            
            if (!xml_completo.empty()) {
                // Limpiar XML: convertir a una línea
                std::string xml_limpio;
                for (char c : xml_completo) {
                    if (c != '\n' && c != '\r' && c != '\t') {
                        xml_limpio += c;
                    } else if (!xml_limpio.empty() && xml_limpio.back() != ' ') {
                        xml_limpio += ' ';
                    }
                }
                datos.push_back(xml_limpio);
                std::cout << "XML recibido: " << xml_limpio.substr(0, 50) << "..." << std::endl;
            }
        }
        
        // Pausa entre lecturas
        if (i < cantidad - 1) {
            std::cout << "Esperando antes del siguiente..." << std::endl;
            sleep(1);
        }
    }

    close(fd);
    std::cout << "Total datos recibidos: " << datos.size() << std::endl;
    return datos;
}