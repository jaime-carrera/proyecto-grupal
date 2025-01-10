

#include "Casino.h"

// Constructor: inicializa los juegos y carga los jugadores desde un archivo
Casino::Casino() {
    try {
        juegos.push_back(new Ruleta());        // Juego 1: Ruleta
        juegos.push_back(new Blackjack());    // Juego 2: Blackjack
        juegos.push_back(new Tragamonedas()); // Juego 3: Tragamonedas
        cargarJugadores(); // Cargar jugadores al iniciar el casino
    } catch (const exception& e) {
        cerr << "Excepción al inicializar el casino: " << e.what() << endl;
    }
}


// Destructor: libera memoria y guarda los jugadores en un archivo
Casino::~Casino() {
    try {
        for (Juego* juego : juegos) {
            delete juego;
        }
        guardarJugadores(); // Guardar jugadores al cerrar el casino
    } catch (const exception& e) {
        cerr << "Excepción al cerrar el casino: " << e.what() << endl;
    }
}

// Cargar jugadores desde un archivo
void Casino::cargarJugadores() {
    try {
        ifstream archivo("jugadores.txt");
        if (!archivo.is_open()) { // Comprobar si el archivo se abre correctamente
            cerr << "Error al abrir el archivo de jugadores para lectura." << endl;
            return;
        }

        string nombre;
        double saldo;
        while (archivo >> nombre >> saldo) {
            jugadores.emplace_back(nombre, saldo);
        }

        if (archivo.fail() && !archivo.eof()) { // Comprobar errores al leer del archivo
            cerr << "Error al leer el archivo de jugadores." << endl;
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al cargar jugadores: " << e.what() << endl;
    }
}

// Guardar jugadores en un archivo
void Casino::guardarJugadores() {
    try {
        ofstream archivo("jugadores.txt");
        if (!archivo.is_open()) { // Comprobar si el archivo se abre correctamente
            cerr << "Error al abrir el archivo de jugadores para escritura." << endl;
            return;
        }

        for (const auto& jugador : jugadores) {
            archivo << jugador.nombre << " " << jugador.saldo << endl;
        }

        if (archivo.fail()) { // Comprobar errores al escribir en el archivo
            cerr << "Error al guardar los jugadores en el archivo." << endl;
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al guardar jugadores: " << e.what() << endl;
    }
}

// Mostrar los juegos disponibles en el casino
void Casino::mostrarJuegos() {
    try {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "¡Bienvenido al Casino! Elige un juego:" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (size_t i = 0; i < juegos.size(); ++i) {
            cout << i + 1 << ". " << juegos[i]->getNombre() << endl;
        }
        cout << "0. Volver a Menu Principal" << endl;
    } catch (const exception& e) {
        cerr << "Error al mostrar los juegos: " << e.what() << endl;
    }
}

// Agregar un nuevo jugador al casino
void Casino::agregarJugador(const string& nombre, double saldo) {
    try {
        jugadores.emplace_back(nombre, saldo);
    } catch (const exception& e) {
        cerr << "Error al agregar jugador: " << e.what() << endl;
    }
}

// Verificar si un jugador existe en la lista
bool Casino::jugadorExiste(const string& nombreJugador) {
    try {
        for (const auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                return true;
            }
        }
        return false;
    } catch (const exception& e) {
        cerr << "Error al verificar si el jugador existe: " << e.what() << endl;
        return false;
    }
}

// Jugar un juego seleccionado por el jugador
void Casino::jugarJuego(int opcion, const string& nombreJugador) {
    try {
        for (auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                if (opcion > 0 && opcion <= static_cast<int>(juegos.size())) {
                    cout << juegos[opcion - 1]->getReglas() << endl; // Mostrar reglas antes de jugar
                    cout << "¿Deseas continuar con el juego? (1: SÍ, 0: No): ";
                    int continuar;
                    cin >> continuar;

                    if (cin.fail()) { // Comprobación de errores en la entrada del usuario
                        cin.clear(); // Limpiar el estado de error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el resto de la entrada
                        cout << "Entrada no válida. Por favor ingresa un número entero." << endl;
                        return;
                    }

                    if (continuar == 1) {
                        juegos[opcion - 1]->jugar(jugador);
                    } else {
                        cout << "Volviendo al menú principal..." << endl;
                    }
                } else {
                    cout << "Opción no válida." << endl;
                }
                return;
            }
        }
        cout << "Jugador no encontrado." << endl;
    } catch (const exception& e) {
        cerr << "Error al jugar el juego: " << e.what() << endl;
    }
}

