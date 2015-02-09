// TONES  ==========================================
#define  c4     262 
#define  d4     294 
#define  e4     330 
#define  f4     349 
#define  g4     392 
#define  a4     440 
#define  b4     494 
#define  c5     523 
// Define a special note, 'R', to represent a rest
#define  R     0

int speakerOut = 9;

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
int melody[] = {  c4,  d4,  e4,  f4,  g4,   g4,  a4,  a4,  a4,  a4, g4 };
int beats[]  = { 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1 };
int MAX_COUNT = 11; // Melody length, for looping.

long tempo = 1000;  // Set overall tempo
long pauseTime = tempo/25;  // Set length of pause between notes
int frequency = 0;  
int beat = 0;
long duration  = 0;

void setup() {
  pinMode(speakerOut, OUTPUT);
}

void loop() {
 // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    frequency = melody[i];
    beat = beats[i];
    duration = tempo / beat; // Set up timing
    tone(speakerOut, frequency, duration);
    delay(duration);
    delay(pauseTime); // A pause between notes...
    }
  delay(500); // A pause between melodies.
}

