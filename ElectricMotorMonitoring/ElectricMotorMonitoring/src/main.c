
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