// Mostrar la lista de jugadores registrados
void Casino::mostrarJugadores() {
    try {
        cout << "\nLista de jugadores:" << endl;
        if (jugadores.empty()) {
            cout << "No hay jugadores registrados." << endl;
        } else {
            for (const auto& jugador : jugadores) {
                cout << jugador << endl; // Usando la sobrecarga del operador <<
            }
        }
    } catch (const exception& e) {
        cerr << "Error al mostrar los jugadores: " << e.what() << endl;
    }
}

// Gestionar el saldo de un jugador
void Casino::gestionarSaldo(const string& nombreJugador) {
    try {
        bool jugadorEncontrado = false; // Variable para verificar si se encuentra el jugador

        for (auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                jugadorEncontrado = true; // Se encuentra el jugador
                int opcion;
                do {
                    cout << "\nGestión de Saldo:" << endl;
                    cout << "\n1. Consultar Saldo" << endl;
                    cout << "2. Hacer Recarga de Saldo" << endl;
                    cout << "3. Sumar Saldo con otro Jugador" << endl;
                    cout << "4. Restar Saldo con otro Jugador" << endl;
                    cout << "5. Comparar Saldo con otro Jugador" << endl;
                    cout << "6. Consultar Lista de Jugadores" << endl;
                    cout << "0. Volver a Menu Principal" << endl;
                    cout << "Selecciona una opción: ";
                    cin >> opcion;

                    if (cin.fail()) { // Comprobación de errores en la entrada del usuario
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada no válida. Por favor ingresa un número entero." << endl;
                        return;
                    }

                    switch (opcion) {
                    case 1:
                        cout << "Tu saldo actual es: " << jugador.saldo << endl;
                        break;
                    case 2: {
                        double recarga;
                        cout << "Introduce la cantidad a recargar: ";
                        cin >> recarga;

                        if (cin.fail() || recarga <= 0) { // Validar que la recarga sea un número positivo
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Cantidad no válida. La cantidad debe ser un número positivo." << endl;
                            return;
                        }

                        jugador.saldo += recarga;
                        cout << "Saldo recargado. Tu nuevo saldo es: " << jugador.saldo << endl;
                        break;
                    }
                    case 3: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encuentra el otro jugador
                        for (auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                jugador = jugador + otro; // Sumar saldo
                                cout << "Nuevo saldo tras la suma: " << jugador.saldo << endl;
                                otroJugadorEncontrado = true; // Se encuentra el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 4: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encontró el otro jugador
                        for (auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                jugador = jugador - otro; // Restar saldo
                                cout << "Nuevo saldo tras la resta: " << jugador.saldo << endl;
                                otroJugadorEncontrado = true; // Se encontró el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 5: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encontró el otro jugador
                        for (const auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                if (jugador == otro) {
                                    cout << "Los saldos son iguales." << endl;
                                } else {
                                    cout << "Los saldos son diferentes." << endl;
                                }
                                otroJugadorEncontrado = true; // Se encontró el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 6:
                        mostrarJugadores();
                        break;
                    case 0:
                        cout << "Volviendo al menú principal..." << endl;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                    }
                } while (opcion != 0);
                return;
            }
        }

        // Mensaje de error si no se encontró el jugador
        if (!jugadorEncontrado) {
            cout << "El jugador '" << nombreJugador << "' no se encuentra en la base de datos." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al gestionar saldo: " << e.what() << endl;
    }
}
