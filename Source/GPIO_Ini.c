//void stm32f4_GPIO_Init (void);
#include "stm32f4xx.h"

#define bit(x) (1ul<<x)
#define bit2(x) (3ul<<x)
	
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
//=========================================================================== External interrupt/event Configuration
// <e0> External interrupt/event Configuration
//--------------------------------------------------------------------------- EXTI line 0
//   <e1.0> EXTI0: EXTI line 0 enable
//     <o2.0> interrupt enable (NVIC)
//     <o3.0> generate interrupt (IMR)
//     <o4.0> generate event
//     <o5.0> use rising trigger for interrupt/event
//     <o6.0> use falling trigger for interrupt/event
//     <o7.0..3> use pin for interrupt/event
//        <i> Default: pin = PA0
//          <0=>         pin = PA0
//          <1=>         pin = PB0
//          <2=>         pin = PC0
//          <3=>         pin = PD0
//          <4=>         pin = PE0
//          <5=>         pin = PF0
//          <6=>         pin = PG0
//          <7=>         pin = PH0
//          <8=>         pin = PI0
//   </e>

//--------------------------------------------------------------------------- EXTI line 1
//   <e1.1> EXTI1: EXTI line 1 enable
//     <o2.1> interrupt enable (NVIC)
//     <o3.1> generate interrupt (IMR)
//     <o4.1> generate event
//     <o5.1> use rising trigger for interrupt/event
//     <o6.1> use falling trigger for interrupt/event
//     <o7.4..7> use pin for interrupt/event
//        <i> Default: pin = PA1
//          <0=>         pin = PA1
//          <1=>         pin = PB1
//          <2=>         pin = PC1
//          <3=>         pin = PD1
//          <4=>         pin = PE1
//          <5=>         pin = PF1
//          <6=>         pin = PG1
//          <7=>         pin = PH1
//          <8=>         pin = PI1
//   </e>

//--------------------------------------------------------------------------- EXTI line 2
//   <e1.2> EXTI2: EXTI line 2 enable
//     <o2.2> interrupt enable (NVIC)
//     <o3.2> generate interrupt (IMR)
//     <o4.2> generate event
//     <o5.2> use rising trigger for interrupt/event
//     <o6.2> use falling trigger for interrupt/event
//     <o7.8..11> use pin for interrupt/event
//        <i> Default: pin = PA2
//          <0=>         pin = PA2
//          <1=>         pin = PB2
//          <2=>         pin = PC2
//          <3=>         pin = PD2
//          <4=>         pin = PE2
//          <5=>         pin = PF2
//          <6=>         pin = PG2
//          <7=>         pin = PH2
//          <8=>         pin = PI2
//   </e>

//--------------------------------------------------------------------------- EXTI line 3
//   <e1.3> EXTI3: EXTI line 3 enable
//     <o2.3> interrupt enable (NVIC)
//     <o3.3> generate interrupt (IMR)
//     <o4.3> generate event
//     <o5.3> use rising trigger for interrupt/event
//     <o6.3> use falling trigger for interrupt/event
//     <o7.12..15> use pin for interrupt/event
//        <i> Default: pin = PA3
//          <0=>         pin = PA3
//          <1=>         pin = PB3
//          <2=>         pin = PC3
//          <3=>         pin = PD3
//          <4=>         pin = PE3
//          <5=>         pin = PF3
//          <6=>         pin = PG3
//          <7=>         pin = PH3
//          <8=>         pin = PI3
//   </e>

//--------------------------------------------------------------------------- EXTI line 4
//   <e1.4> EXTI4: EXTI line 4 enable
//     <o2.4> interrupt enable (NVIC)
//     <o3.4> generate interrupt (IMR)
//     <o4.4> generate event
//     <o5.4> use rising trigger for interrupt/event
//     <o6.4> use falling trigger for interrupt/event
//     <o8.0..3> use pin for interrupt/event
//        <i> Default: pin = PA4
//          <0=>         pin = PA4
//          <1=>         pin = PB4
//          <2=>         pin = PC4
//          <3=>         pin = PD4
//          <4=>         pin = PE4
//          <5=>         pin = PF4
//          <6=>         pin = PG4
//          <7=>         pin = PH4
//          <8=>         pin = PI4
//   </e>

//--------------------------------------------------------------------------- EXTI line 5
//   <e1.5> EXTI5: EXTI line 5 enable
//     <o2.5> interrupt enable (NVIC)
//     <o3.5> generate interrupt (IMR)
//     <o4.5> generate event
//     <o5.5> use rising trigger for interrupt/event
//     <o6.5> use falling trigger for interrupt/event
//     <o8.4..7> use pin for interrupt/event
//        <i> Default: pin = PA5
//          <0=>         pin = PA5
//          <1=>         pin = PB5
//          <2=>         pin = PC5
//          <3=>         pin = PD5
//          <4=>         pin = PE5
//          <5=>         pin = PF5
//          <6=>         pin = PG5
//          <7=>         pin = PH5
//          <8=>         pin = PI5
//   </e>

//--------------------------------------------------------------------------- EXTI line 6
//   <e1.6> EXTI6: EXTI line 6 enable
//     <o2.6> interrupt enable (NVIC)
//     <o3.6> generate interrupt (IMR)
//     <o4.6> generate event
//     <o5.6> use rising trigger for interrupt/event
//     <o6.6> use falling trigger for interrupt/event
//     <o8.8..11> use pin for interrupt/event
//        <i> Default: pin = PA6
//          <0=>         pin = PA6
//          <1=>         pin = PB6
//          <2=>         pin = PC6
//          <3=>         pin = PD6
//          <4=>         pin = PE6
//          <5=>         pin = PF6
//          <6=>         pin = PG6
//          <7=>         pin = PH6
//          <8=>         pin = PI6
//   </e>

//--------------------------------------------------------------------------- EXTI line 7
//   <e1.7> EXTI7: EXTI line 7 enable
//     <o2.7> interrupt enable (NVIC)
//     <o3.7> generate interrupt (IMR)
//     <o4.7> generate event
//     <o5.7> use rising trigger for interrupt/event
//     <o6.7> use falling trigger for interrupt/event
//     <o8.12..15> use pin for interrupt/event
//        <i> Default: pin = PA7
//          <0=>         pin = PA7
//          <1=>         pin = PB7
//          <2=>         pin = PC7
//          <3=>         pin = PD7
//          <4=>         pin = PE7
//          <5=>         pin = PF7
//          <6=>         pin = PG7
//          <7=>         pin = PH7
//          <8=>         pin = PI7
//   </e>

//--------------------------------------------------------------------------- EXTI line 8
//   <e1.8> EXTI8: EXTI line 8 enable
//     <o2.8> interrupt enable (NVIC)
//     <o3.8> generate interrupt (IMR)
//     <o4.8> generate event
//     <o5.8> use rising trigger for interrupt/event
//     <o6.8> use falling trigger for interrupt/event
//     <o9.0..3> use pin for interrupt/event
//        <i> Default: pin = PA8
//          <0=>         pin = PA8
//          <1=>         pin = PB8
//          <2=>         pin = PC8
//          <3=>         pin = PD8
//          <4=>         pin = PE8
//          <5=>         pin = PF8
//          <6=>         pin = PG8
//          <7=>         pin = PH8
//          <8=>         pin = PI8
//   </e>

//--------------------------------------------------------------------------- EXTI line 9
//   <e1.9> EXTI9: EXTI line 9 enable
//     <o2.9> interrupt enable (NVIC)
//     <o3.9> generate interrupt (IMR)
//     <o4.9> generate event
//     <o5.9> use rising trigger for interrupt/event
//     <o6.9> use falling trigger for interrupt/event
//     <o9.4..7> use pin for interrupt/event
//        <i> Default: pin = PA9
//          <0=>         pin = PA9
//          <1=>         pin = PB9
//          <2=>         pin = PC9
//          <3=>         pin = PD9
//          <4=>         pin = PE9
//          <5=>         pin = PF9
//          <6=>         pin = PG9
//          <7=>         pin = PH9
//          <8=>         pin = PI9
//   </e>

