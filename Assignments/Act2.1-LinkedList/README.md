# ¿Qué prompts utilzaste durante esta actividad?
> _Implementa la carga de operadores para la clase LinkedList para los operadores `[]` y `=`._
> **Autocompletado de copilot para main.cpp**

# Contesta esta pregunta como reflexión:
## ¿Qué parte del código te propuso la IA que aceptaste tal cual y por qué era correcta?
La parte de sobrecarga de operadores con structs. Sobre todo la de `T& operator[]`, no se me había ocurrido que tenias que referenciar los elementos de la lista para poder acceder a ellos mediante el operador de índice.

## ¿Qué parte modificaste y cómo verificaste que tu cambio era mejor?
Principalmente por medio de otras actividades, cambie el sistema de nodos y la linked list en sí para que fuera mas segura. 

## ¿Dónde se equivocó la IA (si ocurrió) y cómo lo detectaste?
En la sobrecarga de operadores, la IA se confundió porque no estaba referenciando correctamente los nodos y estaba usando una keyword que nunca había visto `noexcept`. Lo detecté porque lo busque de manera independiente y me di cuenta que para la sobrecarga de este operador tienes que referenciar linked list y tienes que utilizar dicha keyword para evitar que en una operación peculiar se rompa el programa.

## ¿Qué harías diferente si no tuvieras Copilot/ChatGPT?
No haría la sobrecarga de operadores, no porque no fuera útil, sino porque sería extremadamente riesgoso realizarlo sin ayuda de algo o alguien que me dijera que estaba haciendo mal. Anexaría todo adentro de métodos y dejaría la sobrecarga de operadores como algo "para despues" o bien, para cuando sepa utilizarlo de manera efectiva y segura.