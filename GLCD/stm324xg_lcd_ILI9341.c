/******************************************************************************
  * @file    stm324xg_lcd_ILI9341.c
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */


//=========================================================================== External interrupt/event Configuration
#define __Fonts_select         0x00000012			//0
#define __default_Font         3			//1
#define __LCD_DIRECT	         1      //2 ==> 1: LANDSCAPEÆÁ  2: PORTRAIT

//=================================================
#define PNr_reset 2		// 0
#define PIN_rs	5     // 1
#define PNr_backlight 1		// 2
#define PIN_bl	0         // 3
//=============================================

//=================================================
#define PNr_FSMC_set1 3									// 0
#define PinBit_FSMC_set1 0xC733     		// 1
#define PNr_FSMC_set2 4									// 2
#define PinBit_FSMC_set2	0xFF80        // 3
#define PNr_FSMC_set3 6									// 4
#define PinBit_FSMC_set3	0x1001        // 5


/* Includes ------------------------------------------------------------------*/
#include "stm324xg_lcd_sklin.h"
#include "stm32f4xx_fsmc.h"

#define _LCD_bit(x) (0x01ul<<x)

/** 
  * @brief LCD default font 
  */ 
	#include ".\Fonts\fonts.h"
#if (__default_Font == 0)
	#define LCD_DEFAULT_FONT         Font8
#endif
#if (__default_Font == 1)
	#define LCD_DEFAULT_FONT         Font12
#endif
#if (__default_Font == 2)
	#define LCD_DEFAULT_FONT         Font16
#endif
#if (__default_Font == 3)
	#define LCD_DEFAULT_FONT         Font20
#endif
#if (__default_Font == 4)
	#define LCD_DEFAULT_FONT         Font24
#endif
	
#define _fontSel   (0x01<<(__default_Font) | __Fonts_select) 
#if (_fontSel & _LCD_bit(0))
	#include ".\Fonts\font8.c"
#endif
#if (_fontSel & _LCD_bit(1))
	#include ".\Fonts\font12.c"
#endif
#if (_fontSel & _LCD_bit(2))
	#include ".\Fonts\font16.c"
#endif
#if (_fontSel & _LCD_bit(3))
	#include ".\Fonts\font20.c"
#endif
#if (_fontSel & _LCD_bit(4))
	#include ".\Fonts\font24.c"
#endif


#define ABS(X)  ((X) > 0 ? (X) : -(X))
#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))

/* Global variables to set the written text color */
typedef struct 
{ 
  uint32_t TextColor;
  uint32_t BackColor;
  sFONT    *pFont; 
}LCD_DrawPropTypeDef;

LCD_DrawPropTypeDef DrawProp={ \
			LCD_COLOR_WHITE, LCD_COLOR_BLACK, &LCD_DEFAULT_FONT};

//*** Variables concerning FONT ************
#define	pLCD_Currentfonts DrawProp.pFont
static uint16_t wf, hf;	// font_width, font_height
static uint16_t bytes_f, bytes_wf;	// number of bytes per font, that per width line in a font

static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed);

//########################################################
//########################################################
//  DRIVER 													 
//########################################################
//########################################################
#if __LCD_DIRECT==1
  #define  LANDSCAPE			1
	#define  LCD_ROW_NUM    240                //pages in ILI9341
	#define  LCD_COL_NUM    320                //columns in ILI9341
#else
  #define  LANDSCAPE			0
	#define  LCD_ROW_NUM    320                //pages
	#define  LCD_COL_NUM    240                //columns
#endif
	#define  LCD_PIXEL_WIDTH   LCD_COL_NUM  
	#define  LCD_PIXEL_HEIGHT  LCD_ROW_NUM   

uint16_t LCD_Pixel_Width(void){ return LCD_PIXEL_WIDTH;}
uint16_t LCD_Pixel_Heigth(void){ return LCD_PIXEL_HEIGHT;}

typedef struct
{
  volatile uint16_t LCD_REG;			// RS = 0
  volatile uint16_t LCD_RAM;      // RS = 1
} LCD_TypeDef;		


	GPIO_TypeDef *GPIO_backlight, *GPIO_reset;
#define	 LCD_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define  LCD             ((LCD_TypeDef *) LCD_BASE)
#define  LCD_turnON_backlight	 (GPIO_backlight->BSRR = _LCD_bit(PIN_bl))		// set: output 1
#define  LCD_turnOFF_backlight (GPIO_backlight->BSRR = _LCD_bit(PIN_bl)<<16)		// reset: output 0
#define	 LCD_RESET_H  		(GPIO_reset->BSRR = _LCD_bit(PIN_rs))
#define	 LCD_RESET_L  		(GPIO_reset->BSRR = _LCD_bit(PIN_rs)<<16)
//<<<<<<<<<<<

#define LCD_WriteReg(x)	(LCD->LCD_REG = (uint16_t) x)	//lcd write reg
#define LCD_WriteData(x)	(LCD->LCD_RAM = (uint16_t) x)	//lcd write data

/********************************************************************************************************
// Display Inversion On & Off
********************************************************************************************************/
#define ReverseLCD()		LCD_WriteReg(0x21)	// Display Inversion ON (21h)
#define NormalLCD()			LCD_WriteReg(0x20)	// Display Inversion ON (21h)

/***********************************************
  * @brief  Configures the Parallel interface (FSMC) for LCD(Parallel mode)
  * @param  None
  * @retval None
  */
void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  wr, w;

  /* Enable FSMC clock */
//  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
		RCC->AHB3ENR |= _LCD_bit(0); //bit 0: RCC_AHB3Periph_FSMC


/*-- FSMC Configuration ------------------------------------------------------*/
/*----------------------- SRAM Bank 1 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 configuration */
  wr.FSMC_AddressSetupTime = 15;
  wr.FSMC_AddressHoldTime = 0;
  wr.FSMC_DataSetupTime = 0x3C;		// 60
  wr.FSMC_BusTurnAroundDuration = 0;
  wr.FSMC_CLKDivision = 0;
  wr.FSMC_DataLatency = 0;
  wr.FSMC_AccessMode = FSMC_AccessMode_A;

  w.FSMC_AddressSetupTime = 9;
  w.FSMC_AddressHoldTime = 0;
  w.FSMC_DataSetupTime = 8;		// 60
  w.FSMC_BusTurnAroundDuration = 0;
  w.FSMC_CLKDivision = 0;
  w.FSMC_DataLatency = 0;
  w.FSMC_AccessMode = FSMC_AccessMode_A;
  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &wr;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &w;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  
  /* Enable FSMC NOR/SRAM Bank1 */
   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE); 
}