//--------------------------------------------------------------------------- EXTI line 10
//   <e1.10> EXTI10: EXTI line 10 enable
//     <o2.10> interrupt enable (NVIC)
//     <o3.10> generate interrupt (IMR)
//     <o4.10> generate event
//     <o5.10> use rising trigger for interrupt/event
//     <o6.10> use falling trigger for interrupt/event
//     <o9.8..11> use pin for interrupt/event
//        <i> Default: pin = PA10
//          <0=>         pin = PA10
//          <1=>         pin = PB10
//          <2=>         pin = PC10
//          <3=>         pin = PD10
//          <4=>         pin = PE10
//          <5=>         pin = PF10
//          <6=>         pin = PG10
//          <7=>         pin = PH10
//          <8=>         pin = PI10
//   </e>

//--------------------------------------------------------------------------- EXTI line 11
//   <e1.11> EXTI11: EXTI line 11 enable
//     <o2.11> interrupt enable (NVIC)
//     <o3.11> generate interrupt (IMR)
//     <o4.11> generate event
//     <o5.11> use rising trigger for interrupt/event
//     <o6.11> use falling trigger for interrupt/event
//     <o9.12..15> use pin for interrupt/event
//        <i> Default: pin = PA11
//          <0=>         pin = PA11
//          <1=>         pin = PB11
//          <2=>         pin = PC11
//          <3=>         pin = PD11
//          <4=>         pin = PE11
//          <5=>         pin = PF11
//          <6=>         pin = PG11
//          <7=>         pin = PH11
//          <8=>         pin = PI11
//   </e>

//--------------------------------------------------------------------------- EXTI line 12
//   <e1.12> EXTI12: EXTI line 12 enable
//     <o2.12> interrupt enable (NVIC)
//     <o3.12> generate interrupt (IMR)
//     <o4.12> generate event
//     <o5.12> use rising trigger for interrupt/event
//     <o6.12> use falling trigger for interrupt/event
//     <o10.0..3> use pin for interrupt/event
//        <i> Default: pin = PA12
//          <0=>         pin = PA12
//          <1=>         pin = PB12
//          <2=>         pin = PC12
//          <3=>         pin = PD12
//          <4=>         pin = PE12
//          <5=>         pin = PF12
//          <6=>         pin = PG12
//          <7=>         pin = PH12
//          <8=>         pin = PI12
//   </e>

//--------------------------------------------------------------------------- EXTI line 13
//   <e1.13> EXTI13: EXTI line 13 enable
//     <o2.13> interrupt enable (NVIC)
//     <o3.13> generate interrupt (IMR)
//     <o4.13> generate event
//     <o5.13> use rising trigger for interrupt/event
//     <o6.13> use falling trigger for interrupt/event
//     <o10.4..7> use pin for interrupt/event
//        <i> Default: pin = PA13
//          <0=>         pin = PA13
//          <1=>         pin = PB13
//          <2=>         pin = PC13
//          <3=>         pin = PD13
//          <4=>         pin = PE13
//          <5=>         pin = PF13
//          <6=>         pin = PG13
//          <7=>         pin = PH13
//          <8=>         pin = PI13
//   </e>

//--------------------------------------------------------------------------- EXTI line 14
//   <e1.14> EXTI14: EXTI line 14 enable
//     <o2.14> interrupt enable (NVIC)
//     <o3.14> generate interrupt (IMR)
//     <o4.14> generate event
//     <o5.14> use rising trigger for interrupt/event
//     <o6.14> use falling trigger for interrupt/event
//     <o10.8..11> use pin for interrupt/event
//        <i> Default: pin = PA14
//          <0=>         pin = PA14
//          <1=>         pin = PB14
//          <2=>         pin = PC14
//          <3=>         pin = PD14
//          <4=>         pin = PE14
//          <5=>         pin = PF14
//          <6=>         pin = PG14
//          <7=>         pin = PH14
//          <8=>         pin = PI14
//   </e>

//--------------------------------------------------------------------------- EXTI line 15
//   <e1.15> EXTI15: EXTI line 15 enable
//     <o2.15> interrupt enable (NVIC)
//     <o3.15> generate interrupt (IMR)
//     <o4.15> generate event
//     <o5.15> use rising trigger for interrupt/event
//     <o6.15> use falling trigger for interrupt/event
//     <o10.12..15> use pin for interrupt/event
//        <i> Default: pin = PA15
//          <0=>         pin = PA15
//          <1=>         pin = PB15
//          <2=>         pin = PC15
//          <3=>         pin = PD15
//          <4=>         pin = PE15
//          <5=>         pin = PF15
//          <6=>         pin = PG15
//          <7=>         pin = PH15
//          <8=>         pin = PI15
//   </e>

//--------------------------------------------------------------------------- EXTI line 16
//   <e1.16> EXTI16: EXTI line 16 (PVD) enable
//     <o2.16> interrupt enable (NVIC)
//     <o3.16> generate interrupt (IMR)
//     <o4.16> generate event
//     <o5.16> use rising trigger for interrupt/event
//     <o6.16> use falling trigger for interrupt/event
//   </e>

//--------------------------------------------------------------------------- EXTI line 17
//   <e1.17> EXTI17: EXTI line 17 (RTC Alarm Event) enable 
//     <o2.17> interrupt enable (NVIC)
//     <o3.17> generate interrupt (IMR)
//     <o4.17> generate event
//     <o5.17> use rising trigger for interrupt/event
//     <o6.17> use falling trigger for interrupt/event
//   </e>

// </e> End of External interrupt/event Configuration
#define __EXTI_SETUP              0                       //  0
#define __EXTI_USED               0x00001                 //  1
#define __EXTI_INTERRUPTS         0x00000001              //  2
#define __EXTI_IMR                0x00000001              //  3
#define __EXTI_EMR                0x00000000              //  4
#define __EXTI_RTSR               0x00000001              //  5
#define __EXTI_FTSR               0x00000001              //  6
#define __SYSCFG_EXTICR1          0x00000000              //  7
#define __SYSCFG_EXTICR2          0x00000000              //  8
#define __SYSCFG_EXTICR3          0x00000000              //  9
#define __SYSCFG_EXTICR4          0x00000000              // 10

#if __EXTI_SETUP
/*----------------------------------------------------------------------------
 STM32 EXTI setup.
 initializes the EXTI register
 *----------------------------------------------------------------------------*/
