Sistemas Operativos II - Laboratorio I IPC
###  Ingeniería en Compitación - FCEFyN - UNC
# Interprocess Communication

## Introducción
Los mecanismos de IPC permiten a los procesos intercambiar información. Hemos visto que se pueden clasificar en dos grandes grupos, los de transferencia de datos (pipe, FIFO, message queue, sockets, etc.) y los de memoria compartida (shared memory, memory mapping, etc.). Todo este conjunto de mecanismos son sumamente útiles en todo proyecto y es lo que motiva el presente trabajo.

## Objetivo
El objetivo del presente trabajo práctico es que el estudiante sea capaz de diseñar e implementar un software que haga uso de los mecanismos de IPC que provee el Sistema Operativo, implementando lo visto en el teórico, práctico y haciendo uso todos los conocimientos adquiridos en Ingeniería de Software y Sistemas Operativos I.

## Desarrollo
Se pide que diseñe, implemente y testee un conjunto de aplicaciones (desarrollado en lenguaje C) de una arquitectura cliente servidor con al menos 3 protocolos de la familia descriptas en  <sys/socket.h>.  

![Diagrama de Componentes](/img/block_diagram.jpg)
*Figura 1: Diagrama de Componentes del sistema*

### Servidor

- El servidor debe ser capaz de atender todos los tipos clientes. Cada cliente puede tener más de una instancia.
- El servidor debe mostrar la cantidad de datos de cada uno de sus protocolos y el total. Estos datos deben persistir en un archivos
- El servidor no puede tener direcciones, rutas, puerto, etc hardcodeados. Todo debe ser suministrado por parámetro al servidor o por variables de entorno.


## Criterios de Corrección
- Se debe compilar el código con los flags de compilación: 
     -Wall -Pedantic -Werror -Wextra -Wconversion -std=gnu11
- La correcta gestion de memoria.
- Dividir el código en módulos de manera juiciosa.
- Estilo de código.
- Manejo de errores
- El código no debe contener errores, ni warnings.
- El código no debe contener errores de cppcheck.

## Entrega

La entrega se hace a travéz del repositorio de GitHub y se deberá demostrar la realización del mismo mediante un correcto uso del [workflow de Git][workflow]. El repositorio deberá proveer los archivos fuente y cualquier otro archivo asociados a la compilación, archivos  de  proyecto  ”Makefile”  y  el  código correctamente documentado. No debe contener ningún archivo asociado a proyectos de un IDE y se debe asumir que el proyecto podrá ser compilado y corrido por una `tty` en una distribución de Linux con las herramientas típicas de desarrollo. También se deberá entregar un informe (que pude ser en MD en el repo) explicando paso a paso el desarrllo, inluyendo graficos del diseño solución propuesto, justificando en todo momento lo implementrado.

## Evaluación
El presente trabajo práctico es individual y deberá entregarse antes de las 16:59ART del día 25 de Abril de 2022 dejando asentado en el LEV con el archivo de informe. Será corregido y luego se coordinará una fecha para la defensa oral del mismo.

## Links / Referencias
- [Git Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows)

[workflow]: https://www.atlassian.com/git/tutorials/comparing-workflows "Git Workflow"