/********************************************************************************************************
*  Function: GPIO_outPPhigh				                                                           
*  Object: set GPIO pin as output, push-pull, high speed (100 MHz)
*  Input: PortNum (0, ..., 6); PinNum (0, ..., 15)
*  Output: none                                  
********************************************************************************************************/
static GPIO_TypeDef* GPIO_outPPhigh(uint32_t PortNum, uint32_t PinNum)
{
	GPIO_TypeDef *GPIO_x;
	uint32_t y=PinNum;

		RCC->AHB1ENR |=  (1UL << PortNum);     // enable clock for GPIOx
    // __SPI1_CS_PORT = 0: PORTA, 1: PORTB, ..., 10: PORTK
    GPIO_x  = (GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400 * PortNum);

    GPIO_x->MODER   = (GPIO_x->MODER & ~_LCD_bit((y*2+1)) )  | _LCD_bit(y*2); //Output mode (01b)
    GPIO_x->OSPEEDR = (GPIO_x->OSPEEDR |  (0x03<<(y*2)) ); //high speed (11b)
    GPIO_x->OTYPER  &= ~_LCD_bit(y);                      // push-pull (0b)
    GPIO_x->PUPDR   &= ~(0x03<<(y*2));       //NO pull (00b)
  if (y < 8)
    GPIO_x->AFR[0]  &= ~(0x0F<<(y*4));      // AF0
  else
    GPIO_x->AFR[1]  &= ~(0x0F<<((y-8)*4));  // AF0
	
		return GPIO_x;
}

/********************************************************************************************************
*  Function: GPIO_outPPhigh				                                                           
*  Object: set GPIO pin as output, push-pull, high speed (100 MHz)
*  Input: PortNum (0, ..., 6); PinNum (0, ..., 15)
*  Output: none                                  
********************************************************************************************************/
static void GPIO_AF12PPhigh(uint32_t PortNum, uint32_t PinBit)
{
	GPIO_TypeDef *GPIO_x;
	uint32_t temp, chg1= PinBit, chg2=0, chg4L=0, chg4H=0;
	uint32_t fill2=0, fill4L=0, fill4H=0;

		RCC->AHB1ENR |=  (1UL << PortNum);     // enable clock for GPIOx
    // __SPI1_CS_PORT = 0: PORTA, 1: PORTB, ..., 10: PORTK
    GPIO_x  = (GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400 * PortNum);

  
	for (temp=0; temp<16; temp++){
			if (PinBit & 0x01){
			   chg2 |= (0x03ul) << (temp*2);
			   fill2 |= (0x02ul) << (temp*2);
			  if (temp <8){
			   chg4L |= (0x0Ful) << (temp*4);
			   fill4L |= (0x0Cul) << (temp*4);
			  }else {
			   chg4H |= (0x0Ful) << ((temp-8)*4);
			   fill4H |= (0x0Cul) << ((temp-8)*4);
			  }				
		  }
			PinBit = PinBit >> 1;
	}

		GPIO_x->MODER   = (GPIO_x->MODER & ~chg2)  | fill2; //AF mode (10b)
    GPIO_x->OSPEEDR = (GPIO_x->OSPEEDR |  chg2 ); //high speed (11b)
    GPIO_x->OTYPER  &= ~chg1;                      // push-pull (0b)
    GPIO_x->PUPDR   &= ~chg2;       //NO pull (00b)
  if (chg4L)
	{
    temp = GPIO_x->AFR[0];
    temp &= ~chg4L;						// clear to 0000b
		GPIO_x->AFR[0] = (temp | fill4L);      // AF12  (1100b)
	}
	if (chg4H)
	{
    temp = GPIO_x->AFR[1];
    temp &= ~chg4H;						// clear to 0000b
		GPIO_x->AFR[1] = (temp | fill4H);      // AF12  (1100b)
	}
}

/********************************************************************************************************
*  Function: LCD_Delayms				                                                           
*  Object: lcd init wait..
*  Input: Num
*  Output: none                                  
*  brief: time = Num * 1ms
********************************************************************************************************/
static void LCD_Delayms(uint16_t Num)
{
		uint16_t Timer;
		while(Num--)
		{
		 	Timer = 11500;
			while(Timer--); 
		}
}