__inline static void stm32_ExtiSetup (void) {
                                                    
#if __EXTI_USED
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                    // enable clock for System Configuration

  if (__EXTI_USED & 0x0000000F) {                            // some of EXTI0 ~ 3 used
    SYSCFG->EXTICR[0] =  __SYSCFG_EXTICR1;         // set pin to use
	}
  if (__EXTI_USED & 0x000000F0) {                            // some of EXTI4 ~ 7 used
    SYSCFG->EXTICR[1] = __SYSCFG_EXTICR2;         // set pin to use
	}
  if (__EXTI_USED & 0x00000F00) {                            // some of EXTI8 ~ 11 used
    SYSCFG->EXTICR[2] = __SYSCFG_EXTICR3;         // set pin to use
	}
  if (__EXTI_USED & 0x0000F000) {                            // some of EXTI12 ~ 15 used
    SYSCFG->EXTICR[3] = __SYSCFG_EXTICR4;         // set pin to use
	}
	
    EXTI->IMR       |= (__EXTI_USED & __EXTI_IMR);             // unmask interrupt
    EXTI->EMR       |= (__EXTI_USED & __EXTI_EMR);             // unmask event
    EXTI->RTSR      |= (__EXTI_USED & __EXTI_RTSR);            // set rising edge
    EXTI->FTSR      |= (__EXTI_USED & __EXTI_FTSR);            // set falling edge
	
#endif   // #if __EXTI_USED	
	
#define NVIC_interrupts (__EXTI_INTERRUPTS & __EXTI_USED)
    if (NVIC_interrupts & bit(0)) {                     // interrupt used
      NVIC->ISER[0]  = (1 << (EXTI0_IRQn & 0x1F));    // enable interrupt EXTI 0
    }
    if (NVIC_interrupts & bit(1)) {                     // interrupt used
      NVIC->ISER[0]  = (1 << (EXTI1_IRQn & 0x1F));    // enable interrupt EXTI 1
    }
     if (NVIC_interrupts & bit(2)) {                     // interrupt used
      NVIC->ISER[0]  = (1 << (EXTI2_IRQn & 0x1F));    // enable interrupt EXTI 2
    }
     if (NVIC_interrupts & bit(3)) {                     // interrupt used
      NVIC->ISER[0]  = (1 << (EXTI3_IRQn & 0x1F));    // enable interrupt EXTI 3
    }
    if (NVIC_interrupts & bit(4)) {                     // interrupt used
      NVIC->ISER[0]  = (1 << (EXTI4_IRQn & 0x1F));    // enable interrupt EXTI 4
    }
    if (NVIC_interrupts & 0x03E0) {                     // interrupt used EXTI 5~9
      NVIC->ISER[0]  = (1 << (EXTI9_5_IRQn & 0x1F));  // enable interrupt EXTI 9..5
    }

    if (NVIC_interrupts & 0xFC00) {                    // interrupt used EXTI 10~15
      NVIC->ISER[1]  = (1 << (EXTI15_10_IRQn & 0x1F));// enable interrupt EXTI 10..15
    }

    if (NVIC_interrupts & bit(16)) {                    // interrupt used
      NVIC->ISER[1]  = (1 << (PVD_IRQn & 0x1F));// enable interrupt PVD
    }
    if (NVIC_interrupts & bit(17)) {                    // interrupt used
      NVIC->ISER[1]  = (1 << (RTC_Alarm_IRQn & 0x1F));					// enable interrupt RTC Alarm Event
    }

} // end of stm32_ExtiSetup
#endif

//==========================
//--------------------------------------------------------------------------- GPIO port G
//   <e7> GPIO_i : GPIO port i configuration
//     <o0>   Port label of GPIO i 
//                 <0=> PORT A 
//                 <1=> PORT B 
//                 <2=> PORT C 
//                 <3=> PORT D 
//                 <4=> PORT E 
//                 <5=> PORT F 
//                 <6=> PORT G 
//                 <7=> PORT H 
//                 <8=> PORT I 
//                 <9=> PORT J 
//                 <10=> PORT K 
//--------------------------
//==========================
//     <h>   Pin 0 used as 
//       <o1.0..1> MODRER0: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.0..1> PUPDR0: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 0 as Output or Alternate Function
//         <o3.0> OT0: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.0..1> OSPEEDR0: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.0..3> AFRL0: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 1 used as 
//       <o1.2..3> MODRER1: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.2..3> PUPDR1: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 1 as Output or Alternate Function
//         <o3.1> OT1: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.2..3> OSPEEDR1: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.4..7> AFRL1: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 2 used as 
//       <o1.4..5> MODRER2: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.4..5> PUPDR2: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 2 as Output or Alternate Function
//         <o3.2> OT2: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.4..5> OSPEEDR2: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.8..11> AFRL2: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 3 used as 
//       <o1.6..7> MODRER3: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.6..7> PUPDR3: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 3 as Output or Alternate Function
//         <o3.3> OT3: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.6..7> OSPEEDR3: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.12..15> AFRL3: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 4 used as 
//       <o1.8..9> MODRER4: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.8..9> PUPDR4: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 4 as Output or Alternate Function
//         <o3.0> OT4: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.8..9> OSPEEDR4: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.16..19> AFRL4: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 5 used as 
//       <o1.10..11> MODRER5: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.10..11> PUPDR5: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 5 as Output or Alternate Function
//         <o3.5> OT5: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.10..11> OSPEEDR5: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.20..23> AFRL5: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 6 used as 
//       <o1.12..13> MODRER6: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.12..13> PUPDR6: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 6 as Output or Alternate Function
//         <o3.6> OT6: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.12..13> OSPEEDR6: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.24..27> AFRL6: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 7 used as 
//       <o1.14..15> MODRER7: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.14..15> PUPDR7: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 7 as Output or Alternate Function
//         <o3.7> OT7: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.14..15> OSPEEDR7: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o5.28..31> AFRL7: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 8 used as 
//       <o1.16..17> MODRER8: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.16..17> PUPDR8: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 8 as Output or Alternate Function
//         <o3.8> OT8: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.16..17> OSPEEDR8: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.0..3> AFRH8: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 9 used as 
//       <o1.18..19> MODRER9: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.18..19> PUPDR9: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 9 as Output or Alternate Function
//         <o3.9> OT9: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.18..19> OSPEEDR9: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.4..7> AFRH9: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 10 used as 
//       <o1.20..21> MODRER10: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.20..21> PUPDR10: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 10 as Output or Alternate Function
//         <o3.10> OT10: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.20..21> OSPEEDR10: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.8..11> AFRH10: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 11 used as 
//       <o1.22..23> MODRER11: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.22..23> PUPDR11: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 11 as Output or Alternate Function
//         <o3.11> OT11: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.22..23> OSPEEDR11: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.12..15> AFRH11: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 12 used as 
//       <o1.24..25> MODRER12: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.24..25> PUPDR12: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 12 as Output or Alternate Function
//         <o3.12> OT12: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.24..25> OSPEEDR12: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.16..19> AFRH12: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 13 used as 
//       <o1.26..27> MODRER13: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.26..27> PUPDR13: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 13 as Output or Alternate Function
//         <o3.13> OT13: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.26..27> OSPEEDR13: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.20..23> AFRH13: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 14 used as 
//       <o1.28..29> MODRER14: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.28..29> PUPDR14: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 14 as Output or Alternate Function
//         <o3.14> OT14: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.28..29> OSPEEDR14: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.24..27> AFRH14: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//==========================
//     <h>   Pin 15 used as 
//       <o1.30..31> MODRER15: mode
//                 <0=> Input (reset mode)
//                 <1=> Output
//                 <2=> Alternate Function
//                 <3=> Analog (power saving)
//       <o2.30..31> PUPDR15: pull-up/pull-down
//          <i> "NO pull-up/down" for Analog
//                 <0=> no pull-up/down 
//                 <1=> pull-up
//                 <2=> pull-down
//       <h> Pin 15 as Output or Alternate Function
//         <o3.15> OT15: output type
//                 <0=> push-pull 
//                 <1=> open-drain
//         <o4.30..31> OSPEEDR15: output speed
//                 <0=> low 
//                 <1=> medium
//                 <2=> fast
//                 <2=> high
//       </h> 
//       <o6.28..31> AFRH15: alternate function selection 
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0(system) 
//                 <1=> AF1(TIM1/TIM2) 
//                 <2=> AF2(TIM3..5) 
//                 <3=> AF3(TIM8..11) 
//                 <4=> AF4(I2C1..3) 
//                 <5=> AF5(SPI1/SPI2) 
//                 <6=> AF6(SPI3) 
//                 <7=> AF7(USART1..3) 
//                 <8=> AF8(USART4..6) 
//                 <9=> AF9(CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//     </h>
//    </e>
#define __GPIO_i_PORT_num         3
#define __GPIO_i_MODER            0x55FFFFFF
#define __GPIO_i_UD               0x00000000
#define __GPIO_i_PPOD             0x00000000
#define __GPIO_i_SPEED            0xAA000000
#define __GPIO_i_AFRL             0x00000000
#define __GPIO_i_AFRH             0x00000000
#define __GPIO_i_USED             0x00000000
//--------------------------------------------------------------------------- GPIO port G
//   <e7> GPIO_j : GPIO port j configuration
//     <o0>   Port label of GPIO j 
//                 <0=> PORT A 
//                 <1=> PORT B 
//                 <2=> PORT C 
//                 <3=> PORT D 
//                 <4=> PORT E 
//                 <5=> PORT F 
//                 <6=> PORT G 
//                 <7=> PORT H 
//                 <8=> PORT I 
//                 <9=> PORT J 
//                 <10=> PORT K 
//==========================
//     <h> IMPORTANT: check PINS of GPIO_j (to be NEWLY configured)
//          <i> You should CHECK the pin no. that you want to configure!!! 
//         <q8.0>  pin 0  
//         <q8.1>  pin 1  
//         <q8.2>  pin 2  
//         <q8.3>  pin 3  
//         <q8.4>  pin 4  
//         <q8.5>  pin 5  
//         <q8.6>  pin 6  
//         <q8.7>  pin 7  
//         <q8.8>  pin 8  
//         <q8.9>  pin 9  
//         <q8.10>  pin 10  
//         <q8.11>  pin 11  
//         <q8.12>  pin 12  
//         <q8.13>  pin 13  
//         <q8.14>  pin 14  
//         <q8.15>  pin 15  
//     </h>
//--------------------------
//       <o1.0..4> **Pin 0 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [0] Analog or NOT used
//                 <0x00=> [0] In: Floating (reset mode)
//                 <0x04=> [0] In: Pull Up
//                 <0x08=> [0] In: Pull Down
//                 <0x01=> [0] Out PP: no Pull
//                 <0x05=> [0] Out PP: Pull Up
//                 <0x09=> [0] Out PP: Pull Down
//                 <0x11=> [0] Out OD: no Pull
//                 <0x15=> [0] Out OD: Pull Up
//                 <0x19=> [0] Out OD: Pull Down
//                 <0x02=> [0] AF PP: no Pull
//                 <0x06=> [0] AF PP: Pull Up
//                 <0x0A=> [0] AF PP: Pull Down
//                 <0x12=> [0] AF OD: no Pull
//                 <0x16=> [0] AF OD: Pull Up
//                 <0x1A=> [0] AF OD: Pull Down
//       <o4.0..1> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.0..3> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//    </e>
#define __GPIO_j_PORT_num         0								//0
#define jtmp1               0x06318C68						//1
#define jtmp2               0x06318C63						//2
#define jtmp3               0x00018C63						//3
#define __GPIO_j_SPEED            0x00000000			//4
#define __GPIO_j_AFRL             0x00000000			//5
#define __GPIO_j_AFRH             0x00000000			//6
#define __GPIO_j_USED             0x00000001			//7
#define __GPIO_j_pinChg1           0x00000001			//8

