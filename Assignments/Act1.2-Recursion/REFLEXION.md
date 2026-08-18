# Reflexión
## ¿En qué casos notaste que la versión recursiva fue más lenta o usó más memoria que la iterativa? ¿A qué se debió?
No hubo tanto cambio en la velocidad. Lo que si fue muy intenso fue en el uso de la memoria; utilizando en todo momento más que simplemente iterar. Esto se debe a que se colocó la función y la variable en el stack, y no fue hasta que se termino de evaluar, que esta memoria se libero.

## Para la suma 1..n, `sumFormula` resuelve en un solo paso lo que a sumIterative y sumRecursive les toma n pasos. ¿Qué te dice esto sobre buscar una fórmula antes de escribir código?
Hay maneras de optimizar los algoritmos, en algunos sistemas, nos permite resolver problemas de manera más efectiva. Utilizar estos métodos nos permite ahorrar tiempo y memoria; a cambio de ser mas complejos en entenderlos.

## Si `bacteriasRecursive` tuviera que calcular n = 100,000 días, ¿qué problema esperarías encontrar y cómo lo resolverías?
El problema principal sería tener un stack overflow. Como estamos colocando todo dentro del stack, con un número tan grande de días, simplemente nos acabaríamos la memoria. Si estuviera obligado a utilizar recursión, utilizaría recursión de cola. De esta forma, no malgastaría la memoria y evitaría el stack overflow.