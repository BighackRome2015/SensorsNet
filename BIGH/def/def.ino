#include <Bridge.h>
#include <HttpClient.h>

int led = 8;

double oldGAS=0;
double GAS=0;
double oldProx=0;
double Prox=0;


void setup() {
  Bridge.begin();
  Serial.begin(9600);
//  Console.begin();
pinMode(led,OUTPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
//  while (!Serial)
//    runCpuInfo();
}


void loop() {
  getGAS();
  alarm();
  if(oldGAS>(GAS+50) || oldGAS<(GAS-50)){
    runCurl(1,GAS);
    Serial.println("GAS: "+String(GAS));
  }
  getProx();
  alarm();
  if(Prox!=oldProx){
    runCurl(2,Prox);
    Serial.println("casco non indossato: "+String(Prox));
  }
  delay(1000);
}

void runCurl(int table, double param) {
  Process p;           
  p.begin("curl");     
  p.addParameter("www.bacuuk.com/registrati.php");
  p.addParameter("-d");
  p.addParameter("param"+String(table)+"="+String(param));
  p.run();
 }
 
 void runCpuInfo(){
   Process p;
   p.begin("cat");
   p.addParameter("/proc/cpuinfo");
   p.run();
    while(p.available()>0){
    char c=p.read();
  Serial.print(c);
  }
  Serial.flush();
 }
 
 void getGAS(){
  oldGAS=GAS;
  GAS=double(analogRead(A0));
}

void getProx(){
  oldProx=Prox;
  Prox=double(analogRead(A1));
}

void alarm(){
  if(GAS>800 || Prox > 20){
    digitalWrite(led,HIGH);
    delay(1000);
  }
  else
    digitalWrite(led,LOW);  
}
