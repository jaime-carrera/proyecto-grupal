
#include "Tragamonedas.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

// Función para girar la tragamonedas y obtener el resultado
vector<string> Tragamonedas::girarTragamonedas() {
    try {
        vector<string> resultado;
        for (int i = 0; i < lineasDePago; ++i) {
            resultado.push_back(simbolos[rand() % simbolos.size()]); // Seleccionar un símbolo aleatorio
        }
        return resultado;
    } catch (const exception& e) {
        cout << "Error al girar las tragamonedas: " << e.what() << endl;
        return {};
    }
}

// Función para calcular las ganancias
double Tragamonedas::calcularGanancias(const vector<string>& resultado, double apuestaPorLinea) {
    try {
        double ganancias = 0.0;

        // Contar cuántos símbolos iguales hay en las líneas de pago
        for (const auto& simbolo : simbolos) {
            int countResult = count(resultado.begin(), resultado.end(), simbolo);
            if (countResult > 0) {
                // Ejemplo de pago: 3 símbolos iguales
                if (countResult == 3) {
                    ganancias += apuestaPorLinea * 10; // Ganancia por 3 símbolos iguales
                } else if (countResult == 2) {
                    ganancias += apuestaPorLinea * 5; // Ganancia por 2 símbolos iguales
                }
            }
        }

        return ganancias;
    } catch (const exception& e) {
        cout << "Error al calcular las ganancias: " << e.what() << endl;
        return 0.0;
    }
}

// Implementación del juego de Tragamonedas
void Tragamonedas::jugar(Jugador& jugador) {
    try {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "¡Bienvenido a las Tragamonedas, " << jugador.nombre << "! Tu saldo actual es: " << jugador.saldo << endl;
        cout << "---------------------------------------------------------" << endl;

        int lineas;
        cout << "¿Cuántas líneas de pago deseas jugar? (1-" << lineasDePago << "): ";
        if (!(cin >> lineas) || lineas < 1 || lineas > lineasDePago) {
            cout << "Número de líneas inválido. Debe estar entre 1 y " << lineasDePago << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        double apuestaPorLinea;
        cout << "Introduce la cantidad a apostar por línea: ";
        if (!(cin >> apuestaPorLinea) || apuestaPorLinea <= 0 || apuestaPorLinea * lineas > jugador.saldo) {
            cout << "Apuesta inválida. Debe ser mayor que 0 y no superar tu saldo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Girar las tragamonedas
        vector<string> resultado = girarTragamonedas();
        cout << "Has girado las tragamonedas y el resultado es: ";
        for (const auto& simbolo : resultado) {
            cout << simbolo << " ";
        }
        cout << endl;

        // Calcular las ganancias
        double ganancias = calcularGanancias(resultado, apuestaPorLinea);
        if (ganancias > 0) {
            cout << "¡Felicidades! Has ganado: " << ganancias << " monedas." << endl;
            jugador.saldo += ganancias;
        } else {
            cout << "Lo siento, has perdido tu apuesta." << endl;
            jugador.saldo -= apuestaPorLinea * lineas; // Pérdida total
        }

        cout << "Tu saldo actual es: " << jugador.saldo << endl;
    } catch (const exception& e) {
        cout << "Error al jugar: " << e.what() << endl;
    }
}

// Obtener el nombre del juego
string Tragamonedas::getNombre() const {
    return "Tragamonedas";
}

// Obtener las reglas del juego
string Tragamonedas::getReglas() const {
    return "\nReglas de las Tragamonedas:\n"
           "1. Puedes elegir cuántas líneas de pago jugar (1-3).\n"
           "2. Cada línea de pago tiene un costo de apuesta.\n"
           "3. Si obtienes 3 símbolos iguales en una línea de pago, ganas.\n"
           "4. Las ganancias dependen del número de símbolos iguales en las líneas de pago.\n"
           "5. Las combinaciones ganadoras varían según el símbolo.";
}
