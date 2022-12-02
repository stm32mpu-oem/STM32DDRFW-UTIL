;********************************************************************************
;* File Name          : startup_stm32mp257xx.s
;* Author             : MCD Application Team
;* Description        : STM32MP257xx
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M33 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************
;* @attention
;*
;* Copyright (c) 2021 STMicroelectronics.
;* All rights reserved.
;*
;* This software is licensed under terms that can be found in the LICENSE file
;* in the root directory of this software component.
;* If no LICENSE file comes with this software, it is provided AS-IS.
;*
;*******************************************************************************
;
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                    ; Reset Handler

        DCD     NMI_Handler                      ; NMI Handler
        DCD     HardFault_Handler                ; Hard Fault Handler
        DCD     MemManage_Handler                ; MPU Fault Handler
        DCD     BusFault_Handler                 ; Bus Fault Handler
        DCD     UsageFault_Handler               ; Usage Fault Handler
        DCD     SecureFault_Handler              ; Secure Fault Handler
        DCD     0                                ; Reserved
        DCD     0                                ; Reserved
        DCD     0                                ; Reserved
        DCD     SVC_Handler                      ; SVCall Handler
        DCD     DebugMon_Handler                 ; Debug Monitor Handler
        DCD     0                                ; Reserved
        DCD     PendSV_Handler                   ; PendSV Handler
        DCD     SysTick_Handler                  ; SysTick Handler

        ; External Interrupts
        ; **********************************************************************
        ; External interrupts according to
        ; "Table 226. interrupt mapping for Cortex®-M33"
        ; in chapitre 32 "interrupt list" of reference document
        ; RM0457 - Reference Manual - STM32MP25xx - advanced ARM-based 32/64-bit MPUs
        ; file "DM00485804 (RM0457) Rev0.1.pdf" (Revision 0.1 / 09-Mar-2021)
        ;***********************************************************************
        DCD     PVD_IRQHandler                   ; PVD detector through EXTI
        DCD     PVM_IRQHandler                   ; PVM detector through EXTI
        DCD     IWDG3_IRQHandler                 ; Independent Watchdog 3 Early wake interrupt
        DCD     IWDG4_IRQHandler                 ; Independent Watchdog 4 Early wake interrupt
        DCD     IWDG1_RST_IRQHandler             ; Independent Watchdog 1 Reset through EXTI
        DCD     IWDG2_RST_IRQHandler             ; Independent Watchdog 2 Reset through EXTI
        DCD     IWDG4_RST_IRQHandler             ; Independent Watchdog 4 Reset through EXTI
        DCD     IWDG5_RST_IRQHandler             ; Independent Watchdog 5 Reset through EXTI
        DCD     WWDG1_IRQHandler                 ; Window Watchdog 1 Early Wakeup interrupt
        DCD     0
        DCD     0
        DCD     WWDG2_RST_IRQHandler             ; Window Watchdog 2 Reset through EXTI
        DCD     TAMP_IRQHandler                  ; Tamper interrupt (include LSECSS interrupts)
        DCD     RTC_IRQHandler                   ; RTC global interrupt
        DCD     TAMP_S_IRQHandler                ; Tamper secure interrupt (include LSECSS interrupts)
        DCD     RTC_S_IRQHandler                 ; RTC global secure interrupt
        DCD     RCC_IRQHandler                   ; RCC global interrupt
        DCD     EXTI2_0_IRQHandler               ; EXTI2 Line 0 interrupt
        DCD     EXTI2_1_IRQHandler               ; EXTI2 Line 1 interrupt
        DCD     EXTI2_2_IRQHandler               ; EXTI2 Line 2 interrupt
        DCD     EXTI2_3_IRQHandler               ; EXTI2 Line 3 interrupt
        DCD     EXTI2_4_IRQHandler               ; EXTI2 Line 4 interrupt
        DCD     EXTI2_5_IRQHandler               ; EXTI2 Line 5 interrupt
        DCD     EXTI2_6_IRQHandler               ; EXTI2 Line 6 interrupt
        DCD     EXTI2_7_IRQHandler               ; EXTI2 Line 7 interrupt
        DCD     EXTI2_8_IRQHandler               ; EXTI2 Line 8 interrupt
        DCD     EXTI2_9_IRQHandler               ; EXTI2 Line 9 interrupt
        DCD     EXTI2_10_IRQHandler              ; EXTI2 Line 10 interrupt
        DCD     EXTI2_11_IRQHandler              ; EXTI2 Line 11 interrupt
        DCD     EXTI2_12_IRQHandler              ; EXTI2 Line 12 interrupt
        DCD     EXTI2_13_IRQHandler              ; EXTI2 Line 13 interrupt
        DCD     EXTI2_14_IRQHandler              ; EXTI2 Line 14 interrupt
        DCD     EXTI2_15_IRQHandler              ; EXTI2 Line 15 interrupt
        DCD     HPDMA1_Channel0_IRQHandler       ; HPDMA1 Channel0 interrupt
        DCD     HPDMA1_Channel1_IRQHandler       ; HPDMA1 Channel1 interrupt
        DCD     HPDMA1_Channel2_IRQHandler       ; HPDMA1 Channel2 interrupt
        DCD     HPDMA1_Channel3_IRQHandler       ; HPDMA1 Channel3 interrupt
        DCD     HPDMA1_Channel4_IRQHandler       ; HPDMA1 Channel4 interrupt
        DCD     HPDMA1_Channel5_IRQHandler       ; HPDMA1 Channel5 interrupt
        DCD     HPDMA1_Channel6_IRQHandler       ; HPDMA1 Channel6 interrupt
        DCD     HPDMA1_Channel7_IRQHandler       ; HPDMA1 Channel7 interrupt
        DCD     HPDMA1_Channel8_IRQHandler       ; HPDMA1 Channel8 interrupt
        DCD     HPDMA1_Channel9_IRQHandler       ; HPDMA1 Channel9 interrupt
        DCD     HPDMA1_Channel10_IRQHandler      ; HPDMA1 Channel10 interrupt
        DCD     HPDMA1_Channel11_IRQHandler      ; HPDMA1 Channel11 interrupt
        DCD     HPDMA1_Channel12_IRQHandler      ; HPDMA1 Channel12 interrupt
        DCD     HPDMA1_Channel13_IRQHandler      ; HPDMA1 Channel13 interrupt
        DCD     HPDMA1_Channel14_IRQHandler      ; HPDMA1 Channel14 interrupt
        DCD     HPDMA1_Channel15_IRQHandler      ; HPDMA1 Channel15 interrupt
        DCD     HPDMA2_Channel0_IRQHandler       ; HPDMA2 Channel0 interrupt
        DCD     HPDMA2_Channel1_IRQHandler       ; HPDMA2 Channel1 interrupt
        DCD     HPDMA2_Channel2_IRQHandler       ; HPDMA2 Channel2 interrupt
        DCD     HPDMA2_Channel3_IRQHandler       ; HPDMA2 Channel3 interrupt
        DCD     HPDMA2_Channel4_IRQHandler       ; HPDMA2 Channel4 interrupt
        DCD     HPDMA2_Channel5_IRQHandler       ; HPDMA2 Channel5 interrupt
        DCD     HPDMA2_Channel6_IRQHandler       ; HPDMA2 Channel6 interrupt
        DCD     HPDMA2_Channel7_IRQHandler       ; HPDMA2 Channel7 interrupt
        DCD     HPDMA2_Channel8_IRQHandler       ; HPDMA2 Channel8 interrupt
        DCD     HPDMA2_Channel9_IRQHandler       ; HPDMA2 Channel9 interrupt
        DCD     HPDMA2_Channel10_IRQHandler      ; HPDMA2 Channel10 interrupt
        DCD     HPDMA2_Channel11_IRQHandler      ; HPDMA2 Channel11 interrupt
        DCD     HPDMA2_Channel12_IRQHandler      ; HPDMA2 Channel12 interrupt
        DCD     HPDMA2_Channel13_IRQHandler      ; HPDMA2 Channel13 interrupt
        DCD     HPDMA2_Channel14_IRQHandler      ; HPDMA2 Channel14 interrupt
        DCD     HPDMA2_Channel15_IRQHandler      ; HPDMA2 Channel15 interrupt
        DCD     HPDMA3_Channel0_IRQHandler       ; HPDMA3 Channel0 interrupt
        DCD     HPDMA3_Channel1_IRQHandler       ; HPDMA3 Channel1 interrupt
        DCD     HPDMA3_Channel2_IRQHandler       ; HPDMA3 Channel2 interrupt
        DCD     HPDMA3_Channel3_IRQHandler       ; HPDMA3 Channel3 interrupt
        DCD     HPDMA3_Channel4_IRQHandler       ; HPDMA3 Channel4 interrupt
        DCD     HPDMA3_Channel5_IRQHandler       ; HPDMA3 Channel5 interrupt
        DCD     HPDMA3_Channel6_IRQHandler       ; HPDMA3 Channel6 interrupt
        DCD     HPDMA3_Channel7_IRQHandler       ; HPDMA3 Channel7 interrupt
        DCD     HPDMA3_Channel8_IRQHandler       ; HPDMA3 Channel8 interrupt
        DCD     HPDMA3_Channel9_IRQHandler       ; HPDMA3 Channel9 interrupt
        DCD     HPDMA3_Channel10_IRQHandler      ; HPDMA3 Channel10 interrupt
        DCD     HPDMA3_Channel11_IRQHandler      ; HPDMA3 Channel11 interrupt
        DCD     HPDMA3_Channel12_IRQHandler      ; HPDMA3 Channel12 interrupt
        DCD     HPDMA3_Channel13_IRQHandler      ; HPDMA3 Channel13 interrupt
        DCD     HPDMA3_Channel14_IRQHandler      ; HPDMA3 Channel14 interrupt
        DCD     HPDMA3_Channel15_IRQHandler      ; HPDMA3 Channel15 interrupt
        DCD     LPDMA_Channel0_IRQHandler        ; LPDMA Channel0 interrupt
        DCD     LPDMA_Channel1_IRQHandler        ; LPDMA Channel1 interrupt
        DCD     LPDMA_Channel2_IRQHandler        ; LPDMA Channel2 interrupt
        DCD     LPDMA_Channel3_IRQHandler        ; LPDMA Channel3 interrupt
        DCD     ICACHE_IRQHandler                ; ICACHE interrupt
        DCD     DCACHE_IRQHandler                ; DCACHE interrupt
        DCD     ADC1_IRQHandler                  ; ADC1 interrupt
        DCD     ADC2_IRQHandler                  ; ADC2  interrupt
        DCD     ADC3_IRQHandler                  ; ADC3 interrupt
        DCD     FDCAN_CAL_IRQHandler             ; FDCAN CCU interrupt
        DCD     FDCAN1_IT0_IRQHandler            ; FDCAN1 interrupt 0
        DCD     FDCAN2_IT0_IRQHandler            ; FDCAN2 interrupt 0
        DCD     FDCAN3_IT0_IRQHandler            ; FDCAN3 interrupt 0
        DCD     FDCAN1_IT1_IRQHandler            ; FDCAN1 interrupt 1
        DCD     FDCAN2_IT1_IRQHandler            ; FDCAN2 interrupt 1
        DCD     FDCAN3_IT1_IRQHandler            ; FDCAN3 interrupt 1
        DCD     TIM1_BRK_IRQHandler              ; TIM1 Break interrupt
        DCD     TIM1_UP_IRQHandler               ; TIM1 Update interrupt
        DCD     TIM1_TRG_COM_IRQHandler          ; TIM1 Trigger and Commutation interrupts
        DCD     TIM1_CC_IRQHandler               ; TIM1 Capture Compare interrupt
        DCD     TIM20_BRK_IRQHandler             ; TIM20 Break interrupt
        DCD     TIM20_UP_IRQHandler              ; TIM20 Update interrupt
        DCD     TIM20_TRG_COM_IRQHandler         ; TIM20 Trigger and Commutation interrupts
        DCD     TIM20_CC_IRQHandler              ; TIM20 Capture Compare interrupt
        DCD     TIM2_IRQHandler                  ; TIM2 global interrupt
        DCD     TIM3_IRQHandler                  ; TIM3 global interrupt
        DCD     TIM4_IRQHandler                  ; TIM4 global interrupt
        DCD     I2C1_IRQHandler                  ; I2C1 global interrupt
        DCD     I3C1_IRQHandler                  ; I3C1 global interrupt
        DCD     I2C2_IRQHandler                  ; I2C2 global interrupt
        DCD     I3C2_IRQHandler                  ; I3C2 global interrupt
        DCD     SPI1_IRQHandler                  ; SPI1 global interrupt
        DCD     SPI2_IRQHandler                  ; SPI2 global interrupt
        DCD     USART1_IRQHandler                ; USART1 global interrupt
        DCD     USART2_IRQHandler                ; USART2 global interrupt
        DCD     USART3_IRQHandler                ; USART3 global interrupt
        DCD     VDEC_IRQHandler                  ; VDEC global interrupt
        DCD     TIM8_BRK_IRQHandler              ; TIM8 Break interrupt
        DCD     TIM8_UP_IRQHandler               ; TIM8 Update interrupt
        DCD     TIM8_TRG_COM_IRQHandler          ; TIM8 Trigger & Commutation interrupt
        DCD     TIM8_CC_IRQHandler               ; TIM8 Capture Compare interrupt
        DCD     FMC_IRQHandler                   ; FMC global interrupt
        DCD     SDMMC1_IRQHandler                ; SDMMC1 global interrupt
        DCD     TIM5_IRQHandler                  ; TIM5 global interrupt
        DCD     SPI3_IRQHandler                  ; SPI3 global interrupt
        DCD     UART4_IRQHandler                 ; UART4 global interrupt
        DCD     UART5_IRQHandler                 ; UART5 global interrupt
        DCD     TIM6_IRQHandler                  ; TIM6 global interrupt
        DCD     TIM7_IRQHandler                  ; TIM7 global interrupt
        DCD     ETH1_SBD_IRQHandler              ; ETH1 global interrupt
        DCD     ETH1_PMT_IRQHandler              ; ETH1 wake-up interrupt
        DCD     ETH1_LPI_IRQHandler              ; ETH1 LPI interrupt
        DCD     ETH2_SBD_IRQHandler              ; ETH2 global interrupt
        DCD     ETH2_PMT_IRQHandler              ; ETH2 wake-up interrupt
        DCD     ETH2_LPI_IRQHandler              ; ETH2 LPI interrupt
        DCD     USART6_IRQHandler                ; USART6 global interrupt
        DCD     I2C3_IRQHandler                  ; I2C3 global interrupt
        DCD     I3C3_IRQHandler                  ; I3C3 global interrupt
        DCD     USBH_EHCI_IRQHandler             ; USB Host EHCI interrupt
        DCD     USBH_OHCI_IRQHandler             ; USB Host OHCI interrupt
        DCD     DCMI_PSSI_IRQHandler             ; DCMI & PSSI global interrupt
        DCD     CSI_IRQHandler                   ; CSI-2 interrupt
        DCD     DSI_IRQHandler                   ; DSI Host controller global interrupt
        DCD     CRYP1_IRQHandler                 ; Crypto1 interrupt
        DCD     HASH_IRQHandler                  ; Hash interrupt
        DCD     PKA_IRQHandler                   ; PKA interrupt
        DCD     FPU_IRQHandler                   ; FPU global interrupt
        DCD     UART7_IRQHandler                 ; UART7 global interrupt
        DCD     UART8_IRQHandler                 ; UART8 global interrupt
        DCD     UART9_IRQHandler                 ; UART9 global interrupt
        DCD     LPUART1_IRQHandler               ; LPUART1 global interrupt
        DCD     SPI4_IRQHandler                  ; SPI4 global interrupt
        DCD     SPI5_IRQHandler                  ; SPI5 global interrupt
        DCD     SPI6_IRQHandler                  ; SPI6 global interrupt
        DCD     SPI7_IRQHandler                  ; SPI7 global interrupt
        DCD     SPI8_IRQHandler                  ; SPI8 global interrupt
        DCD     SAI1_IRQHandler                  ; SAI1 global interrupt
        DCD     LTDC_IRQHandler                  ; LTDC global interrupt
        DCD     LTDC_ER_IRQHandler               ; LTDC global error interrupt
        DCD     LTDC_SEC_IRQHandler              ; LTDC security global interrupt
        DCD     LTDC_SEC_ER_IRQHandler           ; LTDC security global error interrupt
        DCD     SAI2_IRQHandler                  ; SAI2 global interrupt
        DCD     OCTOSPI1_IRQHandler              ; OCTOSPI1 global interrupt
        DCD     OCTOSPI2_IRQHandler              ; OCTOSPI2 global interrupt
        DCD     OTFDEC1_IRQHandler               ; OTFDEC1 interrupt
        DCD     LPTIM1_IRQHandler                ; LPTIMER1 global interrupt
        DCD     VENC_IRQHandler                  ; VENC global interrupt
        DCD     I2C4_IRQHandler                  ; I2C4 global interrupt
        DCD     USBH_WAKEUP_IRQHandler           ; USB Host remote wake up from USB2PHY1 interrupt
        DCD     SPDIFRX_IRQHandler               ; SPDIFRX global interrupt
        DCD     IPCC1_RX_IRQHandler              ; Mailbox 1 RX Occupied interrupt
        DCD     IPCC1_TX_IRQHandler              ; Mailbox 1 TX Free interrupt
        DCD     IPCC1_RX_S_IRQHandler            ; Mailbox 1 RX Occupied secure interrupt
        DCD     IPCC1_TX_S_IRQHandler            ; Mailbox 1 TX Free secure interrupt
        DCD     IPCC2_RX_IRQHandler              ; Mailbox 2 RX Occupied interrupt
        DCD     IPCC2_TX_IRQHandler              ; Mailbox 2 TX Free interrupt
        DCD     IPCC2_RX_S_IRQHandler            ; Mailbox 2 RX Occupied secure interrupt
        DCD     IPCC2_TX_S_IRQHandler            ; Mailbox 2 TX Free secure interrupt
        DCD     SAES_IRQHandler                  ; Secure AES
        DCD     CRYP2_IRQHandler                 ; Crypto2 interrupt
        DCD     I2C5_IRQHandler                  ; I2C5 global interrupt
        DCD     USB3DR_WAKEUP_IRQHandler         ; USB3 remote wake up from USB2PHY1 interrupt
        DCD     GPU_IRQHandler                   ; GPU global Interrupt
        DCD     MDF1_FLT0_IRQHandler             ; MDF1 Filter0 interrupt
        DCD     MDF1_FLT1_IRQHandler             ; MDF1 Filter1 interrupt
        DCD     MDF1_FLT2_IRQHandler             ; MDF1 Filter2 interrupt
        DCD     MDF1_FLT3_IRQHandler             ; MDF1 Filter3 interrupt
        DCD     MDF1_FLT4_IRQHandler             ; MDF1 Filter4 interrupt
        DCD     MDF1_FLT5_IRQHandler             ; MDF1 Filter5 interrupt
        DCD     MDF1_FLT6_IRQHandler             ; MDF1 Filter6 interrupt
        DCD     MDF1_FLT7_IRQHandler             ; MDF1 Filter7 interrupt
        DCD     SAI3_IRQHandler                  ; SAI3 global interrupt
        DCD     TIM15_IRQHandler                 ; TIM15 global interrupt
        DCD     TIM16_IRQHandler                 ; TIM16 global interrupt
        DCD     TIM17_IRQHandler                 ; TIM17 global interrupt
        DCD     TIM12_IRQHandler                 ; TIM12 global interrupt
        DCD     SDMMC2_IRQHandler                ; SDMMC2 global interrupt
        DCD     DCMIPP_IRQHandler                ; DCMIPP global interrupt
        DCD     HSEM_IRQHandler                  ; HSEM nonsecure interrupt
        DCD     HSEM_S_IRQHandler                ; HSEM secure interrupt
        DCD     nCTIIRQ1_IRQHandler              ; Cortex-M33 CTI interrupt 1
        DCD     nCTIIRQ2_IRQHandler              ; Cortex-M33 CTI interrupt 2
        DCD     TIM13_IRQHandler                 ; TIM13 global interrupt
        DCD     TIM14_IRQHandler                 ; TIM14 global interrupt
        DCD     TIM10_IRQHandler                 ; TIM10 global interrupt
        DCD     RNG_IRQHandler                   ; RNG global interrupt
        DCD     ADF1_FLT_IRQHandler              ; ADF1 Filter interrupt
        DCD     I2C6_IRQHandler                  ; I2C6 global interrupt
        DCD     COMBOPHY_WAKEUP_IRQHandler       ; COMBOPHY LFPS start request interrupt
        DCD     I2C7_IRQHandler                  ; I2C7 global interrupt
        DCD     0
        DCD     I2C8_IRQHandler                  ; I2C8 global interrupt
        DCD     I3C4_IRQHandler                  ; I3C4 global interrupt
        DCD     SDMMC3_IRQHandler                ; SDMMC3 global interrupt
        DCD     LPTIM2_IRQHandler                ; LPTIMER2 global interrupt
        DCD     LPTIM3_IRQHandler                ; LPTIMER3 global interrupt
        DCD     LPTIM4_IRQHandler                ; LPTIMER4 global interrupt
        DCD     LPTIM5_IRQHandler                ; LPTIMER5 global interrupt
        DCD     OTFDEC2_IRQHandler               ; OTFDEC2 interrupt
        DCD     CPU1_SEV_IRQHandler              ; Cortex-A35 Send Event through EXTI
        DCD     CPU3_SEV_IRQHandler              ; Cortex-M0+ Send Event through EXTI
        DCD     RCC_WAKEUP_IRQHandler            ; RCC CPU2 Wake up interrupt
        DCD     SAI4_IRQHandler                  ; SAI4 global interrupt
        DCD     DTS_IRQHandler                   ; Temperature sensor interrupt
        DCD     TIM11_IRQHandler                 ; TIMER11 global interrupt
        DCD     CPU2_WAKEUP_PIN_IRQHandler       ; Interrupt for all 6 wake-up enabled by CPU2
        DCD     USB3DR_BC_IRQHandler             ; USB3 BC interrupt
        DCD     USB3DR_IRQHandler                ; USB3 interrupt
        DCD     UCPD1_IRQHandler                 ; USB PD interrupt
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SERF_IRQHandler                  ; SERF global interrupt
        DCD     BUSPERFM_IRQHandler              ; BUS Performance Monitor interrupt
        DCD     RAMCFG_IRQHandler                ; RAM configuration global interrupt
        DCD     DDRCTRL_IRQHandler               ; DDRCTRL interrupt
        DCD     DDRPHYC_IRQHandler               ; DDRPHY interrupt (active low)
        DCD     DFI_ERR_IRQHandler               ; DDRPHY DFI error interrupt
        DCD     IAC_IRQHandler                   ; RIF Illegal access Controller interrupt
        DCD     VDDCPU_VD_IRQHandler             ; VDDCPU voltage detector interrupt
        DCD     VDDCORE_VD_IRQHandler            ; VDDCORE voltage detector interrupt
        DCD     0
        DCD     ETHSW_IRQHandler                 ; Ethernet Switch global interrupt
        DCD     ETHSW_MSGBUF_IRQHandler          ; Ethernet ACM Message buffer interrupt
        DCD     ETHSW_FSC_IRQHandler             ; Ethernet ACM Scheduler interrupt
        DCD     HPDMA1_WKUP_IRQHandler           ; HPDMA1 channel 0 to 15 wake up
        DCD     HPDMA2_WKUP_IRQHandler           ; HPDMA2 channel 0 to 15 wake up
        DCD     HPDMA3_WKUP_IRQHandler           ; HPDMA3 channel 0 to 15 wake up
        DCD     LPDMA_WKUP_IRQHandler            ; LPDMA channel 0 to 3 wake up
        DCD     UCPD1_VBUS_IRQHandler             ; USB TypeC VBUS valid interrupt
        DCD     UCPD1_VSAFE5V_IRQHandler          ; USB TypeC VSAFE5V valid interrupt
        DCD     RCC_HSI_FMON_IRQHandler          ; HSI Frequency Monitor interrupt
        DCD     VDDGPU_VD_IRQHandler             ; VDDGPU voltage detector interrupt
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     EXTI1_0_IRQHandler               ; EXTI1 Line 0 interrupt
        DCD     EXTI1_1_IRQHandler               ; EXTI1 Line 1 interrupt
        DCD     EXTI1_2_IRQHandler               ; EXTI1 Line 2 interrupt
        DCD     EXTI1_3_IRQHandler               ; EXTI1 Line 3 interrupt
        DCD     EXTI1_4_IRQHandler               ; EXTI1 Line 4 interrupt
        DCD     EXTI1_5_IRQHandler               ; EXTI1 Line 5 interrupt
        DCD     EXTI1_6_IRQHandler               ; EXTI1 Line 6 interrupt
        DCD     EXTI1_7_IRQHandler               ; EXTI1 Line 7 interrupt
        DCD     EXTI1_8_IRQHandler               ; EXTI1 Line 8 interrupt
        DCD     EXTI1_9_IRQHandler               ; EXTI1 Line 9 interrupt
        DCD     EXTI1_10_IRQHandler              ; EXTI1 Line 10 interrupt
        DCD     EXTI1_11_IRQHandler              ; EXTI1 Line 11 interrupt
        DCD     EXTI1_12_IRQHandler              ; EXTI1 Line 12 interrupt
        DCD     EXTI1_13_IRQHandler              ; EXTI1 Line 13 interrupt
        DCD     EXTI1_14_IRQHandler              ; EXTI1 Line 14 interrupt
        DCD     EXTI1_15_IRQHandler              ; EXTI1 Line 15 interrupt
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     IS2M_IRQHandler                  ; IS2M fault detection interrupt
        DCD     0
        DCD     DDRPERFM_IRQHandler              ; DDR Performance Monitor interrupt
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0

