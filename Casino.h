

#ifndef CASINO_H
#define CASINO_H

#include "Jugador.h"
#include "Ruleta.h"
#include "Blackjack.h"
#include "Tragamonedas.h"
#include <vector>
#include <fstream>

using namespace std;

// Clase que representa el casino
class Casino {
private:
    vector<Juego*> juegos;    // Lista de juegos disponibles
    vector<Jugador> jugadores; // Lista de jugadores registrados

    // Cargar jugadores desde un archivo
    void cargarJugadores();

    // Guardar jugadores en un archivo
    void guardarJugadores();

public:
    // Constructor: inicializa los juegos y carga los jugadores
    Casino();

    // Destructor: libera la memoria de los juegos y guarda los jugadores
    ~Casino();

    // Mostrar los juegos disponibles en el casino
    void mostrarJuegos();

    // Agregar un nuevo jugador al casino
    void agregarJugador(const string& nombre, double saldo);

    // Verificar si un jugador existe
    bool jugadorExiste(const string& nombreJugador);

    // Jugar un juego seleccionado por el jugador
    void jugarJuego(int opcion, const string& nombreJugador);

    // Mostrar la lista de jugadores registrados
    void mostrarJugadores();

    // Gestionar el saldo de un jugador
    void gestionarSaldo(const string& nombreJugador);
};

#endif
