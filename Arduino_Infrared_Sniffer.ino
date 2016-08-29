/* 	Arduino Infrared Sniffer,
	This program captures raw Ir frames from any remote control
	that uses an Ir transmitter and send it to the Serial terminal .}
    Copyright (C) 2016  Med Chaouki Chamsi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#define infraredSensor 6					//the infrared sensor is at pin 6 of the arduino (you are free to choose any other pin if you like)
#define baudRate 9600						//choosing a baudrate =9600 (it the most common value you can change it if you like )
unsigned int rawData[200];				
int intervalCounter=0;
int value=0;
int oldValue=0;
int flag=0;
unsigned int timeInterval=0;


void setup() {
Serial.begin(baudRate);  					//initialisation of the Serial communication at a baudrate=9600
pinMode(infraredSensor,INPUT);				//initialisation of the infrared sensor pin as INPUT 
value=digitalRead(infraredSensor);			//initialisation of the value and the oldValue variables to the initial state of the sensor
oldValue=digitalRead(infraredSensor);
}


void loop() {

/*
this section handels the communication between the Serial terminal and the board
*/

											// send a char from the terminal to request the recorded frame
if(Serial.available())						// if there is a char sent from the terminal , the code returns the captured frame 
{
  
  Serial.read();							//read the sent char to remove it from the serial buffer 

  if(intervalCounter>0)						//if the frame size is greater than zero (we successfully captured a frame) 
  {
  	Serial.print("(");
  	Serial.print(intervalCounter);			//send the length of the Ir frame
  	Serial.print(")");
  	for(int i=0;i<intervalCounter;i++)		//send the  captured Ir frame
  	{
    	Serial.print(irVals[i]);
    	Serial.print(",");
    	}
  	}
  else										//if the frame size equals zero , it mean that there is a problem with the sensor ,so check your wiring please
  {

	Serial.print("No frame detected please check your wiring, reset the board and try again");


  	}	  
  }
  
 
 /*
 this section handels capturing the Ir data frame
 */ 

value=digitalRead(infraredSensor);			//capture the state of the infrared sensor

//if the current sensor value is diffrent from the old state for the first time (flag==0) we start capturing the time interval 
if((value!=oldValue)&&(flag==0))			
{

  timeInterval=micros();            //register the starting time of the signal
  oldValue=value;                   //update the oldValue
  flag=1;                           //set the flag to 1
  }
//if the current sensor value is diffrent from the old state for the secound time (flag==1) we compute the real time interval 
 else if((val!=oldVal)&&(flag==1))
{

  timeInterval=micros()-timeInterval;  		//calculate the real time interval
  rawData[intervalCounter]=timeInterval; 	//save the value
  intervalCounter++;                  		//incriment the counter
 
  flag=0;                           		//set the flag to 0
  }
 

  

}
