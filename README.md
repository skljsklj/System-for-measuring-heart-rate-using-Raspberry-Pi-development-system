# System-for-measuring-heart-rate-using-Raspberry-Pi-development-system

Parts used for implementation:

1) Any model of **Raspberry Pi** (specifically, Model 2B with 1GB RAM was used)
2) **Analog sensor KY-039**
3) **AD converter PCF8591**
4) Protoboard and specific cables for connecting the mentioned components.
   
Raspberry Pi Model 2, developed by the Raspberry Pi Foundation, was a significant improvement over previous models. Launched in 2015, it featured a quad-core processor unit, specifically the Broadcom BCM2836 quad-core ARM Cortex-A7 processor clocked at 900 MHz. With 1GB LPDDR2 SDRAM, it provided enhanced performance compared to earlier models, allowing smoother multitasking.

Despite its specifications, there were issues with Qt freezing, requiring frequent resets after every third build.

**The KY-039 analog sensor**, also known as the "Heartbeat Detection Sensor Module," is commonly used for monitoring heartbeats or pulsations. It operates optically, with an LED emitting light through the skin and a phototransistor detecting reflected light changes, enabling heartbeat detection.

As Raspberry Pi can only receive digital output, an AD converter like the **PCF8591** was necessary for the project. **The PCF8591 module**, based on the NXP PCF8591 chip, serves as a digital-to-analog and analog-to-digital converter. It features four analog inputs, one analog output, and interfaces via I2C. Additionally, it includes a photoresistor, thermistor, and potentiometer on the board. The device functions with single-supply, low-power consumption, and 8-bit CMOS technology, with data transmission occurring via the serial I2C interface.

For more details, refer to the NXP datasheet (https://www.nxp.com/docs/en/data-sheet/PCF8591.pdf). The PCF8591 offers features such as analog input multiplexing, tracking and holding function, 8-bit analog-to-digital conversion, and 8-bit digital-to-analog conversion. The maximum conversion speed is determined by the maximum I2C bus speed.
