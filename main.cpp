#include "mbed.h"
#include "arm_book_lib.h"

#define GAS_DETECTOR_PIN D2
#define OVERTEMP_DETECTOR_PIN D3
#define ALARM_OFF_BUTTON_PIN BUTTON1
#define ALARM_LED_PIN LED1

#define GAS_DETECTOR_PORT D2
#define OVERTEMP_DETECTOR_PORT D3
#define ALARM_OFF_BUTTON_PORT BUTTON1
#define ALARM_LED_PORT GPIOA
int main()
{
    DigitalIn gasDetector(D2); 
    /** En la primera capa de la clase DigitalIn estan los distintos métodos de la clase
    Los métodos son los que aparecen aca: https://os.mbed.com/docs/mbed-os/v6.16/mbed-os-api-doxy/classmbed_1_1_digital_in.html#aaab5dab5b969a87f538242e524431637
    En el init, esta el gpio_init que tiene un pinmap.
    Dentro del pinmap, esta el mapeo al nombre
    */
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);
        }

        alarmLed = alarmState;
        

        if ( alarmOffButton ) {
            alarmState = OFF;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);
        }
    }
}