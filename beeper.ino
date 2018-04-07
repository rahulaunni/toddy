
int beeper(int times){
   if(times != 0){
    for (long j=0;j<times;j++){
       for (long i = 0; i < 250; i++ )
        {
            digitalWrite(15, HIGH);
            delayMicroseconds(500);
            digitalWrite(15, LOW);
            delayMicroseconds(500);
        } 
      delay(200);
      yield();
    }
              
   }
   return 0;
}

