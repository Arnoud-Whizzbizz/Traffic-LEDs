// Whizzbizz.com - Arnoud - July 2024
//
// Traffic LEDs for two directions. Sequences are configurable in an array of structs.
//
// The cycle in which the colored lights alternate or burn at the same time differs from country to country.
// In the Netherlands, only one light of the tri-color traffic is on at a time. Here in the Netherlands, the
// red light jumps directly to green. In other countries, for example Germany, Hungary, Great Britain, Austria, 
// Switzerland, Poland, Lithuania, Norway, Russia and Sweden, before the red light turns green, the orange light
// is lit together with the red light to indicate that the green light will be lit soon.
//
// Written for Arduino. Mega board was used, but should also work with Uno and other types.
// This Sketch also reads two inputs (touch sensors) at inputs D12 and D13
// Sensor 1 off/false shows the 'Dutch traffic lights sequence'
// Sensor 1 on/true switches to the 'German traffic lights sequence'
// When sensor 2 is on/true it overrules and only the two yellow lights will blink
//

// Define digital input pins of touch sensors...
#define touchSensor1 12
#define touchSensor2 13

// Define pins for traffic LED lights
#define redLight1    2
#define yellowLight1 3
#define greenLight1  4
#define redLight2    5
#define yellowLight2 6
#define greenLight2  7

#define debug 0 // Set to 1 for logging to serial monitor...

// Define struct for traffic light sequence
struct LightsStep {
  int duration; // Time in ms for this step in the sequence
  bool red1;    // Red light 1
  bool yellow1; // Yellow light 1
  bool green1;  // Green light 1
  bool red2;    // Red light 2
  bool yellow2; // Yellow light 2
  bool green2;  // Green light 2
};

uint8_t controlSequence = 0; // 1=nl, 2=de, 3=blink. Set to 0 to force initialisation...
uint8_t SequenceStep = 0;

// Define array of structs for traffic light sequences
LightsStep trafficControl_nl[] = {
  { 5000, true, false, false, false, false, true }, // Red1 & Green2 are on...
  { 3000, true, false, false, false, true, false }, // Red1 stays, Green2 --> Yellow2...
  { 5000, false, false, true, true, false, false }, // Green1 & Red2 are on...
  { 3000, false, true, false, true, false, false }  // Green1-->Yellow1, Red2 stays on...
};

LightsStep trafficControl_de[] = {
  { 5000, true, false, false, false, false, true }, // Red1 & Green2 are on...
  { 3000, true, true, false, false, true, false },  // Red1+Yellow1 are on, Green2 --> Yellow2...
  { 5000, false, false, true, true, false, false }, // Green1 & Red2 are on...
  { 3000, false, true, false, true, true, false },  // Green1-->Yellow1, Red2+Yellow2 are on...
};

LightsStep trafficControl_blink[] = {
  { 800, false, true, false, false, false, false },  // Yellow1 & Yellow2 on...
  { 800, false, false, false, false, true, false } // All lamps off...
};

int SequenceSteps; // Number of steps in active sequence. This is size/8 because each struct has a size of 8 bytes...
LightsStep *currentSequence; // Pointer to the current traffic control sequence...

void doLightsStep(LightsStep thisLights) {
  // Light the LED lights of both traffic light posts according this step...
  digitalWrite(redLight1, thisLights.red1);
  digitalWrite(yellowLight1, thisLights.yellow1);
  digitalWrite(greenLight1, thisLights.green1);
  digitalWrite(redLight2, thisLights.red2);
  digitalWrite(yellowLight2, thisLights.yellow2);
  digitalWrite(greenLight2, thisLights.green2);

  // Delay for the duration of this step in the sequence...
  if (debug) {
    Serial.print("Delay: ");
    Serial.println(thisLights.duration);
    Serial.println();
  }
  delay(thisLights.duration);
}

void setup() {
  // Initialize serial communication at 19200 baud rate
  Serial.begin(19200);

  // Set the input pins as inputs
  pinMode(touchSensor1, INPUT);
  pinMode(touchSensor2, INPUT);

  // Initialize traffic light pins as outputs
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
  pinMode(redLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(greenLight2, OUTPUT);
}

void loop() {
  // Read the status of the two touch sensors...
  if (digitalRead(touchSensor2)) {
    // Blink mode overrules any traffic control...
    if (controlSequence!=3) {
      currentSequence = trafficControl_blink;
      controlSequence = 3;
      SequenceStep = 0;
      SequenceSteps = (sizeof(trafficControl_blink)/sizeof(trafficControl_blink[0]));
    }
  } else {
    if (digitalRead(touchSensor1)) {
      if (controlSequence!=2) {
        currentSequence = trafficControl_de;
        controlSequence = 2;
        SequenceStep = 0;
        SequenceSteps = (sizeof(trafficControl_de)/sizeof(trafficControl_de[0]));
      }
    } else {
      if (controlSequence!=1) {
        currentSequence = trafficControl_nl;
        controlSequence = 1;
        SequenceStep = 0;
        SequenceSteps = (sizeof(trafficControl_nl)/sizeof(trafficControl_nl[0]));
      }    
    }
  }

  if (debug) {
    Serial.print("controlSequence: ");
    Serial.println(controlSequence);
    Serial.print("SequenceStep: ");
    Serial.println(SequenceStep);
    Serial.print("SequenceSteps: ");
    Serial.println(SequenceSteps);
  }

  // Do the current traffic light step of the sequence...
  doLightsStep(currentSequence[SequenceStep]);

  // Increment current sequence index for next step...
  SequenceStep++;
  
  // Check if current sequence index is greater than or equal to the number of steps in this sequence...
  if (SequenceStep >= SequenceSteps) {
    // Reset current sequence index to 0...
    SequenceStep = 0;
  }
}