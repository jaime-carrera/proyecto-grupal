/*
 PROYECTOS DE PROGRAMACIoN 
 Primera entrega proyecto: CASINO
 Grupo formado por: Rodrigo Calderon, alvaro Aguilar, Pedro Riveiro, Gonzalo Olivares, Eduardo Bernad y Jaime Carrera
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
//El valor maximo de la baraja siempre va a ser 52.
#define C 52

using namespace std;
//Una constante para establecer el nº maximo de jugadores que puede haber.
const int MAX = 100;
//Creamos la estructura de la carta.
typedef struct{
    int cartas[C];
    //el numero de cartas que va a tener cada jugador.
    int num;
}Cartas;
//Creamos la estructura del jugador.
typedef struct{
    int partidasGanadas;
    int partidasPerdidas;
    float saldo;
    string nickJugador;
}Jugador;
//Creamos la estructura de los datos.
typedef struct{
    int numJugadores;
    Jugador jugadoresBlackjack[MAX];
} DatosPartida;

//funcion encargada de mostrar el menu por pantalla, comprobar que la opcion escogida sea valida, y devolver la opcion escogida.
int menu();
//en esta funcion se desarrolla el turno del jugador, devuelve la puntuacion total del jugador.
int juegaHumano(Cartas & mazo, Cartas & cartasJugador);
//en esta funcion se desarrolla el turno del Crupier, devuelve la puntuacion total del Crupier.
int juegaCrupier(Cartas & mazo, Cartas & cartasCrupier);
//funcion que, dada una mano de cartas calcula los puntos de las cartas de la mano de acuerdo a las reglas del juego.
int calculaPuntos(Cartas mano);
//saca una carta del mazo y devuelve su valor.
int sacarCartaMazo(Cartas & mazo);
//esta funcion calcula el ganador de la partida teniendo en cuenta la puntuacion y, en caso de empate, el numero de cartas de cada uno.
int ganador(int jugadorPts, int crupierPts, int numCartasJugador, int numCartasCrupier);
// busca al jugador con el nick especificado y devuelve un entero indicando su posicion en la lista. Si no lo encuentra, devuelve -1
int buscaJugador(DatosPartida d, string nick);
//muestra el texto de las reglas del BLACKJACK por pantalla.
void muestraReglas_BJ();
//muestra el texto de las reglas de la RULETA por pantalla.
void muestraReglas_R ();
//dado un mazo de cartas creado, inicializa los valores en orden con los 52 valores de la baraja.
void inicializaMazo(Cartas& mazo);
//dado un mazo de cartas, las mezcla aleatoriamente
void barajar(Cartas& mazo);
//aqui se desarrolla la accion principal del juego
void juegoBlackjack(DatosPartida &d, Jugador &j);
//añade una carta a la mano de cartas
void annadeCarta(Cartas & mano, int carta);
//muestra el mazo de cartas por pantalla
void muestraMazo(Cartas cartas);
// carga los datos de los jugadores del archivo "jugadores.txt"
void cargaDatos(DatosPartida &d);
// permite consultar y recargar el saldo de un jugador
void gestionSaldo(DatosPartida &d, Jugador &j);
// muestra la informacion del jugador con el nick especificado
void muestraInfo(DatosPartida d, string nick); //ok
// muestra la informacion de todos los jugadores registrados
void infoJugadores(DatosPartida d);
// actualiza la lista de jugadores con los datos del jugador j, si no existe lo añade a la lista
void actualizaJugador(DatosPartida &d, Jugador j);
// añade un nuevo jugador a la lista. Si no cabe, muestra un mensaje de error
void guardaJugador(DatosPartida &d, Jugador j);
// guarda los datos de todos los jugadores registrados en el archivo "jugadores.txt"
void guardaDatos(DatosPartida d);
Jugador iniciarSesion(DatosPartida &d, string nick);
//Strings para los menus y encabezados.
string menuPrincipal = "\n----------------------------------- \
    \n BIENVENIDO AL CASINO \
    \n----------------------------------- \
    \n1 - BLACKJACK\n2 - RULETA \n3 - Ver informacion de todos los jugadores \
    \n4 - Ver informacion jugador \
    \n5 - Saldo \n6 - Reglas BLACKJACK \
    \n7 - Reglas RULETA \n0 - Salir \
    \nElige: ";
string menuSaldo = "\n---------------- \nGESTION DE SALDO \n---------------- \
    \n1 - Consulta el saldo disponible \
    \n2 - Recarga \n0 - Salir \nElige una opcion: ";
string reglas_bj = "\nAntes de comenzar la partida, has de hacer tu apuesta. \
    \nSi no tienes suficiente saldo, puedes recargarlo antes de jugar eligiendo\
 la opcion 4 del menu. \
    \nAl principio, los jugadores obtienen 2 cartas. \
    \nEn tu turno, eligiras si quieres una carta mas o si quieres plantarte. \
    \nEl ganador de la partida sera el que mas se aproxime a 21 sin pasarse. \
    \nLas cartas numericas suman su valor, las figuras suman 10 y el As vale 11 o 1. \
    \nLa mejor jugada es el Blackjack: conseguir 21 con solo dos cartas, un As mas un 10. \
    \nUn Blackjack gana sobre un 21 conseguido con mas de dos cartas. \
    \nVolviendo al menu...";
string reglas_ruleta = "\nBienvenido al juego de la ruleta. \
    \n En este juego, podras realizar tres tipos de apuestas. \
    \n Estas apuestas consisten en elegir entre un numero par o impar, un color (rojo o negro), o un numero especifico. \
    \n Cada apuesta ofrece un multiplicador distinto sobre el dinero invertido: si aciertas en par o impar, tu dinero se duplicara, al igual que si aciertas el color. \
    \n Sin embargo, si logras acertar el numero exacto entre el 0 y el 36, ¡tu dinero se multiplicara por 36!";
string turnoJugador = "\nTurno del jugador \
    \n-----------------------------------";
string turnoCrupier = "\nTurno del crupier \
    \n-----------------------------------";
string puntuacionFinal = "\n----------------------------------- \
    \n Puntuacion final \
    \n-----------------------------------\n";

int main(){
    int eleccion;
    //Servira para buscar al jugador o crear uno nuevo.
    string nick;
    DatosPartida d;
    d.numJugadores = 0;
    Jugador j;
    //Carga los datos.
    cargaDatos(d);
    
    cout << "Introduce tu nick: " << endl;
    cin >> nick;
    
    j = iniciarSesion(d, nick);
    //loop para que se pueda jugar tantas veces como quiera el jugador.
    do {
        eleccion = menu();
        //dependiendo de la eleccion del jugador se llevara a cabo una de las opciones
        switch (eleccion){
            case 1:
                juegoBlackjack(d,j);
                actualizaJugador(d, j);
                break;
            case 2:
                // juegoRuleta(d,j);
                break;
            case 3:
                infoJugadores(d);
                break;
            case 4:
                muestraInfo(d, nick);
                break;
            case 5:
                gestionSaldo(d,j);
                break;
            case 6:
                muestraReglas_BJ();
                break;
            case 7: 
                muestraReglas_R();
            case 0:
                cout << "¡Hasta pronto!" << endl;
                //Al salir se guardan los datos en el archivo de texto.
                guardaDatos(d);
                break;
            //por si se introduce cualquier otro numero.
            default:
                cout << "Esta opcion no es valida" << endl;
                break;
        }

    }
    while (eleccion != 0);
}

int menu(){
    int eleccion;
    cout << menuPrincipal << endl;
    cin >> eleccion;
    //devuelve el valor de la opcion que hemos elegido.
    return eleccion;
}
int sacarCartaMazo(Cartas& mazo){
    //Cada vez que sacamos una carta quitamos 1 a la baraja.
    mazo.num = mazo.num - 1;
    return mazo.cartas[mazo.num];
}
int juegaHumano(Cartas & mazo, Cartas & cartasJugador){
    //Variables.
    int puntos = 0;
    string eleccionJugador;
    bool plantarse = false;
    
    cout << turnoJugador << endl;
    
    //loop para que podamos sacar cartas hasta que nos plantemos o superemos 21.
    while (plantarse == false){
        cout << "Tus cartas:\t";
        muestraMazo(cartasJugador);
        puntos = calculaPuntos(cartasJugador);
        cout << "\tPuntos: " << puntos << endl;
    
        if (puntos < 21){
            cout << "¿Quieres plantarte? (S/N)" << endl;
            cin >> eleccionJugador;
            if (eleccionJugador == "s" || eleccionJugador == "S"){
                plantarse = true;
            }
            else if (eleccionJugador == "n" || eleccionJugador == "N"){
                annadeCarta(cartasJugador, sacarCartaMazo(mazo));
            }
        }
        if (puntos == 21){
            plantarse = true;
        }
        else if (puntos > 21){
            cout << "Te pasas de 21. ¡Pierdes!" << endl;
            plantarse = true;
        }
    }
    //Nos devuelve el total de puntos del jugador.
    return puntos;
}
int calculaPuntos(Cartas mano){
    //Variables.
    int ptsJugador = 0;
    //Recorremos todas las cartas que hay en la mano.
    for(int i = 0; i < mano.num; i++){
        //Si es distinto de 0 y menor que 10, la carta vale su valor.
        if (mano.cartas[i] != 0 && mano.cartas[i] < 10){
            ptsJugador = ptsJugador + mano.cartas[i] + 1 ;
        }
        //Si es mayor o igual que 10, la carta vale 10.
        else if (mano.cartas[i] >= 10){
            ptsJugador = ptsJugador + 10;
        }
        //El as valdra 11 o 1, segun convenga al jugador.
        else if (mano.cartas[i] == 0){
            if (ptsJugador + 11 <= 21){
                ptsJugador = ptsJugador + 11;
            }
            else if (ptsJugador + 11 > 21){
                ptsJugador = ptsJugador + 1;
            }
        }
    }
    return ptsJugador;
}
int juegaCrupier(Cartas & mazo, Cartas & cartasCrupier){
    int puntosC = 0;
    bool terminar = false;
    
    cout << turnoCrupier << endl;
   
    while (terminar == false){
        muestraMazo(cartasCrupier);
        puntosC = calculaPuntos(cartasCrupier);
        cout << "\tPuntos: " << puntosC << endl;
    
        //Si su puntuacion es menor de 17, sigue sacando carta.
        if (puntosC < 17){
            annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
        }
        //Si su puntuacion es mayor o igual a 17, se planta.
        else if (puntosC >= 17){
            terminar = true;
        }
    }
    return puntosC;
}
int ganador(int jugadorPts, int crupierPts, int numCartasJugador, int numCartasCrupier){
    int ganador = 0;
    //El jugador pierde por pasarse de 21.
    if (jugadorPts > 21){
        ganador = 2;
    }
    //El crupier pierde por pasarse de 21.
    else if (crupierPts > 21){
        ganador = 1;
    }
    else if (jugadorPts < crupierPts){
        ganador = 2;
    }
    else if (jugadorPts > crupierPts){
        ganador = 1;
    }
    //Gana el que menos cartas tenga.
    else {
        if (numCartasJugador < numCartasCrupier){
            ganador = 1;
        }
        else if (numCartasJugador > numCartasCrupier){
            ganador = 2;
        }
        else {
            ganador = 0;
        }
    }
    return ganador;
}
Jugador iniciarSesion(DatosPartida &d, string nick){
    int jugadorActual;
    //Nos permite ver si el jugador esta en la base de datos o no.
    jugadorActual = buscaJugador(d, nick);
    //Para poder crear un nuevo perfil de jugador.
    Jugador j;
    //Si el jugador no esta en la base de datos.
    if (jugadorActual == -1){
        cout << "El jugador no esta en nuestra base de datos." << endl;
        cout << "Creando un nuevo usuario..." << endl;
        //Se crea el perfil determinado.
        j.nickJugador = nick;
        j.partidasGanadas = 0;
        j.partidasPerdidas = 0;
        j.saldo = 100;
        //Se guarda el jugador.
        guardaJugador(d, j);
        cout << "Bienvenido " << j.nickJugador << endl;
        }
    //Si el jugador esta en la base de datos.
    else {
        j = d.jugadoresBlackjack[jugadorActual];
        cout << "Bienvenido " << j.nickJugador << endl;
    }

    return j;
}
int buscaJugador(DatosPartida d, string nick){
    int existeJugador = -1;
    int i = 0;
    bool encontrado = false;
    while (i < d.numJugadores && encontrado == false){
        if (d.jugadoresBlackjack[i].nickJugador == nick){
            existeJugador = i;
            encontrado = true;
        }
        i++;
    }
    return existeJugador;
}
void juegoBlackjack(DatosPartida &d, Jugador &j){
    //variables:
    int jugadorPts = 0;
    int crupierPts = 0;
    int numCartasJugador;
    int numCartasCrupier;
    int victoria;
    float apuesta = 0;
  
    Cartas mazo;
    mazo.num = 0;
    
    //Inicializamos y barajamos el mazo.
    inicializaMazo(mazo);
    barajar(mazo);
   
    //Repartimos las cartas al crupier y mostramos la primera carta.
    Cartas cartasCrupier;
    cartasCrupier.num = 0;
    annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
    annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
    
    cout << "¿Cuanto quieres apostar? Tienes " << j.saldo << " Euros: " << endl;
    cin >> apuesta;
    
    if (apuesta <= j.saldo){
        cout << "Empieza el juego. Apuestas " << apuesta << " Euros." << endl;
        //Se quita el valor apostado al saldo (luego se devolvera o no).
        j.saldo = j.saldo - apuesta;
    
        cout <<"\nSe ha repartido."<< endl;
        cout <<"La primera carta del crupier es un "<< cartasCrupier.cartas[0] + 1 << endl;
        
        //Repartimos las cartas al jugador.
        Cartas cartasJugador;
        cartasJugador.num = 0;
        annadeCarta(cartasJugador, sacarCartaMazo(mazo));
        annadeCarta(cartasJugador, sacarCartaMazo(mazo));
    
        //Se lleva a cabo el juego del jugador.
        jugadorPts = juegaHumano(mazo, cartasJugador);
        numCartasJugador = cartasJugador.num;
   
        //El juego del crupier solo se desarrolla si el jugador no ha superado los 21 puntos.
        if (jugadorPts <= 21){
            crupierPts = juegaCrupier(mazo, cartasCrupier);
            numCartasCrupier = cartasCrupier.num;
    
            cout << puntuacionFinal << "Crupier: " << crupierPts << "\tJugador: " << jugadorPts << endl;
            victoria = ganador(jugadorPts, crupierPts, numCartasJugador, numCartasCrupier);
        }
        //Si la puntuacion del jugador es mayor de 21, automaticamente gana el crupier.
        else {
            victoria = 2;
        }
    
        switch (victoria){
            case 1:
                cout << "¡Ganas!" << endl;
                //Se devuelve el dinero apostado y se suma el valor apostado.
                j.saldo = j.saldo + (apuesta * 2);
                //Se suma una victoria.
                j.partidasGanadas = j.partidasGanadas + 1;
                //Se guardan los datos del jugador.
                guardaDatos(d);
                break;
            case 2:
                cout << "¡Gana el crupier!" << endl;
                j.partidasPerdidas = j.partidasPerdidas + 1;
                guardaDatos(d);
                break;
            case 0:
                cout << "¡Habeis empatado!" << endl;
                //Se devuelve lo apostado pero no se suma mas.
                j.saldo = j.saldo + apuesta;
                guardaDatos(d);
                break;
        }
    }
    else if (apuesta > j.saldo){
        cout << "No dispones de saldo. \nPara jugar, realiza una recarga" << endl;
    }
}
void inicializaMazo(Cartas& mazo){
    for(int i = 0; i < C; i++){
        //Asignamos un valor a cada posicion, hay 13 valores por palo.
        mazo.cartas[i] = i % 13;
        mazo.num++;
    }
}
void barajar(Cartas& mazo){
    srand((unsigned int )time(NULL));
    int j, k, temp;
    for(j = 0; j < C; j++){
        //Generamos numeros aleatorios hasta el 52.
        k = rand() % 52;
        //Intercambiamos las barajas para hacer la "mezcla".
        temp = mazo.cartas[j];
        mazo.cartas[j] = mazo.cartas[k];
        mazo.cartas[k] = temp;
    }
}
void annadeCarta(Cartas & mano, int carta){
    mano.cartas[mano.num] = carta;
    //añadimos una carta mas a la mano.
    mano.num++;
}
void muestraReglas_BJ(){
    cout << reglas_bj << endl;
}
void muestraReglas_R(){
    cout << reglas_ruleta << endl; 
}
void muestraMazo(Cartas cartas){
    //Loop para enseñar las cartas.
    for (int i = 0; i < cartas.num; ++i){
        cout << cartas.cartas[i] + 1 << " ";
    }
}
void cargaDatos(DatosPartida &d){
    ifstream file;
    file.open ("jugadores.txt");
    
    if (file.is_open()){
        //Si se abre el archivo, el programa carga los datos de los jugadores.
        file >> d.numJugadores;
        for (int i = 0; i < d.numJugadores; i++){
            file >> d.jugadoresBlackjack[i].nickJugador;
            file >> d.jugadoresBlackjack[i].partidasGanadas;
            file >> d.jugadoresBlackjack[i].partidasPerdidas;
            file >> d.jugadoresBlackjack[i].saldo;
        }
    }
    else{
        cout << "No se ha podido abrir el archivo" << endl;
    }
    file.close();
}
void guardaDatos(DatosPartida d){
    ofstream file;
    file.open ("jugadores.txt");
    //Si se abre, se añaden los datos y se guardan en el archivo de texto.
    if (file.is_open()){
        file << d.numJugadores << endl;
        for (int i = 0; i < d.numJugadores; i++){
            file << d.jugadoresBlackjack[i].nickJugador << endl;
            file << d.jugadoresBlackjack[i].partidasGanadas << endl;
            file << d.jugadoresBlackjack[i].partidasPerdidas << endl;
            file << d.jugadoresBlackjack[i].saldo << endl;
        }
    }
    else{
        cout << "El Archivo 'jugadores.txt' No Se Ha Podido Abrir. " << endl;
    }
    file.close();
}
void guardaJugador(DatosPartida &d, Jugador j){
    if (d.numJugadores < MAX){
        //Se guarda el jugador en la lista de los jugadores.
        d.jugadoresBlackjack[d.numJugadores] = j;
        d.numJugadores ++;
    }
    else if (d.numJugadores == MAX){
        cout << "No se pueden añadir mas jugadores" << endl;
    }
}
void actualizaJugador(DatosPartida &d, Jugador j){
    int buscar;
    buscar = buscaJugador(d, j.nickJugador);
    //Si el jugador existe, se guardan los nuevos datos.
    if (buscar != -1){
        d.jugadoresBlackjack[buscar] = j;
    }
    else if (buscar == -1){
        guardaJugador(d, j);
    }
}
void infoJugadores(DatosPartida d){
    //Imprime por pantalla los datos de los jugadores.
    for (int i = 0; i < d.numJugadores; i++){
        cout << "\nLos datos almacenados del jugador " << d.jugadoresBlackjack[i].nickJugador << " son: " << endl;
        cout << "Numero de partidas ganadas: \t" << d.jugadoresBlackjack[i].partidasGanadas << endl;
        cout << "Numero de partidas perdidas : \t" << d.jugadoresBlackjack[i].partidasPerdidas << endl;
        cout << "Saldo disponible: \t" << d.jugadoresBlackjack[i].saldo << "euros" << endl;
    }
}
void muestraInfo(DatosPartida d, string nick){
    int jugadorActual;
    jugadorActual = buscaJugador(d, nick);
    //Imprime por pantalla los datos del jugador.
    cout << "\nLos datos almacenados del jugador " << d.jugadoresBlackjack[jugadorActual].nickJugador << " son: " << endl;
    cout << "Numero de partidas ganadas: \t" << d.jugadoresBlackjack[jugadorActual].partidasGanadas << endl;
    cout << "Numero de partidas perdidas : \t" << d.jugadoresBlackjack[jugadorActual].partidasPerdidas << endl;
    cout << "Saldo disponible: \t" << d.jugadoresBlackjack[jugadorActual].saldo << "euros0" << endl;
}
void gestionSaldo(DatosPartida &d, Jugador &j){
    int opcion;
    do{
        cout << menuSaldo << endl;
        cin >> opcion;
        
        switch (opcion){
            case 1:
                //Muestra el saldo del jugador por pantalla.
                cout << "Tu saldo disponible es: " << j.saldo << endl;
                break;
            case 2:
                //Si el saldo es positivo o 0 se suman 100euros.
                if (j.saldo >= 0){
                    j.saldo = j.saldo + 100;
                    //Se guardan los nuevos datos del jugador.
                    guardaDatos(d);
                    actualizaJugador(d, j);
                    cout << "Se ha recargado tu saldo con 100euros" << endl;
                }
                else {
                    cout << "error" << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Esta opcion no es valida" << endl;
                break;
        }
    }
    while (opcion != 0);
}
