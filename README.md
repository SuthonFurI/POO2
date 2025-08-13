6/8/25
Para instalar ubuntu
partición de disco
sudo hostnamectl -set-hostname apellidoLegajo

Diferencias entre C y C++

para flags siempre usar BOOL
para nombres usamos sting en vez de char
ya no usamos extensión .h
cctype - cmath - cstdlib
la extension para c++ es .cpp y .c para C

13/8/25
-Manejo de excepciones
  Errores de tiempo de ejecucion
    Entramos a traves de la apliacion, la cual interactua ocn el isstema operativo, luego el sistema operativo le define zonas para programar, en una se carga el codigo, luego hay una zona de datos dinámicos y estáticos, la otra zona es parte de la apliaciòn pero es manejada por el sistema operativo y tiene las llamadas, se llama "stack" conteniendo algunas definiciones globales y las llamadas. (el sistema operativo ve a la aplicación como un proceso)
    Hay 3 flujos estandares construidos por el sistema operativo, flujo de entrada, salida y flujo de errores. Si por ejemplo realizamos un pedido para reservar memoria dinamica, el codigo se lo pide al SO y el mismo guarda memoria en la sección de datos.
  cout<< es enviado al flujo estqandas de salida
  cerr<< es enviando al flujo de errores - esto nos permite tener tener un historial de errores

  Indicador de estado: estan en la zona de datos como datos globales o estáticos. ya no usamos "return...", solo le asignamos un valor nuevo al indicador y luego consultamos el valor final del indicador.
  Excepciones en C++: usamos try para "probar agarrar lo que otro lanza"
Ejemplo (10)
en la zona try puede producirse el error
si se ejecuta bien el resultado es un puntero q apunta a la direcciòn memoria
(11)
En la zona de prueba lanzo y se captura en catch. pero solo captura dependiendo de que se lanzó. "cuando hago throw lo mando a la senguiente capa, si la otra capa puede la manda a la siquiente hasta que llega al SO" (niidea)

raise transporta el error, permite generar librerias solidas.


g++ -o (para compilar)
usamos el makefile con comandos ls/ nano main.cpp (nombre dle archivo a editar)/ cat matriz.h para editar y no tener que compilar cada vez que edito el .cpp o el .h

Modularidad: un modulo es transformar un flujo de trabajo en una caja negra, un modulo es una funcion en un archivo, un modulo es un archivo, el mismo tiene deficiones de constantes u otras cosas. Para un compilaciòn separada generamos archivos separados.

cuando los archivos se unen en un ejecutable enlazandose

Fenomeno vs Concepto
(9) Cuando se genera un objeto se le asigna un proposito y los miembros que forman parte.

Objeto/Clase (10)
Una calse es un molde o categoria, ej: entero

Encapsulamiento (13)
cosas que el objeto sabe hacer

Jerarquia, una entidad depende de otra pero tambien tiene que ver con los elementos que conforman a los objetos bit-byte-variable
La interfaz estaen el lìmite, esta relacionado con el encapsulamiento,
(17) el objeto tiene atributos o variables que manejan datos del objeto, para encapsular hacemos que todos los atributos son privados y le mostramos al usuario la interfaz, la publico es la interfaz.
(18) podemos definir variables del elemento, color, material, display, resolucion.
y las acciones que puede realizar el objeto o lo que sabe hacer: apagar, prender, detectar señal de radio, subir el volumen.
