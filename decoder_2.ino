int motorPin3 = 15; // digital pin D15 for vibration motor 1
int motorPin4 = 18; // digital pin D18 for vibration motor 2
int motorPin1 = 19; // digital pin D18 for vibration motor 2
int motorPin2 = 21; // digital pin D18 for vibration motor 2
int sender; //The reciving number

void setup ()
{
pinMode ( motorPin1 , OUTPUT );
pinMode ( motorPin2 , OUTPUT );
pinMode ( motorPin3 , OUTPUT );
pinMode ( motorPin4 , OUTPUT );
}


void loop ()
{

  for (int test_round = 0; test_round < 10; test_round++) 
  {
    for  (sender = 0; sender <9; sender++)
    {    
      if (sender == 1) 
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender ==2) 
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender ==3)
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender ==4)
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender ==5)
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender ==6)
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender ==7)
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender ==8)
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender ==9)
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender ==0)
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
    delay (750);

    //PAUSE
    digitalWrite ( motorPin3 , LOW );
    digitalWrite ( motorPin4 , LOW );
    digitalWrite ( motorPin1 , LOW );
    digitalWrite ( motorPin2 , LOW );
    delay(750);       
  }
  /*
  while(1)

    {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(2000);  
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);
      
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);

      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);

      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);
  */
  
      
    }
}



//digitalWrite ( motorPin1 , HIGH );
//digitalWrite ( motorPin2 , HIGH );
//digitalWrite ( motorPin3 , HIGH );
//digitalWrite ( motorPin4 , HIGH );
//delay (1000);

//digitalWrite ( motorPin1 , LOW );
//digitalWrite ( motorPin2 , LOW );
//digitalWrite ( motorPin3 , LOW );
//digitalWrite ( motorPin4 , LOW );

//delay (1000);
