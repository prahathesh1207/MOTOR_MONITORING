# ENERGY EFFICIENT SYSTEM FOR ELECTRICAL MOTORS
A system that monitors motor vibrations in accordance with ISO 10816 standards and alerts the user when vibration levels exceed safety limits.
# INTRODUCTION
Industrial motors play a critical role in various applications, from manufacturing plants to power generation. Ensuring their safe operation is vital to prevent failures, downtime, and hazards. Our system monitors the vibration of a motor, providing real-time alerts if the motor exceeds its safety operating limits. Using a VSD Squadron microcontroller, SW420 vibration sensor, and an LCD for display, this system ensures proactive maintenance and enhances motor lifespan.
# Importance of Monitoring Vibration
According to ISO 10816 standards, monitoring vibration is essential for predictive maintenance and motor reliability. Excessive vibration can lead to mechanical failures, increased wear and tear, and unexpected breakdowns.

Example: 150 HP Motor (Approx. 110 kW)

For a 150 HP motor, ISO standards define acceptable vibration limits based on motor mounting and application. Typically:
Vibration Levels (ISO 10816-3): Acceptable values for a rigidly mounted motor range from 1.8 to 4.5 mm/s RMS. If vibration exceeds 7 mm/s, the motor is considered to be in an alert zone requiring immediate maintenance.

By continuously tracking these parameters, our system ensures early fault detection, preventing costly repairs and minimizing downtime.
# Overview of System Operation
   1.Vibration Monitoring (SW420 Sensor, PC6 Pin): Detects abnormal mechanical oscillations and sends alerts.
   
   2.LCD Display (PD6, PD7): Shows real-time vibration levels.
   
   3.Alarm System: Alerts users if vibration crosses critical thresholds.
 
 This system aligns with ISO guidelines, ensuring a reliable and safe motor operation strategy.
# Components Required with Bill of Materials (BoM)  

|          **Component**           | **Quantity**|                  **Description**                    |      **Example Model**       |  
|----------------------------------|-------------|-----------------------------------------------------|------------------------------|  
| **VSD Squadron Microcontroller** | 1           | Microcontroller board for sensor interfacing        | VSD Squadron Mini            |  
| **SW420 Vibration Sensor**       | 1           | Detects abnormal vibrations in the motor            | SW420                        |  
| **LCD Display**                  | 1           | Displays vibration levels and alerts                | 16x2 LCD (I2C or parallel)   |  
| **Jumper Wires**                 | 1 set       | Used for connections between components             | Male-to-Male, Male-to-Female |  
| **Micro USB Cable**              | 1           | Used for power and programming                      | Standard Micro USB Cable     |  
| **Power Supply (5V/12V)**        | 1           | Supplies power to the system                        | 5V Adapter / 12V Battery     |  
# Table for Pin Connections 

| **Component**               | **VSD Squadron Mini Pin** | **Description**                                             |  
|-----------------------------|--------------------------|-------------------------------------------------------------|  
| **Vibration Sensor D0**      | PD4                      | Digital output from SW420 vibration sensor                  |  
| **LCD SDA**                 | PC1                      | Serial data line for I2C communication                      |  
| **LCD SCL**                 | PC2                      | Serial clock line for I2C communication                     |  
| **Green LED**               | PD6                      | Turns on when vibration is within safe limits               |  
| **Red LED**                 | PD5                      | Turns on when vibration exceeds safe limits                 |  
| **LCD VCC**                 | 5V                       | LCD power supply                                            |  
| **LCD GND**                 | GND                      | LCD ground                                                  |  
| **Vibration Sensor VCC**     | 5V                       | SW420 sensor power supply                                   |  
| **Vibration Sensor GND**     | GND                      | SW420 sensor ground                                         |  
| **Microcontroller Power**    | Micro USB                | Provides power to the microcontroller                       |  
# WORKING CODE
#include <ch32v00x.h>
#include <debug.h>
#include "lcd.h"
#include "i2c.h"

void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        for (unsigned int j = 0; j < 8000; j++) {
            __NOP();
        }
    }
}

void lcd_send_cmd(unsigned char cmd);
void lcd_send_data(unsigned char data);
void lcd_send_str(unsigned char *str);
void lcd_init(void);
void delay_ms(unsigned int ms);

//pin configuration
// GPIO pins for I2C
#define SDA_PIN GPIO_Pin_1
#define SCL_PIN GPIO_Pin_2
#define LCD_Address 0x27

void GPIO_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Initialize SDA and SCL pins for I2C
   GPIO_InitStructure.GPIO_Pin = SDA_PIN | SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIO_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure = {0}; //structure variable GPIO_InitStructure of type GPIO_InitTypeDef which is used for GPIO configuration.

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D
//pin 4 OUT PIN FOR IR SENSOR
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; // Defines which Pin to configure
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Defines Output Type
GPIO_Init(GPIOD, &GPIO_InitStructure);
//pin 6 IS LED PIN
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; //
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Defines Output Type
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
GPIO_Init(GPIOD, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOD, &GPIO_InitStructure);


}
//main function
int main(void)
{
        SystemCoreClockUpdate();    
        GPIO_INIT(); // Initialize GPIO pins
        lcd_init();  // Initialize the LCD Display
        delay_ms(20); 
        uint8_t VIB = 0;
        uint8_t set=1;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// Configuring NVIC priority group
        SystemCoreClockUpdate();// Update System Core Clock
        Delay_Init();//Initialize Delay
        GPIO_Config();//Call GPIO configuration function
        GPIO_WriteBit(GPIOD, GPIO_Pin_5, set);
        lcd_send_cmd(0x80); // Move the cursor to first row, first column
        lcd_send_str((unsigned char *)"MOTOR MONITORING");
        lcd_send_cmd(0xC0); // Move to second row
        lcd_send_str((unsigned char *)"System OFF");
        delay_ms(5000);
        GPIO_WriteBit(GPIOD, GPIO_Pin_5, 0);
        lcd_send_cmd(0x01);
        lcd_send_cmd(0x80); // Move the cursor to first row, first column
        delay_ms(20);
        lcd_send_str((unsigned char *)"MOTOR MONITORING");
        lcd_send_cmd(0xC0); // Move to second row
        lcd_send_str((unsigned char *)"System ON");
        delay_ms(3000);
        lcd_send_cmd(0x01);
    while(1)
    {
            GPIO_WriteBit(GPIOD, GPIO_Pin_6, set);
            VIB = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);
            lcd_send_cmd(0x80);
            lcd_send_str((unsigned char *)"MOTOR IS IN ");
            lcd_send_cmd(0xC0); // Move to second row
            lcd_send_str((unsigned char *)"STANDBY MODE");
            delay_ms(10);
            if (VIB==1)//Read state of Pin 4 (IR sensor)
            { 
            lcd_send_cmd(0x01); // Clear display
            lcd_send_cmd(0x80); // Move the cursor to first row, first column
            delay_ms(20);
            lcd_send_str((unsigned char*)"VIBRATION FOUND");
            lcd_send_cmd(0xC0); // Move to second row
            lcd_send_str((unsigned char *)"NEED PRECAUTION");
            delay_ms(4500);
            lcd_send_cmd(0x01); // Clear display
            }
    }

}
