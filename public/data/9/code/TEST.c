#include <REGX51.H>

//chan ket noi lcd
#define LCD_RS  P0_0
#define LCD_RW  P0_1
#define LCD_EN  P0_2
#define LCD_D4  P0_4
#define LCD_D5  P0_5
#define LCD_D6  P0_6
#define LCD_D7  P0_7

//chan ket noi ADC0804 
#define CS  P3_3
#define RD  P3_2
#define WR  P3_1
#define INTR P3_0
#define Data P2

// chan ra tin hieu canh bao
#define led P3_6     // canh bao muc 1
#define chuong P3_7  // canh bao nguy hiem

// --- Delay ---
void delay_us(unsigned int t){
    while(t--);
}

void delay_ms(unsigned int t){
    unsigned int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 125; j++);
}

void delay(long time){
    time = time * 25;
    while(time--);
}

// --- LCD ---
void LCD_Enable(void){
    LCD_EN = 1;
    delay_us(3);
    LCD_EN = 0;
    delay_us(50);
}

void LCD_Send4Bit(unsigned char Data){
    LCD_D4 = Data & 0x01;
    LCD_D5 = (Data >> 1) & 1;
    LCD_D6 = (Data >> 2) & 1;
    LCD_D7 = (Data >> 3) & 1;
}

void LCD_SendCommand(unsigned char command){
    LCD_Send4Bit(command >> 4);
    LCD_Enable();
    LCD_Send4Bit(command);
    LCD_Enable();
}

void LCD_Clear(){
    LCD_SendCommand(0x01);
    delay_ms(2);
}

void LCD_Init(){
    LCD_Send4Bit(0x00);
    delay_ms(20);
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_Send4Bit(0x03); LCD_Enable(); delay_ms(5);
    LCD_Send4Bit(0x03); LCD_Enable(); delay_us(100);
    LCD_Send4Bit(0x03); LCD_Enable();
    LCD_Send4Bit(0x02); LCD_Enable();

    LCD_SendCommand(0x28); // 2 dong, font 5x8
    LCD_SendCommand(0x0C); // hien thi, tat con tro
    LCD_SendCommand(0x06); // tang dia chi
    LCD_SendCommand(0x01); // xoa man hinh
    delay_ms(2);
}

void LCD_Gotoxy(unsigned char x, unsigned char y){
    unsigned char address;
    x -= 1; y -= 1;
    address = y ? (0xC0 + x) : (0x80 + x);
    LCD_SendCommand(address);
    delay_us(50);
}

void LCD_PutChar(unsigned char Data){
    LCD_RS = 1;
    LCD_SendCommand(Data);
    LCD_RS = 0;
}

void LCD_Puts(char *s){
    while (*s){
        LCD_PutChar(*s++);
    }
}

void LCD_PutNumber(int number){
    LCD_PutChar((number / 100) % 10 + '0');
    LCD_PutChar((number / 10) % 10 + '0');
    LCD_PutChar(number % 10 + '0');
}

// --- ADC0804 ---
unsigned char ADC_Read(){
    unsigned char ketqua;

    CS = 0;
    WR = 0; WR = 1;

    while(INTR); // doi chuyen doi xong

    RD = 0;
    ketqua = Data; // doc gia tri ADC
    RD = 1;

    return ketqua;
}

// --- MAIN ---
void main(){
    float kq;
    unsigned int giatri;

    // Khoi tao trang thai
    led = 0;
    chuong = 0;

    LCD_Init();
    LCD_Gotoxy(1,1); LCD_Puts("DO NONG DO GAS ");
    LCD_Gotoxy(1,2); LCD_Puts("VA CANH BAO    ");
    delay(2500);
    LCD_Clear();

    while(1){
        // Doc gia tri ADC
        kq = ADC_Read();
        giatri = (unsigned int)(kq / 0.511 + 0.5); // lam tron

        // DOng 1: canh bao
        LCD_Gotoxy(1,1);
        LCD_Puts("                "); // clear
        LCD_Gotoxy(1,1);

        if (giatri >= 50){
            LCD_Puts("KHI GAS MUC CAO");
            led = 1;
            chuong = 1;
        } else if (giatri >= 25){
            LCD_Puts("KHI GAS MUC THAP     ");
            led = 1;
            chuong = 0;
        } else {
            LCD_Puts("    AN TOAN           ");
            led = 0;
            chuong = 0;
        }

        // DOng 2: gia tri
        LCD_Gotoxy(1,2);
        LCD_Puts("GIA TRI:     ");
        LCD_Gotoxy(10,2);
        LCD_PutNumber(giatri);
        LCD_Gotoxy(13,2);
        LCD_Puts("%");

        delay_ms(500);
    }
}
