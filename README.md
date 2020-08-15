
# Ball and Beam Control System

This is a mechanism capable to control a ball on a beam at any desired setpoints. 
##  Parts

### Mechancial Parts

* Beam - 40 [cm]
* Aluminum profiles
* Servo and IR sensor brackets
* Servo flange

### Electrical Parts

* Arduino Uno
* Servo motor (MG90S)
* Sharp distance sensor


## Connections
![Circuit](https://github.com/amin-tabrizian/Ball-and-Beam-Controll-system/blob/master/Circuit.png)

## Final Mechanism
![Final Model](https://github.com/amin-tabrizian/Ball-and-Beam-Controll-system/blob/master/Mechanism.JPG =250x250)
## Controller

In this system we read position of the ball along the beam with a distance sensor. Then we filter the input data for eliminating noises. A PID Controller will receive the data and after the computation adjust servo angle.

### PID Coefficients Tuning

Here is a toturial that we have created for tuning PID coefficients:

## System Test

This system has been tested with numerous setpoints. Here is a video for a setpoint at 22 cm:


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.



