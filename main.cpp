
#include <iostream>
#include <ctime>

// Incluir todas las cabeceras necesarias
#include "Jugador.h"
#include "Juego.h"
#include "Ruleta.h"
#include "Blackjack.h"
#include "Tragamonedas.h"
#include "Casino.h"

using namespace std;

int main() {
    try {
        srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla para números aleatorios
        Casino casino;

        while (true) {
            string nombreJugador;
            cout << "\nIntroduce tu nombre (o escribe 'salir' para terminar): ";
            cin >> nombreJugador;

            // Opción para salir del programa
            if (nombreJugador == "salir") {
                cout << "\nGracias por jugar. ¡Hasta luego!" << endl;
                return 0;
            }

            // Verificar si el jugador ya existe
            if (!casino.jugadorExiste(nombreJugador)) {
                double saldoInicial;
                cout << "Eres un nuevo jugador. Ingresa tu saldo inicial: ";
                cin >> saldoInicial;

                if (cin.fail() || saldoInicial <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Saldo inválido. Intenta nuevamente." << endl;
                    continue;
                }

                casino.agregarJugador(nombreJugador, saldoInicial); // Agregar nuevo jugador
                cout << "Jugador agregado con éxito." << endl;
            }

            // Menú principal para el jugador actual
            while (true) {
                int opcion;
                cout << "\n---------------------------------" << endl;
                cout << "Menú Principal para " << nombreJugador << ":" << endl;
                cout << "---------------------------------" << endl;
                cout << "1. Jugar" << endl;
                cout << "2. Gestionar Saldo" << endl;
                cout << "3. Cambiar de jugador" << endl;
                cout << "0. Salir del programa" << endl;
                cout << "Selecciona una opción: ";
                cin >> opcion;

                if (cin.fail()) { // Validar que la entrada sea un número
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Opción no válida. Por favor ingresa un número entero." << endl;
                    continue;
                }

                if (opcion == 0) {
                    cout << "\nGracias por jugar. ¡Hasta luego!" << endl;
                    return 0; // Salir del programa
                } else if (opcion == 3) {
                    cout << "\nCambiando de jugador..." << endl;
                    break; // Salir al menú de selección de jugador
                } else if (opcion == 1) {
                    // Mostrar juegos disponibles
                    cout << "\n---------------------------------" << endl;
                    cout << "Juegos disponibles:" << endl;
                    cout << "---------------------------------" << endl;
                    cout << "1. Ruleta" << endl;
                    cout << "2. Blackjack" << endl;
                    cout << "3. Tragamonedas" << endl;
                    cout << "0. Volver al menú principal" << endl;
                    cout << "Selecciona un juego: ";
                    int juegoSeleccionado;
                    cin >> juegoSeleccionado;

                    if (cin.fail() || juegoSeleccionado < 0 || juegoSeleccionado > 3) { // Validar entrada
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Opción no válida. Intenta nuevamente." << endl;
                        continue;
                    }

                    if (juegoSeleccionado == 0) {
                        cout << "Volviendo al menú principal..." << endl;
                        continue;
                    }

                    // Jugar el juego seleccionado
                    casino.jugarJuego(juegoSeleccionado, nombreJugador);
                } else if (opcion == 2) {
                    // Gestionar saldo del jugador
                    casino.gestionarSaldo(nombreJugador);
                } else {
                    cout << "Opción no válida." << endl;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Excepción en el programa: " << e.what() << endl;
        return 1; // Código de error
    }
}
