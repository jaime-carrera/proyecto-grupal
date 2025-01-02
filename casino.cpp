/*
 PROYECTOS DE PROGRAMACIoN 
 Primera entrega proyecto: CASINO
 Grupo formado por: Rodrigo Calderon, alvaro Aguilar, Pedro Riveiro, Gonzalo Olivares, Eduardo Bernad y Jaime Carrera
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

class Jugador {
public:
    string nombre;
    double saldo;

    Jugador(const string& nombre, double saldo) : nombre(nombre), saldo(saldo) {}

    // Sobrecarga del operador +
    Jugador operator+(const Jugador& otro) const {
        return Jugador(this->nombre + " & " + otro.nombre, this->saldo + otro.saldo);
    }

    // Sobrecarga del operador -
    Jugador operator-(const Jugador& otro) const {
        return Jugador(this->nombre + " - " + otro.nombre, this->saldo - otro.saldo);
    }

    // Sobrecarga del operador ==
    bool operator==(const Jugador& otro) const {
        return this->saldo == otro.saldo;
    }

    // Sobrecarga del operador <<
    friend ostream& operator<<(ostream& os, const Jugador& jugador) {
        os << "Nombre: " << jugador.nombre << ", Saldo: " << jugador.saldo;
        return os;
    }
};

class Juego {
public:
    virtual void jugar(Jugador& jugador) = 0; // Método virtual puro
    virtual string getNombre() const = 0; // Método para obtener el nombre del juego
    virtual string getReglas() const = 0; // Método para obtener las reglas del juego
    virtual ~Juego() {} // Destructor virtual
};

class Ruleta : public Juego {
public:
    void jugar(Jugador& jugador) override {
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
            cout << "Entrada inválida. Por favor, ingresa un número entero para la opción." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Introduce la cantidad a apostar: ";
        if (!(cin >> apuesta) || apuesta <= 0 || apuesta > jugador.saldo) {
            cout << "Apuesta inválida. Debe ser mayor que 0 y no superar tu saldo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Generar el resultado de la ruleta
        int resultado = rand() % 37; // Número aleatorio entre 0 y 36

        if (tipoApuesta == 1) { // Apostar a un número
            int numeroApostado;
            cout << "¿A qué número deseas apostar? (0-36): ";
            if (!(cin >> numeroApostado) || numeroApostado < 0 || numeroApostado > 36) {
                cout << "Número inválido. Debe estar entre 0 y 36." << endl;
                return;
            }

            // Mostrar el resultado de la ruleta
            cout << "La ruleta ha girado y el número es: " << resultado << endl;

            if (numeroApostado == resultado) {
                cout << "¡Felicidades! Has acertado el número." << endl;
                jugador.saldo += apuesta * 36; // Ganancia
            }
            else {
                cout << "Lo siento, has perdido tu apuesta." << endl;
                jugador.saldo -= apuesta; // Pérdida
            }
        }
        else if (tipoApuesta == 2) { // Apostar a Par o Impar
            char parImpar;
            cout << "¿Apostarías a Par (p) o Impar (i)? ";
            if (!(cin >> parImpar) || (parImpar != 'p' && parImpar != 'i')) {
                cout << "Opción inválida. Debe ser 'p' para Par o 'i' para Impar." << endl;
                return;
            }

            // Mostrar el resultado de la ruleta
            cout << "La ruleta ha girado y el número es: " << resultado << endl;

            bool esPar = (resultado % 2 == 0);
            if ((parImpar == 'p' && esPar) || (parImpar == 'i' && !esPar)) {
                cout << "¡Felicidades! Has acertado." << endl;
                jugador.saldo += apuesta * 2; // Ganancia
            }
            else {
                cout << "Lo siento, has perdido tu apuesta." << endl;
                jugador.saldo -= apuesta; // Pérdida
            }
        }
        else {
            cout << "Opción de apuesta no válida." << endl;
        }
    }

    string getNombre() const override {
        return "Ruleta";
    }

    string getReglas() const override {
        return "\nReglas de la Ruleta:\n"
            "    Puedes apostar a un número específico (0-36) o a si el número será par o impar.\n"
            "    Si aciertas el número, ganas 36 veces tu apuesta.\n"
            "    Si aciertas si el número es par o impar, ganas 2 veces tu apuesta.\n"
            "    Si no aciertas, pierdes tu apuesta.";
    }
};

// Aquí continúa la implementación de Blackjack y Tragamonedas con los mismos cambios de validación para la entrada del usuario:
class Blackjack : public Juego {
private:
    vector<int> baraja;

    void inicializarBaraja() {
        baraja.clear();
        for (int i = 1; i <= 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                baraja.push_back(i);
            }
        }
        random_device rd;
        default_random_engine rng(rd());
        shuffle(baraja.begin(), baraja.end(), rng);
    }

    int valorCarta(int carta) {
        if (carta > 10) return 10;
        return carta;
    }

    int calcularPuntaje(const vector<int>& mano) {
        int puntaje = 0;
        int ases = 0;

        for (int carta : mano) {
            puntaje += valorCarta(carta);
            if (carta == 1) ases++;
        }

        while (puntaje <= 11 && ases > 0) {
            puntaje += 10;
            ases--;
        }

        return puntaje;
    }

public:
    void jugar(Jugador& jugador) override {
        inicializarBaraja();

        vector<int> manoJugador;
        vector<int> manoDealer;

        manoJugador.push_back(baraja.back()); baraja.pop_back();
        manoJugador.push_back(baraja.back()); baraja.pop_back();
        manoDealer.push_back(baraja.back()); baraja.pop_back();
        manoDealer.push_back(baraja.back()); baraja.pop_back();

        double apuesta;
        cout << "\nTu saldo actual es: " << jugador.saldo << endl;
        cout << "Introduce tu apuesta: ";
        if (!(cin >> apuesta) || apuesta <= 0 || apuesta > jugador.saldo) {
            cout << "Apuesta inválida. Debe ser mayor que 0 y no superar tu saldo." << endl;
            return;
        }

        cout << "\nTu mano es: ";
        for (int carta : manoJugador) {
            cout << valorCarta(carta) << " ";
        }
        cout << "(Puntaje: " << calcularPuntaje(manoJugador) << ")" << endl;

        cout << "Mano del dealer: " << valorCarta(manoDealer[0]) << " ? (una carta oculta)" << endl;

        bool jugadorPlantado = false;
        while (!jugadorPlantado) {
            cout << "\n¿Qué desea hacer? (1: Pedir carta, 2: Plantarse, 3: Doblar): ";
            int opcion;
            if (!(cin >> opcion)) {
                cout << "Opción inválida. Por favor, ingresa un número entero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (opcion == 1) {
                manoJugador.push_back(baraja.back());
                baraja.pop_back();
                cout << "\nTu mano: ";
                for (int carta : manoJugador) {
                    cout << valorCarta(carta) << " ";
                }
                cout << "(Puntaje: " << calcularPuntaje(manoJugador) << ")" << endl;

                if (calcularPuntaje(manoJugador) > 21) {
                    cout << "\nTe has pasado. Has perdido tu apuesta." << endl;
                    jugador.saldo -= apuesta;
                    return;
                }
            }
            else if (opcion == 2) {
                jugadorPlantado = true;
            }
            else if (opcion == 3) {
                if (jugador.saldo < apuesta) {
                    cout << "\nNo tienes suficiente saldo para doblar." << endl;
                    continue;
                }
                apuesta *= 2;
                manoJugador.push_back(baraja.back());
                baraja.pop_back();
                cout << "Tu mano: ";
                for (int carta : manoJugador) {
                    cout << valorCarta(carta) << " ";
                }
                cout << "(Puntaje: " << calcularPuntaje(manoJugador) << ")" << endl;

                if (calcularPuntaje(manoJugador) > 21) {
                    cout << "Te has pasado. Has perdido tu apuesta." << endl;
                    jugador.saldo -= apuesta;
                    return;
                }
                jugadorPlantado = true;
            }
            else {
                cout << "Opción no válida." << endl;
            }
        }

        cout << "Mano del dealer: ";
        for (int carta : manoDealer) {
            cout << valorCarta(carta) << " ";
        }
        cout << "(Puntaje: " << calcularPuntaje(manoDealer) << ")" << endl;

        while (calcularPuntaje(manoDealer) < 17) {
            manoDealer.push_back(baraja.back());
            baraja.pop_back();
            cout << "El dealer pide carta." << endl;
            cout << "Mano del dealer: ";
            for (int carta : manoDealer) {
                cout << valorCarta(carta) << " ";
            }
            cout << "(Puntaje: " << calcularPuntaje(manoDealer) << ")" << endl;
        }

        int puntajeJugador = calcularPuntaje(manoJugador);
        int puntajeDealer = calcularPuntaje(manoDealer);

        if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {
            cout << "¡Felicidades! Has ganado." << endl;
            jugador.saldo += apuesta;
        }
        else if (puntajeJugador < puntajeDealer) {
            cout << "Lo siento, has perdido." << endl;
            jugador.saldo -= apuesta;
        }
        else {
            cout << "Es un empate." << endl;
        }
    }

    string getNombre() const override {
        return "Blackjack";
    }

    string getReglas() const override {
        return "\nReglas del Blackjack:\n"
            "    El objetivo es tener una mano con un valor total más cercano a 21 sin pasarse.\n"
            "    Las cartas del 2 al 10 valen su valor nominal, las figuras (J, Q, K) valen 10, y los Ases pueden valer 1 o 11.\n"
            "    Los jugadores pueden pedir cartas adicionales o plantarse.\n"
            "    Si el jugador supera 21, pierde automáticamente.\n"
            "    El dealer debe pedir cartas hasta alcanzar al menos 17.";
    }
};

class Tragamonedas : public Juego {
private:
    vector<string> simbolos = { "ð", "ð", "ð", "ð", "â­", "ð" }; // Símbolos de la tragamonedas
    int lineasDePago = 3; // Número de líneas de pago

    // Función para girar la tragamonedas y obtener el resultado
    vector<string> girarTragamonedas() {
        vector<string> resultado;
        for (int i = 0; i < lineasDePago; ++i) {
            resultado.push_back(simbolos[rand() % simbolos.size()]); // Seleccionar un símbolo aleatorio
        }
        return resultado;
    }

    // Función para calcular las ganancias
    double calcularGanancias(const vector<string>& resultado, double apuestaPorLinea) {
        double ganancias = 0.0;

        // Contar cuántos símbolos iguales hay en las líneas de pago
        for (const auto& simbolo : simbolos) {
            int countResult = std::count(resultado.begin(), resultado.end(), simbolo);
            if (countResult > 0) {
                // Ejemplo de pago: 3 símbolos iguales
                if (countResult == 3) {
                    ganancias += apuestaPorLinea * 10; // Ganancia por 3 símbolos iguales
                }
                else if (countResult == 2) {
                    ganancias += apuestaPorLinea * 5; // Ganancia por 2 símbolos iguales
                }
            }
        }

        return ganancias;
    }

public:
    void jugar(Jugador& jugador) override {
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
        }
        else {
            cout << "Lo siento, has perdido tu apuesta." << endl;
            jugador.saldo -= apuestaPorLinea * lineas; // Pérdida total
        }

        cout << "Tu saldo actual es: " << jugador.saldo << endl;
    }

    string getNombre() const override {
        return "Tragamonedas";
    }

    string getReglas() const override {
        return "\nReglas de las Tragamonedas:\n"
            "1. Puedes elegir cuántas líneas de pago jugar (1-3).\n"
            "2. Cada línea de pago tiene un costo de apuesta.\n"
            "3. Si obtienes 3 símbolos iguales en una línea de pago, ganas.\n"
            "4. Las ganancias dependen del número de símbolos iguales en las líneas de pago.\n"
            "5. Las combinaciones ganadoras varían según el símbolo.";
    }
};

class Casino {
private:
    vector<Juego*> juegos;
    vector<Jugador> jugadores;

    void cargarJugadores() {
        ifstream archivo("jugadores.txt");
        if (!archivo.is_open()) { // Comprobar si el archivo se abre correctamente
            cerr << "Error al abrir el archivo de jugadores para lectura." << endl;
            return;
        }

        string nombre;
        double saldo;
        while (archivo >> nombre >> saldo) {
            jugadores.emplace_back(nombre, saldo);
        }

        if (archivo.fail() && !archivo.eof()) { // Comprobar errores al leer del archivo
            cerr << "Error al leer el archivo de jugadores." << endl;
        }

        archivo.close();
    }

    void guardarJugadores() {
        ofstream archivo("jugadores.txt");
        if (!archivo.is_open()) { // Comprobar si el archivo se abre correctamente
            cerr << "Error al abrir el archivo de jugadores para escritura." << endl;
            return;
        }

        for (const auto& jugador : jugadores) {
            archivo << jugador.nombre << " " << jugador.saldo << endl;
        }

        if (archivo.fail()) { // Comprobar errores al escribir en el archivo
            cerr << "Error al guardar los jugadores en el archivo." << endl;
        }

        archivo.close();
    }

public:
    Casino() {
        juegos.push_back(new Ruleta());
        juegos.push_back(new Blackjack());
        juegos.push_back(new Tragamonedas());
        cargarJugadores(); // Cargar jugadores al iniciar el casino
    }

    ~Casino() {
        for (Juego* juego : juegos) {
            delete juego;
        }
        guardarJugadores(); // Guardar jugadores al cerrar el casino
    }

    void mostrarJuegos() {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "¡Bienvenido al Casino! Elige un juego:" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (size_t i = 0; i < juegos.size(); ++i) {
            cout << i + 1 << ". " << juegos[i]->getNombre() << endl;
        }
        cout << "0. Volver a Menu Principal" << endl;
    }

    void agregarJugador(const string& nombre, double saldo) {
        jugadores.emplace_back(nombre, saldo);
    }

    bool jugadorExiste(const string& nombreJugador) {
        for (const auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                return true;
            }
        }
        return false;
    }

    void jugarJuego(int opcion, const string& nombreJugador) {
        for (auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                if (opcion > 0 && opcion <= juegos.size()) {
                    cout << juegos[opcion - 1]->getReglas() << endl; // Mostrar reglas antes de jugar
                    cout << "¿Deseas continuar con el juego? (1: SÍ, 0: No): ";
                    int continuar;
                    cin >> continuar;

                    if (cin.fail()) { // Comprobación de errores en la entrada del usuario
                        cin.clear(); // Limpiar el estado de error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el resto de la entrada
                        cout << "Entrada no válida. Por favor ingresa un número entero." << endl;
                        return;
                    }

                    if (continuar == 1) {
                        juegos[opcion - 1]->jugar(jugador);
                    }
                    else {
                        cout << "Volviendo al menú principal..." << endl;
                    }
                }
                else {
                    cout << "Opción no válida." << endl;
                }
                return;
            }
        }
        cout << "Jugador no encontrado." << endl;
    }

    void mostrarJugadores() {
        cout << "\nLista de jugadores:" << endl;
        if (jugadores.empty()) {
            cout << "No hay jugadores registrados." << endl;
        }
        else {
            for (const auto& jugador : jugadores) {
                cout << jugador << endl; // Usando la sobrecarga del operador <<
            }
        }
    }

    void gestionarSaldo(const string& nombreJugador) {
        bool jugadorEncontrado = false; // Variable para verificar si se encuentra el jugador

        for (auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                jugadorEncontrado = true; // Se encuentra el jugador
                int opcion;
                do {
                    cout << "\nGestión de Saldo:" << endl;
                    cout << "\n1. Consultar Saldo" << endl;
                    cout << "2. Hacer Recarga de Saldo" << endl;
                    cout << "3. Sumar Saldo con otro Jugador" << endl;
                    cout << "4. Restar Saldo con otro Jugador" << endl;
                    cout << "5. Comparar Saldo con otro Jugador" << endl;
                    cout << "6. Consultar Lista de Jugadores" << endl;
                    cout << "0. Volver a Menu Principal" << endl;
                    cout << "Selecciona una opción: ";
                    cin >> opcion;

                    if (cin.fail()) { // Comprobación de errores en la entrada del usuario
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada no válida. Por favor ingresa un número entero." << endl;
                        return;
                    }

                    switch (opcion) {
                    case 1:
                        cout << "Tu saldo actual es: " << jugador.saldo << endl;
                        break;
                    case 2: {
                        double recarga;
                        cout << "Introduce la cantidad a recargar: ";
                        cin >> recarga;

                        if (cin.fail() || recarga <= 0) { // Validar que la recarga sea un número positivo
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Cantidad no válida. La cantidad debe ser un número positivo." << endl;
                            return;
                        }

                        jugador.saldo += recarga;
                        cout << "Saldo recargado. Tu nuevo saldo es: " << jugador.saldo << endl;
                        break;
                    }
                    case 3: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encuentra el otro jugador
                        for (auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                jugador = jugador + otro; // Sumar saldo
                                cout << "Nuevo saldo tras la suma: " << jugador.saldo << endl;
                                otroJugadorEncontrado = true; // Se encuentra el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 4: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encontró el otro jugador
                        for (auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                jugador = jugador - otro; // Restar saldo
                                cout << "Nuevo saldo tras la resta: " << jugador.saldo << endl;
                                otroJugadorEncontrado = true; // Se encontró el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 5: {
                        string nombreOtro;
                        cout << "Introduce el nombre del otro jugador: ";
                        cin >> nombreOtro;
                        bool otroJugadorEncontrado = false; // Variable para verificar si se encontró el otro jugador
                        for (const auto& otro : jugadores) {
                            if (otro.nombre == nombreOtro) {
                                if (jugador == otro) {
                                    cout << "Los saldos son iguales." << endl;
                                }
                                else {
                                    cout << "Los saldos son diferentes." << endl;
                                }
                                otroJugadorEncontrado = true; // Se encontró el otro jugador
                                break;
                            }
                        }
                        if (!otroJugadorEncontrado) {
                            cout << "El jugador '" << nombreOtro << "' no se encuentra en la base de datos." << endl;
                        }
                        break;
                    }
                    case 6:
                        mostrarJugadores();
                        break;
                    case 0:
                        cout << "Volviendo al menú principal..." << endl;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                    }
                } while (opcion != 0);
                return;
            }
        }

        // Mensaje de error si no se encontró el jugador
        if (!jugadorEncontrado) {
            cout << "El jugador '" << nombreJugador << "' no se encuentra en la base de datos." << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla para números aleatorios
    Casino casino;

    string nombreJugador;
    cout << "Introduce tu nombre: ";
    cin >> nombreJugador;

    // Verificar si el jugador ya existe
    if (!casino.jugadorExiste(nombreJugador)) {
        casino.agregarJugador(nombreJugador, 100.0); // Saldo inicial
    }

    while (true) {
        int opcion;
        cout << "\n---------------------------------" << endl; //--------------------
        cout << "Menú Principal:" << endl;
        cout << "---------------------------------" << endl;  //--------------------
        cout << "1. Jugar" << endl;
        cout << "2. Gestionar Saldo" << endl;
        cout << "0. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        if (cin.fail()) { // Verificar si la opción es un número válido
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción no válida. Por favor ingresa un número entero." << endl;
            continue;
        }

        if (opcion == 0) {
            cout << "\nGracias por jugar. ¡Hasta luego!" << endl;
            break;
        }
        else if (opcion == 1) {
            casino.mostrarJuegos();
            cout << "Selecciona un juego (0 para salir): ";
            cin >> opcion;

            if (opcion == 0) {
                cout << "Volviendo al menú principal..." << endl;
                continue;
            }

            casino.jugarJuego(opcion, nombreJugador);
        }
        else if (opcion == 2) {
            casino.gestionarSaldo(nombreJugador);
        }
        else {
            cout << "Opción no válida." << endl;
        }
    }

    return 0;
}