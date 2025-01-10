
#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Juego.h"
#include <vector>

using namespace std;

// Clase que representa el juego de Blackjack
class Blackjack : public Juego {
private:
    vector<int> baraja;

    // Inicializar la baraja de cartas
    void inicializarBaraja();

    // Obtener el valor de una carta
    int valorCarta(int carta);

    // Calcular el puntaje total de una mano
    int calcularPuntaje(const vector<int>& mano);

public:
    void jugar(Jugador& jugador) override; // Método para jugar al Blackjack
    string getNombre() const override;    // Obtener el nombre del juego
    string getReglas() const override;    // Obtener las reglas del juego
};

#endif
