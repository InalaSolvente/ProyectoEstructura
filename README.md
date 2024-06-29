# Digital Horse Race Simulator

## Descripción del juego y aplicación
El `Digital Horse Race Simulator` es un simulador de carreras de caballos que consiste en 

## Ejemplo de uso de la aplicación
### Ejecución
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar `repl.it` para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
* Visita `repl.it`.
* Crea una nueva cuenta o inicia sesión si ya tienes una.
* Una vez en tu dashboard, selecciona `New Repl` y elige `Import from GitHub`.
* Pega la URL de este repositorio.
* repl.it clonará el repositorio y preparará un entorno de ejecución.
* Para ejecutar el main en `repl.it` debemos apretar el botón `run`

### Uso de la aplicación
Al realizar la ejecución indicada se abrirá el siguiente menú:
````
 ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ 
¿Ya tiene una cuenta? (s/n)
````
Si ya se tiene cuenta escribimos `s` para ingresar a la cuenta o, si no tenemos cuenta, escribimos `n` para registrarnos.

* Si se seleccionó `n` deberemos ingresar el nuevo nombre con una nueva contraseña (con letras y/o números) como se ve a continuación:
````
 ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ 
¿Ya tiene una cuenta? (s/n)
n
Ingrese un nombre de usuario
Juan
Ingrese una contraseña
qwerty123
````
Colocamos `enter` y nos habremos registrado e ingresado a la aplicación.

* En cambio si se selecciona `s`, se debe ingresar el nombre y contraseña de nuestra cuenta como a continuación:
````
 ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ 
¿Ya tiene una cuenta? (s/n)
s
Ingrese nombre de usuario
Juan
Ingrese contraseña
qwerty123
````
Colocamos `enter` y habremos ingresado a la aplicación.

Al ingresar se mostrará el siguiente menú:
````
 ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ 
Bienvenido Juan! Saldo actual: 0.00

Por favor ingrese el número del comando que desea ejecutar.
1: Agregar fondos a la cuenta.
2: Apostar por los caballos.
3: Ver carrera.
4: Cerrar sesión.
````
En el menú se solicita ingresar el número respectivo para realizar alguna de las siguientes acciones, acciones que al finalizar nos devolverán al menú actual:

* `1: Agregar fondos a la cuenta`: Sección en la cual el usuario puede añadir los fondos que le sean necesarios para jugar y apostar. A continuación un ejemplo:
````
Saldo actual es 0.00
¿Cuánto desea agregar?
10000
````
* `2: Apostar por los caballos`: Apartado que nos permite ver a todos los caballos que van a correr, con sus respectivas posibilidades de victoria(PdV), también permite ingresar a que caballo se desea apostar y cuanto se desea apostar por él. A continuación un ejemplo:
````
Saldo actual: $10000.00
Caballos que correrán en la próxima carrera:
Carril 1: Relincho Salvaje [PdV: 26%, $0.00 de dinero apostado]
Carril 2: Centella Azul [PdV: 16%, $0.00 de dinero apostado]
Carril 3: Aurora Boreal [PdV: 18%, $0.00 de dinero apostado]
Carril 4: Estrella Fugaz [PdV: 40%, $0.00 de dinero apostado]
¿En qué carril desea apostar? (1-4)
1
¿Cuánto desea apostar?
10000
````
* También se agrega una sub-acción que nos confirma el dinero apostado al caballo escogido y nos pregunta si deseamos apostar a otro caballo:
````
$10000.00 apostado al caballo Relincho Salvaje en el carril 1.
¿Desea apostar por otro caballo? S/N
n
````
* `3: Ver carrera`: Nos muestra los caballos que están corriendo, la cantidad de dinero que se apostó por ellos y su PdV, también nos muestra la carrera y el ganador de esta, si se apostó por el caballo ganador se entregara un premio al usuario pero en el caso de apostarle a algún caballo perdedor el usuario perderá lo apostado. Un ejemplo a continuación:
````
Relincho Salvaje: $10000.00 (26%) Centella Azul: $0.00 (16%) Aurora Boreal: $0.00 (18%) Estrella Fugaz: $0.00 (40%) 

                =============================================================================
Relincho Salvaje|                                                                    *    | |
Centella Azul   |                                               *                         | |
Aurora Boreal   |                                                           *             | |
Estrella Fugaz  |                                                                         |*|
                =============================================================================
¡El caballo Estrella Fugaz gana! 
Presione cualquier tecla para regresar al menú:
````
* `4: Cerrar sesión`: Guarda los datos de la cuenta y se termina el programa.

## Especificaciones de la aplicación
### Funciones main.c
* `main`: Ejecuta el menú de inicio (ingreso/registro), el menú principal y según la selección del usuario las funciones del programa.
* `login`: Función que recibe un nombre y contraseña del usuario, compara con los usuarios creados y, en caso de que la información sea correcta, lo ingresa al menú principal. En el caso que se ingresen datos erróneos se preguntará si desea ingresar el usuario nuevamente o generar uno nuevo.
* `registerUser`: Función que permite crear un nuevo usuario con su respectivo nombre, contraseña y fondos en el archivo users.txt.
* `addFunds`: Función que añade los fondos ingresados por el usuario a su cuenta.
* `saveUser`: Función que guarda en el archivo users.txt los fondos actualizados del usuario.
* `bet`: Función que muestra los caballos que van a correr con sus respectivos porcentajes de victoria y que nos permite apostar por alguno(s) de ellos.
* `watch`: Función que nos muestra la carrera y que si el caballo seleccionado por el usuario resultase ganador se le entregara su premio correspondiente.
### Funciones horses.h/horses.c
* `makeHorses`: Función principal para crear los caballos.
* `printHorses`: Función para imprimir la información de los caballos.
* `loadHorseNames`: Función para cargar nombres de caballos desde un archivo.
* `findUnusedName`: Función para encontrar un nombre de caballo no utilizado.

### Posibles errores en la aplicación
* Los principales errores que podrían ocurrir en la aplicación son `errores humanos`, ya que, si el usuario ingresa palabras/letras en las secciones donde se deben ingresar números la aplicación se salta la sección completa.