#define __GPIO_j_PPOD  ( ((jtmp1&bit(4))>>4) | ((jtmp1&bit(9))>>8)  \
         | ((jtmp1&bit(14))>>12) | ((jtmp1&bit(19))>>16)  \
         | ((jtmp1&bit(24))>>20) | ((jtmp1&bit(29))>>24)  \
         | ((jtmp2&bit(4))<<(6-4)) | ((jtmp2&bit(9))>>(9-7))  \
         | ((jtmp2&bit(14))>>(14-8)) | ((jtmp2&bit(19))>>(19-9))  \
         | ((jtmp2&bit(24))>>(24-10)) | ((jtmp2&bit(29))>>(29-11))\
         | ((jtmp3&bit(4))<<(12-4)) | ((jtmp3&bit(9))<<(13-9))  \
         | ((jtmp3&bit(14))) | ((jtmp3&bit(19))>>(19-15))  )
#define __GPIO_j_MODER ( (jtmp1&bit2(0)) | ((jtmp1&bit2(5))>>3) \
         |((jtmp1&bit2(10))>>(10-4)) | ((jtmp1&bit2(15))>>(15-6))  \
         |((jtmp1&bit2(20))>>(20-8)) | ((jtmp1&bit2(25))>>(25-10))  \
         |((jtmp2&bit2(0))<<(12)) | ((jtmp2&bit2(5))<<(14-5))  \
         |((jtmp2&bit2(10))<<(16-10)) | ((jtmp2&bit2(15))<<(18-15))  \
         |(jtmp2&bit2(20)) | ((jtmp2&bit2(25))>>(25-22))\
         |((jtmp3&bit2(0))<<(24)) | ((jtmp3&bit2(5))<<(26-5))  \
         |((jtmp3&bit2(10))<<(28-10)) | ((jtmp3&bit2(15))<<(30-15)) )
#define __GPIO_j_UD (((jtmp1&bit2(2))>>2) | ((jtmp1&bit2(7))>>(7-2)) \
         |((jtmp1&bit2(12))>>(12-4)) | ((jtmp1&bit2(17))>>(17-6))  \
         |((jtmp1&bit2(22))>>(22-8)) | ((jtmp1&bit2(27))>>(27-10))  \
         |((jtmp2&bit2(2))<<(12-2)) | ((jtmp2&bit2(7))<<(14-7))  \
         |((jtmp2&bit2(12))<<(16-12)) | ((jtmp2&bit2(17))<<(18-17))  \
         |((jtmp2&bit2(22))>>(22-20)) | ((jtmp2&bit2(27))>>(27-22))\
         |((jtmp3&bit2(2))<<(24-2)) | ((jtmp3&bit2(7))<<(26-7))  \
         |((jtmp3&bit2(12))<<(28-12)) | ((jtmp3&bit2(17))<<(30-17))  )


