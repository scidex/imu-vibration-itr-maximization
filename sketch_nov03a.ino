int motorPin1 = 15; // digital pin D15 for vibration motor 1
int motorPin2 = 18; // digital pin D18 for vibration motor 2
int motorPin3 = 19; // digital pin D18 for vibration motor 2
int motorPin4 = 21; // digital pin D18 for vibration motor 2
int sender=2; //The reciving number

void setup ()
{
pinMode ( motorPin1 , OUTPUT );
pinMode ( motorPin2 , OUTPUT );
pinMode ( motorPin3 , OUTPUT );
pinMode ( motorPin4 , OUTPUT );
}


void loop ()
{


/*  
  digitalWrite(motorPin3, HIGH);
  delay(1000);

  digitalWrite(motorPin3, LOW);
  delay(1000);


  digitalWrite(motorPin4, HIGH);
  delay(2000);

  digitalWrite(motorPin4, LOW);
  delay(2000);

*/
 /* digitalWrite(motorPin3, HIGH);
  delay(1000);

  digitalWrite(motorPin3, LOW);
  delay(1000);

/*
  digitalWrite(motorPin4, HIGH);
  delay(2000);

  digitalWrite(motorPin4, LOW);
  delay(2000);
  */
     

  
  
/*
  for (int sender = 0; sender <= 9.; sender++) 
  {    
    if (sender == 1) 
        {
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , HIGH );
           digitalWrite ( motorPin3 , LOW );
           digitalWrite ( motorPin4 , LOW );
        } 
    else if (sender ==2) 
        {
           digitalWrite ( motorPin2 , HIGH );
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin1 , LOW );
           digitalWrite ( motorPin3 , LOW );
        } 
    else if (sender ==3)
        {
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin1 , LOW );
           digitalWrite ( motorPin2 , LOW );
        }
    else if (sender ==4)
        {
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin3 , LOW );
           digitalWrite ( motorPin2 , LOW );
        }
        else if (sender ==5)
        {
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin2 , LOW );
        }
        else if (sender ==6)
        {
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , HIGH );
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin4 , LOW );
        }
        else if (sender ==7)
        {
           digitalWrite ( motorPin2 , HIGH );
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin1 , LOW );
        }
        else if (sender ==8)
        {
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , LOW );
        }
        else if (sender ==9)
        {
           digitalWrite ( motorPin3 , HIGH );
           digitalWrite ( motorPin4 , HIGH );
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , HIGH );
        }
        else if (sender ==0)
        {
           digitalWrite ( motorPin3 , LOW );
           digitalWrite ( motorPin4 , LOW );
           digitalWrite ( motorPin1 , HIGH );
           digitalWrite ( motorPin2 , LOW );
        }
    delay (2000);
    
    digitalWrite ( motorPin3 , LOW );
    digitalWrite ( motorPin4 , LOW );
    digitalWrite ( motorPin1 , LOW );
    digitalWrite ( motorPin2 , LOW );
    delay(1000);
        
  }
  */
  while(1)

    {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, HIGH);
      delay(2000);  
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);
      
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);

      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      digitalWrite(motorPin1, LOW);
      delay(1000);
      
      
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
