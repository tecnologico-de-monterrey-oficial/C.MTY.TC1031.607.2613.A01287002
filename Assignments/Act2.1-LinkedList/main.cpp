/*
 *  Act 2.1 - Linked List (ADT con Template)
 *  Andrés Rodríguez Cantú
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <random>
#include <cstddef>

#include "helper.h"
#include "linkedlist.h"

int main() {
    std::cout << "========================================================\n"
              << "  Act 2.1 - Linked List                                 \n"
              << "========================================================\n"
              << "¿De cual de los 2 tipos de datos quieres crear la lista?\n"
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

    LinkedList<int> listaEnteros;
    LinkedList<double> listaDecimales;

    std::random_device rd;
    std::mt19937 gen(rd());

    if (modo == 1) {
        if (tipo == 1) {
            std::uniform_int_distribution<int> dist(1, 100);
            for (long long i = 0; i < cuantos; i++) {
                listaEnteros.append(dist(gen));
            }
            std::cout << "\nLista generada (" << cuantos << " elemento(s) aleatorio(s)): ";
            listaEnteros.print();
        } else {
            std::uniform_real_distribution<double> dist(0.0, 100.0);
            for (long long i = 0; i < cuantos; i++) {
                listaDecimales.append(dist(gen));
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
                listaEnteros.append(valor);
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
                listaDecimales.append(valor);
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
                  << "  3. Insertar un elemento despues del indice dado\n"
                  << "  4. Borrar un elemento dado de la lista\n"
                  << "  5. Borrar un elemento en una posicion de la lista\n"
                  << "  6. Obtener el elemento de una posicion dada de la lista\n"
                  << "  7. Actualizar un elemento dado de la lista\n"
                  << "  8. Actualizar un elemento que se encuentra en una posicion dada\n"
                  << "  9. Encontrar un elemento dado en la lista\n"
                  << " 10. Obtener el elemento de una posicion  [operador []]\n"
                  << " 11. Actualizar el elemento de una posicion [operador []]\n"
                  << " 12. Igualar la lista con los datos de otra [operador =]\n"
                  << " 13. Mostrar la lista\n"
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
                    if (tipo == 1) {
                        std::cout << "\nLista final: ";
                        listaEnteros.print();
                    } else {
                        std::cout << "\nLista final: ";
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
                        listaEnteros.prepend(valor);
                        std::cout << "Elemento agregado al principio.";
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a agregar al principio: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.prepend(valor);
                        std::cout << "Elemento agregado al principio.";
                    }
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
                        listaEnteros.append(valor);
                        std::cout << "Elemento agregado al final.";
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a agregar al final: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.append(valor);
                        std::cout << "Elemento agregado al final.";
                    }
                    break;
                }

                case 3: {
                    if (tipo == 1) {
                        if (listaEnteros.empty()) {
                            throw std::out_of_range("La lista esta vacia");
                        }
                        long long indice = -1;
                        std::cout << "Indice despues del cual insertas (0-based): ";
                        while (!(std::cin >> indice) || indice < 0) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Indice invalido] Indice: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                        listaEnteros.insertAt(static_cast<size_t>(indice) + 1, valor);
                        std::cout << "Elemento insertado despues del indice " << indice << ".";
                    } else {
                        if (listaDecimales.empty()) {
                            throw std::out_of_range("La lista esta vacia");
                        }
                        long long indice = -1;
                        std::cout << "Indice despues del cual insertas (0-based): ";
                        while (!(std::cin >> indice) || indice < 0) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Indice invalido] Indice: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                        listaDecimales.insertAt(static_cast<size_t>(indice) + 1, valor);
                        std::cout << "Elemento insertado despues del indice " << indice << ".";
                    }
                    break;
                }

                case 4: {
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a borrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros.deleteData(valor);
                        std::cout << "Elemento borrado.";
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a borrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales.deleteData(valor);
                        std::cout << "Elemento borrado.";
                    }
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
                    if (tipo == 1) {
                        listaEnteros.removeAt(static_cast<size_t>(indice));
                        std::cout << "Elemento de la posicion " << indice << " borrado.";
                    } else {
                        listaDecimales.removeAt(static_cast<size_t>(indice));
                        std::cout << "Elemento de la posicion " << indice << " borrado.";
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
                        int valor = 0;
                        listaEnteros.getData(static_cast<size_t>(indice), valor);
                        std::cout << "Elemento en la posicion " << indice << ": " << valor;
                    } else {
                        double valor = 0;
                        listaDecimales.getData(static_cast<size_t>(indice), valor);
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
                        std::cout << "Elemento actualizado.";
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
                        std::cout << "Elemento actualizado.";
                    }
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
                        std::cout << "Elemento de la posicion " << indice << " actualizado.";
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
                        std::cout << "Elemento de la posicion " << indice << " actualizado.";
                    }
                    break;
                }

                case 9: {
                    if (tipo == 1) {
                        int valor = 0;
                        std::cout << "Elemento a encontrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        size_t posicion = 0;
                        listaEnteros.findData(valor, posicion);
                        std::cout << "El elemento esta en la posicion " << posicion << ".";
                    } else {
                        double valor = 0;
                        std::cout << "Elemento a encontrar: ";
                        while (!(std::cin >> valor)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Elemento: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        size_t posicion = 0;
                        listaDecimales.findData(valor, posicion);
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
                        std::cout << "lista[" << indice << "] = " << listaEnteros[static_cast<size_t>(indice)];
                    } else {
                        std::cout << "lista[" << indice << "] = " << listaDecimales[static_cast<size_t>(indice)];
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
                        int nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaEnteros[static_cast<size_t>(indice)] = nuevo;
                        std::cout << "lista[" << indice << "] ahora es " << listaEnteros[static_cast<size_t>(indice)];
                    } else {
                        double nuevo = 0;
                        std::cout << "Nuevo valor: ";
                        while (!(std::cin >> nuevo)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[Dato invalido] Nuevo valor: ";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        listaDecimales[static_cast<size_t>(indice)] = nuevo;
                        std::cout << "lista[" << indice << "] ahora es " << listaDecimales[static_cast<size_t>(indice)];
                    }
                    break;
                }

                case 12: {
                    LinkedList<int> fuenteEnteros;
                    LinkedList<double> fuenteDecimales;

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
                                fuenteEnteros.append(dist(gen));
                            }
                        } else {
                            std::uniform_real_distribution<double> dist(0.0, 100.0);
                            for (long long i = 0; i < cuantosFuente; i++) {
                                fuenteDecimales.append(dist(gen));
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
                                fuenteEnteros.append(valor);
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
                                fuenteDecimales.append(valor);
                            }
                        }
                    }

                    if (tipo == 1) {
                        listaEnteros = fuenteEnteros;  // operador =
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
                        fuenteEnteros.append(extra);

                        std::cout << "Fuente  (modificada): ";
                        fuenteEnteros.print();
                        std::cout << "Copia   (sin cambio): ";
                        listaEnteros.print();
                    } else {
                        listaDecimales = fuenteDecimales;  // operador =
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
                        fuenteDecimales.append(extra);

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
                        std::cout << "Lista: ";
                        listaEnteros.print();
                    } else {
                        std::cout << "Lista: ";
                        listaDecimales.print();
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