/********************************************************************************************************
*  Function: LCD_Reset				                                                           
*  Object: lcd reset control
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_Reset(void)
{
		LCD_RESET_L;
		LCD_Delayms(150);		// 150 ms
		LCD_RESET_H;
		LCD_Delayms(50);	// 50 ms
}

/********************************************************************************************************
*  Function: LCD_Init				                                                           
*  Object: lcd initialization
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdFSMCON(void);
#define LCD_PortInit(void)  Driver_LcdFSMCON(void)
void LCD_Init(void)
{ 
		//-- LCD PORT INIT --
//		LCD_PortInit();
		GPIO_backlight = GPIO_outPPhigh(PNr_backlight, PIN_bl);	// backlight pin (LIG): PB0
		GPIO_reset = GPIO_outPPhigh(PNr_reset, PIN_rs);  				// reset pin (RST): PC5
		GPIO_AF12PPhigh(PNr_FSMC_set1, PinBit_FSMC_set1);
		GPIO_AF12PPhigh(PNr_FSMC_set2, PinBit_FSMC_set2);
		GPIO_AF12PPhigh(PNr_FSMC_set3, PinBit_FSMC_set3);
/*  GPIOD: AF_FSMC, Speed_100MHz , push pull, no pull-up or pull-down 
	  --------------------------------------------------------------
	  | Pin: PD |   0   1    4    5       8    9   10   14   15
    | GLCD    |  D2  D3   (RD) (WR)    D13  D14  D15  D0   D1
	  --------------------------------------------------------------
    GPIOE: AF_FSMC, Speed_100MHz , push pull, no pull-up or pull-down 
	  --------------------------------------------------------------
	  | Pin: PE |    7   8   9   10  11  12  13   14   15
    | GLCD    |   D4  D5  D6  D7  D8  D9  D10  D11  D12
	  --------------------------------------------------------------
   GPIOG: AF_FSMC, Speed_100MHz , push pull, no pull-up or pull-down 
	  --------------------------------------------------------------
	  | Pin : PG |   0         12
    | GLCD     |  (RS)      (CS)
	            (FSMC_A10)  (FSMC_NE4)
	  --------------------------------------------------------------
*/

	
		LCD_FSMCConfig();
	
		//-- LCD RESET--
		LCD_Reset();
		//-------------- Initial Sequence ---------------
		//************* Start Initial Sequence **********//	
		LCD_WriteReg(0xCF);  // Power control B (CFh)
		LCD_WriteData(0x00); 
		LCD_WriteData(0xC1); 
		LCD_WriteData(0X30); 
		LCD_WriteReg(0xED);  // Power on sequence control (EDh)
		LCD_WriteData(0x64); 
		LCD_WriteData(0x03); 
		LCD_WriteData(0X12); 
		LCD_WriteData(0X81); 
		LCD_WriteReg(0xE8);  // Driver timing control A (E8h)
		LCD_WriteData(0x85); 
		LCD_WriteData(0x10); 
		LCD_WriteData(0x7A); 
		LCD_WriteReg(0xCB);  // Power control A (CBh)
		LCD_WriteData(0x39); 
		LCD_WriteData(0x2C); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x34); 
		LCD_WriteData(0x02); 
		LCD_WriteReg(0xF7);  
		LCD_WriteData(0x20); 
		LCD_WriteReg(0xEA);  
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteReg(0xC0);    // Power Control 1 (C0h)
		LCD_WriteData(0x1B);   //VRH[5:0] 
		LCD_WriteReg(0xC1);    // Power Control 2 (C1h)
		LCD_WriteData(0x01);   //SAP[2:0];BT[3:0] 
		LCD_WriteReg(0xC5);    // VCOM Control 1(C5h)
		LCD_WriteData(0x30); 	 //3F
		LCD_WriteData(0x30); 	 //3C
		LCD_WriteReg(0xC7);    // VCOM Control 2(C7h)
		LCD_WriteData(0XB7); 
		LCD_WriteReg(0x3A);   	// Pixel Format Set (3Ah)
		LCD_WriteData(0x55); 		// 16 bits Format
		LCD_WriteReg(0xB1);   
		LCD_WriteData(0x00);   
		LCD_WriteData(0x1A); 
		LCD_WriteReg(0xB6);    // Display Function Control 
		LCD_WriteData(0x0A); 
		LCD_WriteData(0xA2); 
		LCD_WriteReg(0xF2);    // 3Gamma Function Disable 
		LCD_WriteData(0x00); 
		LCD_WriteReg(0x26);    //Gamma curve selected 
		LCD_WriteData(0x01); 
		LCD_WriteReg(0xE0);    //Set Gamma 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x2A); 
		LCD_WriteData(0x28); 
		LCD_WriteData(0x08); 
		LCD_WriteData(0x0E); 
		LCD_WriteData(0x08); 
		LCD_WriteData(0x54); 
		LCD_WriteData(0XA9); 
		LCD_WriteData(0x43); 
		LCD_WriteData(0x0A); 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 		 
		LCD_WriteReg(0XE1);    //Set Gamma 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x15); 
		LCD_WriteData(0x17); 
		LCD_WriteData(0x07); 
		LCD_WriteData(0x11); 
		LCD_WriteData(0x06); 
		LCD_WriteData(0x2B); 
		LCD_WriteData(0x56); 
		LCD_WriteData(0x3C); 
		LCD_WriteData(0x05); 
		LCD_WriteData(0x10); 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x3F); 
		LCD_WriteData(0x3F); 
		LCD_WriteData(0x0F); 
		//
		//   <-------------------- page (x)
		//                       |
		//                       |
		//                       \/
		//                     column (y) 
		LCD_WriteReg(0x2B); 	// Page Address Set (2Bh) < 320
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0x01);
		LCD_WriteData(0x3f);
		LCD_WriteReg(0x2A);  // Column Address Set (2Ah) <240
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0xef);	 
		LCD_WriteReg(0x11); //Exit Sleep
		LCD_Delayms(120);
		LCD_WriteReg(0x29); //display on
   	LCD_WriteReg(0x36);  // Memory Access Control (36h)
  #if (LANDSCAPE == 1)
    /* AM=1   (address is updated in vertical writing direction)              */
		LCD_WriteData(0xA8);	// bit 7, 5, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 5 (column and row exchange) = 1
		// bit 6 (column addr. order) = 0   rightward: 0 ==> width 
    // bit 7 (page (row) addr. order) = 1  downward: height ==> 0
		//
		//   --------------------> page (x)
		//   |
		//   |
		//   \/
		//   column (y) 
		//
  #else
    /* AM=0   (address is updated in horizontal writing direction)            */
		LCD_WriteData(0xC8);	// bit 7, 6, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 6 (column addr. order) = 1   upward: width ==> 0
    // bit 7 (page (row) addr. order) = 1  rightward: height ==> 0
		//
		//   column (x) 
		//   ^
		//   |
		//   |
		//   --------------------> page (y)
		//
  #endif
	
	//----- setting the following initial variables:
	//----- pLCD_Currentfonts
	//----- wf, hf, bytes_wf, bytes_f
	LCD_SetFont( &LCD_DEFAULT_FONT);
}

/********************************************************************************************************
*  Function: LCD_toPortrait				                                                           
*  Object: lcd display in Portrait mode
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_toPortrait(void)
{
#if (LANDSCAPE == 1)
   	LCD_WriteReg(0x36);  // Memory Access Control (36h)
		LCD_WriteData(0xC8);	// bit 7, 6, 3 = 1  
#endif	
}
/********************************************************************************************************
*  Function: LCD_toLandscape				                                                           
*  Object: lcd display in Portrait mode
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_toLandscape(void)
{
#if (LANDSCAPE != 1)
   	LCD_WriteReg(0x36);  // Memory Access Control (36h)
		LCD_WriteData(0xA8);	// bit 7, 6, 3 = 1  
#endif
}
/********************************************************************************************************
*  Function: LCD_toDefaultDisDirection				                                                           
*  Object: lcd display in Portrait mode
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_toDefaultDisDirection(void)
{
   	LCD_WriteReg(0x36);  // Memory Access Control (36h)
#if (LANDSCAPE == 1)
		LCD_WriteData(0xA8);	// bit 7, 6, 3 = 1  
#else
		LCD_WriteData(0xC8);	// bit 7, 6, 3 = 1  
#endif
}
/********************************************************************************************************
*  Function: LCD_OpenWin				                                                           
*  Object: lcd open window for display
*  Input: x0,y0, x1, y1
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_OpenWin(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
		LCD_WriteReg(0x2A);					// Column Address Set (2Ah)
		LCD_WriteData(x0>>8);
		LCD_WriteData(0x00FF&x0);		
		LCD_WriteData(x1>>8);
		LCD_WriteData(0x00FF&x1);
	
		LCD_WriteReg(0x2B);				// Page (Row) Address Set (2Bh) 
		LCD_WriteData(y0>>8);
		LCD_WriteData(0x00FF&y0);		
		LCD_WriteData(y1>>8);
		LCD_WriteData(0x00FF&y1);

		LCD_WriteReg(0x2C);
}

/********************************************************************************************************
*  Function: LCD_Clear				                                                           
*  Object: lcd clear screen
*  Input: backcolor
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_Clear(uint16_t BackColor)
{
		uint16_t i,j;
		LCD_OpenWin(0, 0, LCD_COL_NUM-1, LCD_ROW_NUM-1);
		for(i = 0; i < LCD_ROW_NUM; i++)
			 for(j =0; j < LCD_COL_NUM; j++)
					 LCD_WriteData(BackColor);
}

/**
  * @brief  Enable the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOn(void)
{
 	//---- turn on backlight ----------
	LCD_turnON_backlight;			// //   GPIOB->BSRR = 0x01;
	
  /* Display On */
	LCD_WriteReg(0x29);				// Display ON (0x29)
}