//--------------------------------------------------------------------------- GPIO port G
//   <e7> GPIO_k : GPIO port k configuration
//     <o0>   _____port label of GPIO_k 
//                 <0=> PORT A 
//                 <1=> PORT B 
//                 <2=> PORT C 
//                 <3=> PORT D 
//                 <4=> PORT E 
//                 <5=> PORT F 
//                 <6=> PORT G 
//                 <7=> PORT H 
//                 <8=> PORT I 
//                 <9=> PORT J 
//                 <10=> PORT K 
//==========================
//     <h> IMPORTANT: check PINS of GPIO_k (to be NEWLY configured)
//          <i> You should CHECK the pin no. that you want to configure!!! 
//         <q8.0>  pin 0  
//         <q8.1>  pin 1  
//         <q8.2>  pin 2  
//         <q8.3>  pin 3  
//         <q8.4>  pin 4  
//         <q8.5>  pin 5  
//         <q8.6>  pin 6  
//         <q8.7>  pin 7  
//         <q8.8>  pin 8  
//         <q8.9>  pin 9  
//         <q8.10>  pin 10  
//         <q8.11>  pin 11  
//         <q8.12>  pin 12  
//         <q8.13>  pin 13  
//         <q8.14>  pin 14  
//         <q8.15>  pin 15  
//     </h>
//==========================
//       <o1.0..4> **Pin 0 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [0] Analog or NOT used
//                 <0x00=> [0] In: Floating (reset mode)
//                 <0x04=> [0] In: Pull Up
//                 <0x08=> [0] In: Pull Down
//                 <0x01=> [0] Out PP: no Pull
//                 <0x05=> [0] Out PP: Pull Up
//                 <0x09=> [0] Out PP: Pull Down
//                 <0x11=> [0] Out OD: no Pull
//                 <0x15=> [0] Out OD: Pull Up
//                 <0x19=> [0] Out OD: Pull Down
//                 <0x02=> [0] AF PP: no Pull
//                 <0x06=> [0] AF PP: Pull Up
//                 <0x0A=> [0] AF PP: Pull Down
//                 <0x12=> [0] AF OD: no Pull
//                 <0x16=> [0] AF OD: Pull Up
//                 <0x1A=> [0] AF OD: Pull Down
//       <o4.0..1> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.0..3> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o1.5..9> **Pin 1 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [1] Analog or NOT used
//                 <0x00=> [1] In: Floating (reset mode)
//                 <0x04=> [1] In: Pull Up
//                 <0x08=> [1] In: Pull Down
//                 <0x01=> [1] Out PP: no Pull
//                 <0x05=> [1] Out PP: Pull Up
//                 <0x09=> [1] Out PP: Pull Down
//                 <0x11=> [1] Out OD: no Pull
//                 <0x15=> [1] Out OD: Pull Up
//                 <0x19=> [1] Out OD: Pull Down
//                 <0x02=> [1] AF PP: no Pull
//                 <0x06=> [1] AF PP: Pull Up
//                 <0x0A=> [1] AF PP: Pull Down
//                 <0x12=> [1] AF OD: no Pull
//                 <0x16=> [1] AF OD: Pull Up
//                 <0x1A=> [1] AF OD: Pull Down
//       <o4.2..3> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.4..7> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o1.10..14> **Pin 2 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [2] Analog or NOT used
//                 <0x00=> [2] In: Floating (reset mode)
//                 <0x04=> [2] In: Pull Up
//                 <0x08=> [2] In: Pull Down
//                 <0x01=> [2] Out PP: no Pull
//                 <0x05=> [2] Out PP: Pull Up
//                 <0x09=> [2] Out PP: Pull Down
//                 <0x11=> [2] Out OD: no Pull
//                 <0x15=> [2] Out OD: Pull Up
//                 <0x19=> [2] Out OD: Pull Down
//                 <0x02=> [2] AF PP: no Pull
//                 <0x06=> [2] AF PP: Pull Up
//                 <0x0A=> [2] AF PP: Pull Down
//                 <0x12=> [2] AF OD: no Pull
//                 <0x16=> [2] AF OD: Pull Up
//                 <0x1A=> [2] AF OD: Pull Down
//       <o4.4..5> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.8..11> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o1.15..19> **Pin 3 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [3] Analog or NOT used
//                 <0x00=> [3] In: Floating (reset mode)
//                 <0x04=> [3] In: Pull Up
//                 <0x08=> [3] In: Pull Down
//                 <0x01=> [3] Out PP: no Pull
//                 <0x05=> [3] Out PP: Pull Up
//                 <0x09=> [3] Out PP: Pull Down
//                 <0x11=> [3] Out OD: no Pull
//                 <0x15=> [3] Out OD: Pull Up
//                 <0x19=> [3] Out OD: Pull Down
//                 <0x02=> [3] AF PP: no Pull
//                 <0x06=> [3] AF PP: Pull Up
//                 <0x0A=> [3] AF PP: Pull Down
//                 <0x12=> [3] AF OD: no Pull
//                 <0x16=> [3] AF OD: Pull Up
//                 <0x1A=> [3] AF OD: Pull Down
//       <o4.6..7> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.12..15> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o1.20..24> **Pin 4 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [4] Analog or NOT used
//                 <0x00=> [4] In: Floating (reset mode)
//                 <0x04=> [4] In: Pull Up
//                 <0x08=> [4] In: Pull Down
//                 <0x01=> [4] Out PP: no Pull
//                 <0x05=> [4] Out PP: Pull Up
//                 <0x09=> [4] Out PP: Pull Down
//                 <0x11=> [4] Out OD: no Pull
//                 <0x15=> [4] Out OD: Pull Up
//                 <0x19=> [4] Out OD: Pull Down
//                 <0x02=> [4] AF PP: no Pull
//                 <0x06=> [4] AF PP: Pull Up
//                 <0x0A=> [4] AF PP: Pull Down
//                 <0x12=> [4] AF OD: no Pull
//                 <0x16=> [4] AF OD: Pull Up
//                 <0x1A=> [4] AF OD: Pull Down
//       <o4.8..9> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.16..19> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o1.25..29> **Pin 5 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [5] Analog or NOT used
//                 <0x00=> [5] In: Floating (reset mode)
//                 <0x04=> [5] In: Pull Up
//                 <0x08=> [5] In: Pull Down
//                 <0x01=> [5] Out PP: no Pull
//                 <0x05=> [5] Out PP: Pull Up
//                 <0x09=> [5] Out PP: Pull Down
//                 <0x11=> [5] Out OD: no Pull
//                 <0x15=> [5] Out OD: Pull Up
//                 <0x19=> [5] Out OD: Pull Down
//                 <0x02=> [5] AF PP: no Pull
//                 <0x06=> [5] AF PP: Pull Up
//                 <0x0A=> [5] AF PP: Pull Down
//                 <0x12=> [5] AF OD: no Pull
//                 <0x16=> [5] AF OD: Pull Up
//                 <0x1A=> [5] AF OD: Pull Down
//       <o4.10..11> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.20..23> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//           ^^^^----------------------
//       <o2.0..4> **Pin 6 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [6] Analog or NOT used
//                 <0x00=> [6] In: Floating (reset mode)
//                 <0x04=> [6] In: Pull Up
//                 <0x08=> [6] In: Pull Down
//                 <0x01=> [6] Out PP: no Pull
//                 <0x05=> [6] Out PP: Pull Up
//                 <0x09=> [6] Out PP: Pull Down
//                 <0x11=> [6] Out OD: no Pull
//                 <0x15=> [6] Out OD: Pull Up
//                 <0x19=> [6] Out OD: Pull Down
//                 <0x02=> [6] AF PP: no Pull
//                 <0x06=> [6] AF PP: Pull Up
//                 <0x0A=> [6] AF PP: Pull Down
//                 <0x12=> [6] AF OD: no Pull
//                 <0x16=> [6] AF OD: Pull Up
//                 <0x1A=> [6] AF OD: Pull Down
//       <o4.12..13> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.24..27> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o2.5..9> **Pin 7 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [7] Analog or NOT used
//                 <0x00=> [7] In: Floating (reset mode)
//                 <0x04=> [7] In: Pull Up
//                 <0x08=> [7] In: Pull Down
//                 <0x01=> [7] Out PP: no Pull
//                 <0x05=> [7] Out PP: Pull Up
//                 <0x09=> [7] Out PP: Pull Down
//                 <0x11=> [7] Out OD: no Pull
//                 <0x15=> [7] Out OD: Pull Up
//                 <0x19=> [7] Out OD: Pull Down
//                 <0x02=> [7] AF PP: no Pull
//                 <0x06=> [7] AF PP: Pull Up
//                 <0x0A=> [7] AF PP: Pull Down
//                 <0x12=> [7] AF OD: no Pull
//                 <0x16=> [7] AF OD: Pull Up
//                 <0x1A=> [7] AF OD: Pull Down
//       <o4.14..15> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o5.28..31> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o2.10..14> **Pin 8 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [8] Analog or NOT used
//                 <0x00=> [8] In: Floating (reset mode)
//                 <0x04=> [8] In: Pull Up
//                 <0x08=> [8] In: Pull Down
//                 <0x01=> [8] Out PP: no Pull
//                 <0x05=> [8] Out PP: Pull Up
//                 <0x09=> [8] Out PP: Pull Down
//                 <0x11=> [8] Out OD: no Pull
//                 <0x15=> [8] Out OD: Pull Up
//                 <0x19=> [8] Out OD: Pull Down
//                 <0x02=> [8] AF PP: no Pull
//                 <0x06=> [8] AF PP: Pull Up
//                 <0x0A=> [8] AF PP: Pull Down
//                 <0x12=> [8] AF OD: no Pull
//                 <0x16=> [8] AF OD: Pull Up
//                 <0x1A=> [8] AF OD: Pull Down
//       <o4.16..17> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.0..3> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o2.15..19> **Pin 9 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [9] Analog or NOT used
//                 <0x00=> [9] In: Floating (reset mode)
//                 <0x04=> [9] In: Pull Up
//                 <0x08=> [9] In: Pull Down
//                 <0x01=> [9] Out PP: no Pull
//                 <0x05=> [9] Out PP: Pull Up
//                 <0x09=> [9] Out PP: Pull Down
//                 <0x11=> [9] Out OD: no Pull
//                 <0x15=> [9] Out OD: Pull Up
//                 <0x19=> [9] Out OD: Pull Down
//                 <0x02=> [9] AF PP: no Pull
//                 <0x06=> [9] AF PP: Pull Up
//                 <0x0A=> [9] AF PP: Pull Down
//                 <0x12=> [9] AF OD: no Pull
//                 <0x16=> [9] AF OD: Pull Up
//                 <0x1A=> [9] AF OD: Pull Down
//       <o4.18..19> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.4..7> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o2.20..24> **Pin 10 ========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [10] Analog or NOT used
//                 <0x00=> [10] In: Floating (reset mode)
//                 <0x04=> [10] In: Pull Up
//                 <0x08=> [10] In: Pull Down
//                 <0x01=> [10] Out PP: no Pull
//                 <0x05=> [10] Out PP: Pull Up
//                 <0x09=> [10] Out PP: Pull Down
//                 <0x11=> [10] Out OD: no Pull
//                 <0x15=> [10] Out OD: Pull Up
//                 <0x19=> [10] Out OD: Pull Down
//                 <0x02=> [10] AF PP: no Pull
//                 <0x06=> [10] AF PP: Pull Up
//                 <0x0A=> [10] AF PP: Pull Down
//                 <0x12=> [10] AF OD: no Pull
//                 <0x16=> [10] AF OD: Pull Up
//                 <0x1A=> [10] AF OD: Pull Down
//       <o4.20..21> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.8..11> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o2.25..29> **Pin 11 ========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [11] Analog or NOT used
//                 <0x00=> [11] In: Floating (reset mode)
//                 <0x04=> [11] In: Pull Up
//                 <0x08=> [11] In: Pull Down
//                 <0x01=> [11] Out PP: no Pull
//                 <0x05=> [11] Out PP: Pull Up
//                 <0x09=> [11] Out PP: Pull Down
//                 <0x11=> [11] Out OD: no Pull
//                 <0x15=> [11] Out OD: Pull Up
//                 <0x19=> [11] Out OD: Pull Down
//                 <0x02=> [11] AF PP: no Pull
//                 <0x06=> [11] AF PP: Pull Up
//                 <0x0A=> [11] AF PP: Pull Down
//                 <0x12=> [11] AF OD: no Pull
//                 <0x16=> [11] AF OD: Pull Up
//                 <0x1A=> [11] AF OD: Pull Down
//       <o4.22..23> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.12..15> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//           ^^^^----------------------
//       <o3.0..4> **Pin 12 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [12] Analog or NOT used
//                 <0x00=> [12] In: Floating (reset mode)
//                 <0x04=> [12] In: Pull Up
//                 <0x08=> [12] In: Pull Down
//                 <0x01=> [12] Out PP: no Pull
//                 <0x05=> [12] Out PP: Pull Up
//                 <0x09=> [12] Out PP: Pull Down
//                 <0x11=> [12] Out OD: no Pull
//                 <0x15=> [12] Out OD: Pull Up
//                 <0x19=> [12] Out OD: Pull Down
//                 <0x02=> [12] AF PP: no Pull
//                 <0x06=> [12] AF PP: Pull Up
//                 <0x0A=> [12] AF PP: Pull Down
//                 <0x12=> [12] AF OD: no Pull
//                 <0x16=> [12] AF OD: Pull Up
//                 <0x1A=> [12] AF OD: Pull Down
//       <o4.24..25> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.16..19> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o3.5..9> **Pin 13 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [13] Analog or NOT used
//                 <0x00=> [13] In: Floating (reset mode)
//                 <0x04=> [13] In: Pull Up
//                 <0x08=> [13] In: Pull Down
//                 <0x01=> [13] Out PP: no Pull
//                 <0x05=> [13] Out PP: Pull Up
//                 <0x09=> [13] Out PP: Pull Down
//                 <0x11=> [13] Out OD: no Pull
//                 <0x15=> [13] Out OD: Pull Up
//                 <0x19=> [13] Out OD: Pull Down
//                 <0x02=> [13] AF PP: no Pull
//                 <0x06=> [13] AF PP: Pull Up
//                 <0x0A=> [13] AF PP: Pull Down
//                 <0x12=> [13] AF OD: no Pull
//                 <0x16=> [13] AF OD: Pull Up
//                 <0x1A=> [13] AF OD: Pull Down
//       <o4.26..27> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.20..23> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o3.10..14> **Pin 14 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [14] Analog or NOT used
//                 <0x00=> [14] In: Floating (reset mode)
//                 <0x04=> [14] In: Pull Up
//                 <0x08=> [14] In: Pull Down
//                 <0x01=> [14] Out PP: no Pull
//                 <0x05=> [14] Out PP: Pull Up
//                 <0x09=> [14] Out PP: Pull Down
//                 <0x11=> [14] Out OD: no Pull
//                 <0x15=> [14] Out OD: Pull Up
//                 <0x19=> [14] Out OD: Pull Down
//                 <0x02=> [14] AF PP: no Pull
//                 <0x06=> [14] AF PP: Pull Up
//                 <0x0A=> [14] AF PP: Pull Down
//                 <0x12=> [14] AF OD: no Pull
//                 <0x16=> [14] AF OD: Pull Up
//                 <0x1A=> [14] AF OD: Pull Down
//       <o4.28..29> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.24..27> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//       <o3.15..19> **Pin 15 =========>
//          <i> bits [0:1] as MODE; 
//          <i> bits [2:3] as Pull Up/Down; 
//          <i> bits [4] as Push Pull/ Open Drain; 
//                 <0x03=> [15] Analog or NOT used
//                 <0x00=> [15] In: Floating (reset mode)
//                 <0x04=> [15] In: Pull Up
//                 <0x08=> [15] In: Pull Down
//                 <0x01=> [15] Out PP: no Pull
//                 <0x05=> [15] Out PP: Pull Up
//                 <0x09=> [15] Out PP: Pull Down
//                 <0x11=> [15] Out OD: no Pull
//                 <0x15=> [15] Out OD: Pull Up
//                 <0x19=> [15] Out OD: Pull Down
//                 <0x02=> [15] AF PP: no Pull
//                 <0x06=> [15] AF PP: Pull Up
//                 <0x0A=> [15] AF PP: Pull Down
//                 <0x12=> [15] AF OD: no Pull
//                 <0x16=> [15] AF OD: Pull Up
//                 <0x1A=> [15] AF OD: Pull Down
//       <o4.30..31> ^---- Speed for Out/AF:
//                 <0=> low (2MHz)
//                 <1=> medium (25MHz)
//                 <2=> fast (50MHz)
//                 <3=> high (100MHz)
//       <o6.28..31> ^---- Alternate Function:
//          <i> "AF0" for the mode other than Alternate Function
//                 <0=> AF0 (system) 
//                 <1=> AF1 (TIM1/TIM2) 
//                 <2=> AF2 (TIM3..5) 
//                 <3=> AF3 (TIM8..11) 
//                 <4=> AF4 (I2C1..3) 
//                 <5=> AF5 (SPI1/SPI2) 
//                 <6=> AF6 (SPI3) 
//                 <7=> AF7 (USART1..3) 
//                 <8=> AF8 (USART4..6) 
//                 <9=> AF9 (CAN1/CAN2, TIM12..14) 
//                 <10=> AF10(OTG_FS, OTG_HS) 
//                 <11=> AF11(ETH) 
//                 <12=> AF12(FSMC, SDIO, OTG_HS) 
//                 <13=> AF13(DCMI) 
//                 <14=> AF14 
//                 <15=> AF15(EVENTOUT) 
//           ^^^^----------------------
//           ^^^^----------------------
//    </e>
#define __GPIO_k_PORT_num         3								//0
#define ktmp1   0x06308C61												//1
#define ktmp2   0x06318C63												//2
#define ktmp3   0x00018C63												//3
#define __GPIO_k_SPEED            0x00000040			//4
#define __GPIO_k_AFRL             0x00000000			//5
#define __GPIO_k_AFRH             0x00000000			//6
#define __GPIO_k_USED             0x00000001			//7
#define __GPIO_k_pinChg1           0x00000008			//8

