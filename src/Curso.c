#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaak.h"            /* <= ciaa kernel header */
/*Esto deberia estar en Curso.h pero ahora esta vacio*/

int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(Normal);
	/*Con Appmode = Normal*/
	
   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

void ErrorHook(void)
{
      ShutdownOS(0);
}


 int32_t leds;

TASK(Inicializacion)
{
   /* init CIAA kernel and devices */
   ciaak_start();

   /* open CIAA digital outputs */
   leds = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */
   SetRelAlarm(ActivarPeriodica, 350, 250);

   /* terminate task */
   TerminateTask();
}

TASK(Periodica)
{
   uint8_t salidas;

   
   /* blink output */
   ciaaPOSIX_read(leds, &salidas, 1);
   salidas ^= 0x20;
   ciaaPOSIX_write(leds, &salidas, 1);

   /* terminate task */
   TerminateTask();
}
