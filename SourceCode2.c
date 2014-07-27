void speedCalculator(float & encoderSpeed, float & ultraSpeed, int colour, int motorPower ){
 float initialDistance=SensorValue[S3];
 nMotorEncoder[motorA]=0;
 time1[0]=0;
 motor[motorA]=75;
 motor[motorC]=75;
 while (SensorValue[S2]!=colour;
 float elapsedDistance=SensorValue[S3]-intialValue;
 motor[motorA]=0;
 motor[motorC]=0;
 encoderSpeed=nMotorEncoder[motorA]/time1[0];
 ultraSpeed=elapsedDistance/time1[0];
}
