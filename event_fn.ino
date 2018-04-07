 /*drop detecton and encoder button detection*/

void checkButton() {
  const unsigned long LONG_DELTA = 400ul;               // hold seconds for a long press
  const unsigned long DEBOUNCE_DELTA = 10ul;        // debounce time
  static int lastButtonStatus = HIGH;                                   // HIGH indicates the button is NOT pressed
  int buttonStatus;                                                                    // button atate Pressed/LOW; Open/HIGH
  static unsigned long longTime = 0ul, shortTime = 0ul; // future times to determine is button has been poressed a short or long time
  boolean Released = true, Transition = false;                  // various button states
  boolean timeoutShort = false, timeoutLong = false;    // flags for the state of the presses

  buttonStatus = digitalRead(ENCODER_BTN);                // read the button state on the pin "BUTTON_PIN"
  timeoutShort = (millis() > shortTime);                          // calculate the current time states for the button presses
  timeoutLong = (millis() > longTime);

  if (buttonStatus != lastButtonStatus) {                          // reset the timeouts if the button state changed
    shortTime = millis() + DEBOUNCE_DELTA;
    longTime = millis() + LONG_DELTA;
  }

  Transition = (buttonStatus != lastButtonStatus);        // has the button changed state
  Released = (Transition && (buttonStatus == HIGH)); // for input pullup circuit

  lastButtonStatus = buttonStatus;                                     // save the button status

  if (timeoutLong && Released) { // long timeout has occurred and the button was just released
    idle_time = millis();

    BTN = 2; // long press
  }

 else if (timeoutShort && Released)                // short timeout has occurred (and not long timeout) and button was just released
  {
    idle_time = millis();

    BTN = 1; ///Short press
  }




}

void encoder() {
  if((millis()-lastmillis)>50){
  volatile int lastEncoded = 0;
  unsigned int encoderValue = 1;
  unsigned int lastencoderValue = 1;


  // Read A and B signals
  boolean A_val = digitalRead(ENCODER_PINA);
  boolean B_val = digitalRead(ENCODER_PINB);

  int encoded = (A_val << 1) | B_val; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded;
  if (encoderValue > lastencoderValue)
  {
    idle_time = millis();

    BTN = 3;
    lastencoderValue = encoderValue;
  }

  else if (encoderValue < lastencoderValue)
  {
    idle_time = millis();
    BTN = 4;
    lastencoderValue = encoderValue;

  }
  }
 lastmillis = millis();


}

/*Drop dectection interrupt code*/
void checkdrop()
{
// if (millis()- > 200) {  //detect drop id time b/w drops is > 200ms.. to avoid double detection of drops and too limit dectection rate
//   _dripo.setTime(timeElapsed);    //send time b/w drops for calculations
logtime = millis()-dropmillis;  // for preclincal studies log each drop
drop_detect = true;
inf_msg_send = true;
////   logstatus = 1;
//   timeElapsed = 0;
   detect1 = 0;                    //  blinker on each drop
    detect2 = 1;
    dcount++;
// //   outofrange = false;
// }

// else {
//      outofrange = true;
//  timeElapsed = 0;
//
// }
 dropmillis = millis();


}

int get_button()
{
  int button = BTN;
  BTN = 0;
  return button;

}





int checkLongHold()
{
  int event = 0;
  // Read the state of the button
  buttonVal = digitalRead(ENCODER_BTN);
  // Button pressed down
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce) {
    downTime = millis();

    longHoldEventPast = false;

  }

  // Trigger "long" hold
  if (buttonVal == LOW && (millis() - downTime) >= longHoldTime) {
    if (not longHoldEventPast) {
      event = 5;
      longHoldEventPast = true;
    }
  }

  buttonLast = buttonVal;
  
  return event;
}

