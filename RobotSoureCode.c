//Function to launch cage, either puts down cage or raises it
//Dependin boolean input
void launchCage(bool launch)
{
	int direction;
	if (launch)
		direction = 1;
	else
		direction = -1;

	nMotorEncoder[motorB] = 0;
	while (abs(nMotorEncoder[motorB]) < 180)
	{
		motor[motorB] = direction * 20;
	}
	motor[motorB] = 0;
}


//Function that checks if the robot has made contact while searching for balls
bool checkTouch()
{
	while (!SensorValue[S2]){}
	return true;
}

//Function that checks the color of the ball to catalog it
int checkColour()
{
	return SensorValue[S3];
}

//Function that allows navigation to select the order of the ball retrieval
int askForInput(int  colourNumber)
{
	colourNumber = 0;
	bool select = 1;
	while (select)
	{
		if (nNxtButtonPressed == 1)
		{
			colourNumber++;
			nxtDisplayString(0, " colour # %d", colourNumber);
			wait10Msec(50);
		}
		else if (nNxtButtonPressed == 2)
		{
			colourNumber--;
			nxtDisplayString(0, " colour # %d", colourNumber);
			wait10Msec(50);
		}
		else if (nNxtButtonPressed == 3)
		{
			nxtDisplayString(0, "# %d is%d ", colourNumber + 1);
			select = false;
		}
	}
	return colourNumber;
}

//Goes forward and checks color of the object and the distance to the ball
//Stores these values
void checkBall(int & color, int & distance){
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 30;
	motor[motorC] = 30;
	while (!checkTouch()){}
	distance = nMotorEncoder[motorA];
	motor[motorA] = 0;
	motor[motorC] = 0;
	wait10Msec(100);
	color = checkColour();
}

//Returns to the center of the scanning circle, or the initial position
void returnPos(int distance)
{
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -50;
	motor[motorC] = -50;
	while (distance>(-1)*nMotorEncoder[motorA]){}
	motor[motorA] = 0;
	motor[motorC] = 0;
}

//Assigns values to an array that stores the information around the robot
void scan(int & distance, int & angle, int & color)
{

	//stores angle of found ball
	angle = nMotorEncoder[motorA];
	//Goes forward to check the ball

	checkBall(color, distance);
	//Returns back before continuing the scan
	returnPos(distance);
}

//Rotates the robot for a given angle and direction
void rotation(int angle, bool direction)
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorC] = 0;
	if (direction)
	{
		motor[motorA] = 30;
		motor[motorC] = -30;
		while (nMotorEncoder[motorA]<angle){}
		motor[motorA] = 0;
		motor[motorC] = 0;
	}
	else if (!direction)
	{
		motor[motorA] = -30;
		motor[motorC] = 30;
		while (nMotorEncoder[motorC]<angle){}
		motor[motorA] = 0;
		motor[motorC] = 0;
	}
}

//Goes through the angle array, adding the angles after 0 to the previous one
//This is done to account for rotation from the main axis
int correctAngle(int  initialAngle, int previousAngle)
{
	int angle = initialAngle + previousAngle;
	return  angle;
}

//Moves forward for a given distance, launches the cage and returns
void getBall(int distance)
{
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 50;
	motor[motorC] = 50;
	while (distance>nMotorEncoder[motorA]){}
	motor[motorA] = 0;
	motor[motorC] = 0;
	launchCage(true);
	returnPos(distance);
	launchCage(false);
}

//
void checkRemoval()
{
	time100[0] = 0;
	wait10Msec(500);
	while ((SensorValue[S4]<8) || time100[0]<100)
	{
		wait10Msec(100);
		launchCage((time100[0]) % 2);
		wait10Msec(100);
	}
	while ((SensorValue[S4]<3)){}
	launchCage(false);
}






task main{
	//Initiatilization
	int ball[5][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int colors[5] = { 0, 0, 0, 0, 0 };
	SensorType[S2] = sensorTouch;
	SensorType[S3] = sensorCOLORFULL;
	SensorType[S4] = sensorSONAR;
	nxtDisplayString(0, " orange 2 start", );
	while (nNxtButtonPressed != 3){}


	nMotorEncoder[motorA] = 0;

	for (int i = 0; i<5; i++)
	{
		nMotorEncoder[motorA] = 0;
		motor[motorA] = 20;
		motor[motorC] = -20;
		wait10Msec(100);
		while (SensorValue[S4]>50){}
		time10[2] = 0;
		while (time10[2]<3 && SensorValue[S4]<50){}
		scan(ball[i][0], ball[i][1], ball[i][2]);
	}
	motor[motorA] = 20;
	motor[motorC] = -20;
	for (int i = 1; i<5; i++)
	{
		ball[i][1] = correctAngle(ball[i][1], ball[i - 1][1]);
	}
	nMotorEncoder[motorA] = 0;
	while ((1995 - ball[4][1])>nMotorEncoder[motorA]){}
	motor[motorA] = 0;
	motor[motorC] = 0;

	nxtDisplayString(0, "orange 2 select", );
	nxtDisplayString(1, "arrows change color", );

	for (int i = 0; i<5; i++)
	{
		colors[i] = askForInput(i);
		switch (colors[i])
		{
		case 1:
			nxtDisplayString(i + 1, "# %d is black", (i + 1));
			break;
		case 2:
			nxtDisplayString(i + 1, "# %d is blue", (i + 1));
			break;
		case 3:
			nxtDisplayString(i + 1, "# %d is green", (i + 1));
			break;
		case 4:
			nxtDisplayString(i + 1, "# %d is yellow", (i + 1));
			break;
		case 5:
			nxtDisplayString(i + 1, "# %d is red", (i + 1));
			break;
		}
		wait10Msec(300);
	}

	//Find and return ball
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (ball[j][2] == colors[i])
			{
				rotation(ball[j][1], true);
				getBall(ball[j][0]);
				//checkRemoval();
				rotation(ball[j][1], false);

			}
		}
	}
}