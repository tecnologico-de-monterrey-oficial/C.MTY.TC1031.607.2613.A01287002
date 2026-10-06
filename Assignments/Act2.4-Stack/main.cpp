#include "helper.h"

class PaginaWeb {
private:
    std::string titulo;
    std::string link;

public:
    PaginaWeb(std::string t, std::string l) : titulo(std::move(t)), link(std::move(l)) {}

    void print() const {
        std::cout << "Titulo: " << titulo << ", Link: " << link << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const PaginaWeb& pagina) {
        os << pagina.titulo << " (" << pagina.link << ")";
        return os;
    }
};

int main() {
    Stack<PaginaWeb> historial;
    int opcion = 0;

    while (opcion != 5) {
        std::cout << "\n===== Navegador web =====" << std::endl;
        std::cout << "1. Visitar una nueva pagina" << std::endl;
        std::cout << "2. Retroceder a la pagina anterior" << std::endl;
        std::cout << "3. Ver la pagina actual" << std::endl;
        std::cout << "4. Mostrar cuantas paginas hay en el historial" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Selecciona una opcion: ";

        std::string entrada;
        std::getline(std::cin, entrada);
        try {
            opcion = std::stoi(entrada);
        } catch (...) {
            opcion = 0;
        }

        switch (opcion) {
            case 1: {
                std::string titulo, url;
                std::cout << "Titulo de la pagina: ";
                std::getline(std::cin, titulo);
                std::cout << "URL de la pagina: ";
                std::getline(std::cin, url);

                historial.push(PaginaWeb(titulo, url));
                std::cout << "Pagina agregada al historial: " << historial.top() << std::endl;
                break;
            }
            case 2: {
                if (historial.size() == 0) {
                    std::cout << "El historial esta vacio, no hay paginas que cerrar." << std::endl;
                    break;
                }
                PaginaWeb cerrada = historial.top();
                historial.pop();
                std::cout << "Se cerro la pagina: " << cerrada << std::endl;
                std::cout << "Pagina actual: ";
                if (historial.size() == 0) {
                    std::cout << "(ninguna, el historial quedo vacio)" << std::endl;
                } else {
                    historial.top().print();
                }
                break;
            }
            case 3: {
                if (historial.size() == 0) {
                    std::cout << "No hay ninguna pagina abierta." << std::endl;
                    break;
                }
                std::cout << "Pagina actual: " << std::endl;
                historial.top().print();
                break;
            }
            case 4: {
                std::cout << "Paginas en el historial: " << historial.size() << std::endl;
                if (historial.size() > 0) {
                    std::cout << "Historial (de mas reciente a mas antigua): ";
                    historial.print();
                }
                break;
            }
            case 5: {
                std::cout << "Saliendo del navegador. Paginas en el historial: "
                          << historial.size() << std::endl;
                break;
            }
            default: {
                std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                break;
            }
        }
    }

    return 0;
}
