
#include <gas.h>
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B3
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
#fuses XT, NOWDT, NOLVP, NOPUT, NOPROTECT
#use delay(clock=4000000) 
#include <lcd.c>         
#define MQ3_ADC_CHANNEL 0

void main() 
{
   FLOAT adc_value = 0;
   FLOAT voltage = 0;
   FLOAT alcohol_mg_per_L = 0;
   set_tris_a (0xFF);
   setup_adc_ports (ALL_ANALOG);
   setup_adc (ADC_CLOCK_INTERNAL); /
   set_adc_channel (MQ3_ADC_CHANNEL);
   lcd_init ();
   lcd_putc ("DO AN CDT 1");
   delay_ms (1000);

   WHILE (TRUE)
   {
      delay_ms (200);
      adc_value = read_adc ();
      voltage = (adc_value * 5.0) / 1023.0;
      alcohol_mg_per_L = voltage * 1.0;
      lcd_gotoxy (1, 2) ;
      printf (lcd_putc, "Alcohol: % .2f mg / L", alcohol_mg_per_L);
   }
}

