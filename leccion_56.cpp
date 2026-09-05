/* uso de constexpr y const
constexpr int MAX_JUGADORES = 4;          // fijo, conocido de antemano → constexpr
constexpr double PI = 3.14159;              // fijo, conocido de antemano → constexpr

int edad;
std::cin >> edad;
const int edadIngresada = edad;             // no cambia después, pero depende de runtime → const (NO constexpr)

std::string nombre = obtenerNombreDeArchivo();
const std::string nombreUsuario = nombre;   // igual, depende de runtime → const

int puntaje = 0;
puntaje += 10;                                // esto SÍ cambia → ninguno de los dos, variable normal

*/