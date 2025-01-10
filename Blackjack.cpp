#include "Blackjack.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

// Inicializar la baraja de cartas
void Blackjack::inicializarBaraja() {
    baraja.clear();
    for (int i = 1; i <= 13; ++i) { // Valores del 1 al 13
        for (int j = 0; j < 4; ++j) { // 4 cartas de cada valor
            baraja.push_back(i);
        }
    }

    // Barajar las cartas
    random_device rd;
    default_random_engine rng(rd());
    shuffle(baraja.begin(), baraja.end(), rng);
}

// Obtener el valor de una carta
int Blackjack::valorCarta(int carta) {
    return (carta > 10) ? 10 : carta; // Las figuras (J, Q, K) valen 10
}

// Calcular el puntaje total de una mano
int Blackjack::calcularPuntaje(const vector<int>& mano) {
    int puntaje = 0;
    int ases = 0;

    for (int carta : mano) {
        puntaje += valorCarta(carta);
        if (carta == 1) ases++; // Contar ases
    }

    // Convertir ases de 1 a 11 si no se excede 21
    while (puntaje <= 11 && ases > 0) {
        puntaje += 10;
        ases--;
    }

    return puntaje;
}

// Implementación del juego de Blackjack
void Blackjack::jugar(Jugador& jugador) {
    try {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "¡Bienvenido al Blackjack, " << jugador.nombre << "! Tu saldo actual es: " << jugador.saldo << endl;
        cout << "---------------------------------------------------------" << endl;

        inicializarBaraja();

        vector<int> manoJugador;
        vector<int> manoDealer;

        // Repartir cartas iniciales
        manoJugador.push_back(baraja.back()); baraja.pop_back();
        manoJugador.push_back(baraja.back()); baraja.pop_back();
        manoDealer.push_back(baraja.back()); baraja.pop_back();
        manoDealer.push_back(baraja.back()); baraja.pop_back();

        double apuesta;
        cout << "\nIntroduce tu apuesta: ";
        if (!(cin >> apuesta) || apuesta <= 0 || apuesta > jugador.saldo) {
            cout << "Apuesta inválida. Debe ser mayor que 0 y no superar tu saldo." << endl;
            return; // Salir si la entrada no es válida
        }

        // Mostrar la mano inicial del jugador
        cout << "\nTu mano inicial es: ";
        for (int carta : manoJugador) {
            cout << valorCarta(carta) << " ";
        }
        cout << "(Puntaje: " << calcularPuntaje(manoJugador) << ")" << endl;

        // Mostrar la mano inicial del dealer (solo una carta visible)
        cout << "Mano del dealer: " << valorCarta(manoDealer[0]) << " ?" << endl;

        // Turno del jugador
        while (true) {
            int opcion;
            cout << "\n¿Qué deseas hacer? (1: Pedir carta, 2: Plantarse): ";
            cin >> opcion;

            if (opcion == 1) { // Pedir carta
                manoJugador.push_back(baraja.back());
                baraja.pop_back();
                cout << "Tu nueva mano: ";
                for (int carta : manoJugador) {
                    cout << valorCarta(carta) << " ";
                }
                cout << "(Puntaje: " << calcularPuntaje(manoJugador) << ")" << endl;

                if (calcularPuntaje(manoJugador) > 21) {
                    cout << "Te has pasado. Has perdido tu apuesta." << endl;
                    jugador.saldo -= apuesta;
                    return; // Salir si el jugador pierde
                }
            } else if (opcion == 2) { // Plantarse
                break;
            } else {
                cout << "Opción no válida. Intenta nuevamente." << endl;
            }
        }

        // Turno del dealer
        cout << "Mano del dealer: ";
        for (int carta : manoDealer) {
            cout << valorCarta(carta) << " ";
        }
        cout << "(Puntaje: " << calcularPuntaje(manoDealer) << ")" << endl;

        while (calcularPuntaje(manoDealer) < 17) {
            manoDealer.push_back(baraja.back());
            baraja.pop_back();
            cout << "El dealer pide carta. Nueva mano: ";
            for (int carta : manoDealer) {
                cout << valorCarta(carta) << " ";
            }
            cout << "(Puntaje: " << calcularPuntaje(manoDealer) << ")" << endl;
        }

        // Comparar puntajes
        int puntajeJugador = calcularPuntaje(manoJugador);
        int puntajeDealer = calcularPuntaje(manoDealer);

        if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {
            cout << "¡Felicidades! Has ganado." << endl;
            jugador.saldo += apuesta;
        } else if (puntajeJugador < puntajeDealer) {
            cout << "Lo siento, has perdido." << endl;
            jugador.saldo -= apuesta;
        } else {
            cout << "Es un empate." << endl;
        }
    } catch (const exception& e) {
        cout << "Error al jugar: " << e.what() << endl;
    }
}

// Obtener el nombre del juego
string Blackjack::getNombre() const {
    return "Blackjack";
}

// Obtener las reglas del juego
string Blackjack::getReglas() const {
    return "\nReglas del Blackjack:\n"
           "    El objetivo es tener una mano con un valor total más cercano a 21 sin pasarse.\n"
           "    Las cartas del 2 al 10 valen su valor nominal, las figuras (J, Q, K) valen 10, y los Ases pueden valer 1 o 11.\n"
           "    Los jugadores pueden pedir cartas adicionales o plantarse.\n"
           "    Si el jugador supera 21, pierde automáticamente.\n"
           "    El dealer debe pedir cartas hasta alcanzar al menos 17.";
}