__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SecureFault_Handler
        B SecureFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK PVM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVM_IRQHandler
        B PVM_IRQHandler

        PUBWEAK IWDG3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG3_IRQHandler
        B IWDG3_IRQHandler

        PUBWEAK IWDG4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG4_IRQHandler
        B IWDG4_IRQHandler

        PUBWEAK IWDG1_RST_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG1_RST_IRQHandler
        B IWDG1_RST_IRQHandler

        PUBWEAK IWDG2_RST_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG2_RST_IRQHandler
        B IWDG2_RST_IRQHandler

        PUBWEAK IWDG4_RST_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG4_RST_IRQHandler
        B IWDG4_RST_IRQHandler

        PUBWEAK IWDG5_RST_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG5_RST_IRQHandler
        B IWDG5_RST_IRQHandler

        PUBWEAK WWDG1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG1_IRQHandler
        B WWDG1_IRQHandler

        PUBWEAK WWDG2_RST_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG2_RST_IRQHandler
        B WWDG2_RST_IRQHandler

        PUBWEAK TAMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMP_IRQHandler
        B TAMP_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK TAMP_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMP_S_IRQHandler
        B TAMP_S_IRQHandler

        PUBWEAK RTC_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_S_IRQHandler
        B RTC_S_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI2_0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_0_IRQHandler
        B EXTI2_0_IRQHandler

        PUBWEAK EXTI2_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_1_IRQHandler
        B EXTI2_1_IRQHandler

        PUBWEAK EXTI2_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_2_IRQHandler
        B EXTI2_2_IRQHandler

        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler

        PUBWEAK EXTI2_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_4_IRQHandler
        B EXTI2_4_IRQHandler

        PUBWEAK EXTI2_5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_5_IRQHandler
        B EXTI2_5_IRQHandler

        PUBWEAK EXTI2_6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_6_IRQHandler
        B EXTI2_6_IRQHandler

        PUBWEAK EXTI2_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_7_IRQHandler
        B EXTI2_7_IRQHandler

        PUBWEAK EXTI2_8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_8_IRQHandler
        B EXTI2_8_IRQHandler

        PUBWEAK EXTI2_9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_9_IRQHandler
        B EXTI2_9_IRQHandler

        PUBWEAK EXTI2_10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_10_IRQHandler
        B EXTI2_10_IRQHandler

        PUBWEAK EXTI2_11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_11_IRQHandler
        B EXTI2_11_IRQHandler

        PUBWEAK EXTI2_12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_12_IRQHandler
        B EXTI2_12_IRQHandler

        PUBWEAK EXTI2_13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_13_IRQHandler
        B EXTI2_13_IRQHandler

        PUBWEAK EXTI2_14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_14_IRQHandler
        B EXTI2_14_IRQHandler

        PUBWEAK EXTI2_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_15_IRQHandler
        B EXTI2_15_IRQHandler

        PUBWEAK HPDMA1_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel0_IRQHandler
        B HPDMA1_Channel0_IRQHandler

        PUBWEAK HPDMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel1_IRQHandler
        B HPDMA1_Channel1_IRQHandler

        PUBWEAK HPDMA1_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel2_IRQHandler
        B HPDMA1_Channel2_IRQHandler

        PUBWEAK HPDMA1_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel3_IRQHandler
        B HPDMA1_Channel3_IRQHandler

        PUBWEAK HPDMA1_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel4_IRQHandler
        B HPDMA1_Channel4_IRQHandler

        PUBWEAK HPDMA1_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel5_IRQHandler
        B HPDMA1_Channel5_IRQHandler

        PUBWEAK HPDMA1_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel6_IRQHandler
        B HPDMA1_Channel6_IRQHandler

        PUBWEAK HPDMA1_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel7_IRQHandler
        B HPDMA1_Channel7_IRQHandler

        PUBWEAK HPDMA1_Channel8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel8_IRQHandler
        B HPDMA1_Channel8_IRQHandler

        PUBWEAK HPDMA1_Channel9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel9_IRQHandler
        B HPDMA1_Channel9_IRQHandler

        PUBWEAK HPDMA1_Channel10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel10_IRQHandler
        B HPDMA1_Channel10_IRQHandler

        PUBWEAK HPDMA1_Channel11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel11_IRQHandler
        B HPDMA1_Channel11_IRQHandler

        PUBWEAK HPDMA1_Channel12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel12_IRQHandler
        B HPDMA1_Channel12_IRQHandler

        PUBWEAK HPDMA1_Channel13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel13_IRQHandler
        B HPDMA1_Channel13_IRQHandler

        PUBWEAK HPDMA1_Channel14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel14_IRQHandler
        B HPDMA1_Channel14_IRQHandler

        PUBWEAK HPDMA1_Channel15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_Channel15_IRQHandler
        B HPDMA1_Channel15_IRQHandler

        PUBWEAK HPDMA2_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel0_IRQHandler
        B HPDMA2_Channel0_IRQHandler

        PUBWEAK HPDMA2_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel1_IRQHandler
        B HPDMA2_Channel1_IRQHandler

        PUBWEAK HPDMA2_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel2_IRQHandler
        B HPDMA2_Channel2_IRQHandler

        PUBWEAK HPDMA2_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel3_IRQHandler
        B HPDMA2_Channel3_IRQHandler

        PUBWEAK HPDMA2_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel4_IRQHandler
        B HPDMA2_Channel4_IRQHandler

        PUBWEAK HPDMA2_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel5_IRQHandler
        B HPDMA2_Channel5_IRQHandler

        PUBWEAK HPDMA2_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel6_IRQHandler
        B HPDMA2_Channel6_IRQHandler

        PUBWEAK HPDMA2_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel7_IRQHandler
        B HPDMA2_Channel7_IRQHandler

        PUBWEAK HPDMA2_Channel8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel8_IRQHandler
        B HPDMA2_Channel8_IRQHandler

        PUBWEAK HPDMA2_Channel9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel9_IRQHandler
        B HPDMA2_Channel9_IRQHandler

        PUBWEAK HPDMA2_Channel10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel10_IRQHandler
        B HPDMA2_Channel10_IRQHandler

        PUBWEAK HPDMA2_Channel11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel11_IRQHandler
        B HPDMA2_Channel11_IRQHandler

        PUBWEAK HPDMA2_Channel12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel12_IRQHandler
        B HPDMA2_Channel12_IRQHandler

        PUBWEAK HPDMA2_Channel13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel13_IRQHandler
        B HPDMA2_Channel13_IRQHandler

        PUBWEAK HPDMA2_Channel14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel14_IRQHandler
        B HPDMA2_Channel14_IRQHandler

        PUBWEAK HPDMA2_Channel15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_Channel15_IRQHandler
        B HPDMA2_Channel15_IRQHandler

        PUBWEAK HPDMA3_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel0_IRQHandler
        B HPDMA3_Channel0_IRQHandler

        PUBWEAK HPDMA3_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel1_IRQHandler
        B HPDMA3_Channel1_IRQHandler

        PUBWEAK HPDMA3_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel2_IRQHandler
        B HPDMA3_Channel2_IRQHandler

        PUBWEAK HPDMA3_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel3_IRQHandler
        B HPDMA3_Channel3_IRQHandler

        PUBWEAK HPDMA3_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel4_IRQHandler
        B HPDMA3_Channel4_IRQHandler

        PUBWEAK HPDMA3_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel5_IRQHandler
        B HPDMA3_Channel5_IRQHandler

        PUBWEAK HPDMA3_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel6_IRQHandler
        B HPDMA3_Channel6_IRQHandler

        PUBWEAK HPDMA3_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel7_IRQHandler
        B HPDMA3_Channel7_IRQHandler

        PUBWEAK HPDMA3_Channel8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel8_IRQHandler
        B HPDMA3_Channel8_IRQHandler

        PUBWEAK HPDMA3_Channel9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel9_IRQHandler
        B HPDMA3_Channel9_IRQHandler

        PUBWEAK HPDMA3_Channel10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel10_IRQHandler
        B HPDMA3_Channel10_IRQHandler

        PUBWEAK HPDMA3_Channel11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel11_IRQHandler
        B HPDMA3_Channel11_IRQHandler

        PUBWEAK HPDMA3_Channel12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel12_IRQHandler
        B HPDMA3_Channel12_IRQHandler

        PUBWEAK HPDMA3_Channel13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel13_IRQHandler
        B HPDMA3_Channel13_IRQHandler

        PUBWEAK HPDMA3_Channel14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel14_IRQHandler
        B HPDMA3_Channel14_IRQHandler

        PUBWEAK HPDMA3_Channel15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_Channel15_IRQHandler
        B HPDMA3_Channel15_IRQHandler

        PUBWEAK LPDMA_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDMA_Channel0_IRQHandler
        B LPDMA_Channel0_IRQHandler

        PUBWEAK LPDMA_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDMA_Channel1_IRQHandler
        B LPDMA_Channel1_IRQHandler

        PUBWEAK LPDMA_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDMA_Channel2_IRQHandler
        B LPDMA_Channel2_IRQHandler

        PUBWEAK LPDMA_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDMA_Channel3_IRQHandler
        B LPDMA_Channel3_IRQHandler

        PUBWEAK ICACHE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ICACHE_IRQHandler
        B ICACHE_IRQHandler

        PUBWEAK DCACHE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DCACHE_IRQHandler
        B DCACHE_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK ADC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC3_IRQHandler
        B ADC3_IRQHandler

        PUBWEAK FDCAN_CAL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN_CAL_IRQHandler
        B FDCAN_CAL_IRQHandler

        PUBWEAK FDCAN1_IT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN1_IT0_IRQHandler
        B FDCAN1_IT0_IRQHandler

        PUBWEAK FDCAN2_IT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN2_IT0_IRQHandler
        B FDCAN2_IT0_IRQHandler

        PUBWEAK FDCAN3_IT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN3_IT0_IRQHandler
        B FDCAN3_IT0_IRQHandler

        PUBWEAK FDCAN1_IT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN1_IT1_IRQHandler
        B FDCAN1_IT1_IRQHandler

        PUBWEAK FDCAN2_IT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN2_IT1_IRQHandler
        B FDCAN2_IT1_IRQHandler

        PUBWEAK FDCAN3_IT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDCAN3_IT1_IRQHandler
        B FDCAN3_IT1_IRQHandler

        PUBWEAK TIM1_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_IRQHandler
        B TIM1_BRK_IRQHandler

        PUBWEAK TIM1_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_UP_IRQHandler
        B TIM1_UP_IRQHandler

        PUBWEAK TIM1_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_TRG_COM_IRQHandler
        B TIM1_TRG_COM_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM20_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_BRK_IRQHandler
        B TIM20_BRK_IRQHandler

        PUBWEAK TIM20_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_UP_IRQHandler
        B TIM20_UP_IRQHandler

        PUBWEAK TIM20_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_TRG_COM_IRQHandler
        B TIM20_TRG_COM_IRQHandler

        PUBWEAK TIM20_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_CC_IRQHandler
        B TIM20_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM4_IRQHandler
        B TIM4_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I3C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I3C1_IRQHandler
        B I3C1_IRQHandler

        PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

        PUBWEAK I3C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I3C2_IRQHandler
        B I3C2_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK VDEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VDEC_IRQHandler
        B VDEC_IRQHandler

        PUBWEAK TIM8_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_BRK_IRQHandler
        B TIM8_BRK_IRQHandler

        PUBWEAK TIM8_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_UP_IRQHandler
        B TIM8_UP_IRQHandler

        PUBWEAK TIM8_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_TRG_COM_IRQHandler
        B TIM8_TRG_COM_IRQHandler

        PUBWEAK TIM8_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_CC_IRQHandler
        B TIM8_CC_IRQHandler

        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler

        PUBWEAK SDMMC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDMMC1_IRQHandler
        B SDMMC1_IRQHandler

        PUBWEAK TIM5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM5_IRQHandler
        B TIM5_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK TIM6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_IRQHandler
        B TIM6_IRQHandler

        PUBWEAK TIM7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM7_IRQHandler
        B TIM7_IRQHandler

        PUBWEAK ETH1_SBD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH1_SBD_IRQHandler
        B ETH1_SBD_IRQHandler

        PUBWEAK ETH1_PMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH1_PMT_IRQHandler
        B ETH1_PMT_IRQHandler

        PUBWEAK ETH1_LPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH1_LPI_IRQHandler
        B ETH1_LPI_IRQHandler

        PUBWEAK ETH2_SBD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH2_SBD_IRQHandler
        B ETH2_SBD_IRQHandler

        PUBWEAK ETH2_PMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH2_PMT_IRQHandler
        B ETH2_PMT_IRQHandler

        PUBWEAK ETH2_LPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH2_LPI_IRQHandler
        B ETH2_LPI_IRQHandler

        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART6_IRQHandler
        B USART6_IRQHandler

        PUBWEAK I2C3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_IRQHandler
        B I2C3_IRQHandler

        PUBWEAK I3C3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I3C3_IRQHandler
        B I3C3_IRQHandler

        PUBWEAK USBH_EHCI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBH_EHCI_IRQHandler
        B USBH_EHCI_IRQHandler

        PUBWEAK USBH_OHCI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBH_OHCI_IRQHandler
        B USBH_OHCI_IRQHandler

        PUBWEAK DCMI_PSSI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DCMI_PSSI_IRQHandler
        B DCMI_PSSI_IRQHandler

        PUBWEAK CSI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CSI_IRQHandler
        B CSI_IRQHandler

        PUBWEAK DSI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DSI_IRQHandler
        B DSI_IRQHandler

        PUBWEAK CRYP1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRYP1_IRQHandler
        B CRYP1_IRQHandler

        PUBWEAK HASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HASH_IRQHandler
        B HASH_IRQHandler

        PUBWEAK PKA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PKA_IRQHandler
        B PKA_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK UART7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART7_IRQHandler
        B UART7_IRQHandler

        PUBWEAK UART8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART8_IRQHandler
        B UART8_IRQHandler

        PUBWEAK UART9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART9_IRQHandler
        B UART9_IRQHandler

        PUBWEAK LPUART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART1_IRQHandler
        B LPUART1_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_IRQHandler
        B SPI4_IRQHandler

        PUBWEAK SPI5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI5_IRQHandler
        B SPI5_IRQHandler

        PUBWEAK SPI6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI6_IRQHandler
        B SPI6_IRQHandler

        PUBWEAK SPI7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI7_IRQHandler
        B SPI7_IRQHandler

        PUBWEAK SPI8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI8_IRQHandler
        B SPI8_IRQHandler

        PUBWEAK SAI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI1_IRQHandler
        B SAI1_IRQHandler

        PUBWEAK LTDC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LTDC_IRQHandler
        B LTDC_IRQHandler

        PUBWEAK LTDC_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LTDC_ER_IRQHandler
        B LTDC_ER_IRQHandler

        PUBWEAK LTDC_SEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LTDC_SEC_IRQHandler
        B LTDC_SEC_IRQHandler

        PUBWEAK LTDC_SEC_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LTDC_SEC_ER_IRQHandler
        B LTDC_SEC_ER_IRQHandler

        PUBWEAK SAI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI2_IRQHandler
        B SAI2_IRQHandler

        PUBWEAK OCTOSPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OCTOSPI1_IRQHandler
        B OCTOSPI1_IRQHandler

        PUBWEAK OCTOSPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OCTOSPI2_IRQHandler
        B OCTOSPI2_IRQHandler

        PUBWEAK OTFDEC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTFDEC1_IRQHandler
        B OTFDEC1_IRQHandler

        PUBWEAK LPTIM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM1_IRQHandler
        B LPTIM1_IRQHandler

        PUBWEAK VENC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VENC_IRQHandler
        B VENC_IRQHandler

        PUBWEAK I2C4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C4_IRQHandler
        B I2C4_IRQHandler

        PUBWEAK USBH_WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBH_WAKEUP_IRQHandler
        B USBH_WAKEUP_IRQHandler

        PUBWEAK SPDIFRX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPDIFRX_IRQHandler
        B SPDIFRX_IRQHandler

        PUBWEAK IPCC1_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC1_RX_IRQHandler
        B IPCC1_RX_IRQHandler

        PUBWEAK IPCC1_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC1_TX_IRQHandler
        B IPCC1_TX_IRQHandler

        PUBWEAK IPCC1_RX_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC1_RX_S_IRQHandler
        B IPCC1_RX_S_IRQHandler

        PUBWEAK IPCC1_TX_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC1_TX_S_IRQHandler
        B IPCC1_TX_S_IRQHandler

        PUBWEAK IPCC2_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC2_RX_IRQHandler
        B IPCC2_RX_IRQHandler

        PUBWEAK IPCC2_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC2_TX_IRQHandler
        B IPCC2_TX_IRQHandler

        PUBWEAK IPCC2_RX_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC2_RX_S_IRQHandler
        B IPCC2_RX_S_IRQHandler

        PUBWEAK IPCC2_TX_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC2_TX_S_IRQHandler
        B IPCC2_TX_S_IRQHandler

        PUBWEAK SAES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAES_IRQHandler
        B SAES_IRQHandler

        PUBWEAK CRYP2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRYP2_IRQHandler
        B CRYP2_IRQHandler

        PUBWEAK I2C5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C5_IRQHandler
        B I2C5_IRQHandler

        PUBWEAK USB3DR_WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB3DR_WAKEUP_IRQHandler
        B USB3DR_WAKEUP_IRQHandler

        PUBWEAK GPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPU_IRQHandler
        B GPU_IRQHandler

        PUBWEAK MDF1_FLT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT0_IRQHandler
        B MDF1_FLT0_IRQHandler

        PUBWEAK MDF1_FLT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT1_IRQHandler
        B MDF1_FLT1_IRQHandler

        PUBWEAK MDF1_FLT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT2_IRQHandler
        B MDF1_FLT2_IRQHandler

        PUBWEAK MDF1_FLT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT3_IRQHandler
        B MDF1_FLT3_IRQHandler

        PUBWEAK MDF1_FLT4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT4_IRQHandler
        B MDF1_FLT4_IRQHandler

        PUBWEAK MDF1_FLT5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT5_IRQHandler
        B MDF1_FLT5_IRQHandler

        PUBWEAK MDF1_FLT6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT6_IRQHandler
        B MDF1_FLT6_IRQHandler

        PUBWEAK MDF1_FLT7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDF1_FLT7_IRQHandler
        B MDF1_FLT7_IRQHandler

        PUBWEAK SAI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI3_IRQHandler
        B SAI3_IRQHandler

        PUBWEAK TIM15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM15_IRQHandler
        B TIM15_IRQHandler

        PUBWEAK TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM16_IRQHandler
        B TIM16_IRQHandler

        PUBWEAK TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM17_IRQHandler
        B TIM17_IRQHandler

        PUBWEAK TIM12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM12_IRQHandler
        B TIM12_IRQHandler

        PUBWEAK SDMMC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDMMC2_IRQHandler
        B SDMMC2_IRQHandler

        PUBWEAK DCMIPP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DCMIPP_IRQHandler
        B DCMIPP_IRQHandler

        PUBWEAK HSEM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HSEM_IRQHandler
        B HSEM_IRQHandler

        PUBWEAK HSEM_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HSEM_S_IRQHandler
        B HSEM_S_IRQHandler

        PUBWEAK nCTIIRQ1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
