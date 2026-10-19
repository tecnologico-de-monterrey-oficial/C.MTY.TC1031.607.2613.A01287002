## Reflexión
### Explica qué aprendiste del uso de IA en esta actividad, qué parte hiciste tú, qué parte fue sugerida o completada por la IA y qué hubieras hecho diferente sin su ayuda.
Mas que nada la implementación de las estruturas de datos lineales y el iniciar la maquina de estados de la segunda evidencia, la IA me ayudo a perfecciónar la máquina de estados y en la corrección de algoritmos.

### Explica por qué cada estructura ocupa el lugar que ocupa en tu aplicación. En particular: tu lista doblemente ligada ya puede recorrerse hacia atrás con prev, ¿era necesaria la Pila para la opción 3? ¿Qué ventajas y desventajas tiene cada opción?
La pila no es necesaria y tampoco la mejor opción, quieres que de tus datos de fecha únicamente recoger las condiciones de rango. Para el ejemplo número dos quizas hubiera sido mejor opción el uso de la pila, pero para el caso 3, como no puedes acceder a los datos de fecha de la cola mas que guardando temporalmente los datos, diría que no es recomendable hacer este approach. La lista doblemente ligada soluciona ambos problemas a costa de ser un poco mas compleja de implementar.

### Explica por qué no se puede aplicar búsqueda binaria directamente sobre una lista ligada y qué costaría hacerlo posible.
Size nos permite saber el tamaño de la lista y con eso acceder a la mitad de dicha lista. No obstante, seguiriamos teniendo que recorrer la lista n/2 veces para poder acceder a la lista. Te evitas de comparaciones pero no del recorrido

### Interpreta tus mediciones: cómo se comportó tu algoritmo en cada archivo, qué relación tiene la profundidad de recursión con la pila de llamadas y, si usaste Quick Sort, cómo influyó tu pivote.
Mas que nada, con Tim sort evite de problemas de recursión. Aúnque el objetivo de la pila era entorpecernos para recorrer alreves la lista, la verdad por la poca cantidad de datos no se notó la diferencia. El pivote de Quick sort no influyó en nada, ya que el algoritmo no fue implementado.