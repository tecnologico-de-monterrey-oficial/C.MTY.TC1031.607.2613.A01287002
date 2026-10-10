#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <random>
#include <cstddef>

#include "doublylinkedlist.h"

int main() {
    std::cout << "========================================================\n"
              << "  Act 2.2 - Doubly Linked List                          \n"
              << "========================================================\n"
              << "De cual de los 2 tipos de datos quieres crear la lista?\n"
              << "  1) Lista de enteros        (int)\n"
              << "  2) Lista de decimales      (double)\n";

    int tipo = 0;
    while (tipo != 1 && tipo != 2) {
        std::cout << "Selecciona el tipo de lista: ";
        if (!(std::cin >> tipo)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Opcion no valida]\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (tipo != 1 && tipo != 2) {
            std::cout << "[Opcion no valida]\n";
        }
    }

    if (tipo == 2) {
        std::cout << std::fixed << std::setprecision(2);
    }

    int modo = 0;
    while (modo != 1 && modo != 2) {
        std::cout << "\nComo quieres llenar la lista?\n"
                  << "  1) Datos aleatorios\n"
                  << "  2) Datos capturados por el usuario\n"
                  << "Opcion: ";
        if (!(std::cin >> modo)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Opcion no valida]\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (modo != 1 && modo != 2) {
            std::cout << "[Opcion no valida]\n";
        }
    }

    long long cuantos = -1;
    std::cout << "Cuantos elementos tendra la lista? ";
    while (!(std::cin >> cuantos) || cuantos < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Cantidad invalida] Cuantos elementos tendra la lista? ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DoubleLinkedList<int> listaEnteros;
    DoubleLinkedList<double> listaDecimales;

    std::random_device rd;
    std::mt19937 gen(rd());

    if (modo == 1) {
        if (tipo == 1) {
            std::uniform_int_distribution<int> dist(1, 100);
            for (long long i = 0; i < cuantos; i++) {
                listaEnteros.addLast(dist(gen));
            }
            std::cout << "\nLista generada (" << cuantos << " elemento(s) aleatorio(s)): ";
            listaEnteros.print();
        } else {
            std::uniform_real_distribution<double> dist(0.0, 100.0);
            for (long long i = 0; i < cuantos; i++) {
                listaDecimales.addLast(dist(gen));
            }
            std::cout << "\nLista generada (" << cuantos << " elemento(s) aleatorio(s)): ";
            listaDecimales.print();
        }
    } else {
        if (tipo == 1) {
            for (long long i = 0; i < cuantos; i++) {
                int valor = 0;
                std::cout << "Elemento [" << i << "]: ";
                while (!(std::cin >> valor)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "[Dato invalido] Elemento [" << i << "]: ";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                listaEnteros.addLast(valor);
            }
            std::cout << "\nLista capturada: ";
            listaEnteros.print();
        } else {
            for (long long i = 0; i < cuantos; i++) {
                double valor = 0;
                std::cout << "Elemento [" << i << "]: ";
                while (!(std::cin >> valor)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "[Dato invalido] Elemento [" << i << "]: ";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                listaDecimales.addLast(valor);
            }
            std::cout << "\nLista capturada: ";
            listaDecimales.print();
        }
    }

    bool corriendo = true;
    while (corriendo) {
        if (tipo == 1) {
            std::cout << "\nLista actual (" << listaEnteros.size() << " elemento(s)): ";
            listaEnteros.print();
        } else {
            std::cout << "\nLista actual (" << listaDecimales.size() << " elemento(s)): ";
            listaDecimales.print();
        }

        std::cout << "================= MENU DE OPERACIONES =================\n"
                  << "  1. Agregar un elemento al principio de la lista\n"
                  << "  2. Agregar un elemento al final de la lista\n"
                  << "  3. Insertar un elemento a la derecha del indice dado\n"
                  << "  4. Borrar un elemento dado de la lista\n"
                  << "  5. Borrar un elemento en una posicion de la lista\n"
                  << "  6. Obtener el elemento de una posicion dada de la lista\n"
                  << "  7. Actualizar un elemento dado de la lista\n"
                  << "  8. Actualizar un elemento que se encuentra en una posicion dada\n"
                  << "  9. Encontrar un elemento dado en la lista\n"
                  << " 10. Obtener el elemento de una posicion  [operador []]\n"
                  << " 11. Actualizar el elemento de una posicion [operador []]\n"
                  << " 12. Igualar la lista con los datos de otra [operador =]\n"
                  << " 13. Limpiar la lista\n"
                  << " 14. Ordenar la lista\n"
                  << " 15. Duplicar la lista\n"
                  << " 16. Remover los elementos duplicados\n"
                  << " 17. Mostrar la lista (inicio -> fin y fin -> inicio)\n"
                  << "  0. Terminar\n"
                  << "=======================================================\n";

        int op = 0;
        std::cout << "Selecciona una opcion: ";
        while (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Opcion no valida] Selecciona una opcion: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (op) {
                case 0: {
                    corriendo = false;
                    std::cout << "\nLista final: ";
                    if (tipo == 1) {
                        listaEnteros.print();
                    } else {
                        listaDecimales.print();
                    }
                    std::cout << "Programa terminado.\n";
                    break;
                }

                case 1: {
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a agregar al principio: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.addFirst(valor);
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a agregar al principio: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.addFirst(valor);
                    }
                    std::cout << "Elemento agregado al principio.";
                    break;
                }

                case 2: {
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a agregar al final: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.addLast(valor);
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a agregar al final: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.addLast(valor);
                    }
                    std::cout << "Elemento agregado al final.";
                    break;
                }

                case 3: {
                    long long indice = -1;
                    std::cout << "Indice despues del cual insertas (0-based): ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Indice: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (tipo == 1) {
                        if (static_cast<size_t>(indice) >= listaEnteros.size()) {
                            throw std::out_of_range("Indice fuera de rango");
                        }
                        int valor = 0;
                        std::cout << "Elemento a insertar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.insert(static_cast<size_t>(indice), valor);
                    } else {
                        if (static_cast<size_t>(indice) >= listaDecimales.size()) {
                            throw std::out_of_range("Indice fuera de rango");
                        }
                        double valor = 0;
                        std::cout << "Elemento a insertar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.insert(static_cast<size_t>(indice), valor);
                    }
                    std::cout << "Elemento insertado despues del indice " << indice << ".";
                    break;
                }

                case 4: {
                    bool borrado = false;
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a borrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        borrado = listaEnteros.deleteData(valor);
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a borrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        borrado = listaDecimales.deleteData(valor);
                    }
                    std::cout << (borrado ? "Elemento borrado." : "El elemento no se encontro en la lista.");
                    break;
                }

                case 5: {
                    long long indice = -1;
                    std::cout << "Posicion a borrar: ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Posicion: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    bool borrado = false;
                    if (tipo == 1) {
                        borrado = listaEnteros.deleteAt(static_cast<size_t>(indice));
                    } else {
                        borrado = listaDecimales.deleteAt(static_cast<size_t>(indice));
                    }
                    if (borrado) {
                        std::cout << "Elemento de la posicion " << indice << " borrado.";
                    } else {
                        std::cout << "La posicion " << indice << " no existe en la lista.";
                    }
                    break;
                }

                case 6: {
                    long long indice = -1;
                    std::cout << "Posicion a obtener: ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Posicion: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (tipo == 1) {
                        int valor = listaEnteros.getData(static_cast<size_t>(indice));
                        std::cout << "Elemento en la posicion " << indice << ": " << valor;
                    } else {
                        double valor = listaDecimales.getData(static_cast<size_t>(indice));
                        std::cout << "Elemento en la posicion " << indice << ": " << valor;
                    }
                    break;
                }

                case 7: {
                    if (tipo == 1) {
                        int viejo = 0;
                        std::cout << "Elemento a actualizar: ";
                        while (!(std::cin >> viejo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        int nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.updateData(viejo, nuevo);
                    } else {
                        double viejo = 0;
                        std::cout << "Elemento a actualizar: ";
                        while (!(std::cin >> viejo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        double nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.updateData(viejo, nuevo);
                    }
                    std::cout << "Elemento actualizado.";
                    break;
                }

                case 8: {
                    long long indice = -1;
                    std::cout << "Posicion a actualizar: ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Posicion: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (tipo == 1) {
                        int nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.updateAt(static_cast<size_t>(indice), nuevo);
                    } else {
                        double nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.updateAt(static_cast<size_t>(indice), nuevo);
                    }
                    std::cout << "Elemento de la posicion " << indice << " actualizado.";
                    break;
                }

                case 9: {
                    int posicion = -1;
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a encontrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        posicion = listaEnteros.findData(valor);
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a encontrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        posicion = listaDecimales.findData(valor);
                    }
                    if (posicion == -1) {
                        std::cout << "El elemento no se encuentra en la lista (-1).";
                    } else {
                        std::cout << "El elemento esta en la posicion " << posicion << ".";
                    }
                    break;
                }

                case 10: {
                    long long indice = -1;
                    std::cout << "Posicion a obtener con []: ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Posicion: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (tipo == 1) {
                        int valor = listaEnteros[static_cast<size_t>(indice)];
                        std::cout << "lista[" << indice << "] = " << valor;
                    } else {
                        double valor = listaDecimales[static_cast<size_t>(indice)];
                        std::cout << "lista[" << indice << "] = " << valor;
                    }
                    break;
                }

                case 11: {
                    long long indice = -1;
                    std::cout << "Posicion a actualizar con []: ";
                    while (!(std::cin >> indice) || indice < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Indice invalido] Posicion: ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (tipo == 1) {
                        int& destino = listaEnteros[static_cast<size_t>(indice)];
                        int nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        destino = nuevo;
                        std::cout << "lista[" << indice << "] ahora es " << listaEnteros[static_cast<size_t>(indice)];
                    } else {
                        double& destino = listaDecimales[static_cast<size_t>(indice)];
                        double nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        destino = nuevo;
                        std::cout << "lista[" << indice << "] ahora es " << listaDecimales[static_cast<size_t>(indice)];
                    }
                    break;
                }

                case 12: {
                    DoubleLinkedList<int> fuenteEnteros;
                    DoubleLinkedList<double> fuenteDecimales;

                    std::cout << "\n-- Igualar la lista con los datos de otra lista (operador =) --\n";

                    int modoFuente = 0;
                    while (modoFuente != 1 && modoFuente != 2) {
                        std::cout << "Como quieres llenar la lista fuente?\n"
                                  << "  1) Datos aleatorios\n"
                                  << "  2) Datos capturados por el usuario\n"
                                  << "Opcion: ";
                        if (!(std::cin >> modoFuente)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Opcion no valida]\n";
                            continue;
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (modoFuente != 1 && modoFuente != 2) {
                            std::cout << "[Opcion no valida]\n";
                        }
                    }

                    long long cuantosFuente = -1;
                    std::cout << "Cuantos elementos tendra la lista fuente? ";
                    while (!(std::cin >> cuantosFuente) || cuantosFuente < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "[Cantidad invalida] Cuantos elementos tendra la lista fuente? ";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (modoFuente == 1) {
                        if (tipo == 1) {
                            std::uniform_int_distribution<int> dist(1, 100);
                            for (long long i = 0; i < cuantosFuente; i++) {
                                fuenteEnteros.addLast(dist(gen));
                            }
                        } else {
                            std::uniform_real_distribution<double> dist(0.0, 100.0);
                            for (long long i = 0; i < cuantosFuente; i++) {
                                fuenteDecimales.addLast(dist(gen));
                            }
                        }
                    } else {
                        if (tipo == 1) {
                            for (long long i = 0; i < cuantosFuente; i++) {
                                int valor = 0;
                                std::cout << "Elemento fuente [" << i << "]: ";
                                while (!(std::cin >> valor)) {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "[Dato invalido] Elemento: ";
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                fuenteEnteros.addLast(valor);
                            }
                        } else {
                            for (long long i = 0; i < cuantosFuente; i++) {
                                double valor = 0;
                                std::cout << "Elemento fuente [" << i << "]: ";
                                while (!(std::cin >> valor)) {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "[Dato invalido] Elemento: ";
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                fuenteDecimales.addLast(valor);
                            }
                        }
                    }

                    if (tipo == 1) {
                        listaEnteros = fuenteEnteros;
                        std::cout << "Lista fuente : ";
                        fuenteEnteros.print();
                        std::cout << "Lista copiada: ";
                        listaEnteros.print();

                        int extra = 0;
                        std::cout << "Agrega un elemento extra a la lista fuente: ";
                        while (!(std::cin >> extra)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        fuenteEnteros.addLast(extra);

                        std::cout << "Fuente  (modificada): ";
                        fuenteEnteros.print();
                        std::cout << "Copia   (sin cambio): ";
                        listaEnteros.print();
                    } else {
                        listaDecimales = fuenteDecimales;
                        std::cout << "Lista fuente : ";
                        fuenteDecimales.print();
                        std::cout << "Lista copiada: ";
                        listaDecimales.print();

                        double extra = 0;
                        std::cout << "Agrega un elemento extra a la lista fuente: ";
                        while (!(std::cin >> extra)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        fuenteDecimales.addLast(extra);

                        std::cout << "Fuente  (modificada): ";
                        fuenteDecimales.print();
                        std::cout << "Copia   (sin cambio): ";
                        listaDecimales.print();
                    }
                    std::cout << "-> La copia NO cambio: se duplico la lista, no se compartio.";
                    break;
                }

                case 13: {
                    if (tipo == 1) {
                        listaEnteros.clear();
                    } else {
                        listaDecimales.clear();
                    }
                    std::cout << "Lista limpiada.";
                    break;
                }

                case 14: {
                    if (tipo == 1) {
                        listaEnteros.sort();
                    } else {
                        listaDecimales.sort();
                    }
                    std::cout << "Lista ordenada.";
                    break;
                }

                case 15: {
                    if (tipo == 1) {
                        listaEnteros.duplicate();
                    } else {
                        listaDecimales.duplicate();
                    }
                    std::cout << "Cada elemento de la lista fue duplicado.";
                    break;
                }

                case 16: {
                    if (tipo == 1) {
                        listaEnteros.sort();
                        std::cout << "Lista ordenada: ";
                        listaEnteros.print();
                        listaEnteros.removeDuplicates();
                    } else {
                        listaDecimales.sort();
                        std::cout << "Lista ordenada: ";
                        listaDecimales.print();
                        listaDecimales.removeDuplicates();
                    }
                    std::cout << "Elementos duplicados removidos.";
                    break;
                }

                case 17: {
                    if (tipo == 1) {
                        std::cout << "Inicio -> fin: ";
                        listaEnteros.print();
                        std::cout << "Fin -> inicio: ";
                        listaEnteros.printReverse();
                    } else {
                        std::cout << "Inicio -> fin: ";
                        listaDecimales.print();
                        std::cout << "Fin -> inicio: ";
                        listaDecimales.printReverse();
                    }
                    break;
                }

                default: {
                    std::cout << "[Opcion no valida]";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "[Error] " << e.what();
        }

        std::cout << "\n\nPresiona ENTER para continuar...";
        std::string linea;
        std::getline(std::cin, linea);
        std::cout << "\n";
    }

    return 0;
}