#define __GPIO_k_PPOD  ( ((ktmp1&bit(4))>>4) | ((ktmp1&bit(9))>>8)  \
         | ((ktmp1&bit(14))>>12) | ((ktmp1&bit(19))>>16)  \
         | ((ktmp1&bit(24))>>20) | ((ktmp1&bit(29))>>24)  \
         | ((ktmp2&bit(4))<<(6-4)) | ((ktmp2&bit(9))>>(9-7))  \
         | ((ktmp2&bit(14))>>(14-8)) | ((ktmp2&bit(19))>>(19-9))  \
         | ((ktmp2&bit(24))>>(24-10)) | ((ktmp2&bit(29))>>(29-11))\
         | ((ktmp3&bit(4))<<(12-4)) | ((ktmp3&bit(9))<<(13-9))  \
         | ((ktmp3&bit(14))) | ((ktmp3&bit(19))>>(19-15))  )
#define __GPIO_k_MODER ( (ktmp1&bit2(0)) | ((ktmp1&bit2(5))>>3) \
         |((ktmp1&bit2(10))>>(10-4)) | ((ktmp1&bit2(15))>>(15-6))  \
         |((ktmp1&bit2(20))>>(20-8)) | ((ktmp1&bit2(25))>>(25-10))  \
         |((ktmp2&bit2(0))<<(12)) | ((ktmp2&bit2(5))<<(14-5))  \
         |((ktmp2&bit2(10))<<(16-10)) | ((ktmp2&bit2(15))<<(18-15))  \
         |(ktmp2&bit2(20)) | ((ktmp2&bit2(25))>>(25-22))\
         |((ktmp3&bit2(0))<<(24)) | ((ktmp3&bit2(5))<<(26-5))  \
         |((ktmp3&bit2(10))<<(28-10)) | ((ktmp3&bit2(15))<<(30-15)) )
