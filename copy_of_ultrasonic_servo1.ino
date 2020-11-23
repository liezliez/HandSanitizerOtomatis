#include <Servo.h>
int idBotol = 1;
int inches = 0;
int cm = 0;
int kapasitasBotol = 200; //kapasitas botol 200ml 
Servo servoMotor;

//Sistem masih Offline
#define ACCESSKEY "e0b09b9e31836cfa:88fea1e7ae38105c"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "HandSanitizer_Otomatis"
#define deviceName "Arduino"


long jarakUltra(int pin){
  //reset trigger 
  pinMode(pin, OUTPUT); 
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // pin HIGH pancarin ultrasonik selama 10microsecond
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  // baca pin pantulan
  return pulseIn(pin, HIGH);
}

void setup() {
  // antares.setDebug(true);
  // antares.wifiConnection(WIFISSID,PASSWORD);
  pinMode(7, INPUT);
  Serial.begin(9600);
  servoMotor.attach(9);
}
void loop() {
  // ubah ke cm
  cm = 0.01723 * jarakUltra(7);
  // ubah ke inci
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(kapasitasBotol);
  Serial.println("ml Isi Botol");
  if ((kapasitasBotol) > 10){
    if ( (cm) < 30){
      servoMotor.write(100);
      delay(500);
      kapasitasBotol = kapasitasBotol-1; 
	  // satu kali crot 0,8ml hingga 1,5ml sehingga 
      // saya bulatkan jadi 1ml
      servoMotor.write(0);
      delay(800);
    } else {
      servoMotor.write(0);
    };
  } else {
  	Serial.print("Isi Botol habis");
	// antares.add("botol dengan ID : ",idBotol," telah habis");
    // antares.send(projectName, deviceName);
    delay(5000);
  };
  delay(800); // 800 ms delay
}