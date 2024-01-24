/*
* Description    - I2C LCD driver source code for PIC18F microcontroller based applications
* Author         - Aditya Vilas Vinaya Kuware
* Created on     - 20 June 2023
* Last edited on - 02 August 2023
* Bugs           - No known bugs
*/

#include "LCD.h"

void LCD_Initialize()
{
    __delay_ms(PCF8574_Startup);   //For the start-up time of PCF8574 IC
    //__delay_ms(LCD_Startup);     //Not required because the PCF8574 startup time takes care for this.
    LCDPutCmd(0x32);
    LCDPutCmd(FUNCTION_SET);
    LCDPutCmd(LCD_CURSOR_OFF);
    DisplayClr();
    LCDPutCmd(ENTRY_MODE);

}
void LCDWriteNibble(uint8_t ch,uint8_t rs)
{
    ch = (ch >> 4);
    ch = (ch << 2);

    I2C_out(rs);
    ch = ch + rs;
    I2C_out(ch);
    
    
    ch = ch + 2;
    I2C_out(ch);
    __delay_us(10);
    ch = ch - 2;
    I2C_out(ch);
    __delay_us(100);
    
}

void LCDPutChar(uint8_t ch)
{
    __delay_ms(LCD_delay);

    LCDWriteNibble(ch,data); //Send higher nibble first
    ch = (ch << 4);          //get the lower nibble
    LCDWriteNibble(ch,data); //Now send the low nibble
}

    
void LCDPutCmd(uint8_t ch)
{
    __delay_ms(LCD_delay);

    LCDWriteNibble(ch,instr);   //Send the higher nibble
    ch = (ch << 4);             //get the lower nibble
    __delay_ms(1);
    LCDWriteNibble(ch,instr);   //Now send the lower nibble
}

 
void LCDPutStr(const char *str)
{
    uint8_t i=0;
    
    // While string has not been fully traveresed
    while (str[i] && (i < 16))
    {
        LCDPutChar(str[i++]);
    } 
}

void LCDGoto(uint8_t pos,uint8_t ln)
{
    // if incorrect line or column
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1)))
    {
        // Just do nothing
        return;
    }

    // LCD_Goto command
    LCDPutCmd((ln == 1) ? (0xC0 | pos) : (0x80 | pos));

    // Wait for the LCD to finish
    __delay_ms(LCD_delay);
}

void Lcd_Out(unsigned char Row,unsigned char Column,const uint8_t *str)
{
    uint8_t Row_1,Column_1 = 0;
    Row_1 = Row - 1;
    Column_1 = Column - 1;
    LCDGoto(Column_1,Row_1);
    LCDPutStr(str);
    
}

void LCD_Putch(unsigned char Row,unsigned char Column, char ch)
{
    uint8_t Row_1,Column_1 = 0;
    Row_1 = Row - 1;
    Column_1 = Column - 1;
    LCDGoto(Column_1,Row_1);
    LCDPutStr(&ch);
}

void I2C_out(unsigned int amp)
{
   int ii,temp,msb;
   SCL_SetHigh();
   SDA_SetHigh();
   __delay_us(1);
   SDA_SetLow();
   __delay_us(1);
   SCL_SetLow();
   __delay_us(1);
   
   for(ii=0; ii<8; ii++)
   {
	  if(ii==1)
	  {
		  SDA_SetHigh();
	  }
	  else
	  {
		  SDA_SetLow();
	  }
	  __delay_us(1);
	  SCL_SetHigh();
	  __delay_us(1);
	  SCL_SetLow();
	  __delay_us(1);
   }
       //Acknowledge
   SDA_SetLow();
   __delay_us(1);
   SCL_SetHigh();
   __delay_us(1);
   SCL_SetLow();
   __delay_us(1);

   for(ii=7; ii>=0; ii--)
   {
      msb = amp;
      temp = (msb>>ii) & 0x01;
      if(temp == 1)
      {
          SDA_SetHigh();
      }
      else
      {
         SDA_SetLow();
      }
      __delay_us(50);
      SCL_SetHigh();
      __delay_us(1);
      SCL_SetLow();
      __delay_us(1);
   }
   __delay_us(1);
   SDA_SetLow();
   __delay_us(1);
   SCL_SetHigh();
   __delay_us(1);
   SCL_SetLow();
   __delay_us(1);


   SDA_SetLow();
   __delay_us(1);
   SCL_SetHigh();
   __delay_us(1);
   SCL_SetLow();
   __delay_us(1);
   SDA_SetLow();
   __delay_us(1);
   SCL_SetHigh();
   __delay_us(1);
   SDA_SetHigh();
   __delay_us(1);
}
