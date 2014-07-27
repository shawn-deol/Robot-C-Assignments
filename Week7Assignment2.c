void speedCalculator(float & encoderSpeed, float & ultraSpeed, int colour, int motorPower ){

 float initialDistance=SensorValue[S3];
 nMotorEncoder[motorA]=0;
 time1[0]=0;
 time1[1]=0;
 motor[motorA]=motorPower;
 motor[motorC]=motorPower;

  while (SensorValue[S2]!=colour){}

	 float ultraDistance=initialDistance-SensorValue[S3];
	 motor[motorA]=0;
	 motor[motorC]=0;
	 float encoderDistance = (nMotorEncoder[motorA]/180)*PI*2*1.5;
	 encoderSpeed=encoderDistance/(time1[0]*.001);
	 ultraSpeed=ultraDistance/(time1[1]*.001);

}



task main()
{
SensorType[S2]=sensorCOLORFULL;
SensorType[S3]=sensorSONAR;
nxtDisplayString(0,"Tues 2");
float functionInput1,functionInput2,percentError,averagePercentError=0;
for (int i=1;i<6;i++){
		while (nNxtButtonPressed!=3){}
		while (nNxtButtonPressed!=-1){}
	 speedCalculator(functionInput1,functionInput2,i, i*20);
	 nxtDisplayString(1,"%f",functionInput1);
	 nxtDisplayString(2,"%f",functionInput2);
	 percentError=abs(100*((functionInput1-functionInput2)/functionInput2));
	 nxtDisplayString(3,"%f",percentError);
	 averagePercentError+=percentError;
	 wait10Msec(100);
}

nxtDisplayString(0,"%f",averagePercentError/5.0);
wait10Msec(100);
}
