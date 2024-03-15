#include <PololuMaestro.h>

/////////////17 16 15)2L Arduino 2 1 0)0R
/////////////14 13 12)1L         5 4 3)1R
/////////////11 10 9)0L          8 7 6)2R

#include <SoftwareSerial.h>
SoftwareSerial maestroSerial(8, 9);

MiniMaestro maestro(maestroSerial);
int rdy;
int up = 0;
bool loopActionsFlag = false;
void setup()
{
  maestroSerial.begin(9600);
  Serial.begin(115200);
  Serial3.begin(9600);
  Serial.setTimeout(5);
  for (int kanal = 0; kanal < 18; kanal++)
  {
    maestro.setSpeed(kanal, 25);
    maestro.setAcceleration(0, 50);
  }
  /*
  maestro.setSpeed(0, 10);
  maestro.setAcceleration(0,127);*/
  rdy = millis();
  sit();
}

void loop()
{
  if (up == 1)
  {
    stand();
  }
  if (Serial3.available())
  {
    String line = Serial3.readString();
    Serial.println(line);
    if (line.indexOf("up") > -1)
    {
      standup();
    }
    if (line.indexOf("sit") > -1)
    {
      sit();
    }
    if (up == 1)
    {
      if (line.indexOf("wave0") > -1)
      {
        legRwave(0, 4);
      }
      else if (line.indexOf("wave1") > -1)
      {
        legRwave(1, 4);
      }
      else if (line.indexOf("wave2") > -1)
      {
        legRwave(2, 4);
      }
      else if (line.indexOf("wave3") > -1)
      {
        legLwave(0, 4);
      }
      else if (line.indexOf("wave4") > -1)
      {
        legLwave(1, 4);
      }
      else if (line.indexOf("wave5") > -1)
      {
        legLwave(2, 4);
      }
      else if (line.indexOf("everyOther1") > -1)
      {
        everyOther1();
      }
      else if (line.indexOf("everyOther2") > -1)
      {
        everyOther2();
      }
      else if (line.indexOf("forwards") > -1)
      {
        forwards();
      }
      else if (line.indexOf("backwards") > -1)
      {
        backwards();
      }
      else if (line.indexOf("loop") > -1)
      {
        loopActions();
      }
      else if (line.indexOf("breakLoop") > -1)
      {
        loopActions();
      }
    }
  }
}
void sit()
{
  up = 0;
  for (int kanal = 0; kanal < 18; kanal++)
  {
    maestro.setSpeed(kanal, 50);
    maestro.setAcceleration(0, 100);
  }
  legR(0, 3800, 3000, 4000);
  legR(1, 5600, 4000, 4000);
  legR(2, 5000, 3600, 4000);

  legL(0, 8500, 8500, 4000);
  legL(1, 16000, 9000, 5000);
  legL(2, 8500, 8500, 5000);
  delay(5000);
}
void standup()
{
  for (int kanal = 0; kanal < 18; kanal++)
  {
    maestro.setSpeed(kanal, 50);
    maestro.setAcceleration(0, 100);
  }
  stand();
  delay(2000);
  up = 1;
  for (int kanal = 0; kanal < 18; kanal++)
  {
    maestro.setSpeed(kanal, 25);
    maestro.setAcceleration(0, 50);
  }
}
void stand()
{
  legR(0, 6000, 7000, 3700); // Prawy Przód
  legR(1, 7400, 7250, 4500); // Prawy Środek
  legR(2, 7400, 6900, 4000); // Prawy Tył

  legL(2, 6000, 4800, 5000); // Lewy Przód
  legL(1, 7300, 5000, 4500); // Lewy Środek
  legL(0, 6800, 5550, 4000); // Lewy Tył
}
void legR(int kanal, int kolano, int obudowaPion, int obudowaPoziom)
{
  maestro.setTarget(0 + (kanal * 3), kolano);
  maestro.setTarget(1 + (kanal * 3), obudowaPion);
  maestro.setTarget(2 + (kanal * 3), obudowaPoziom);
}
void legL(int kanal, int kolano, int obudowaPion, int obudowaPoziom)
{
  maestro.setTarget(11 + (kanal * 3), kolano);
  maestro.setTarget(10 + (kanal * 3), obudowaPion);
  maestro.setTarget(9 + (kanal * 3), obudowaPoziom);
}
void legRwave(int kanal, int ilosc)
{
  maestro.setSpeed(0 + (kanal * 3), 50); // kolano
  maestro.setAcceleration(0 + (kanal * 3), 200);
  maestro.setSpeed(1 + (kanal * 3), 50); // obudowa pion
  maestro.setAcceleration(1 + (kanal * 3), 200);

  maestro.setTarget(1 + (kanal * 3), 1000);
  delay(500);
  for (int x = 0; x < ilosc; x++)
  {
    maestro.setTarget(0 + (kanal * 3), 9000);
    delay(500);
    maestro.setTarget(0 + (kanal * 3), 6000);
    delay(500);
  }
  maestro.setSpeed(0 + (kanal * 3), 25);
  maestro.setAcceleration(0 + (kanal * 3), 127);
  maestro.setSpeed(1 + (kanal * 3), 25);
  maestro.setAcceleration(1 + (kanal * 3), 127);
  maestro.setTarget(1 + (kanal * 3), 4500);
  stand();
}
void legLwave(int kanal, int ilosc)
{
  maestro.setSpeed(11 + (kanal * 3), 100); // kolano
  maestro.setAcceleration(0 + (kanal * 3), 400);
  maestro.setSpeed(10 + (kanal * 3), 100); // obudowa pion
  maestro.setAcceleration(1 + (kanal * 3), 400);

  maestro.setTarget(10 + (kanal * 3), 10000);
  delay(500);
  for (int x = 0; x < ilosc; x++)
  { // ruch kolanem
    maestro.setTarget(11 + (kanal * 3), 7000);
    delay(500);
    maestro.setTarget(11 + (kanal * 3), 1000);
    delay(500);
  }
  maestro.setSpeed(11 + (kanal * 3), 25); // kolano wraca
  maestro.setAcceleration(0 + (kanal * 3), 127);
  maestro.setSpeed(10 + (kanal * 3), 25);
  maestro.setAcceleration(1 + (kanal * 3), 127);
  maestro.setTarget(10 + (kanal * 3), 4500); // noga wraca
  stand();
}
void liftL(int kanal, int kolano, int pion)
{
  maestro.setSpeed(11 + (kanal * 3), 50); // kolano
  maestro.setAcceleration(0 + (kanal * 3), 200);
  maestro.setSpeed(10 + (kanal * 3), 50); // obudowa pion
  maestro.setAcceleration(1 + (kanal * 3), 200);
  maestro.setTarget(11 + (kanal * 3), kolano);
  maestro.setTarget(10 + (kanal * 3), pion);
}
void liftR(int kanal, int kolano, int pion)
{
  maestro.setSpeed(0 + (kanal * 3), 50); // kolano
  maestro.setAcceleration(0 + (kanal * 3), 200);
  maestro.setSpeed(1 + (kanal * 3), 50); // obudowa pion
  maestro.setAcceleration(1 + (kanal * 3), 200);
  maestro.setTarget(0 + (kanal * 3), kolano);
  maestro.setTarget(1 + (kanal * 3), pion);
}
void moveLateralL(int kanal, int pozycja)
{
  maestro.setSpeed(9 + (kanal * 3), 50);
  maestro.setAcceleration(0 + (kanal * 3), 200);
  maestro.setTarget(9 + (kanal * 3), pozycja);
  // delay(750);
  // liftL(kanal, 6000, 4200);
}
void moveLateralR(int kanal, int pozycja)
{
  maestro.setSpeed(2 + (kanal * 3), 50);
  maestro.setAcceleration(0 + (kanal * 3), 200);
  maestro.setTarget(2 + (kanal * 3), pozycja);
  // delay(750);
  // liftR(kanal, 8500, 8000);
}
void forwards()
{
  // podnieś 3 pierwsze
  pierwszeDown();

  // przesuń pozostałe 3 do przodu
  przesunPozostalePrzod();

  // podnieś pozostałe 3
  pozostaleDown();

  // resetuj 3 pierwsze
  resetujPierwsze();

  // przesuń 3 pozostałe do tyłu
  przesunPozostaleTyl();

  // podnieś 3 pierwsze
  pierwszeDown();

  // resetuj 3 pozostałe
  resetujPozostale();

  // podnieś pozostałe 3
  pozostaleDown();

  // resetuj 3 pierwsze
  resetujPierwsze();

  // przesuń pierwsze 3
  przesunPierwszePrzod();

  // podnieś 3 pierwsze
  pierwszeDown();

  // resetuj 3 pozostałe
  resetujPozostale();

  // przesuń 3 pierwsze do tyłu
  przesunPierwszeTyl();

  // podnieś pozostałe 3
  pozostaleDown();

  // resetuj 3 pierwsze
  resetujPierwsze();

  // podnieś 3 pierwsze
  pierwszeDown();

  stand();
}
void backwards()
{
}
void everyOther1()
{
  liftL(1, 1, 10000);
  delay(500);
  liftR(0, 10000, 1);
  delay(500);
  liftR(2, 10000, 1);
  delay(1500);
  stand();
}
void everyOther2()
{
  liftL(0, 1, 10000);
  delay(500);
  liftR(1, 10000, 1);
  delay(500);
  liftL(2, 1, 10000);
  delay(1500);
  stand();
}
void pierwszeDown()
{
  delay(500);
  liftL(0, 5500, 4000);
  liftR(1, 8500, 8200);
  liftL(2, 5500, 4000);
  delay(50);
}
void pozostaleDown()
{
  delay(500);
  liftR(0, 8500, 8200);
  liftL(1, 5500, 4000);
  liftR(2, 8500, 8200);
  delay(50);
}
void przesunPozostalePrzod()
{
  moveLateralR(0, 1);
  moveLateralL(1, 6000);
  moveLateralR(2, 1);
}
void przesunPozostaleTyl()
{
  moveLateralR(0, 6000);
  moveLateralL(1, 1000);
  moveLateralR(2, 4500);
}
void resetujPierwsze()
{
  legL(0, 6800, 5500, 4000);
  legR(1, 7400, 7300, 4500);
  legL(2, 7000, 5500, 5000);
  delay(500);
}
void resetujPozostale()
{
  legR(0, 7400, 7300, 4000);
  legR(2, 7400, 7300, 4000);
  legL(1, 7300, 5500, 4500);
  delay(500);
}
void przesunPierwszePrzod()
{
  moveLateralL(2, 7000);
  moveLateralR(1, 3200);
  moveLateralL(0, 7000);
}
void przesunPierwszeTyl()
{
  moveLateralL(2, 1000);
  moveLateralR(1, 6500);
  moveLateralL(0, 1000);
}
void loopActions()
{
  String line = Serial3.readString();
  loopActionsFlag = true;
  while (loopActionsFlag)
  {
    legRwave(2, 4);
    delay(2000);
    legLwave(0, 4);
    delay(2000);
    legRwave(0, 4);
    delay(2000);
    legLwave(1, 4);
    delay(2000);
    legLwave(2, 4);
    delay(2000);
    legRwave(1, 4);
    delay(2000);

    everyOther1();
    delay(2000);
    stand();
    delay(2000);
    everyOther2();
    delay(2000);
    stand();
    delay(2000);

    sit();
    delay(2000);
    stand();
    delay(60000);

    if (line.indexOf("breakLoop") > -1)
    {
      loopActionsFlag = false;
    }    
  }
}