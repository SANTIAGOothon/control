/* 
 * File:   xc8_controltemp.c
 * Author: SANTIAGO
 *saniago_sob@hotmail.com
 * Created on 15 de julio de 2014, 09:50 PM
 */

#include <xc.h>
#include "fuses.h"
#include "types.h"
#include "system/system.h"
#include "hd44780/hd44780.h"
#include "printf/printf.h"
#include "pwm/pwm.h"
#include "adc/adc.h"
#include "gpios/gpios.h"
#include "delays/delays.h"

int main(void)
{

    _U16 adc,adc2,adc3;
     _U08 Duty = 0;
      _U16 setpot;
      _U16 tem;
       _U16 pot;


    ANCON0 = 0XFF;  /*Desactivamos las entradas analogicas*/
    ANCON1 = 0XFF;  /*Desactivamos las entradas analogicas*/

     Adc_Init(ADC_8BITS); /*se inciliza el adc con resolucion de 8bits*/

   System_PeripheralPinSelect(CompareOrPWMOutputChannel1A, 2);   /*PWM1_A en el pin RP2 (A5)*/
    Gpios_PinDirection(GPIOS_PORTA, 5, GPIOS_OUTPUT);  /*pin RA5 como salida para PWM_1A*/
    
     Gpios_PinDirection(GPIOS_PORTB,6,GPIOS_OUTPUT);/*control giro (B6) salida*/
      Gpios_PinDirection(GPIOS_PORTB,5,GPIOS_OUTPUT);/*control giro (B5) salida*/
 Gpios_PinDirection(GPIOS_PORTB,2,GPIOS_OUTPUT);/* (B2) salida*/
 
      Pwm_Init(PWM_PORT1, 30000); /*se�al a 20KHz*/

      HD44780_Init();                                     /*inicliza el LCD*/
      xdev_out(HD44780_WriteData); /*establece elcd como salida*/

    while (1)
    {
   adc= Adc_u16Read(3); /*Se lee la lectura del canal 3 en el adc  A3*/
   adc2= Adc_u16Read(2);//A2
   adc3= Adc_u16Read(7); //E2

     tem = (adc/2.2);  //  esta formula no es la de  el sesor de temperaura (lm35) esta fromula la use para prueva   aqui use un potenciometro  como sensor 
     setpot=(adc2/2.2);
     pot = (adc3/2.2);
    
                 
            HD44780_SetCursor(0,1);              
            xprintf("set%3d",setpot);    // poteciometro   usa como seleccion de temperatura deseada 
            Delays_ms(50);

            HD44780_SetCursor(1,1);              
            xprintf("tem%3d",tem); //  en esta parte se utilizara un potenciometro  en ves del sensor
            Delays_ms(50);

             HD44780_SetCursor(0,8);
              xprintf("vel%3d",pot); //  en esta parte se utilizara un potenciometro  en ves del sensor
               Delays_ms(50);                  
                    
                                 
            
               
            if(tem<setpot)
               {
                   Gpios_WritePin(GPIOS_PORTB, 2, 0);

                   Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, 120); 
               }   
               
            if(tem>setpot)
            {
               Gpios_WritePin(GPIOS_PORTB, 2, 1);  /*enciendo pin RA2*/

               Gpios_WritePin(GPIOS_PORTB,6,1); /*giro en un sentido*/
                  Gpios_WritePin(GPIOS_PORTB,5,0);
                  Pwm_DutyCycle(PWM_PORT1, PWM_CHANNEL_A, pot); /*Se�al al 50%*/
               }
                
           }
    }
