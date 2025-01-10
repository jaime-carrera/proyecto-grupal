

#include "Jugador.h"

// Mensaje para excepción de saldo negativo
const char* SaldoNegativoException::what() const noexcept {
    return "Error: El saldo no puede ser negativo.";
}

// Constructor del jugador con validación de saldo negativo
Jugador::Jugador(const string& nombre, double saldo) {
    try {
        if (saldo < 0) {
            throw SaldoNegativoException();
        }
        this->nombre = nombre;
        this->saldo = saldo;
    } catch (const exception& e) {
        cerr << "Error al crear el jugador: " << e.what() << endl;
        throw; // Re-lanzar para manejarlo en un nivel superior si es necesario
    }
}

// Sobrecarga del operador + para sumar saldos de jugadores
Jugador Jugador::operator+(const Jugador& otro) const {
    try {
        double nuevoSaldo = this->saldo + otro.saldo;
        if (nuevoSaldo < 0) {
            throw SaldoNegativoException();
        }
        return Jugador(this->nombre + " & " + otro.nombre, nuevoSaldo);
    } catch (const exception& e) {
        cerr << "Error al sumar jugadores: " << e.what() << endl;
        throw;
    }
}

// Sobrecarga del operador - para restar saldos de jugadores
Jugador Jugador::operator-(const Jugador& otro) const {
    try {
        double nuevoSaldo = this->saldo - otro.saldo;
        if (nuevoSaldo < 0) {
            throw SaldoNegativoException();
        }
        return Jugador(this->nombre + " - " + otro.nombre, nuevoSaldo);
    } catch (const exception& e) {
        cerr << "Error al restar jugadores: " << e.what() << endl;
        throw;
    }
}

// Sobrecarga del operador == para comparar saldos de jugadores
bool Jugador::operator==(const Jugador& otro) const {
    return this->saldo == otro.saldo;
}

// Sobrecarga del operador << para imprimir información del jugador
ostream& operator<<(ostream& os, const Jugador& jugador) {
    os << "Nombre: " << jugador.nombre << ", Saldo: " << jugador.saldo;
    return os;
}