/**
  * @brief  Disable the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOff(void)
{
  /* Display Off */
	LCD_WriteReg(0x28);				// Display OFF (0x28)
	//---- turn off backlight ----------
	LCD_turnOFF_backlight;		//   GPIOB->BSRR = 0x01<<16;	
}

//###########################################################
//
//     Hardware Abstract Layer
//
//###########################################################
/**
  * @brief  Sets a display window by width (w) and height (h)
  *
*/
#define LCD_SetDisplayWindow(x, y, w, h)  LCD_OpenWin(x, y, x+w-1, y+h-1)

/********************************************************************************************************
*  Function: LCD_DisplayChar				                                                           
*  Object: Display an ASCII character
*  Input: start point, end point, ASCII code, text color, background color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
static void LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos,  uint8_t Ascii, uint16_t fColor, uint16_t bColor)
{
// wf = font_width,
// hf =  font_height
// bytes_wf = number of bytes per width line in a font
// bytes_f  = number of bytes per font

	int	iw;
  uint32_t byteNr, jw;
	uint16_t  hp_limit;
	const uint8_t *c;
	
	iw = Ascii - 32;  // make ' ' (space) at offset of 0
  c = &pLCD_Currentfonts->table[iw * bytes_f];	
	
	LCD_OpenWin(Xpos, Ypos, Xpos+wf-1, Ypos+hf-1);
	byteNr =0;
	hp_limit = Ypos + hf;
	
  for(; Ypos < hp_limit; Ypos++)		// font height 
  {
		uint8_t as;

		as = c[byteNr++];
		iw = 0;
    for(jw = 0; jw < wf; jw++)	//  loop for the font width (wf)
    {
				if(as & (0x80))
				{
					LCD_WriteData(fColor);
				}
				else
				{
					LCD_WriteData(bColor);
				}
				as <<= 1;
				iw++;
				if (iw == 8){							// reach 1 byte = 8 bits
					as = c[byteNr++];
					iw = 0;
				}
    }
	}
}

/**
  * @brief  Displays characters between a line segment on the LCD.
  * @param  Xpos: X position (in pixel)
  * @param  Ypos: Y position (in pixel)   
  * @param  Text: Pointer to string to display on LCD
  * @retval None
  */
static void LCD_DisplayStringSegment(uint16_t Xpos, uint16_t Ypos, char *Text, uint16_t font_width)
{
	uint16_t fColor, bColor;
	
	fColor = DrawProp.TextColor;
	bColor = DrawProp.BackColor;
  while ((*Text != 0) & (Xpos  <= (LCD_PIXEL_WIDTH+1-font_width)) )
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Xpos, Ypos, *Text, fColor, bColor);
    /* Decrement the column position by 16 */
    Xpos += font_width;
    /* Point on the next character */
    Text++;
  }
}

/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  _TextColor: specifies the Text Color.
  * @param  _BackColor: specifies the Background Color.
  * @retval None
  */
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
  DrawProp.TextColor = _TextColor;
  DrawProp.BackColor = _BackColor;
}

/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  _TextColor: pointer to the variable that will contain the Text
            Color.
  * @param  _BackColor: pointer to the variable that will contain the Background
            Color.
  * @retval None
  */
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
  *_TextColor = DrawProp.TextColor; 
	*_BackColor = DrawProp.BackColor;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetTextColor(__IO uint16_t Color)
{
  DrawProp.TextColor = Color;
}


/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetBackColor(__IO uint16_t Color)
{
  DrawProp.BackColor = Color;
}

/**
  * @brief  Sets the Text Font.
  * @param  fonts: specifies the font to be used.
  * @retval None
  */
void LCD_SetFont(sFONT *pfonts)
{
  pLCD_Currentfonts = pfonts;
	//----- modified by Shir-Kuan Lin
	wf = pfonts->Width; 	// font_width
	hf = pfonts->Height; // font_height
	bytes_wf = (wf+7) /8;	// number of bytes per width line in a font
	bytes_f = hf * bytes_wf;	// number of bytes per font (see Font12_Table or Font20_Table)
}

/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
sFONT *LCD_GetFont(void)
{
  return pLCD_Currentfonts;
}

/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..n
  * @retval None
  */
void LCD_ClearStringLine(uint16_t LineNr)
{
  uint16_t bColor;
  uint16_t x, y;
	if (((LineNr+1) * pLCD_Currentfonts->Height) > (LCD_PIXEL_HEIGHT)){
		return;
	}
	LineNr = LineNr * pLCD_Currentfonts->Height;
	bColor = DrawProp.BackColor;
	
	LCD_OpenWin(0, LineNr, LCD_PIXEL_WIDTH-1, LineNr+hf-1);
  for(y = 0; y < hf; y++)		
  {
		for(x = 0; x < LCD_PIXEL_WIDTH; x++)
		{
			LCD_WriteData(bColor);
		}
	}
}


/**
  * @brief  Displays characters on the LCD.
  * @param  Xpos: X position (in pixel)
  * @param  Ypos: Y position (in pixel)   
  * @param  Text: Pointer to string to display on LCD
  * @param  Mode: Display mode
  *          This parameter can be one of the following values:
  *            @arg  CENTER_MODE
  *            @arg  RIGHT_MODE
  *            @arg  LEFT_MODE   
  * @retval None
  */
void LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, char *Text, Line_ModeTypdef Mode)
{
  uint16_t refcolumn = 1, font_width;
  uint32_t size = 0, xsize = 0; 
  char  *ptr = Text;
  
 	font_width = pLCD_Currentfonts->Width;
 /* Get the text size */
  while (*ptr++) size ++ ;
  
  /* Characters number per line */
  xsize = (LCD_PIXEL_WIDTH /font_width);
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      refcolumn = Xpos + ((xsize - size)* font_width) / 2;
      break;
    }
  case LEFT_MODE:
    {
      refcolumn = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      refcolumn =  - Xpos + ((xsize - size)*font_width);
      break;
    }    
  default:
    {
      refcolumn = Xpos;
      break;
    }
  }
  
  /* Send the string character by character on lCD */
	LCD_DisplayStringSegment(refcolumn, Ypos, Text, font_width);
}


/**
  * @brief  Displays the string on the required row and column
  * @param ount: specifies the delay time length (time base 10 ms).
  * @retval : None
  */
void LCD_DisplayStringLineCol(uint8_t LineNr, uint16_t ColNr, char *ptr)
{
  uint16_t reftcolumn, font_width;
	
	font_width = pLCD_Currentfonts->Width;
	reftcolumn = ColNr * font_width;
	if(LineNr)
	   LineNr = LineNr * pLCD_Currentfonts->Height;
	
	LCD_DisplayStringSegment(reftcolumn, LineNr, ptr, font_width);
}

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position 
  * @param  Ypos: Y position
  * @param  Color: Pixel color in RGB mode (5-6-5)  
  * @retval None
  */
void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t Color)
{
		LCD_OpenWin(Xpos, Ypos, Xpos, Ypos);
	  LCD_WriteData(Color);
}


/**
  * @brief  Draws a horizontal line on LCD.
  * @param  Xpos: X position 
  * @param  Ypos: Y position
  * @param  Length: line length
  * @param  RGB_Code: Pixel color in RGB mode (5-6-5)  
  * @retval None
  */
void LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint16_t color=DrawProp.TextColor;
	uint16_t i;

	LCD_OpenWin(Xpos, Ypos, (Xpos+Length-1), Ypos);
		for(i = 0; i < Length; i++)
			 LCD_WriteData(color);
}

/**
  * @brief  Draws a vertical line on LCD.
  * @param  Xcen: X position 
  * @param  Ypos: Y position
  * @param  Length: line length
  * @param  RGB_Code: Pixel color in RGB mode (5-6-5)  
  * @retval None
  */
void LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint16_t color=DrawProp.TextColor;
	uint16_t j;

	LCD_OpenWin(Xpos, Ypos, Xpos, (Ypos+Length-1) );
		for(j = 0; j < Length; j++)
			 LCD_WriteData(color);
}


/**
  * @brief  Displays a rectangle border.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	//===  horizontal lines
  LCD_DrawHLine(Xpos, Ypos, Width);
  LCD_DrawHLine(Xpos, (Ypos + Height-1), Width);

	//===  vertical lines
  LCD_DrawVLine(Xpos, Ypos, Height);
  LCD_DrawVLine((Xpos + Width - 1), Ypos, Height);
}

/**
  * @brief  Displays a circle border.
  * @param  Xcen: specifies the X position of the center.
  * @param  Ycen: specifies the Y position of the center.
  * @param  Radius
  * @retval None
  */
void LCD_DrawCircle(uint16_t Xcen, uint16_t Ycen, uint16_t Radius)
{
	uint16_t color=DrawProp.TextColor;

  int32_t  next;/* Decision Variable */
  uint32_t  Ri;/* increasing from 0 to Radius */
  uint32_t  Rd;/* decreasing from Radius to 0 */

  next = 3 - (Radius << 1);
  Ri = 0;
  Rd = Radius;

  while (Ri <= Rd)
  {
		int32_t x0, y0;

		x0 = Xcen -	Ri;
		y0 = Ycen -	Rd;
		if(x0<0) x0=0;
		if(y0<0) y0=0;
				LCD_DrawPixel(x0, y0, color);                          
				LCD_DrawPixel(x0, Ycen+Rd, color);                  
				LCD_DrawPixel(Xcen+Ri, y0, color);             
				LCD_DrawPixel(Xcen+Ri, Ycen+Rd, color);             
		x0 = Xcen -	Rd;
		y0 = Ycen -	Ri;
		if(x0<0) x0=0;
		if(y0<0) y0=0;
				LCD_DrawPixel(x0, y0, color);              	         
				LCD_DrawPixel(x0, Ycen+Ri, color);             
				LCD_DrawPixel(Xcen+Rd, y0, color);                      
				LCD_DrawPixel(Xcen+Rd, Ycen+Ri, color);                          

    if (next < 0)
    {
      next += (Ri << 2) + 6;
    }
    else
    {
      next += ((Ri - Rd) << 2) + 10;
      Rd--;
    }
    Ri++;
  }
}

/**
  * @brief  Displays a full rectangle with TestColor.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: rectangle height.
  * @param  Width: rectangle width.
  * @retval None
  */
void LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint16_t color=DrawProp.TextColor;
	uint16_t Xend = Xpos+ Width-1, Yend = Ypos + Height-1;
	uint16_t i, j;
	
		LCD_OpenWin(Xpos, Ypos, Xend, Yend);
		for(i = 0; i < Width; i++)
			 for(j = 0; j < Height; j++)
					 LCD_WriteData(color);
	
}

/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */
void LCD_FillCircle(uint16_t Xcen, uint16_t Ycen, uint16_t Radius)
{
//	uint16_t color=DrawProp.TextColor;
  int32_t  next;/* Decision Variable */
  uint32_t  Ri;/* increasing from 0 to Radius */
  uint32_t  Rd;/* decreasing from Radius to 0 */

  next = 3 - (Radius << 1);
  Ri = 0;
  Rd = Radius;

  while (Ri <= Rd)
  {
		int32_t X0, Y0;

		X0 = Xcen - Ri;
		Y0 = Ycen -	Rd;
		if(X0<0) X0=0;
		if(Y0<0) Y0=0;
		LCD_DrawVLine(X0, Y0, (Ycen + Rd - Y0));				// vertical line in landscape  view
		X0 = Xcen + Ri;
		LCD_DrawVLine(X0, Y0, (Ycen + Rd - Y0));				// vertical line in landscape  view
		X0 = Xcen - Rd;
		Y0 = Ycen -	Ri;
		if(X0<0) X0=0;
		if(Y0<0) Y0=0;
		LCD_DrawHLine(X0, Y0, (Xcen + Rd - X0));				// horizontal line in landscape  view
		Y0 = Ycen +	Ri;
		LCD_DrawHLine(X0, Y0, (Xcen + Rd - X0));				// horizontal line in landscape  view
    if (next < 0)
    {
      next += (Ri << 2) + 6;
    }
    else
    {
      next += ((Ri - Rd) << 2) + 10;
      Rd--;
    }
    Ri++;
  }
}