nCTIIRQ1_IRQHandler
        B nCTIIRQ1_IRQHandler

        PUBWEAK nCTIIRQ2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
nCTIIRQ2_IRQHandler
        B nCTIIRQ2_IRQHandler

        PUBWEAK TIM13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM13_IRQHandler
        B TIM13_IRQHandler

        PUBWEAK TIM14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM14_IRQHandler
        B TIM14_IRQHandler

        PUBWEAK TIM10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM10_IRQHandler
        B TIM10_IRQHandler

        PUBWEAK RNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RNG_IRQHandler
        B RNG_IRQHandler

        PUBWEAK ADF1_FLT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADF1_FLT_IRQHandler
        B ADF1_FLT_IRQHandler

        PUBWEAK I2C6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C6_IRQHandler
        B I2C6_IRQHandler

        PUBWEAK COMBOPHY_WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMBOPHY_WAKEUP_IRQHandler
        B COMBOPHY_WAKEUP_IRQHandler

        PUBWEAK I2C7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C7_IRQHandler
        B I2C7_IRQHandler

        PUBWEAK I2C8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C8_IRQHandler
        B I2C8_IRQHandler

        PUBWEAK I3C4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I3C4_IRQHandler
        B I3C4_IRQHandler

        PUBWEAK SDMMC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDMMC3_IRQHandler
        B SDMMC3_IRQHandler

        PUBWEAK LPTIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM2_IRQHandler
        B LPTIM2_IRQHandler

        PUBWEAK LPTIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM3_IRQHandler
        B LPTIM3_IRQHandler

        PUBWEAK LPTIM4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM4_IRQHandler
        B LPTIM4_IRQHandler

        PUBWEAK LPTIM5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM5_IRQHandler
        B LPTIM5_IRQHandler

        PUBWEAK OTFDEC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTFDEC2_IRQHandler
        B OTFDEC2_IRQHandler

        PUBWEAK CPU1_SEV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU1_SEV_IRQHandler
        B CPU1_SEV_IRQHandler

        PUBWEAK CPU3_SEV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU3_SEV_IRQHandler
        B CPU3_SEV_IRQHandler

        PUBWEAK RCC_WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_WAKEUP_IRQHandler
        B RCC_WAKEUP_IRQHandler

        PUBWEAK SAI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI4_IRQHandler
        B SAI4_IRQHandler

        PUBWEAK DTS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DTS_IRQHandler
        B DTS_IRQHandler

        PUBWEAK TIM11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM11_IRQHandler
        B TIM11_IRQHandler

        PUBWEAK CPU2_WAKEUP_PIN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU2_WAKEUP_PIN_IRQHandler
        B CPU2_WAKEUP_PIN_IRQHandler

        PUBWEAK USB3DR_BC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB3DR_BC_IRQHandler
        B USB3DR_BC_IRQHandler

        PUBWEAK USB3DR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB3DR_IRQHandler
        B USB3DR_IRQHandler

        PUBWEAK UCPD1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UCPD1_IRQHandler
        B UCPD1_IRQHandler

        PUBWEAK SERF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SERF_IRQHandler
        B SERF_IRQHandler

        PUBWEAK BUSPERFM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BUSPERFM_IRQHandler
        B BUSPERFM_IRQHandler

        PUBWEAK RAMCFG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RAMCFG_IRQHandler
        B RAMCFG_IRQHandler

        PUBWEAK DDRCTRL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DDRCTRL_IRQHandler
        B DDRCTRL_IRQHandler

        PUBWEAK DDRPHYC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DDRPHYC_IRQHandler
        B DDRPHYC_IRQHandler

        PUBWEAK DFI_ERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DFI_ERR_IRQHandler
        B DFI_ERR_IRQHandler

        PUBWEAK IAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IAC_IRQHandler
        B IAC_IRQHandler

        PUBWEAK VDDCPU_VD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VDDCPU_VD_IRQHandler
        B VDDCPU_VD_IRQHandler

        PUBWEAK VDDCORE_VD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VDDCORE_VD_IRQHandler
        B VDDCORE_VD_IRQHandler

        PUBWEAK ETHSW_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETHSW_IRQHandler
        B ETHSW_IRQHandler

        PUBWEAK ETHSW_MSGBUF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETHSW_MSGBUF_IRQHandler
        B ETHSW_MSGBUF_IRQHandler

        PUBWEAK ETHSW_FSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETHSW_FSC_IRQHandler
        B ETHSW_FSC_IRQHandler

        PUBWEAK HPDMA1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA1_WKUP_IRQHandler
        B HPDMA1_WKUP_IRQHandler

        PUBWEAK HPDMA2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA2_WKUP_IRQHandler
        B HPDMA2_WKUP_IRQHandler

        PUBWEAK HPDMA3_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDMA3_WKUP_IRQHandler
        B HPDMA3_WKUP_IRQHandler

        PUBWEAK LPDMA_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDMA_WKUP_IRQHandler
        B LPDMA_WKUP_IRQHandler

        PUBWEAK UCPD1_VBUS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UCPD1_VBUS_IRQHandler
        B UCPD1_VBUS_IRQHandler

        PUBWEAK UCPD1_VSAFE5V_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UCPD1_VSAFE5V_IRQHandler
        B UCPD1_VSAFE5V_IRQHandler

        PUBWEAK RCC_HSI_FMON_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_HSI_FMON_IRQHandler
        B RCC_HSI_FMON_IRQHandler

        PUBWEAK VDDGPU_VD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VDDGPU_VD_IRQHandler
        B VDDGPU_VD_IRQHandler

        PUBWEAK EXTI1_0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_0_IRQHandler
        B EXTI1_0_IRQHandler

        PUBWEAK EXTI1_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_1_IRQHandler
        B EXTI1_1_IRQHandler

        PUBWEAK EXTI1_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_2_IRQHandler
        B EXTI1_2_IRQHandler

        PUBWEAK EXTI1_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_3_IRQHandler
        B EXTI1_3_IRQHandler

        PUBWEAK EXTI1_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_4_IRQHandler
        B EXTI1_4_IRQHandler

        PUBWEAK EXTI1_5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_5_IRQHandler
        B EXTI1_5_IRQHandler

        PUBWEAK EXTI1_6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_6_IRQHandler
        B EXTI1_6_IRQHandler

        PUBWEAK EXTI1_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_7_IRQHandler
        B EXTI1_7_IRQHandler

        PUBWEAK EXTI1_8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_8_IRQHandler
        B EXTI1_8_IRQHandler

        PUBWEAK EXTI1_9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_9_IRQHandler
        B EXTI1_9_IRQHandler

        PUBWEAK EXTI1_10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_10_IRQHandler
        B EXTI1_10_IRQHandler

        PUBWEAK EXTI1_11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_11_IRQHandler
        B EXTI1_11_IRQHandler

        PUBWEAK EXTI1_12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_12_IRQHandler
        B EXTI1_12_IRQHandler

        PUBWEAK EXTI1_13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_13_IRQHandler
        B EXTI1_13_IRQHandler

        PUBWEAK EXTI1_14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_14_IRQHandler
        B EXTI1_14_IRQHandler

        PUBWEAK EXTI1_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_15_IRQHandler
        B EXTI1_15_IRQHandler

        PUBWEAK IS2M_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IS2M_IRQHandler
        B IS2M_IRQHandler

        PUBWEAK DDRPERFM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DDRPERFM_IRQHandler
        B DDRPERFM_IRQHandler

        END
