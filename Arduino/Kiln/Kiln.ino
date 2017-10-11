/*
 * Kiln.ino
 *
 * Created: 10/11/2017 4:13:31 PM
 * Author: GUY
 */ 

void setup()
{

	  /* add setup code here, setup code runs once when the processor starts */
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

}

void loop()
{

	  /* add main program code here, this code starts again each time it ends */
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is acive low on the ESP-01)
  delay(100);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(100);
}
