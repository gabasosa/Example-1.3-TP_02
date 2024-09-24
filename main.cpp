/*
* TP2 - Ejercicio 9
* Fecha: 19/09/24
* Integrantes: Romero Alexis, Sosa Gabriel
*
* Enunciado: utilizar el cógido del ejemplo 1.3
*
* a) Modifique el código para no utilizar C++ (Clases DigitalIn y DigitalOut) y manipular gasDetector,
* overTempDetector y alarmLed con funcionalidades de C (revise el pinout de la placa => Zio and
* Arduino-compatible headers).
*
* b) ¿Cuál es la ventaja/desventaja de la modificación pedida?
* Una ventaja es que se trabaja a más bajo nivel, dando más detalle de lo que estamos haciendo dentro del microcontrolador.
* Y Las desventajas son código un poco mas complejo de interpretar, una mayor cantidad de instrucciones para hacer cada cosa.
* Al trabajar con objetos, se puede agrupar mejor las propiedades y metodos asociados con una clase, que resulta mas simple
* que utilizar estructuras en C.
*
* c) Inserte en el cuerpo del if y en el cuerpo del else, del archivo  main.cpp (en la función main() ),
* líneas de código con: printf("...."); de modo tal que reflejen el estado de gasDetector,
* overTempDetector y alarmLed
*/


// Bibliotecas
#include "mbed.h"
#include "arm_book_lib.h"
#include "hal/gpio_api.h"

// Definición de constantes
#define PROG_LANG_C 0 // Se utiliza C para la declaración de las variables
#define PROG_LANG_CPP 1 // Se utiliza C++ para la declaración de variables
#define PROG_LANG_USED PROG_LANG_CPP // Se define qué lenguaje de programación a utilizar

// Bloque de código en lenguaje C
#if (PROG_LANG_USED == PROG_LANG_C)
    
    // Variables globales
    gpio_t gasDetector;
    gpio_t overTempDetector;
    gpio_t alarmOffButton;
    gpio_t alarmLed;

    // Inicialización de variables
    void initializeGPIO()
    {
        gpio_init_in_ex( &gasDetector, D2, PullDown );
        gpio_init_in_ex( &overTempDetector, D3, PullDown );
        gpio_init_in( &alarmOffButton, BUTTON1 );
        gpio_init_out( &alarmLed, LED1 );
    }
    
    // Lectura de detector de gas
    int gasDetectorState()
    {
        return gpio_read(&gasDetector);
    }

    // Lectura de estado de temperatura por encima de la estipulada
    int overTempDetectorState()
    {
        return gpio_read(&overTempDetector);
    }

    // Lectura de botón de apagado de alarma
    int alarmOffButtonState()
    {
        return gpio_read(&alarmOffButton);
    }

    // Carga el valor booleano recibido por parámetro a la variable alarmState
    void changeAlarmState(bool alarmState)
    {
        gpio_write(&alarmLed,alarmState);
    }

#endif

// Bloque de código en lenguaje C++
#if (PROG_LANG_USED == PROG_LANG_CPP)

    // Objetos globales
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);

    DigitalOut alarmLed(LED1);

    // Inicialización de objetos
    void initializeGPIO ()
    {
        gasDetector.mode( PullDown );
        overTempDetector.mode( PullDown );
        alarmLed = OFF;
    }

    // Lectura de detector de gas
    int gasDetectorState()
    {
        return gasDetector.read();
    }
    
    // Lectura de estado de temperatura por encima de la estipulada
    int overTempDetectorState()
    {
        return overTempDetector.read();
    }

    // Lectura de botón de apagado de alarma
    int alarmOffButtonState()
    {
        return alarmOffButton.read();
    }

    // Carga el valor booleano recibido por parámetro a la variable alarmState
    void changeAlarmState(bool alarmState)
    {
        alarmLed = alarmState;
    }

#endif


int main()
{
    initializeGPIO();

    bool alarmState = OFF;

    while (true) {

        if ( gasDetectorState() || overTempDetectorState() ) {
            printf( "El sensor de gas está %s\n", gasDetectorState() ? "ACTIVADO" : "DESACTIVADO" );
            printf( "El sensor de temperatura está %s\n", overTempDetectorState() ? "ACTIVADO" : "DESACTIVADO" );
            alarmState = ON;
            printf( "La alarma está activada" );
        }

        changeAlarmState(alarmState);

        if ( alarmOffButtonState() ) {
            alarmState = OFF;
            printf("La alarma está desactivada");
        }
    }
}
