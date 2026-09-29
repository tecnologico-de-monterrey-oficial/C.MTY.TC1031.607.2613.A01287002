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
    Stack<PaginaWeb> stack;
    stack.push(PaginaWeb("Un gran video", "https://www.youtube.com/watch?v=dQw4w9WgXcQ"));
    std::cout << "¡Videos!" << std::endl;
    std::string titulo, link;

    while (true) {
        std::cout << "Ingrese el titulo del video (o 'salir' para terminar): ";
        std::getline(std::cin, titulo);
        if (titulo == "salir") {
            break;
        }
        
        std::cout << "Ingrese el link del video: ";
        std::getline(std::cin, link);
        
        stack.push(PaginaWeb(titulo, link));
        std::cout << "Video agregado: " << stack.top() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Retrocediendo a la página anterior:" << std::endl;
    stack.pop();
    stack.print();
    std::cout << std::endl;

    std::cout << "Video actual en la parte superior de la pila:" << std::endl;
    stack.top().print();
    std::cout << std::endl;

    std::cout << "Número de videos en la pila: " << stack.size() << std::endl;
}