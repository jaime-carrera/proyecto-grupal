#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include <string>

using namespace std;

// Clase base abstracta para todos los juegos del casino
class Juego {
public:
    virtual void jugar(Jugador& jugador) = 0; // Método virtual puro: iniciar el juego
    virtual string getNombre() const = 0;    // Método virtual puro: obtener el nombre del juego
    virtual string getReglas() const = 0;    // Método virtual puro: obtener las reglas del juego
    virtual ~Juego() {}                      // Destructor virtual para manejar herencia
};

#endif
