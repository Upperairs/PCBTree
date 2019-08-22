#include <EEPROM.h>
int addr = 0;
byte value;

int ledBlu = 3;
int ledGrn = 5;
int ledRed = 6;;
int speakerPin = A2;

int switcher = 0;
int x = 0;
int tempo = 140;
long Number = 0;
long randRed;
long randGrn;
long randBlu;

//Frosty the Snowman
//number of notes in song
int length = 117;
//notes
char notes[] = "gefgCbCDCbagbCDCbaagCegagfefggefgCbCDCbagbCDCbaagCegagfedccaaCCbagefagfeeddggbbDbCDCbaggefgCbCDCbagbCDCbaagCegaggabC ";
//length of each note
int beats[] = { 4,3,1,2,4,1,1,2,2,2,2,6,1,1,2,2,2,1,1,2,2,2,1,1,2,2,2,2,8,4,3,1,2,4,1,1,2,2,2,2,6,1,1,2,2,2,1,1,2,2,2,1,1,2,2,2,2,6, 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,1,1,2,2,2,2,6 ,4,3,1,2,4,1,1,2,2,2,2,6,1,1,2,2,2,1,1,2,2,2,1,1,4,4,4,4,8,8};
//End Frosty the Snowman

//Ding Dong Merrily on High
int length1 = 73;
//notes
char notes1[] = "ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg "; // a space represents a rest
//length of each note
int beats1[] = { 2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 };
//End Ding Dong Merrily on High

//God Rest Ye Merry Gentlemen
int length2 = 69;
//notes
char notes2[] = "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed";
//length of each note
int beats2[] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 };
//End God Rest Ye Merry Gentlemen

//Hark the Herald
int length5 = 77;
//notes
char notes5[] = "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ";
//length of each note
int beats5[] = {2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8};
//End Hark the Herald

//O come all Ye Faithful
int length6 = 64;
//notes
char notes6[] = "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ";
//length of each note
int beats6[] = { 2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8 };
//End O come all Ye Faithful

//O Come O Come Emmanuel
int length7 = 63;
char notes7[] = "egbbbaCbagabgegasedeaaeesgsedgabbbaCbag DD bb baCdagabgegasede ";
int beats7[] = { 2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,2,2,6,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,4,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,8,8 };
//End O Come O Come Emmanuel


//function to play a tone at a set frequency for a given duration
void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

//function to play a note for a duration - calls playTone
void playNote(char note, int duration)
{
  //these two arrays allow us to get the frequency associated with a letter (note)
  char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' , 'F'};
  int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758, 730};

  //calls playTone to play the tone
  for (int i = 0; i < 13; i++)
  {
    if (names[i] == note)
    {
      playTone(tones[i], duration);
    }
  }
}

//function to blink lights only
void lights()
{
      randBlu = random(0,200);
      randGrn = random(0,200);
      randRed = random(0,200);
      
      analogWrite(ledBlu, randBlu);
      analogWrite(ledGrn, randGrn);
      analogWrite(ledRed, randRed);

     delay(1000);
}


//function to blink the lights and play the song - acts as a mode
void playFrosty()
{
  Number = (Number + 1);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length; i++)
  {
    //rests
    if (notes[i] == ' ')
    {
      delay(beats[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes[i], beats[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}
//function to blink the lights and play the song - acts as a mode
void playDing()
{
  Number = (Number + 1);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length1; i++)
  {
    //rests
    if (notes1[i] == ' ')
    {
      delay(beats1[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes1[i], beats1[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}

//function to blink the lights and play the song - acts as a mode
void playGod()
{
  Number = (Number + 1);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length2; i++)
  {
    //rests
    if (notes2[i] == ' ')
    {
      delay(beats2[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes2[i], beats2[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}

void playHark()
{
  Number = (Number + 1);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length5; i++)
  {
    //rests
    if (notes5[i] == ' ')
    {
      delay(beats5[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes5[i], beats5[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}

void playFaithful()
{
  Number = (Number + 1);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length6; i++)
  {
    //rests
    if (notes6[i] == ' ')
    {
      delay(beats6[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes6[i], beats6[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}

void playOCome()
{
  Number = (0);
  EEPROM.write(addr, Number);
  for (int i = 0; i < length7; i++)
  {
    //rests
    if (notes7[i] == ' ')
    {
      delay(beats7[i] * tempo); // rest
    }
    //notes
    else
    {
      playNote(notes7[i], beats7[i] * tempo);
    }

    //randomly lights up one LED in time with the music
    switcher = random(0,3);
    if (switcher == 0)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, HIGH);
      digitalWrite(ledRed, LOW);
    }
    if (switcher == 1)
    {
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, HIGH);
    }
    if (switcher == 2)
    {
      digitalWrite(ledBlu, HIGH);
      digitalWrite(ledGrn, LOW);
      digitalWrite(ledRed, LOW);
    }

    // pause between notes
    delay(tempo / 2);
  }
}

void setup()
{
  Serial.begin(9600);
  Number = EEPROM.read(addr);
  //pinmodes
  pinMode(ledBlu, OUTPUT);
  pinMode(ledGrn, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop()
{
 if (x == 0) 
 {
  
  Serial.println(Number);
   
   if (Number == 0)
   {
   playFrosty();
   x = 1;
   }
   else if (Number == 1)
   {
   playDing();
   x = 1;
   }
   else if (Number == 2)
   {
   playGod();
   x = 1;
   }
   else if (Number == 3)
   {
    playHark();
   x = 1;
   }
   else if (Number == 4)
   {
   playFaithful();
   x = 1;
   }
   else if (Number == 5)
   {
   playOCome();
   x = 1;
   }
 }
 else lights();
 {  
 }
}
