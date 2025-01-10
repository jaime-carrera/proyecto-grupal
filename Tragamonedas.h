

#ifndef TRAGAMONEDAS_H
#define TRAGAMONEDAS_H

#include "Juego.h"
#include <vector>

using namespace std;

// Clase que representa el juego de Tragamonedas
class Tragamonedas : public Juego {
private:
    vector<string> simbolos = { "🍒", "🍋", "🍊", "🍉", "⭐", "💎" }; // Símbolos de la tragamonedas
    int lineasDePago = 3; // Número de líneas de pago

    // Función para girar la tragamonedas y obtener el resultado
    vector<string> girarTragamonedas();

    // Función para calcular las ganancias
    double calcularGanancias(const vector<string>& resultado, double apuestaPorLinea);

public:
    void jugar(Jugador& jugador) override; // Método para jugar a las tragamonedas
    string getNombre() const override;    // Obtener el nombre del juego
    string getReglas() const override;    // Obtener las reglas del juego
};

#endif
