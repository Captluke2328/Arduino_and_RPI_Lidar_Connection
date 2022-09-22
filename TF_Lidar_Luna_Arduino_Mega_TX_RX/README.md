## This Readme elaborate on how to connect TF Luna to Arduino Mega. Pin as follow:
### TF Luna Lidar Pin (1-6)
1. 5V
2. RXD/SDA 
3. TXD/SCL 
4. GND 
5. I2C Enable 
6. Data Signal

### Arduino Mega
1. Connect TX1 to Pin RXD/SDA (Since we're using Serial1)
2. Connect RX1 to Pin TXD/SCL (Since we're using Serial1)
3. 5V to 5V
4. GND to GND

## Schematic AS Follow

![Lidar_Arduino_Connection](https://user-images.githubusercontent.com/81543946/191774574-f78aa4cb-fb9d-4319-aa53-3290e3ccab29.PNG)
