

#ifndef RULETA_H
#define RULETA_H

#include "Juego.h"

using namespace std;

// Clase que representa el juego de la Ruleta
class Ruleta : public Juego {
public:
    void jugar(Jugador& jugador) override; // Método para jugar a la ruleta
    string getNombre() const override;    // Obtener el nombre del juego
    string getReglas() const override;    // Obtener las reglas del juego
};

#endif
