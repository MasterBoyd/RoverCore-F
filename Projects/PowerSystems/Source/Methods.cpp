#include "Methods.h"

/////////////////////////////////////////////////////////////////////////////
//                              Function Definitions                       //
/////////////////////////////////////////////////////////////////////////////

void currentRead(feedback_t * feedback)
{
    // feedback->currentDriveBackup = currentConvert(DRIVE_BACKUP_CURRENT); 
    feedback->currentSteer = currentConvert(STEER_CURRENT);
    feedback->currentArm = currentConvert(ARM_CURRENT);
    feedback->currentDriveFront = currentConvert(DRIVE_FRONT_RELAY);
    feedback->currentDriveBack = currentConvert(DRIVE_BACK_RELAY);
}

double currentConvert(uint8_t pinNumber)
{
	// double readings[10];
	// double average = ZERO;
	// for (uint8_t i = ZERO; i < TEN; i++) {
	double average = (((double)(analogRead(pinNumber)) * (MAX_MV_IN/MAX_ANALOG_VALUE)) - MV_OFFSET) / MV_PER_AMP;
	// }
	// average /= TEN;
	return average; //(((double)(analogRead(pinNumber)) * (MAX_MV_IN/MAX_ANALOG_VALUE)) - MV_OFFSET) / MV_PER_AMP;
}

void coulombCount(feedback_t * feedback)
{
	feedback->mAhRemaining -= (//feedback->currentDriveBackup + 
				   			   feedback->currentSteer + 
				   			   feedback->currentArm   + 
				   			   feedback->currentDriveFront + 
				   			   feedback->currentDriveBack) 
				   			   //MILLI_TO_BASE / RATE_OF_DRAIN; //1000 / 36000
							   / RATE_OF_DRAIN;
}

