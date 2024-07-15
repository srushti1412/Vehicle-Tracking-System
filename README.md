# Vehicle-Tracking-System
This project is a vehicle tracking system with accident detection capabilities. 
It uses an MPU6050 accelerometer and gyroscope to detect falls or accidents, a SIM800L module to send SMS alerts, and a Neo-6M GPS module to provide location data. The system is designed to monitor the vehicle's motion and detect any abnormal activity indicative of an accident, then alert predefined contacts with the vehicle's location.
The mpu_read() function reads accelerometer and gyroscope data from the MPU6050 sensor.
Accelerometer (AcX, AcY, AcZ) and gyroscope (GyX, GyY, GyZ) values are read and processed.
Accelerometer values are converted to ax, ay, az, and gyroscope values to gx, gy, gz.
An SMS alert is sent to a predefined phone number with a message and a Google Maps link to the vehicle's location.
![Picture1](https://github.com/user-attachments/assets/050f81e6-04a7-4742-bbc4-6d99843e1047)
![Picture2](https://github.com/user-attachments/assets/94b7a4d4-0ba3-4dc9-bc38-21e52fee23ca)
![Picture3](https://github.com/user-attachments/assets/99ad32ff-42d3-4572-a0b6-79c9147dbbd0)
