#line 1 "C:/Users/dotai/Downloads/DoAnhTai-2025224224/DoAnhTai_2025224224.c"

sbit LCD_RS at RD4_bit;
sbit LCD_EN at RD5_bit;
sbit LCD_D4 at RD0_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D7 at RD3_bit;
sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;

char *text;


void main() {
 ANSEL = 0;
 ANSELH = 0;
 TRISB=0XFF;
 TRISD=0X00;
 TRISE=0X00;
 PORTD=0;
 PORTB=0;
 PORTE=0;
 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 text = "DoAnhTai";
 Lcd_Out(1,1,text);
 text = "Level warter";
 Lcd_Out(2,1,text);
 Delay_ms(2000);
 for(;;){
 if(portb.f2==1){
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 text = "DoAnhTai";
 Lcd_Out(1,1,text);
 text = "Empty";
 Lcd_Out(2,1,text);
 porte.f1=1;
 porte.f2=1;
 porte.f0=0;}
 else{
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 text = "DoANhTai";
 Lcd_Out(1,1,text);
 text = "Full";
 Lcd_Out(2,1,text);
 porte.f1=0;
 porte.f2=0;
 porte.f0=1;}




 }
}