/**
  * @brief  Displays an uni-line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t color=DrawProp.TextColor;
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
  curpixel = 0;

  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
	
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
		if(x < 0 || x > LCD_PIXEL_WIDTH || y < 0 || y > LCD_PIXEL_HEIGHT)
		{
			goto escape;
		}
		LCD_DrawPixel(x, y, color);
escape:
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}

/**
  * @brief  Displays a mono-color picture.
  * @param  Pict: pointer to the picture array.
  * @retval None
  */
void LCD_DrawMonoPict(const uint32_t *Pict)
{
	uint16_t fcolor=DrawProp.TextColor;
	uint16_t bcolor=DrawProp.BackColor;
  uint32_t index = 0, i = 0;

  LCD_SetDisplayWindow(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT);
//  LCD_SetCursor(0, (LCD_PIXEL_WIDTH - 1));
//  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
 
	for(index = 0; index < 2400; index++)
  {
    for(i = 0; i < 32; i++)						// 2400 x 32 = 240 x 320
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        LCD_WriteData(bcolor);		// background color
      }
      else
      {
        LCD_WriteData(fcolor);
      }
    }
  }
}

/**
  * @brief  Draws a bitmap picture (16 bpp) (24 bpp will be transfered to 16 bpp automatically).
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pbmp: Pointer to Bmp picture address.
  * @retval None
  */
void LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *BmpAddress)	
{
  uint32_t index = 0, size = 0;
  uint16_t bitCount;
	
	uint32_t height = 0, i=0;
  uint32_t width  = 0, j = 0;
  
  //---------------->>>>>>>>>>>>>>>
	/* Read BMP signature */
  width = *(uint16_t *) (BmpAddress + 0);
	if (width != 0x4D42) return;
	
  /* Read bitmap width */
  width = *(uint16_t *) (BmpAddress + 18);
  width |= (*(uint16_t *) (BmpAddress + 20)) << 16;
  
  /* Read bitmap height */
  height = *(uint16_t *) (BmpAddress + 22);
  height |= (*(uint16_t *) (BmpAddress + 24)) << 16; 

//	LCD_SetDisplayWindow(Xpos, Ypos, width, height);
	//-----------------<<<<<<<<<<<<<<<<<<<<<
  
  /* Read number of bits per pixel */
  bitCount = *(uint16_t *) (BmpAddress + 28);

  /* Read bitmap size */
  size = *(__IO uint16_t *) (BmpAddress + 2);
  size |= (*(__IO uint16_t *) (BmpAddress + 4)) << 16;
  /* Get bitmap data address offset */
  index = *(__IO uint16_t *) (BmpAddress + 10);
  index |= (*(__IO uint16_t *) (BmpAddress + 12)) << 16;
  size = (size - index);
  BmpAddress += index;
	
//>>>######################################################
  /* Set GRAM write direction and BGR = 1 */
		LCD_WriteReg(0x36);  // Memory Access Control (36h)
  #if (LANDSCAPE == 1)
    /* BMP updates from bottom to top and left to right        */
		LCD_WriteData(0xE8);	// bit 7, 6, 5, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 5 (column and row exchange) = 1
		// bit 6 (column addr. order) = 1   width ==> 0
    // bit 7 (page (row) addr. order) = 1  height ==> 0
		//
		//   column (y) 
		//   ^
		//   |
		//   |
		//   --------------------> page (x)
		//
  #else
    /* AM=0   (address is updated in horizontal writing direction)            */
		LCD_WriteData(0x48);	// bit 7, 6, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 6 (column addr. order) = 1   width ==> 0
    // bit 7 (page (row) addr. order) = 0  height ==> 0
		//
		//   column (x) 
		//   ^
		//   |
		//   |
		//   --------------------> page (y)
		//
  #endif
//<<<######################################
	LCD_SetDisplayWindow(Xpos, 241-(Ypos+height), width, height);

  if (bitCount == 24)
	{
		uint8_t skip;
		
		skip = 0x03 & (4 - ( (width*3) &0x03));   // align in 4 multiple
		for (i = 0; i<height; i++)
		{ for (j =0; j <width; j++)
			{
				uint16_t temp;
/*				uint16_t t2;
				t2 = (*(__IO uint8_t *)BmpAddress++);
				temp = t2 >>3;
				t2 = (*(__IO uint8_t *)(BmpAddress++));
				temp |= (t2 >>3)<<6;
				t2 = (*(__IO uint8_t *)(BmpAddress++));
				temp |= (t2 >>3)<<(5+6);
*/
				temp = (*(__IO uint8_t *)BmpAddress++)>>3;
				temp |= ((*(__IO uint8_t *)(BmpAddress++) )>> 3)  << 6;
				temp |= ((*(__IO uint8_t *) (BmpAddress++) )>> 3)  << (6+5);
				LCD_WriteData(temp);
			}
			BmpAddress += skip;
		}
	}
	else // bitCount == 16 [RED (5bits): GREEN (6bits): BLUE (5bits)]
	{
	 for(index = 0; index < (size/2); index++)
   {
			LCD_WriteData(*(__IO uint16_t *)BmpAddress);
			BmpAddress += 2;
	 }
  }

//>>>######################################################
  /* Set GRAM write direction and BGR = 1 */
		LCD_WriteReg(0x36);  // Memory Access Control (36h)
  #if (LANDSCAPE == 1)
		LCD_WriteData(0xA8);	// bit 7, 5, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 5 (column and row exchange) = 1
		// bit 6 (column addr. order) = 0   0 ==> width 
    // bit 7 (page (row) addr. order) = 1  height ==> 0
		//
		//   --------------------> page (x)
		//   |
		//   |
		//   \/
		//   column (y) 
		//
  #else
		LCD_WriteData(0xC8);	// bit 7, 6, 3 = 1  
		// bit 3 (BGR) = 1
		// bit 6 (column addr. order) = 1   width ==> 0
    // bit 7 (page (row) addr. order) = 1  height ==> 0
		//
		//   column (x) 
		//   ^
		//   |
		//   |
		//   --------------------> page (y)
		//
  #endif
//<<<######################################
}

