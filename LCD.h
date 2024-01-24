/*
* Description    - I2C LCD driver header file.
* Author         - Aditya Vilas Vinaya Kuware
* Created on     - 20 June 2023
* Last edited on - 02 August 2023
* Bugs           - No known bugs
*/

#ifndef _LCD_XC_H
#define	_LCD_XC_H

//Set up the timing for the LCD delays
#define LCD_delay           2     // ~5mS
#define LCD_Startup         15    // ~15mS
#define PCF8574_Startup     50    // ~50mS

//Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0xC0

//Display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x28    // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06    // increment mode
#define DISPLAY_SETUP       0x0C    // display on, cursor off, blink offd

#define LCDLine1()          LCDPutCmd(LCD_HOME)          		// legacy support
#define LCDLine2()          LCDPutCmd(LCD_CURSOR_LINE2)  		// legacy support
#define shift_cursor()      LCDPutCmd(LCD_CURSOR_FWD)    		// legacy support
#define cursor_on()         LCDPutCmd(LCD_CURSOR_ON)     		// legacy support
#define DisplayClr()        LCDPutCmd(LCD_CLEAR)         		// Legacy support
#define SCL_SetHigh()       do { LATBbits.LATB1 = 1; } while(0)
#define SCL_SetLow()        do { LATBbits.LATB1 = 0; } while(0)
#define SDA_SetHigh()       do { LATBbits.LATB2 = 1; } while(0)
#define SDA_SetLow()        do { LATBbits.LATB2 = 0; } while(0)
	
//----------------------------------------------------------------------
//Definitions specific to the PICDEM 2 Plus
//These apply to the Black (2011) version.
//----------------------------------------------------------------------

//Single bit for selecting command register or data register
#define instr        0
#define data         1
#define NB_LINES     2                                    // Number of display lines
#define NB_COL       16                                  // Number of characters per line

//These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT     LATA
#define LCD_EN       LATAbits.LATA5                      // LCD enable
#define LCD_RS       LATAbits.LATA4                      // LCD register select line

// Function prototypes
/**
  @Summary
    initialize the LCD module

  @Description
    This routine initializes the LCD driver.
    This routine must be called before any other LCD routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void LCD_Initialize(void);
 
 /**
  @Summary
    Writes character to LCD at current cursor position

  @Description
    This function displays the specified ASCII character at current position on the LCD

  @Preconditions
    None

  @Param
    ASCII character to be displayed

  @Returns
    None
*/
void LCDPutChar(uint8_t ch);

/**
  @Summary
    send an ASCII command to the LCD in instruction mode

  @Description
    This routine writes character to LCD command register

  @Preconditions
    None

  @Param
    ASCII command 

  @Returns
    None
*/
void LCDPutCmd(uint8_t ch);

/**
  @Summary
    display a string

  @Description
    This routine writes string to LCD at current cursor position

  @Preconditions
    None

  @Param
    Pointer to string

  @Returns
    None
*/
void LCDPutStr(const char *);                         

/**
  @Summary
    Fuction to write a nibble

  @Description
    This function writes the specified nibble to the LCD.

  @Preconditions
    None

  @Param
    data byte to be written to display

  @Returns
    None
*/
void LCDWriteNibble(uint8_t ch,uint8_t rs);

/**
  @Summary
    Initialization routine that takes inputs from the EUSART GUI.

  @Description
    This function positions the cursor at the specified Line and column.

  @Preconditions
    None

  @Param
    Column and line at which the cursor should be positioned at

  @Returns
    None

  @Comment
      0 <= pos <= 15
      0 <= ln <= 1
*/
void LCDGoto(uint8_t pos, uint8_t ln);
void Lcd_Out(unsigned char Row,unsigned char Column,const char *);
void LCD_Putch(unsigned char Row,unsigned char Column,char );
void I2C_out(unsigned int);

#endif	/* _LCD_XC_H */
