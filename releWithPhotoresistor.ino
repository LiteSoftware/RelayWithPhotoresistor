/*
   Copyright [yyyy] [name of copyright owner]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
   More details: https://udfsoft.com
*/

const int sensorPin = A0;
const int ledPin = 9;
const int relayPin = 10;

int sensorValue = 0;
int sensorMin = 1023;
int sensorMax = 0;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);

  while(millis() < 5000) {
    sensorValue = analogRead(sensorPin);
    if (sensorValue > sensorMax) sensorMax = sensorValue;
    if (sensorValue < sensorMin) sensorMin = sensorValue;
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);
  
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  Serial.println(sensorValue);

  if (sensorValue < 10) {
    digitalWrite(relayPin, HIGH);
    analogWrite(ledPin, 255);
    delay(5000);
  } else {
    analogWrite(ledPin, 0);
    digitalWrite(relayPin, LOW);
  }
  delay(100);
}