#define __GPIO_k_UD (((ktmp1&bit2(2))>>2) | ((ktmp1&bit2(7))>>(7-2)) \
         |((ktmp1&bit2(12))>>(12-4)) | ((ktmp1&bit2(17))>>(17-6))  \
         |((ktmp1&bit2(22))>>(22-8)) | ((ktmp1&bit2(27))>>(27-10))  \
         |((ktmp2&bit2(2))<<(12-2)) | ((ktmp2&bit2(7))<<(14-7))  \
         |((ktmp2&bit2(12))<<(16-12)) | ((ktmp2&bit2(17))<<(18-17))  \
         |((ktmp2&bit2(22))>>(22-20)) | ((ktmp2&bit2(27))>>(27-22))\
         |((ktmp3&bit2(2))<<(24-2)) | ((ktmp3&bit2(7))<<(26-7))  \
         |((ktmp3&bit2(12))<<(28-12)) | ((ktmp3&bit2(17))<<(30-17))  )

//-----------------------------
/*----------------------------------------------------------------------------
 STM32 GPIO i setup.
 initializes the GPIOx_CRL and GPIOx_CRH register
 *----------------------------------------------------------------------------*/
#if __GPIO_i_USED                          // GPIO_i used
__inline static void GPIO_i_SETUP (void) {   // "static" means only to be used in this file 
GPIO_TypeDef *GPIOx;
  
    RCC->AHB1ENR |=  (1UL << __GPIO_i_PORT_num);     // enable clock for GPIOA
    // __GPIO_PORT_num = 0: PORTA, 1: PORTB, ..., 10: PORTK
    GPIOx  = (GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400 * __GPIO_i_PORT_num);
#if ( __GPIO_i_PORT_num == 0)  // GPIOA
    GPIOx->MODER   |= __GPIO_i_MODER &(0x03FFFFFF); // PA13~PA15 as JTAG pins
#else
  #if (__GPIO_i_PORT_num == 1)  // GPIOB	
    GPIOx->MODER   |= __GPIO_i_MODER &(0xFFFFFC3F); // PB3~PB4 as JTAG pins
  #else		
    GPIOx->MODER   = __GPIO_i_MODER;
  #endif
#endif
		
#if (__GPIO_i_PPOD)
#if (__GPIO_i_PORT_num == 0)  // GPIOA
    GPIOx->OTYPER  = __GPIO_i_PPOD &(0x00001FFF); // PA13~PA15 as JTAG pins with OT=0
#else
 #if (__GPIO_i_PORT_num == 1)  // GPIOB	
    GPIOx->OTYPER  = __GPIO_i_PPOD &(0x0000FFE7); // PB3~PB4 as JTAG pins with OT = 0
 #else
    GPIOx->OTYPER  = __GPIO_i_PPOD;
 #endif		
#endif
#endif

#if (__GPIO_i_SPEED)
#if (__GPIO_i_PORT_num == 0)  // GPIOA
    GPIOx->OSPEEDR  = __GPIO_i_SPEED &(0x03FFFFFF); // PA13~PA15 as JTAG pins with OSPEED = 0 
#else
 #if (__GPIO_i_PORT_num == 1)  // GPIOB	
    GPIOx->OSPEEDR  |= __GPIO_i_SPEED &(0xFFFFFC3F); // PB3, PB4 as JTAG pins (with OSPEED = 0, 3)
 #else	
    GPIOx->OSPEEDR = __GPIO_i_SPEED;
 #endif
#endif
#endif

#if (__GPIO_i_UD)
#if (__GPIO_i_PORT_num == 0)  // GPIOA
    GPIOx->PUPDR   |= __GPIO_i_UD &(0x03FFFFFF); // PA13~PA15 (up, down, up) as JTAG pins
#else
  #if (__GPIO_i_PORT_num == 1)  // GPIOB	
    GPIOx->PUPDR   |= __GPIO_i_UD &(0xFFFFFC3F); // PB3~PB4 (no, up) as JTAG pins
  #else		
    GPIOx->PUPDR   = __GPIO_i_UD;
  #endif
#endif
#endif

#if (__GPIO_i_AFRL)
    GPIOx->AFRL   = __GPIO_i_AFRL;
#endif
#if (__GPIO_i_AFRH)
    GPIOx->AFRH   = __GPIO_i_AFRH;
#endif
  
}
#endif	// #if __GPIO_i_USED 

/*----------------------------------------------------------------------------
 STM32 GPIO j setup.
 initializes the GPIOx_CRL and GPIOx_CRH register
 *----------------------------------------------------------------------------*/
