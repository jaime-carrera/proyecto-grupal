#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>
#include <exception>

using namespace std;

// Clase para manejar excepciones de saldo negativo
class SaldoNegativoException : public exception {
public:
    const char* what() const noexcept override;
};

// Clase que representa a un jugador
class Jugador {
public:
    string nombre;  // Nombre del jugador
    double saldo;   // Saldo actual del jugador

    // Constructor con validación de saldo negativo
    Jugador(const string& nombre, double saldo);

    // Sobrecarga del operador +
    Jugador operator+(const Jugador& otro) const;

    // Sobrecarga del operador -
    Jugador operator-(const Jugador& otro) const;

    // Sobrecarga del operador ==
    bool operator==(const Jugador& otro) const;

    // Sobrecarga del operador << para imprimir información del jugador
    friend ostream& operator<<(ostream& os, const Jugador& jugador);
};

#endif