/**
  * @brief  Draws RGB Image (16 bpp).
  * @param  Xpos:  X position in the LCD
  * @param  Ypos:  Y position in the LCD
  * @param  Xsize: X size in the LCD
  * @param  Ysize: Y size in the LCD
  * @param  pdata: Pointer to the RGB Image address.
  * @retval None
  */
void LCD_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  uint32_t index = 0, size = 0;
  
  LCD_SetDisplayWindow(Xpos, Ypos, Xsize, Ysize);
  
  size = (Xsize * Ysize);

  for(index = 0; index < size; index++)
  {
    /* Write 16-bit GRAM Reg */
 		LCD_WriteData(*(volatile uint16_t *)pdata);
    pdata += 2;
  }

}


/**
  * @brief  Displays an poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLine(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    LCD_DrawLine(X, Y, Points->X, Points->Y);
  }
}

/**
  * @brief  Displays an relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @param  Closed: specifies if the draw is closed or not.
  *           1: closed, 0 : not closed.
  * @retval None
  */
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed)
{
  int16_t X = 0, Y = 0;
  pPoint First = Points;

  if(PointCount < 2)
  {
    return;
  }
  X = Points->X;
  Y = Points->Y;
  while(--PointCount)
  {
    Points++;
    LCD_DrawLine(X, Y, X + Points->X, Y + Points->Y);
    X = X + Points->X;
    Y = Y + Points->Y;
  }
  if(Closed)
  {
    LCD_DrawLine(First->X, First->Y, X, Y);
  }
}

/**
  * @brief  Displays a closed poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_DrawPolygon(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLine(Points, PointCount);
  LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
}

/**
  * @brief  Displays a relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 0);
}

/**
  * @brief  Displays a closed relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 1);
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius
  * @retval None
  */
void LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);
  
  do {      
    LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);
    LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}


/**
  * @brief  Fills a triangle (between 3 points).
  * @param  Points: Pointer to the points array
  * @param  Points[0].x: Point 1 X position
  * @param  Points[0].y: Point 1 Y position
  * @param  Points[1].x: Point 2 X position
  * @param  Points[1].y: Point 2 Y position
  * @param  Points[2].x: Point 3 X position
  * @param  Points[2].y: Point 3 Y position
  * @retval None
  */
void LCD_FillTriangle(pPoint Points)
{
	uint16_t	xp[3], yp[3], i, tmp, x_end2, y_end2;
  int16_t int_tmp, deltaX1, deltaY1, deltaX2;
  uint16_t x, y;
	
	for (i=0; i<3; i++)
	{
		xp[i] = Points[i].X;
		yp[i] = Points[i].Y;
		if (i>0){
		  if (yp[0] > yp[i]){
				tmp = xp[0];
				xp[0] = xp[i];
				xp[i] = tmp;
				tmp = yp[0];
				yp[0] = yp[i];
				yp[i] = tmp;
			}
		}
	}
	if (yp[1] > yp[2]){
				tmp = xp[1];
				xp[1] = xp[2];
				xp[2] = tmp;
				tmp = yp[1];
				yp[1] = yp[2];
				yp[2] = tmp;
	}
	//----------
	// Point 0 with smallest y; 
	// Point 1 at the middle height
	// Point 2 with largest y
	//------------ 
	deltaY1 = yp[1]- yp[0];		// deltaY1 >= 0
  deltaX1 = xp[1]- xp[0];
		int_tmp = ((xp[2]-xp[0])*deltaY1) /(yp[2]-yp[0]);
		y_end2 = yp[2];
		yp[2] = yp[1];
		x_end2 = xp[2];
		xp[2] = xp[0] + int_tmp;
	
  deltaX2 = xp[2]- xp[0];
	
	//====== 1st subtriangle 
	x = xp[0];
	y = yp[0];
	if (deltaY1 == 0){
		if (xp[1] < x) {
			x = xp[1];
			tmp = (uint16_t) (-deltaX1);
		}	else {
		  tmp = (uint16_t) deltaX1;
		}
		LCD_DrawHLine(x, y, tmp+1);
	}else {
		if ( xp[2] < xp[1] ){ // Line02 is left to Line01
			tmp = deltaX1;
			deltaX1 = deltaX2;
			deltaX2 = tmp;
		}

		for (i=0; i<=deltaY1; i++)
		{
				int16_t x_tmp, ll;
				
				x_tmp = deltaX1*i /deltaY1;
				ll = deltaX2*i /deltaY1- x_tmp; // Note: deltaY2 >= deltaY1 > 0 and  ll must >= 0

				LCD_DrawHLine(x+x_tmp, y++, (uint16_t) ll+1);
		}	
	}
	//====== 2nd subtriangle 
	
		x = x_end2;
		y = y_end2;
	if (xp[1] < xp[2]){ 
		deltaY1 = y_end2- yp[1];		
		deltaX1 = xp[1]-x_end2;
		deltaX2 = xp[2]-x_end2;
	} else{
		deltaY1 = y_end2- yp[2];		
		deltaX1 = xp[2]-x_end2;
		deltaX2 = xp[1]-x_end2;
	}
	
		for (i=1; i<=deltaY1; i++)
		{
				int16_t x_tmp, ll;
				
				x_tmp = deltaX1*i /deltaY1;
				ll = deltaX2*i /deltaY1- x_tmp; // Note: deltaX2 >= deltaX1 > 0, so ll must >= 0

				LCD_DrawHLine(x+x_tmp, y--, (uint16_t) ll+1);
		}	
}

/**
  * @brief  Draws a full poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void LCD_FillPolygon(pPoint Points, uint16_t PointCount)
{
  Point tmp_pt[3];
  int16_t i;

  if(PointCount <=2)
  {
    LCD_PolyLine(Points, PointCount);
		return;
  }

	LCD_FillTriangle(Points);
	if (PointCount == 3){
		return;
	}
  

	tmp_pt[0].X = Points[0].X;
	tmp_pt[0].Y = Points[0].Y;
	
  for(i = 1; i < (PointCount-1); i++)
  {
		tmp_pt[1].X = Points[i+1].X;
		tmp_pt[1].Y = Points[i+1].Y;
		tmp_pt[2].X = Points[i+2].X;
		tmp_pt[2].Y = Points[i+2].Y;
    
		LCD_FillTriangle(tmp_pt);
  }
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius  
  * @retval None
  */
void LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);    
  
  do 
  { 
    LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1));
    LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}


//============== NEW by Shir-Kuan Lin ++++++++++++
sFONT *lFont;
uint16_t	ltColor, lbColor;

