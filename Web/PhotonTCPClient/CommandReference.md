# Command Reference

## M

	Requests Measurements.
	
	- arguments: none
	- response:
		RPMLS: Left RPM Setpoint
		RPML: Left RPM
		RPMRS: Right RPM Setpoint
		RPMR: Right RPM
		PWMLFWD: Left PWM Forward DutyCycle (0-1)
		PWMLREV: Left PWM Reverse DutyCycle (0-1)
		PWMRFWD: Right PWM Forward DutyCycle (0-1)
		PWMRREV: Right PWM Reverse DutyCycle (0-1)
		sensor: Sensor data (-1 - +1)
		
## SET

	Sets some settings.
	
	- arguments: 
		sharpestCurve: Tightest curve radius in cm
		cruiseKp: Proportional gain of the lineCruiser
		cruiseKd: Differential gain of the lineCruiser
		corneringDBrakeFactor: Number between 0 and 1 to tell how much to slow down in tightening curves. 0 means never slows down. 1 means full stop on tightest curve.
		corneringPBrakeFactor: Number between 0 and 1 to tell how much to slow down in a given curve. 0 means never slows down. 1 means full stop on tightest curve.
		motorKp: Proportional gain of the motors.
		motorKd: Differential gain of the motors.

	- response:
		status:	0 means ok
				-1 means error.