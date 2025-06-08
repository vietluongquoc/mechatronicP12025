
_main:

;DoAnhTai_2025224224.c,18 :: 		void main() {
;DoAnhTai_2025224224.c,19 :: 		ANSEL = 0;
	CLRF       ANSEL+0
;DoAnhTai_2025224224.c,20 :: 		ANSELH = 0;
	CLRF       ANSELH+0
;DoAnhTai_2025224224.c,21 :: 		TRISB=0XFF;
	MOVLW      255
	MOVWF      TRISB+0
;DoAnhTai_2025224224.c,22 :: 		TRISD=0X00;
	CLRF       TRISD+0
;DoAnhTai_2025224224.c,23 :: 		TRISE=0X00;
	CLRF       TRISE+0
;DoAnhTai_2025224224.c,24 :: 		PORTD=0;
	CLRF       PORTD+0
;DoAnhTai_2025224224.c,25 :: 		PORTB=0;
	CLRF       PORTB+0
;DoAnhTai_2025224224.c,26 :: 		PORTE=0;
	CLRF       PORTE+0
;DoAnhTai_2025224224.c,27 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;DoAnhTai_2025224224.c,28 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,29 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,30 :: 		text = "DoAnhTai";
	MOVLW      ?lstr1_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,31 :: 		Lcd_Out(1,1,text);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,32 :: 		text = "Level warter";
	MOVLW      ?lstr2_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,33 :: 		Lcd_Out(2,1,text);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,34 :: 		Delay_ms(2000);
	MOVLW      41
	MOVWF      R11+0
	MOVLW      150
	MOVWF      R12+0
	MOVLW      127
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
;DoAnhTai_2025224224.c,35 :: 		for(;;){
L_main1:
;DoAnhTai_2025224224.c,36 :: 		if(portb.f2==1){
	BTFSS      PORTB+0, 2
	GOTO       L_main4
;DoAnhTai_2025224224.c,37 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,38 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,39 :: 		text = "DoAnhTai";
	MOVLW      ?lstr3_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,40 :: 		Lcd_Out(1,1,text);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,41 :: 		text = "Empty";
	MOVLW      ?lstr4_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,42 :: 		Lcd_Out(2,1,text);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,43 :: 		porte.f1=1;
	BSF        PORTE+0, 1
;DoAnhTai_2025224224.c,44 :: 		porte.f2=1;
	BSF        PORTE+0, 2
;DoAnhTai_2025224224.c,45 :: 		porte.f0=0;}
	BCF        PORTE+0, 0
	GOTO       L_main5
L_main4:
;DoAnhTai_2025224224.c,47 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,48 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DoAnhTai_2025224224.c,49 :: 		text = "DoANhTai";
	MOVLW      ?lstr5_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,50 :: 		Lcd_Out(1,1,text);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,51 :: 		text = "Full";
	MOVLW      ?lstr6_DoAnhTai_2025224224+0
	MOVWF      _text+0
;DoAnhTai_2025224224.c,52 :: 		Lcd_Out(2,1,text);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DoAnhTai_2025224224.c,53 :: 		porte.f1=0;
	BCF        PORTE+0, 1
;DoAnhTai_2025224224.c,54 :: 		porte.f2=0;
	BCF        PORTE+0, 2
;DoAnhTai_2025224224.c,55 :: 		porte.f0=1;}
	BSF        PORTE+0, 0
L_main5:
;DoAnhTai_2025224224.c,60 :: 		}
	GOTO       L_main1
;DoAnhTai_2025224224.c,61 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
