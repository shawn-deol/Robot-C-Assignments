void speedCalculator(float & encoderSpeed, float & ultraSpeed, int colour, int motorPower )
{

 int initialDistance = SensorValue[S3];
 nMotorEncoder[motorA]=0;
 time1[0]=0;
 time1[1]=0;
 motor[motorA]=motorPower;
 motor[motorC]=motorPower;

  while (SensorValue[S1]!=colour){}
  motor[motorA]=0;
	 motor[motorC]=0;
	 float t = time1[0]/1000.0;
	 float ultraDistance=initialDistance-SensorValue[S3];

	 float encoderDistance = nMotorEncoder[motorA]*PI/120;
	 encoderSpeed=encoderDistance/t;
	 ultraSpeed=ultraDistance/t;

}



task main()
{
SensorType[S1]=sensorCOLORFULL;
SensorType[S3]=sensorSONAR;
nxtDisplayString(0,"Tues 2");

float encoder,sonar,percentError,averagePercentError=0;
for (int i=1;i<6;i++)
{
		while (nNxtButtonPressed !=3){}
		while (nNxtButtonPressed ==3){}
	 speedCalculator(encoder,sonar,i, i*20);
	 nxtDisplayString(1,"encoder=%.2f",encoder);
	 nxtDisplayString(2,"sonar=%.2f",sonar);
	 percentError=100*(sonar-encoder)/encoder;
	 nxtDisplayString(3,"err=%.2f",percentError);
	 averagePercentError+=abs(percentError);

}

nxtDisplayString(5,"ave=%.2f",averagePercentError/5.0);
while (nNxtButtonPressed !=3){}
		while (nNxtButtonPressed ==3){}
}