//----------------------
void LCD_SaveColors(void)
{
	ltColor = DrawProp.TextColor;
	lbColor = DrawProp.BackColor;
}
//----------------------
void LCD_RestoreColors(void)
{
	DrawProp.TextColor = ltColor;
	DrawProp.BackColor = lbColor;
}
//----------------------
void LCD_SaveFont(void)
{
	lFont = pLCD_Currentfonts;
}
//----------------------
void LCD_RestoreFont(void)
{
  LCD_SetFont(lFont);
}

//########################################################
//########################################################
//  Test  Experiments 													 
//########################################################
//########################################################

/**
  * @brief  Test LCD Display
  * @retval None
  */
void LCD_RGB_Test(void)
{
  uint32_t index;

  LCD_SetDisplayWindow(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT);

	/* R */
  for(index = 0; index < (LCD_PIXEL_HEIGHT*LCD_PIXEL_WIDTH)/3; index++)
  {
    LCD_WriteData(LCD_COLOR_RED);
  }
	  
  /* G */
  for(;index < 2*(LCD_PIXEL_HEIGHT*LCD_PIXEL_WIDTH)/3; index++)
  {
    LCD_WriteData(LCD_COLOR_GREEN);
  }
	  
	/* B */
  for(; index < LCD_PIXEL_HEIGHT*LCD_PIXEL_WIDTH; index++)
  {
    LCD_WriteData(LCD_COLOR_BLUE);
  }
	
	  LCD_Delayms(1000); /* delay 1000 ms */

}


//==========================
// LCD display off/on test 
//==========================
void LCD_DisplayOnTest(void)
{
	LCD_WriteReg(0x28);				// Display OFF (0x28)
	//---- turn off backlight ----------
	LCD_turnOFF_backlight;

	LCD_Delayms(4000);
 	//---- turn on backlight ----------
	LCD_turnON_backlight;
	
  /* Display On */
	LCD_WriteReg(0x29);				// Display ON (0x29)
}
void LCD_ReadRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata);

/**
  * @brief  Menu Initialisation routine
  */
void MenuInit(void)
{
	LCD_RGB_Test();

	/*	save current Font, Back Color*/
	LCD_SaveColors();

	LCD_SaveFont();
//	LCD_SetFont(&Font20);
  LCD_Clear(LCD_COLOR_BLUE2);
	LCD_SetColors(LCD_COLOR_MAGENTA, LCD_COLOR_BLUE2); // Test = white; back = blue

	LCD_DisplayStringLineCol(0, 2,"PARADIGM LCD DEMO");		// line 0, column 2
  LCD_SetTextColor(LCD_COLOR_GREEN);
  LCD_DisplayStringLineCol(2, 1,"Watch LEDs flashing"); // line 2, column 1

	//----------------------------------
  LCD_SetTextColor(LCD_COLOR_YELLOW);
  /*Draw a rectangle with: Start X-Cood,  Start Y-Cood,  Width,  Heigt*/
  LCD_DrawRect(50,80,220,120);
  LCD_SetTextColor(LCD_COLOR_CYAN);
  /*Draw a rectangle with: Start X-Cood,  Start Y-Cood,  Width,  Heigt*/
  LCD_DrawRect(45,75,230,130);
	//----------------------------------
  LCD_SetTextColor(LCD_COLOR_RED);
	LCD_FillRect(53,83,214,114);
	LCD_SetTextColor(LCD_COLOR_WHITE);
  LCD_DisplayStringLineCol(5, 4, "Value:");
	LCD_DrawCircle(160, 160, 30);
  LCD_SetTextColor(LCD_COLOR_GREEN);
	LCD_FillCircle(160, 160, 26);


	/*	restore last Font, Back Color*/
	LCD_RestoreFont();
	LCD_RestoreColors();
	
	LCD_Delayms(2000);
	ReverseLCD();
	LCD_Delayms(4000);
	NormalLCD();

	LCD_Delayms(2000);
	LCD_DisplayOnTest();
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



#define LCD_ReadData	((uint16_t) LCD->LCD_RAM)	//lcd read data

/**
  * @brief  Reads RGB Image (16 bpp).
  * @param  Xpos:  X position in the LCD
  * @param  Ypos:  Y position in the LCD
  * @param  Xsize: X size in the LCD
  * @param  Ysize: Y size in the LCD
  * @param  pdata: Pointer to the RGB Image address.
  * @retval None
  */
void LCD_ReadRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  uint32_t index, size;
	volatile uint16_t data1, data2;
  
  LCD_SetDisplayWindow(Xpos, Ypos, Xsize, Ysize);

	LCD_WriteReg(0x2E);	// 0x2E: Memory Read
	//LCD_Delayms(1);
  size = (Xsize * Ysize);
	LCD_ReadData;   // the 1st return value is "dummy"

  for(index = 0; index < (size/2); index++)
	{
 		data1 = LCD_ReadData;							// data1[15:11] = RED1[4:0]; data1[7:2] = GREED1[5:0]
		data1 = (data1 & 0xF800) | ((data1<<3) & 0x07E0);
 		data2 = LCD_ReadData;							// data2[15:11] = BLUE1[4:0]; data1[7:3] = RED2[4:0]
		
 		*((volatile uint16_t *) pdata)= data1 | (data2>>11);
     pdata += 2;
		data1 = (data2<<8) & 0xF800;
 		data2 = LCD_ReadData;							// data2[15:10] = GREEN2[5:0]; data1[7:3] = BLUE2[4:0]
		data1 = data1 | ((data2>>5) & 0x07E0) | ((data2>>3) & 0x001F);
 		*((volatile uint16_t *) pdata)= data1;
     pdata += 2;
	}
	
	if( size & 0x01 )	// size is an odd integer
	{
 		data1 = LCD_ReadData;
		data1 = (data1 & 0xF800) | ((data1<<3) & 0x07E0);
 		data2 = LCD_ReadData;
		
 		*((volatile uint16_t *) pdata)= data1 | (data2>>11);
	}
}

//?????????????????
//################## Low LEVEL DRIVER
/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */
/*#define LCD_REG16  (*((volatile unsigned short *)(LCD_BASE+0x00080000UL)))
#define LCD_DAT16  (*((volatile unsigned short *)(LCD_BASE+0x00100000UL)))
uint16_t LCD_ReadReg_Single(uint16_t LCD_Reg)
{
  // Write 16-bit Index (then Read Reg) 
	LCD_WriteReg(LCD_Reg);
  // Read 16-bit Reg //
  return (LCD_ReadData);	// LCD->LCD_RAM;
}

*/

