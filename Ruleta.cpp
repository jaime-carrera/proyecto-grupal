
#include "Ruleta.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Implementación del juego de la Ruleta
void Ruleta::jugar(Jugador& jugador) {
    try {
        int tipoApuesta;
        double apuesta;

        cout << "\n---------------------------------------------------------" << endl;
        cout << "¡Bienvenido a la Ruleta, " << jugador.nombre << "! Tu saldo actual es: " << jugador.saldo << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "¿Qué tipo de apuesta deseas hacer?" << endl;
        cout << "1. Apostar a un número (0-36)" << endl;
        cout << "2. Apostar a Par o Impar" << endl;
        cout << "Selecciona una opción: ";
        if (!(cin >> tipoApuesta)) {
            // Validación de entrada
            throw runtime_error("Entrada inválida. Por favor, ingresa un número entero para la opción.");
        }

        cout << "Introduce la cantidad a apostar: ";
        if (!(cin >> apuesta) || apuesta <= 0 || apuesta > jugador.saldo) {
            // Validación de la cantidad apostada
            throw runtime_error("Apuesta inválida. Debe ser mayor que 0 y no superar tu saldo.");
        }

        // Generar el resultado de la ruleta
        int resultado = rand() % 37; // Número aleatorio entre 0 y 36

        if (tipoApuesta == 1) { // Apostar a un número
            int numeroApostado;
            cout << "¿A qué número deseas apostar? (0-36): ";
            if (!(cin >> numeroApostado) || numeroApostado < 0 || numeroApostado > 36) {
                // Validación del número apostado
                throw runtime_error("Número inválido. Debe estar entre 0 y 36.");
            }

            // Mostrar el resultado de la ruleta
            cout << "La ruleta ha girado y el número es: " << resultado << endl;

            if (numeroApostado == resultado) {
                // El jugador gana
                double ganancia = apuesta * 36;
                cout << "¡Felicidades! Has acertado el número. Has ganado: " << ganancia << " monedas." << endl;
                jugador.saldo += ganancia; // Ganancia
            } else {
                // El jugador pierde
                cout << "Lo siento, has perdido: " << apuesta << " monedas." << endl;
                jugador.saldo -= apuesta; // Pérdida
            }
        } else if (tipoApuesta == 2) { // Apostar a Par o Impar
            char parImpar;
            cout << "¿Apostarías a Par (p) o Impar (i)? ";
            if (!(cin >> parImpar) || (parImpar != 'p' && parImpar != 'i')) {
                // Validación de la opción Par o Impar
                throw runtime_error("Opción inválida. Debe ser 'p' para Par o 'i' para Impar.");
            }

            // Mostrar el resultado de la ruleta
            cout << "La ruleta ha girado y el número es: " << resultado << endl;

            bool esPar = (resultado % 2 == 0);
            if ((parImpar == 'p' && esPar) || (parImpar == 'i' && !esPar)) {
                // El jugador gana
                double ganancia = apuesta * 2;
                cout << "¡Felicidades! Has acertado. Has ganado: " << ganancia << " monedas." << endl;
                jugador.saldo += ganancia; // Ganancia
            } else {
                // El jugador pierde
                cout << "Lo siento, has perdido: " << apuesta << " monedas." << endl;
                jugador.saldo -= apuesta; // Pérdida
            }
        } else {
            // Opción no válida
            throw runtime_error("Opción de apuesta no válida.");
        }

        if (jugador.saldo < 0) {
            // Comprobación del saldo negativo
            throw runtime_error("El saldo del jugador no puede ser negativo.");
        }
    } catch (const exception& e) {
        // Manejo de excepciones
        cerr << "Error durante el juego de Ruleta: " << e.what() << endl;
    }
}

// Obtener el nombre del juego
string Ruleta::getNombre() const {
    return "Ruleta";
}

// Obtener las reglas del juego
string Ruleta::getReglas() const {
    return "\nReglas de la Ruleta:\n"
           "    Puedes apostar a un número específico (0-36) o a si el número será par o impar.\n"
           "    Si aciertas el número, ganas 36 veces tu apuesta.\n"
           "    Si aciertas si el número es par o impar, ganas 2 veces tu apuesta.\n"
           "    Si no aciertas, pierdes tu apuesta.";
}
