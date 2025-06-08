#include <main.h>
#FUSES      HS            // SU DUNG THANH ANH NGOAI 20m       // XT
#USE        DELAY(CLOCK=20M)      // THU VIEN DELAY   

#define LCD_ENABLE_PIN PIN_b2    // dinh nghia theo lcd (phan cung
#define LCD_RS_PIN PIN_b4
#define LCD_RW_PIN PIN_b3

#define LCD_DATA4 PIN_D7
#define LCD_DATA5 PIN_D6
#define LCD_DATA6 PIN_D5
#define LCD_DATA7 PIN_D4

#include <lcd.c>

#define     loa      pin_c0     //          dinh nghia chan tao xung      
#define     led      pin_e1     //          chan tin hieu


#define     tr      pin_d3     //          dinh nghia chan tao xung      
#define     ech     pin_d2     //          chan tin hieu

#define     in1     pin_c2     //          dinh nghia chan tao xung      
#define     in2     pin_c3     //          chan tin hieu
#define     in3     pin_d1     //          dinh nghia chan tao xung      
#define     in4     pin_d0     //          chan tin hieu

unsigned int32    kcs,kc,duty,giay,dem;
int1           tt;

#int_timer0
void ngat_timer0()
{
   set_timer0(6);
   dem++;
   if(dem>5000)
   {
      dem=0;
      giay--;
      if(giay<1)           
      {
         tt=0;
         giay=1;
      }
   }
}

void doc_kc()
{
   delay_ms(50);
   output_low(tr);
   delay_ms(20);
   output_high(tr);
   delay_ms(20);
   output_low(tr);
   
   set_timer1(0);
   while((input(ech))==0);        // cho chan echo = 1
   setup_timer_1(t1_internal|t1_div_by_4);         // bat dau dem tg
   while(input(ech));           // cho echo =0
   kcs = get_timer1();   // so luong xung tra ve tu khi echo = 1 den khi echo = 0      
   setup_timer_1(t1_disabled);
   
   kcs=kcs*0.8;
   kcs = (kcs/58);         // datasheet
   kc=kcs;
}

void hienthi()
{
   lcd_gotoxy(1,1);
   printf(lcd_putc,"K/CACH:%ldcm       ",kc);
   
}

void chay_tu_dong()
{
   if(kc<20)
   {
      duty=0;
      set_pwm2_duty(duty);
      output_low(in1);
      output_low(in2);
      output_low(in3);
      output_low(in4);
      output_high(loa);       delay_ms(200);
      output_low(loa);        delay_ms(200);

   }
   else
   {
      duty=800;
      set_pwm2_duty(duty);
      output_high(in1);
      output_low(in2);
      output_high(in3);
      output_low(in4);
   }
}

void main()
{  
    SET_TRIS_D(0x04);      // khoi tao cac port ra nen cho bang 0
    set_tris_c(0x80);   
    SET_TRIS_B(0x00);
    SET_TRIS_A(0x03);     // vi chan AN0 vao nen cho len 1 con lai ve 0
    
    lcd_init();
    SETUP_TIMER_1(T1_DISABLED);       //tat timer1
    ENABLE_INTERRUPTS(GLOBAL);        // cho phép ngat
    ENABLE_INTERRUPTS(INT_TIMER0);           // cho phep ngat timer 1
    
    setup_timer_0(t0_internal|t0_div_4);    
    set_timer0(6);
    
    SETUP_TIMER_2(T2_DIV_BY_16,249,1);       // 
    duty=500;     
    SETUP_CCP2(CCP_PWM);    
    SET_PWM2_DUTY(duty);
    
    output_low(in1);
    output_low(in2);
    output_low(in3);
    output_low(in4);

    hienthi();
    dem=0;
    giay=16;
    tt=1;
    delay_ms(1000);
    WHILE(TRUE)
    {
      doc_kc();
      hienthi();
      if(tt==1)
      {
         lcd_gotoxy(1,2);
         printf(lcd_putc,"THOI GIAN:%lds       ",giay);
         chay_tu_dong();
      }
      else
      {
         lcd_gotoxy(1,2);
         printf(lcd_putc,"    DUNG XE     ");
         output_low(in1);
         output_low(in2);
         output_low(in3);
         output_low(in4);
      }
      delay_ms(50);
    }
}