#if __GPIO_j_USED                         // GPIO_j used
__inline static void GPIO_j_SETUP (void) {   // "static" means only to be used in this file 
GPIO_TypeDef *GPIOx;
	uint32_t temp, chg2=0, chg4L=0, chg4H=0;
  
	for (temp=0; temp<16; temp++){
		uint32_t vb;
		  vb = (__GPIO_j_pinChg1 >> temp)& 0x01; 
			if (vb !=0){
			   chg2 |= (0x03ul) << (temp*2);
			  if (temp <8){
			   chg4L |= (0x0Ful) << (temp*4);
			  }else {
			   chg4H |= (0x0Ful) << ((temp-8)*4);
			  }				
		  }
	}
#if ( __GPIO_j_PORT_num == 0)  // GPIOA
    chg2   = chg2 &(0x03FFFFFF); // PA13~PA15 as JTAG pins
    chg4H   = chg4H&(0x000FFFFF); // PA13~PA15 as JTAG pins
#else
  #if (__GPIO_j_PORT_num == 1)  // GPIOB	
    chg2   = chg2  &(0xFFFFFC3F); // PB3~PB4 as JTAG pins
    chg4L   = chg4L  &(0xFFF00FFF); // PB3~PB4 as JTAG pins
  #endif
#endif
  
    RCC->AHB1ENR |=  (1UL << __GPIO_j_PORT_num);     // enable clock for GPIOA
    // __GPIO_PORT_num = 0: PORTA, 1: PORTB, ..., 10: PORTK
    GPIOx  = (GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400 * __GPIO_j_PORT_num);

		// MODE register
  	temp = (GPIOx->MODER) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_MODER & chg2);	// mode values only for pins to be configured
    GPIOx->MODER   = temp;
		
	
#if (__GPIO_j_PPOD)
#if (__GPIO_j_PORT_num == 0)  // GPIOA
#define  CHG_j_1 (__GPIO_j_pinChg1 &(0x00001FFF)) // PA13~PA15 as JTAG pins with OT=0
#else
 #if (__GPIO_j_PORT_num == 1)  // GPIOB	
#define  CHG_j_1  (__GPIO_j_pinChg1 &(0x0000FFE7)) // PB3~PB4 as JTAG pins with OT = 0
 #else
#define  CHG_j_1  (__GPIO_j_pinChg1 )
 #endif		
#endif
  	temp = (GPIOx->OTYPER) & (~CHG_j_1);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_PPOD & CHG_j_1);	// pp or open drain only for pins to be configured
    GPIOx->OTYPER  = temp;
#endif

#if (__GPIO_j_SPEED)
  	temp = (GPIOx->OSPEEDR) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_SPEED & chg2);	// speed values only for pins to be configured
    GPIOx->OSPEEDR = temp;
#endif


#if (__GPIO_j_UD)
  	temp = (GPIOx->PUPDR) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_UD & chg2);	// pull up/down values only for pins to be configured
    GPIOx->PUPDR   = temp;
#endif


#if (__GPIO_j_AFRL)
  	temp = (GPIOx->AFR[0]) & (~chg4L);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_AFRL & chg4L);	// AF values only for pins to be configured
    GPIOx->AFR[0]   = temp;
#endif
#if (__GPIO_j_AFRH)
  	temp = (GPIOx->AFR[1]) & (~chg4H);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_j_AFRH & chg4H);	// AF values only for pins to be configured
    GPIOx->AFR[1]   = temp;
#endif
  
}
#endif	// #if __GPIO_j_USED 

/*----------------------------------------------------------------------------
 STM32 GPIO k setup.
 initializes the GPIOx_CRL and GPIOx_CRH register
 *----------------------------------------------------------------------------*/
#if __GPIO_k_USED                          // GPIO_i used
__inline static void GPIO_k_SETUP (void) {   // "static" means only to be used in this file 
GPIO_TypeDef *GPIOx;
	uint32_t temp, chg2=0, chg4L=0, chg4H=0;
  
	for (temp=0; temp<16; temp++){
		uint32_t vb;
		  vb = (__GPIO_k_pinChg1 >> temp)& 0x01; 
			if (vb !=0){
			   chg2 |= (0x03ul) << (temp*2);
			  if (temp <8){
			   chg4L |= (0x0Ful) << (temp*4);
			  }else {
			   chg4H |= (0x0Ful) << ((temp-8)*4);
			  }				
		  }
	}
#if ( __GPIO_k_PORT_num == 0)  // GPIOA
    chg2   = chg2 &(0x03FFFFFF); // PA13~PA15 as JTAG pins
    chg4H   = chg4H&(0x000FFFFF); // PA13~PA15 as JTAG pins
#else
  #if (__GPIO_k_PORT_num == 1)  // GPIOB	
    chg2   = chg2  &(0xFFFFFC3F); // PB3~PB4 as JTAG pins
    chg4L   = chg4L  &(0xFFF00FFF); // PB3~PB4 as JTAG pins
  #endif
#endif
	
    RCC->AHB1ENR |=  (1UL << __GPIO_k_PORT_num);     // enable clock for GPIOx
    // __GPIO_PORT_num = 0: PORTA, 1: PORTB, ..., 10: PORTK
    GPIOx  = (GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400 * __GPIO_k_PORT_num);

		// MODE register
  	temp = (GPIOx->MODER) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_MODER & chg2);	// mode values only for pins to be configured
    GPIOx->MODER   = temp;
		
#if (__GPIO_k_PPOD)
#if (__GPIO_k_PORT_num == 0)  // GPIOA
#define  CHG_k_1 (__GPIO_k_pinChg1 &(0x00001FFF)) // PA13~PA15 as JTAG pins with OT=0
#else
 #if (__GPIO_k_PORT_num == 1)  // GPIOB	
#define  CHG_k_1  (__GPIO_k_pinChg1 &(0x0000FFE7)) // PB3~PB4 as JTAG pins with OT = 0
 #else
#define  CHG_k_1  (__GPIO_k_pinChg1 )
 #endif		
#endif
  	temp = (GPIOx->OTYPER) & (~CHG_k_1);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_PPOD & CHG_k_1);	// pp or open drain only for pins to be configured
    GPIOx->OTYPER  = temp;
#endif

#if (__GPIO_k_SPEED)
  	temp = (GPIOx->OSPEEDR) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_SPEED & chg2);	// speed values only for pins to be configured
    GPIOx->OSPEEDR = temp;
#endif

#if (__GPIO_k_UD)
  	temp = (GPIOx->PUPDR) & (~chg2);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_UD & chg2);	// pull up/down values only for pins to be configured
    GPIOx->PUPDR   = temp;
#endif

#if (__GPIO_k_AFRL)
  	temp = (GPIOx->AFR[0]) & (~chg4L);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_AFRL & chg4L);	// AF values only for pins to be configured
    GPIOx->AFR[0]   = temp;
#endif
#if (__GPIO_k_AFRH)
  	temp = (GPIOx->AFR[1]) & (~chg4H);				// clear the bits for pins to be configured
		temp = temp | (__GPIO_k_AFRH & chg4H);	// AF values only for pins to be configured
    GPIOx->AFR[1]   = temp;
#endif
  
}
#endif	// #if __GPIO_k_USED 


/*----------------------------------------------------------------------------
 STM32 GPIO setup.
 initializes the GPIOx_CRL and GPIOx_CRH register
 *----------------------------------------------------------------------------*/
void stm32f4_GPIO_Init (void) {

#if __GPIO_i_USED                          // GPIO_i used
	GPIO_i_SETUP ();
#endif
	
#if __GPIO_j_USED                          // GPIO_i used
	GPIO_j_SETUP ();
#endif

#if __GPIO_k_USED                          // GPIO_i used
	GPIO_k_SETUP ();
#endif

#if __EXTI_SETUP
	stm32_ExtiSetup();
#endif	
}


