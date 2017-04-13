/********************* (C) COPYRIGHT 2015 e-Design Co.,Ltd. **********************
File Name :      main.c
Version :        S100 APP Ver 2.11   
Description:
Author :         Celery
Data:            2015/07/07
History:
2015/07/07   з»џдёЂе‘ЅеђЌпј›
*******************************************************************************/
#include <string.h>
#include <stdio.h>
#include "APP_Version.h"
#include "Disk.h"
#include "Bios.h"
#include "USB_lib.h"
#include "I2C.h"
#include "Flash.h"
#include "MMA8652FC.h"
#include "UI.h"
#include "OLed.h"
#include "CTRL.h"
#include "HARDWARE.h"

/*******************************************************************************
е‡Ѕж•°еђЌ: main
е‡Ѕж•°дЅњз”Ё:дё»еѕЄзЋЇ
иѕ“е…ҐеЏ‚ж•°:NULL
иї”е›ћеЏ‚ж•°:NULL
*******************************************************************************/
void main(void)
{
    RCC_Config();
    NVIC_Config(0x4000);
    Init_Timer2();
    Init_Timer3();
    GPIO_Config();
    USB_Port(DISABLE);
    Delay_Ms(200);
    USB_Port(ENABLE);
    USB_Init();
    I2C_Configuration();
    
    Ad_Init();
    if (Get_CtrlStatus() != CONFIG)  StartUp_Accelerated();
    
    System_Init();
    Init_Gtime();
    APP_Init();
    
    Disk_BuffInit();
    Config_Analysis();         // еђЇеЉЁи™љж‹џUз›�
    Init_Oled();
    Clear_Screen();
    
    Pid_Init();
    Set_gKey(NO_KEY);
    Start_Watchdog(3000);
    
    while (1) {
        Clear_Watchdog();
        if (Get_CtrlStatus() != CONFIG  && LEAVE_WAIT_TIMER == 0) {
            Check_Accelerated();
            LEAVE_WAIT_TIMER = 50;
        }
        OLed_Display();                             //ж�ѕз¤єCtrl_status
        Status_Tran();                              //ж №жЌ®еЅ“е‰ЌзЉ¶жЂЃпјЊй…Ќеђ€жЊ‰й”®дёЋжЋ§е€¶ж—¶й—ґиЅ¬жЌў
    }
}
/******************************** END OF FILE *********************************/
