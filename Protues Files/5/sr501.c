#include <16F887.h>
#fuses XT, NOWDT
#use delay(clock=12000000)

#define cambien     PIN_A1
#define nutmo       PIN_A2
#define nutchedo    PIN_A3
#define nutdong     PIN_A4

#define ledxanh     PIN_D2
#define leddo       PIN_D3

#define IN1         PIN_C0
#define IN2         PIN_C1

#define ctmo        PIN_B1
#define ctdong      PIN_B0

int chedotay = 0;
int chedobantudong = 0;
int trangthaitruoc = 1;
int modangchay = 0;
int dongdangchay = 0;

void quaythuan() {
   output_high(IN1);
   output_low(IN2);
}

void quaynguoc() {
   output_low(IN1);
   output_high(IN2);
}

void dung() {
   output_low(IN1);
   output_low(IN2);
}

void chuyenchedo() {
   delay_ms(20);
   if(input(nutchedo) == 0 && trangthaitruoc == 1) {
      if(chedotay) {
         chedotay = 0;
         chedobantudong = 1;
      } else if(chedobantudong) {
         chedobantudong = 0;
      } else {
         chedotay = 1;
      }
      modangchay = 0;
      dongdangchay = 0;
      dung();
      output_low(ledxanh);
      output_low(leddo);
   }
   trangthaitruoc = input(nutchedo);
}

void main() {
   set_tris_a(0xFF); 
   set_tris_b(0xFF); 
   set_tris_c(0x00); 
   set_tris_d(0x00); 

   output_low(ledxanh);
   output_low(leddo);
   dung();

   while(TRUE) {
      chuyenchedo();
      if(chedotay) {
         if(input(nutmo) == 0) {
            if(!input(ctmo)) {
               dung();
               output_low(leddo);
            } else {
               quaythuan();
               output_low(ledxanh);
               output_high(leddo);
            }
         } else if(input(nutdong) == 0) {
            if(!input(ctdong)) {
               dung();
               output_low(leddo);
            } else {
               quaynguoc();
               output_low(ledxanh);
               output_high(leddo);
            }
         } else {
            dung();
            output_low(ledxanh);
            output_low(leddo);
         }
      }

      else if(chedobantudong) {
         if(input(nutmo) == 0 && modangchay == 0 && input(ctmo)) {
            modangchay = 1;
            quaythuan();
            output_high(leddo);
         }

         if(input(nutdong) == 0 && dongdangchay == 0 && input(ctdong)) {
            dongdangchay = 1;
            quaynguoc();
            output_high(leddo);
         }

         if(modangchay && !input(ctmo)) {
            modangchay = 0;
            dung();
            output_low(leddo);
         }

         if(dongdangchay && !input(ctdong)) {
            dongdangchay = 0;
            dung();
            output_low(leddo);
         }

         if(!modangchay && !dongdangchay) {
            output_low(ledxanh);
            output_low(leddo);
         }
      }

      else {
         if(input(cambien)) {
            output_high(ledxanh);
            delay_ms(200);
            output_low(ledxanh);
            output_high(leddo);

            if(input(ctmo)) {
               quaythuan();
               while(input(ctmo)) {
                  chuyenchedo();
                  if(chedotay || chedobantudong) break;
               }
               dung();
               output_low(leddo);
               if(chedotay || chedobantudong) continue;
            }

            delay_ms(2000);
            if(chedotay || chedobantudong) continue;

dongcua:
            if(input(ctdong)) {
               output_high(leddo);
               quaynguoc();
               while(input(ctdong)) {
                  chuyenchedo();
                  if(chedotay || chedobantudong) break;

                  if(input(cambien)) {
                     if(input(ctmo)) {
                        output_high(ledxanh);
                        delay_ms(200);
                        output_low(ledxanh);
                        quaythuan();
                        while(input(ctmo)) {
                           chuyenchedo();
                           if(chedotay || chedobantudong) break;
                        }
                        dung();
                        output_low(leddo);
                        output_low(ledxanh);
                     }
                     delay_ms(2000);
                     if(chedotay || chedobantudong) continue;
                     goto dongcua;
                  }
               }
               dung();
               output_low(leddo);
            }

            output_low(ledxanh);
         }
      }
   }
}

