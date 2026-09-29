// Jared Aldana Palacios & Andrés Rodríguez Cantú
// A00844802 & A012870002

#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Queue.h"
#include "Client.h"

using namespace std;

int readInt(const string& message, int min, int max) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "  Entrada invalida. Intenta de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string& message) {
    string text;
    while (true) {
        cout << message;
        getline(cin, text);
        if (!text.empty()) {
            return text;
        }
        cout << "  El nombre no puede estar vacio.\n";
    }
}

void showMenu() {
    cout << "\n===== TAQUILLA DE BOLETOS =====\n";
    cout << "1. Llegada de un nuevo cliente\n";
    cout << "2. Atender al siguiente cliente\n";
    cout << "3. Ver al siguiente cliente sin atenderlo aun\n";
    cout << "4. Mostrar cuantas personas hay en la fila\n";
    cout << "5. Salir\n";
}

int main() {
    Queue<Client> queue;
    int option = 0;

    do {
        showMenu();
        option = readInt("Selecciona una opcion: ", 1, 5);

        switch (option) {
            case 1: {
                string name = readText("Nombre del cliente: ");
                int tickets = readInt("Cantidad de boletos: ", 1, 1000);
                queue.push(Client(name, tickets));
                cout << "  " << name << " se formo en la fila. "
                     << "Personas en fila: " << queue.size() << "\n";
                break;
            }
            case 2: {
                try {
                    Client served = queue.pop();
                    cout << "  Atendiendo a " << served.name
                         << ", quien pidio " << served.tickets
                         << " boleto(s).\n";
                } catch (const out_of_range& e) {
                    cout << "  No hay clientes en la fila. (" << e.what() << ")\n";
                }
                break;
            }
            case 3: {
                try {
                    Client next = queue.front();
                    cout << "  Siguiente cliente: " << next.name
                         << " | Boletos: " << next.tickets << "\n";
                } catch (const out_of_range& e) {
                    cout << "  No hay clientes en la fila. (" << e.what() << ")\n";
                }
                break;
            }
            case 4:
                cout << "  Personas en la fila: " << queue.size() << "\n";
                break;
            case 5:
                cout << "  Saliendo del sistema. Clientes sin atender: "
                     << queue.size() << "\n";
                break;
        }
    } while (option != 5);

    return 0;
}
