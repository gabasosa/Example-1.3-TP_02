#include "mbed.h"
#include "arm_book_lib.h"


/* 
El archivo donde se encuentran las funciones de C stm32f4xx_hal_gpio.h
Esta en la carpeta de target

Las funciones esenciales son:
HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

La declaracion de variables como GPIO_InitTypeDef y GPIO_TypeDef esta descripta en el archivo mencionado
*/
#define ALARM_LED_PIN GPIO_PIN_1
#define GAS_DETECTOR_PIN GPIO_PIN_2
#define OVERTEMP_DETECTOR_PIN GPIO_PIN_3
#define ALARM_OFF_BUTTON_PIN GPIO_PIN_1

#define ALARM_LED_PORT GPIOD
#define GAS_DETECTOR_PORT GPIOD
#define OVERTEMP_DETECTOR_PORT GPIOD
#define ALARM_OFF_BUTTON_PORT GPIOA


int main(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; // Inicializamos el gpio struct para cargar las estructuras

    // Configuración del pin del LED como salida
    GPIO_InitStruct.Pin = ALARM_LED_PIN; // Se configura el pin de salida del LED
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Se pone en modo de salida
    GPIO_InitStruct.Pull = GPIO_NOPULL; // Se pone en modo de no pull
    HAL_GPIO_Init(ALARM_LED_PORT, &GPIO_InitStruct);

    // Configuración del detector de gas como entrada
    GPIO_InitStruct.Pin = GAS_DETECTOR_PIN; // Se configura el pin de entrada del detector
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Se pone en modo input
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Se pone en modo de pull down
    HAL_GPIO_Init(GAS_DETECTOR_PORT, &GPIO_InitStruct);

    // Configuración del detector de sobretemperatura como entrada
    GPIO_InitStruct.Pin = OVERTEMP_DETECTOR_PIN; // Se configura el pin de entrada del detector
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Se pone en modo input
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Se pone en modo de pull down
    HAL_GPIO_Init(OVERTEMP_DETECTOR_PORT, &GPIO_InitStruct);


    // Configuracion del boton de apagado de la alarma
    GPIO_InitStruct.Pin = ALARM_OFF_BUTTON_PIN; // Se configura el pin de la alarma
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Se pone en modo de entrada
    HAL_GPIO_Init(ALARM_OFF_BUTTON_PORT, &GPIO_InitStruct);


    int alarmState = 0;

    while (true) {
        // Se leen los valores del gas detector y del overtemp detector
        if (HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN) || HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN)) {
            alarmState = 1;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);  // Encender el LED
        }

        // Se leen los valores del gas detector y del overtemp detector
        if (HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN)) {
            alarmState = 0;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_RESET);  // Apagar el LED
        }
        
    }
}