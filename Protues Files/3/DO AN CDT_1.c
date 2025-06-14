#include <16f877a.h>
#fuses      hs
#use delay(clock=20M)

#define LCD_ENABLE_PIN PIN_B2
#define LCD_RS_PIN PIN_B0
#define LCD_RW_PIN PIN_B1

#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B4
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B6

#include <lcd.c>     

unsigned int8     nd,nd1,da,da1;


#define     ld    pin_c2
#define     lx    pin_c1
#define     loa   pin_d2

#define     up    pin_e0
#define     dw    pin_e1


unsigned int32    gh;

#BIT  DHT_DATA_OUT =  0x07.0
#BIT  DHT_DATA_IN  =  0x07.0
#BIT  DHT_DDR_DATA =  0x87.0     // set tris cua port A

#define DHT_ER    0
#define DHT_OK    1

#define DDROUT    0
#define DDRIN     1

unsigned int8 DHT_GetTemHumi(unsigned int8 &tem1,&tem2,unsigned int8 &humi1,&humi2)
{
   unsigned int8 buffer[5]={0,0,0,0,0};
   unsigned int8 ii,i,checksum;
   
   DHT_DDR_DATA=DDROUT;   // set la cong ra, huong vao hay ra
   DHT_DATA_OUT=1;
   delay_us(60);
   DHT_DATA_OUT=0;
   delay_ms(25); // it nhat 18ms
   DHT_DATA_OUT=1;    
   DHT_DDR_DATA=DDRIN;//set la cong vao
   delay_us(60);
   if(DHT_DATA_IN)return DHT_ER ;
   else while(!(DHT_DATA_IN));   //Doi DaTa len 1
   delay_us(60);//cho 60us
   if(!DHT_DATA_IN)return DHT_ER;
   else while((DHT_DATA_IN));    //Doi Data ve 0
   //Bat dau doc du lieu
   for(i=0;i<5;i++)
   {
      for(ii=0;ii<8;ii++)
      {   
         while((!DHT_DATA_IN));//Doi Data len 1
         delay_us(50);
         if(DHT_DATA_IN)
         {
            buffer[i]|=(1<<(7-ii));
            while((DHT_DATA_IN));//Doi Data xuong 0
         }
      }
   }
   checksum=buffer[0]+buffer[1]+buffer[2]+buffer[3];
   if((checksum)!=buffer[4])return DHT_ER;
   tem1  =   buffer[2];//gia tri phan nguyen
   tem2  =   buffer[3];//gia tri phan thap phan
   humi1 =   buffer[0];//gia tri phan nguyen
   humi2 =   buffer[1];//gia tri phan thap phan
   return DHT_OK;
}

void phim_up()
{
   if(input(up)==0)
   {
      delay_ms(20);
      if (input(up)==0)
      {
         gh++;
         if(gh>50)          gh=50;
         delay_ms(200);
     }
   }
}
 

void phim_dw()
{
   if(input(dw)==0)
   {
      delay_ms(20);
      if (input(dw)==0)
      {
         gh--;
         if(gh<5)          gh=5;
         delay_ms(200);
     }
   }
}

void doc_dht()       // ham hien thi trong 1 giay lam bao nhieu lan
{
   if(DHT_GetTemHumi(nd,nd1,da,da1))            // dht11
   {
      lcd_gotoxy(1,1);
      lcd_putc("ND:");
      lcd_putc(nd/10+0x30);
      lcd_putc(nd%10+0x30);
      lcd_putc(0xdf);
      lcd_putc("C ");
      
      lcd_gotoxy(11,1);
      lcd_putc("DA:");
      lcd_putc(da/10+0x30);
      lcd_putc(da%10+0x30);
      lcd_putc("%");
   }       
}

void main()
{
   set_tris_e(0xff);
   set_tris_a(0xff);
   
   lcd_init();
   gh=35;
   while(true)
   {
      doc_dht();
      phim_up();
      phim_dw();
      lcd_gotoxy(1,2);
      lcd_putc("GIOI HAN:");
      lcd_putc(gh/10+0x30);
      lcd_putc(gh%10+0x30);
      lcd_putc(0xdf);
      lcd_putc("C ");
      
      if(nd<gh)
      {
         output_high(lx);
         output_low(ld);
         output_low(loa);
      }
      else
      {
         output_high(ld);
         output_high(loa);
         output_low(lx);
      }
      delay_ms(100);
   }
}


