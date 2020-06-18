int tension1 = 0;
int tension2 = 0;
boolean hit = false;
boolean recharging = false;
int timeRecharging = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT); 
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tension1 = analogRead(A0);
  tension2 = analogRead(A1);
  tension1 = map(tension1, 0, 1024, 0, 256);
  tension2 = map(tension2, 0, 1024, 0, 256);
  Serial.print("LDR 1=");
  Serial.println(tension1);
  Serial.print("LDR 2=");
  Serial.println(tension2);
  Serial.print(" hit=");
  Serial.print(hit);
  Serial.print(" cooldown=");
  Serial.println(5 - timeRecharging / 10);

  if (hit && !recharging) {
    recharging = true;
    tone(10, 1320, 100);
    delay(50);
    tone(10, 880, 100);
    delay(50);
    tone(10, 440, 100);
    delay(50);
    tone(10, 880, 250);
    
  }

  if (recharging) {
    timeRecharging++;

    // Executé quand le compteur est terminé
    if (timeRecharging >= 100) {
      timeRecharging = 0;
      recharging = false;
      hit = false;
      tone(10, 1850, 100);
      delay(250);
      tone(10, 1850, 100);
    }
  }

  if (!recharging)
    hit = (tension1 < 140 || tension2 < 140) ? true : false;

  delay(20);
}

