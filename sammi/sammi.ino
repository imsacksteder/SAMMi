//www.elegoo.com
//2016.12.08
#include "SR04.h"
#include <Stepper.h>


//sr04 vars
#define TRIG_PIN 11
#define ECHO_PIN 12

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

//step vars
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
unsigned long step_delay = 0; // delay between steps, in ms, based on speed
//const int rolePerMinute = 15;
const int STOP_DISTANCE = 25;



// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 7, 9, 8, 10);

//2nd motor
Stepper myStepper2(stepsPerRevolution, 3, 5, 4, 6);


void setup() {
   Serial.begin(9600);
   //delay(1000);

   myStepper.setSpeed(rolePerMinute);
   myStepper2.setSpeed(rolePerMinute);
  // initialize the serial port:
  //Serial.begin(9600);
}

void loop() {
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   //Serial.println(a + "cm");
   //delay(0);

   //delay(500);
   //forward();
   //delay(500);
   //forward();
   //delay(700);
    //turnNinty(185);
   //delay(20000);

   //if(a <= STOP_DISTANCE){
//      //backward();
//      for(int i = 0; i < 30; i++){
//        turnRight();
//      }
//      backward();
//      turnRight();
      //Serial.println("entering findPath()"); 
      //findPath(a);
      //delay(700);
      //turnRightPass(40);
      //checkDistanceDeriv(a);
      //Serial.println("done with turn");
      //delay(700);
     // } else {
      Serial.println("entering forward"); 
      //for(int i; i< 2000; i++){
      //  forward();
      //  forward();
      //  forward();
      //  forward();
      //  forward();
      //  forward();
      //  forward();
      //  forward();  
      //}
      runPerimeter(a);
  // }
   //Serial.println("loop!");
}

//Movement
void forward() {  
  // step one revolution  in one direction:
  //Serial.println("forward");
  
  for(int i =0; i < 200; i++){
      myStepper.step(-1);
      myStepper2.step(1);
    }
  //myStepper.step(stepsPerRevolution);
  //myStepper2.step(-stepsPerRevolution);
  //delay(500);
  delay(0);
}
  
void backward(){
  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  
  for(int i=0; i< 200; i++){
    myStepper.step(1);
    myStepper2.step(-1);
  }

  
  //myStepper.step(-stepsPerRevolution);
  //myStepper2.step(stepsPerRevolution);
  //delay(500);
  delay(0);
}


void turnRight(){
    for(int i=0; i< 200; i++){
      myStepper.step(1);
      myStepper2.step(1);
    }
  }

void turnRightPass(int stepCount){
  //for(int i=0; i< 40; i++){
      myStepper.step(-stepCount);
      myStepper2.step(-stepCount);
    //}
  }

void turnLeftPass(int stepCount){
//for(int i=0; i< 40; i++){
    myStepper.step(stepCount);
    myStepper2.step(stepCount);
  //}
}

void turnLeft(){
    for(int i=0; i< 200; i++){
      myStepper.step(-1);
      myStepper2.step(-1);
    }
  }

void turnNinty(long stepCount){
   for(int i=0; i< 20; i++){
      //myStepper.step(-1);
      //myStepper2.step(-1);
      myStepper.step(-stepCount);
      myStepper2.step(-stepCount);
   }
  }

//  Pathing
void findPath(long b){
    //a=sr04.Distance();
    Serial.println("Finding path");
    while(b < STOP_DISTANCE){
      
      Serial.println("Entering while"); 
        for(int i = 0; i <= 120; i++){ //check right
            turnRight();
            turnRight();
            b=sr04.Distance();
            if(b > STOP_DISTANCE + 30){ Serial.println("BREAKRIGHT"); break;  }
        }
        for(int i = 0; i <= 240; i++){
            turnLeft(); //check left
            turnLeft(); 
            turnLeft(); 
            turnLeft(); 
            b=sr04.Distance();
            if(b > STOP_DISTANCE + 30){ Serial.println("BREAKLEFT"); break;  }
        }
        Serial.println("while");
    }
}

void checkDistanceDeriv(long currentDistance){
      Serial.println("\nBegin Check Distance");
      Serial.println("\tCurrent Distance" + currentDistance);
      int steps = 555;
      long prevDist;
      long postDist;
      bool directionRight = false;
      currentDistance = sr04.Distance();
      Serial.println(currentDistance + "cm");
      
      while(currentDistance <= STOP_DISTANCE){
        Serial.println("\tStarting while...");

            
            //turnRightPass(40);
            //i = i++;
            String ourDirection = (directionRight==true) ? "Right" : "Left";
            Serial.println("\n\tOur Direction: " + ourDirection);
            if(directionRight){ // If we want to check right
              
              prevDist = sr04.Distance(); // Sample first point
              
              char str1[20];
              sprintf(str1, "\tfirst point: %d cm", prevDist);
              Serial.println(str1);
              
                //for(int i = 0; i < 15; i++){ //Move to Sample other point
                    turnLeftPass(steps);
                  //}
              postDist = sr04.Distance(); // Sample second point
              
              char str2[20];
              sprintf(str2, "\tsecond point: %d cm", postDist);
              Serial.println(str2);
              
                if(prevDist > postDist){ // if first is further turn around
                  Serial.println();
                  char str3[20];
                  sprintf(str3, "\t%d > %d", prevDist, postDist);
                  Serial.println(str3);
                  directionRight = true;
                }
            } else if(!directionRight){ // else if Direction is left

                prevDist = sr04.Distance(); // sample first point

              
                char str5[20];
                sprintf(str5, "\tfirst point: %d cm", prevDist);
                Serial.println(str5);

              
                //for(int i = 0; i < 15; i++){
                    turnRightPass(steps);          // Move to sample next point
                //  }

                postDist = sr04.Distance(); // Sample next point
                Serial.print(postDist);
                Serial.println("cm");

                
              char str6[20];
              sprintf(str6, "\tsecond point: %d cm", postDist);
              Serial.println(str6);
              int secondDist = postDist;
              
                if(prevDist > secondDist){ // see above
                  Serial.print(secondDist);
                  Serial.println("cmcm");  
                  
                  char str4[20]; 
                  sprintf(str4, "\t%d > %d",prevDist, secondDist);
                  Serial.println(str4);
                    directionRight = false; //see above
                }
            }
            if(currentDistance > STOP_DISTANCE + 30){ Serial.println("BREAKLEFT"); break;  }
        }
        Serial.println("Broke Out of While");
  }
  //}


  void runPerimeter(long dist){
      while(dist > STOP_DISTANCE){
          dist = sr04.Distance();
          //for(int i = 0; i < 1000; i++){ //Smoother wheels, but 1000 is waaaay too big
            forward();
            if(dist <= STOP_DISTANCE){
                turnNinty(100);
                //break;
              }
          //}
        }
    }