void currentCheck(feedback_t * feedback, flags_t * flags, commands_t * commands) 
{
	// char buffer[BUFFER_SIZE] = {ZERO};

	// if(feedback->currentDriveBackup > MAX_DRIVE_BACKUP) {
	// 	analogWrite(DRIVE_BACKUP_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
	// 	flags->driveF = ZERO;
	// 	commands->driveFrontRelay = ZERO;
	// 	feedback->errorCode = DRIVE_BACKUP_CURRENT_TRIP;
	// 	// sprintf(buffer, "DRIVE MODULE OVER-CURRENT.");
	// 	// Serial1.println(buffer);
	// }
	if(feedback->currentSteer > MAX_STEER) {
		analogWrite(STEER_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		flags->steer = ZERO;
		commands->steerRelay = ZERO;
		feedback->errorCode = STEER_CURRENT_TRIP;
		// sprintf(buffer, "STEER MODULE OVER-CURRENT.");
		// Serial1.println(buffer);
	}
	if(feedback->currentArm > MAX_ARM) {
		analogWrite(ARM_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		flags->arm = ZERO;
		commands->armRelay = ZERO;
		feedback->errorCode = ARM_CURRENT_TRIP;
		// sprintf(buffer, "ARM MODULE OVER-CURRENT.");
		// Serial1.println(buffer);
	}
	if(feedback->currentDriveFront > MAX_DRIVE_FRONT) {
		analogWrite(DRIVE_FRONT_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		flags->driveF = ZERO;
		commands->driveFrontRelay = ZERO;
		feedback->errorCode = DRIVE_FRONT_RELAY_TRIP;
		// sprintf(buffer, "INTELLIGENCE MODULE OVER-CURRENT.");
		// Serial1.println(buffer);
	}
	if(feedback->currentDriveBack > MAX_DRIVE_BACK) {
		analogWrite(DRIVE_BACK_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		flags->driveB = ZERO;
		commands->driveBackRelay = ZERO;
		feedback->errorCode = DRIVE_BACK_RELAY_TRIP;
		// sprintf(buffer, "MAST AND TRACKER MODULE OVER-CURRENT.");
		// Serial1.println(buffer);
	}
}

void WireSetup() //initialize i2c communication
{
	const TickType_t xDelay = DELAY_MS(50);
    TickType_t xLastWakeTime = xTaskGetTickCount();
	// Serial.println("got here 1");
	Wire.begin();
	// Serial.println("got here 2");
	// tempConfig(TEMP_SENSOR1_ADDR);
	// vTaskDelayUntil(&xLastWakeTime, xDelay);
	// tempConfig(TEMP_SENSOR2_ADDR);
	// tempConfig(TEMP_SENSOR3_ADDR);
	// vTaskDelayUntil(&xLastWakeTime, xDelay);

	// Serial.println("got here 3");
}

void tempConfig(uint8_t addr) //send configuration bytes to temp sensors
{
	Wire.beginTransmission(addr);
	Wire.write(byte(TEMP_CONFIG_REG));
	Wire.write(byte(TEMP_CONFIG_VALUE));
	Wire.endTransmission();
}

void tempRead(feedback_t * feedback)
{
	// Serial.println("got here 4");
	feedback->temp1 = tempReadTransmit(TEMP_SENSOR1_ADDR);
	// Serial.println(feedback->temp1);
	// Serial.println("got here 5");
	feedback->temp2 = tempReadTransmit(TEMP_SENSOR2_ADDR);
	// Serial.println("got here 9");
	feedback->temp3 = tempReadTransmit(TEMP_SENSOR3_ADDR);
	// Serial.println("got here 10");
}

uint32_t tempReadTransmit(uint8_t addr)
{
	Wire.beginTransmission(addr);
	// Serial.println("got here 6");
	Wire.write(byte(TEMP_READ_REG));
	// Serial.println("got here 7");
	Wire.requestFrom(addr, BYTES_READ);
	// Serial.println("got here 8");
	uint32_t tempVar = (((Wire.read() << 8) | Wire.read()) * INPUT_TO_FAHRENHEIT + FAHRENHEIT_OFFSET);
	// Serial.println(tempVar);
	// Serial.println("got here 11");
	Wire.endTransmission();

	// Serial.println("got here 12");
	return tempVar;
}

void tempCheck(feedback_t * feedback)
{
	if (feedback->temp1 >= CRITICAL_BAT_TEMP)
	{
		feedback->errorCode = BAT1_TEMP_CRITICAL;
	}
	else if (feedback->temp1 >= APPROACH_CRIT_TEMP)
	{
		feedback->errorCode = BAT1_TEMP_WARNING;
	}
	else;


	if (feedback->temp2 >= CRITICAL_BAT_TEMP)
	{
		feedback->errorCode = BAT2_TEMP_CRITICAL;
	}
	else if (feedback->temp2 >= APPROACH_CRIT_TEMP)
	{
		feedback->errorCode = BAT2_TEMP_WARNING;
	}
	else;


	if (feedback->temp3 >= CRITICAL_BAT_TEMP)
	{
		feedback->errorCode = BAT3_TEMP_CRITICAL;
	}
	else if (feedback->temp3 >= APPROACH_CRIT_TEMP)
	{
		feedback->errorCode = BAT3_TEMP_WARNING;
	}
	else;
}

void openCircuitVoltage(feedback_t * feedback)
{
	const TickType_t xDelay = DELAY_MS(200);
    TickType_t xLastWakeTime = xTaskGetTickCount();
	feedback->mAhRemaining = ZERO;

	for (uint8_t i = ZERO; i < FIVE; i++) {
		feedback->previousVoltages[i] = 25;
	}

	updateRealTimeVoltage(feedback);
	
	analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	analogWrite(BAT_RELAY2,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
	analogWrite(BAT_RELAY3,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
	vTaskDelayUntil(&xLastWakeTime, xDelay);

	// feedback->mAhRemaining += OCV_Math(OPEN_CIR_VOL2);
	feedback->mAhRemaining += OCV_Math(OPEN_CIR_VOL3);	

	analogWrite(BAT_RELAY2,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	analogWrite(BAT_RELAY3,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	vTaskDelayUntil(&xLastWakeTime, xDelay);
	analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
	vTaskDelayUntil(&xLastWakeTime, xDelay);

	feedback->mAhRemaining += OCV_Math(OPEN_CIR_VOL1);

	analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	vTaskDelayUntil(&xLastWakeTime, xDelay);
}

double OCV_Math(uint8_t pin)
{
	double ocvIn = (((analogRead(pin)) * (MAX_MV_IN/MAX_ANALOG_VALUE))/MILLI_TO_BASE);
	double voltageOfBat = 4.13*ocvIn + 17.294;
	double VPC = (MAX_V_PER_CELL - ((MAX_V_OF_BAT - voltageOfBat)/NUM_OF_CELL_PER_BAT)); //Voltage Per Cell  //changed ocvIn to voltageOfBat
	
	if (VPC >= MAX_V_PER_CELL) return MAX_MAH;
	else if (VPC > MIN_V_PER_CELL) return dischargeFxn(VPC);	//changed MIN_V_OF_BAT to MIN_V_PER_CELL
	else return 0;
}

double dischargeFxn(double ocv)
{
	double percent = (6396.0014748192*pow(ocv,5) - 
					 121559.760023073*pow(ocv,4) + 
					 922325.784998111*pow(ocv,3) - 
					 3492088.99337948*pow(ocv,2) + 
					 6597614.143813046*(ocv) - 
					 4976011.86099692)
					 /100;
	return percent*MAX_MAH; //4000 = MAX_MAH per battery
}

void closeModuleRelays(feedback_t * feedback, flags_t * flags, commands_t * commands)
{
	const TickType_t xDelay = DELAY_MS(DELAY_TIME);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
	analogWrite(DRIVE_BACKUP_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	// vTaskDelayUntil(&xLastWakeTime, xDelay);
	analogWrite(STEER_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	// vTaskDelayUntil(&xLastWakeTime, xDelay);
	analogWrite(ARM_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	// vTaskDelayUntil(&xLastWakeTime, xDelay);
	analogWrite(DRIVE_FRONT_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	// vTaskDelayUntil(&xLastWakeTime, xDelay);
	analogWrite(DRIVE_BACK_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, TWELVE));
	vTaskDelayUntil(&xLastWakeTime, xDelay);

	updateRealTimeVoltage(feedback);

	//initialize error code
	feedback->errorCode = NO_ERROR;

	//initialize flags to true
	flags->bat1  = ONE;
	flags->bat2  = ONE;
	flags->bat3  = ONE;
	flags->driveF = ONE;
	flags->steer = ONE;
	flags->arm 	 = ONE;
	flags->driveF = ONE;
	flags->driveB  = ONE;
	flags->allPower = ONE;

	commands->batRelay1  = ONE;
	commands->batRelay2  = ONE;
	commands->batRelay3  = ONE;
	commands->driveFrontRelay = ONE;
	commands->steerRelay = ONE;
	commands->armRelay   = ONE;
	commands->driveFrontRelay = ONE;
	commands->driveBackRelay  = ONE;
	commands->allPower 	 = ONE;
}

void updatePWM(feedback_t * feedback, flags_t * flags)
{
	updateRealTimeVoltage(feedback);
	if (flags->allPower) {
		if(flags->bat1) {
			analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if(flags->bat2) {
			analogWrite(BAT_RELAY2,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if(flags->bat3) {
			analogWrite(BAT_RELAY3,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if (flags->driveBackup) {
			analogWrite(DRIVE_BACKUP_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if (flags->steer) {
			analogWrite(STEER_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if (flags->arm)   {
			analogWrite(ARM_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if (flags->driveF) {
			analogWrite(DRIVE_FRONT_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
		if (flags->driveB)  {
			analogWrite(DRIVE_BACK_RELAY,	dutyCycleVoltageTransfer(feedback->realTimeVoltage, FIVE));
		}
	}
}

void updateRealTimeVoltage(feedback_t * feedback)
{
	//need to send signal to activate real time circuit

	digitalWrite(REAL_TIME_CTRL, HIGH);

	const TickType_t xDelay = DELAY_MS(DELAY_TIME);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&xLastWakeTime, xDelay);
	//linear relationship above 22V
	double voltageIn = analogRead(REAL_TIME_VOL) / MAX_ANALOG_VALUE * (MAX_MV_IN / MILLI_TO_BASE);
	feedback->realTimeVoltage = REAL_TIME_RELATION * voltageIn + REAL_TIME_OFFSET;

	digitalWrite(REAL_TIME_CTRL, LOW);

	for (uint8_t i= ZERO; i < 4; i++) {
		feedback->previousVoltages[i] = feedback->previousVoltages[i+1];
	}
	feedback->previousVoltages[4] = feedback->realTimeVoltage;
	if (feedback->previousVoltages[0] < CUTOFF_VOLTAGE &&
		feedback->previousVoltages[1] < CUTOFF_VOLTAGE &&
		feedback->previousVoltages[2] < CUTOFF_VOLTAGE &&
		feedback->previousVoltages[3] < CUTOFF_VOLTAGE &&
		feedback->previousVoltages[4] < CUTOFF_VOLTAGE)
	{
		analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		analogWrite(BAT_RELAY2,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
		analogWrite(BAT_RELAY3,dutyCycleVoltageTransfer(feedback->realTimeVoltage, ZERO));
	}
	if (feedback->realTimeVoltage < 21.9) {
		feedback->realTimeVoltage = feedback->previousVoltages[3];
	}
}

void commandResponse(feedback_t * feedback, flags_t * flags, commands_t * commands, SemaphoreHandle_t * xSemaphore)
{
	const TickType_t xDelay = DELAY_MS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();

	bool changed = false;
	// updateRealTimeVoltage(feedback);

	//bat1
	if (flags->bat1 != commands->batRelay1)
	{
		analogWrite(BAT_RELAY1,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->batRelay1) ? TWELVE : ZERO));
		flags->bat1 = commands->batRelay1;
		changed = true;
	}
	//bat2
	if (flags->bat2 != commands->batRelay2)
	{
		analogWrite(BAT_RELAY2,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->batRelay2) ? TWELVE : ZERO));
		flags->bat2 = commands->batRelay2;
		changed = true;
	}
	//bat3
	if (flags->bat3 != commands->batRelay3)
	{
		analogWrite(BAT_RELAY3,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->batRelay3) ? TWELVE : ZERO));
		flags->bat3 = commands->batRelay3;
		changed = true;
	}
	//drive
	if (flags->driveBackup != commands->driveBackupRelay)
	{
		analogWrite(DRIVE_BACKUP_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->driveBackupRelay) ? TWELVE : ZERO));
		flags->driveBackup = commands->driveBackupRelay;
		changed = true;
	}
	//steer
	if (flags->steer != commands->steerRelay)
	{
		analogWrite(STEER_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->steerRelay) ? TWELVE : ZERO));
		flags->steer = commands->steerRelay;
		changed = true;
	}
	//arm
	if (flags->arm != commands->armRelay)
	{
		analogWrite(ARM_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->armRelay) ? TWELVE : ZERO));
		flags->arm = commands->armRelay;
		changed = true;
	}
	//intel
	if (flags->driveF != commands->driveFrontRelay)
	{
		analogWrite(DRIVE_FRONT_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->driveFrontRelay) ? TWELVE : ZERO));
		flags->driveF = commands->driveFrontRelay;
		changed = true;
	}
	//mast
	if (flags->driveB != commands->driveBackRelay)
	{
		analogWrite(DRIVE_BACK_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->driveBackRelay) ? TWELVE : ZERO));
		flags->driveB = commands->driveBackRelay;
		changed = true;
	}
	if (flags->allPower != commands->allPower)
	{
		analogWrite(BAT_RELAY3, dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(BAT_RELAY2, dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(BAT_RELAY1, dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(DRIVE_BACK_RELAY, dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(DRIVE_FRONT_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(ARM_RELAY,  dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(STEER_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		analogWrite(DRIVE_BACKUP_RELAY,dutyCycleVoltageTransfer(feedback->realTimeVoltage, (commands->allPower) ? TWELVE : ZERO));
		flags->allPower = commands->allPower;
		// changed = true;
	}
	if (changed)
	{
		xSemaphoreTake(*xSemaphore, ( TickType_t ) 0 );
		vTaskDelayUntil(&xLastWakeTime, xDelay);
		updatePWM(feedback, flags);
		xSemaphoreGive(*xSemaphore);
	}
}