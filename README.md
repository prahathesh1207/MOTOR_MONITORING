# MOTOR MONITORING
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
| **Buzzer/Alarm**                 | 1           | Provides an audible alert when limits are exceeded  | Active Buzzer Module         |  
| **Jumper Wires**                 | 1 set       | Used for connections between components             | Male-to-Male, Male-to-Female |  
| **Micro USB Cable**              | 1           | Used for power and programming                      | Standard Micro USB Cable     |  
| **Power Supply (5V/12V)**        | 1           | Supplies power to the system                        | 5V Adapter / 12V Battery     |  


