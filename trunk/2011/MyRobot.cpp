#include "WPILib.h"
#include "Arm.h"
#include "LineTracking.h"

class RobotDemo : public SimpleRobot
{
		Gyro		   	  *gyro;
		Solenoid	  *shifting;
		Solenoid	 *shifting2;
		DigitalInput    *toggle;
		Ultrasonic       *sonar;
		Ultrasonic      *sonar2;
		Relay			 *spike;
		LineTracking *myTracker;
        Arm         *ParadoxArm;
        RobotDrive	   *myRobot; // robot drive system
        Joystick 		*stickL; // only joystick
        Joystick   		*stickR;
        DriverStationLCD 	*ds;
        
        float GyDrift;
        float GyCorrected;
        	

public:
        RobotDemo() 
        {
        		gyro		= new Gyro 		   (1);
        		shifting	= new Solenoid	   (8);
        		shifting2	= new Solenoid	   (7);
        		sonar		= new Ultrasonic (1,2);        		
        		sonar2		= new Ultrasonic (3,4);
        		toggle		= new DigitalInput (8);
        		spike		= new Relay		   (5);
        		myTracker	= new LineTracking(1,2,3);
        		ParadoxArm  = new Arm(1,2,3,4,13,14,1,2,10);
        		myRobot 	= new RobotDrive(1,2,3,5); // these must be initialized in the same order
                stickL  	= new Joystick(1);             // as they are declared above.
                stickR		= new Joystick(2);
                ds			= DriverStationLCD::GetInstance();
                
        }
        void Autonomous(void)
        {
        	Timer *timer = new Timer();
        	timer->Start();
        	timer->Reset();
        	float GyDrift;
        	float GyCorrected;
        	gyro->Reset();
        	GyDrift = 0.0;
        	Wait(1.0);	
        	GyDrift = gyro->GetAngle();
        	GyCorrected -= GyDrift;
        	gyro->Reset();
        	GyCorrected = gyro->GetAngle() - (0.01 * GyDrift);
        	
        	while(timer->Get() < 10.0)
        	{
        		if (timer->Get()== 3.2)
        		{
        			bool toggleValue = toggle->Get()?1:0;
        			if (toggleValue == 1) 
        			{	
        				//while (GyCorrected != -18)
        				//{
        					myRobot->Drive(-0.5,-0.3);
        					Wait (0.5);
        				//}
        			}
        			else
        			{
        				//while (GyCorrected != 18)
        				//{
        					myRobot->Drive(-0.5,0.3);
        					Wait (0.5);
        				//}
        			}
        		}	
        		myRobot->Drive(myTracker->GetSpeed(),myTracker->GetTurn());
        		Wait (0.5);
        	}
        }
        void OperatorControl(void)
        {
                myRobot->SetSafetyEnabled(false);
                UINT32 arm_setpoint;
                while (IsOperatorControl())
                {
                		sonar->SetAutomaticMode(1);
                		if (stickL->GetRawButton(6)) 
                		{
                			shifting->Set(1);
                			shifting2->Set(0);
                		}
                		else
                		{
                			shifting->Set(0);
                			shifting2->Set(1);
                		}
                		if (stickR->GetRawButton(1)) arm_setpoint=1;
                		if (stickR->GetRawButton(2)) arm_setpoint=2;
                		if (stickR->GetRawButton(3)) arm_setpoint=3;
                		if (stickR->GetRawButton(4)) arm_setpoint=4;
                		if (stickR->GetRawButton(5)) arm_setpoint=5;
                		if (stickR->GetRawButton(6)) arm_setpoint=6;
                		ParadoxArm->SetPosition(arm_setpoint);
                		ParadoxArm->Set(stickR->GetY());
                        ds->Clear();
                        ds->Printf(DriverStationLCD::kUser_Line1, 1, "Sonar: %f\n", myTracker->GetTurn());
                        ds->UpdateLCD();
                        myRobot->TankDrive(stickL->GetTwist(),stickL->GetY()); // drive with arcade style (use right stick)
                        Wait(0.0005); // wait for a motor update time
                }
        }
};

START_ROBOT_CLASS(RobotDemo);