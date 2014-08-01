//* Author: SANTIAGO
 //* santiago_sob@hotmail.com
 //* Created on 20 de julio de 2014, 11:10 PM
 //  se controla el centido  y velicidad de los motores a pasos 

#include <xc.h>
#include "fuses.h"
#include "types.h"
#include "system/system.h"
#include "gpios/gpios.h"
#include "delays/delays.h"
#include "pwm/pwm.h"
#include "adc/adc.h"
#include "hd44780/hd44780.h"
#include "printf/printf.h"


int main(void)
{

    _U16 boton1,boton2;
   
    _U16  adc,pot;

    ANCON0 = 0XFF;  /*Desativamos las salidas analogicas*/
    ANCON1 = 0XFF;  /*Desativamos las salidas analogicas*/


    Adc_Init(ADC_8BITS); /*se inciliza el adc con resolucion de 8bits*/

   System_PeripheralPinSelect(CompareOrPWMOutputChannel1A, 2);   /*PWM1_A en el pin RP2 (A5)*/
    Gpios_PinDirection(GPIOS_PORTA, 5, GPIOS_OUTPUT);  /*pin RA5 como salida para PWM_1A*/

     Pwm_Init(PWM_PORT1, 30000); /*señal a 20KHz*/

    
    Gpios_PinDirection(GPIOS_PORTD, 0, GPIOS_INPUT);
     Gpios_PinDirection(GPIOS_PORTC, 1, GPIOS_INPUT);
      Gpios_PinDirection(GPIOS_PORTC, 2, GPIOS_INPUT);
       Gpios_PinDirection(GPIOS_PORTC, 0, GPIOS_INPUT);
      
Gpios_WriteTris(GPIOS_PORTB, 0x00);     /*puerto B como salida*/

    while (1)
      

    {
             
            adc= Adc_u16Read(7); /*Se lee la lectura del canal 7 en el adc  e2*/
              pot = (adc/2.2);
              
               if( Gpios_bReadPin(GPIOS_PORTC, 1)==1)  //  MATOR 1   DERECHA
            {
               Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b01111111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b10111111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11011111);
                Delays_ms(20); 
                Gpios_WritePort(GPIOS_PORTB, 0b11101111);
                

                  Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, pot); /*Señal al 50%*/
               }
               
              else if( Gpios_bReadPin(GPIOS_PORTC, 2)==1) //MOTOR 1  IZQ
            {

                Gpios_WritePort(GPIOS_PORTB, 0b11101111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11011111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b10111111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b01111111);
                Delays_ms(20);

                  Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, pot); /*Señal al 50%*/
               
              }
               else if (Gpios_bReadPin(GPIOS_PORTC, 0)==1) //motor 2  DERECHA
                {
                Gpios_WritePort(GPIOS_PORTB, 0b11110111);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11111011);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11111101);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11111110);
                Delays_ms(20);
                Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, pot); /*Señal al 50%*/
                }

               else if (Gpios_bReadPin(GPIOS_PORTD, 0)==1)// MATOR 2  IZQ
                {
                Gpios_WritePort(GPIOS_PORTB, 0b11111110);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11111101);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11111011);
                Delays_ms(20);
                Gpios_WritePort(GPIOS_PORTB, 0b11110111);
                Delays_ms(20);

                Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, pot); /*Señal al 50%*/
                }

               
                else
                   {
                   Gpios_WritePort(GPIOS_PORTB, 0b11111111);
                   }


               }
    }

