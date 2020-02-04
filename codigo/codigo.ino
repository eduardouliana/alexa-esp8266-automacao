// Biblioteca de comunicação
#include "fauxmoESP.h"

// Valor para o Serial - Desativar depois
#define SERIAL_BAUDRATE 115200

// Dados para conexão com a Wi-Fi
#define WIFI_SSID "NOME-WIFI"
#define WIFI_PASS "SENHA"

// Pinos para ligar no ESP
#define LAMPADA_1 D1
#define LAMPADA_2 D2
#define LAMPADA_3 D3
#define LAMPADA_4 D4

// Nome dos dispositivos que a Alexa irá encontrar 
// (Pode mudar no aplicativo depois)
#define LAMP_1 "luz do quarto"
#define LAMP_2 "luz da cozinha"
#define LAMP_3 "luz da sala"
#define LAMP_4 "cafeteira"

// Variável para uso da lib de conexão
fauxmoESP fauxmo;


// Conecta com o Wi-Fi
void wifiSetup() {
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Aguarda até conectar com a Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
}

void setup() {
  // Inicia a porta Serial - Remover depois
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  // Chama a conexão com a Wi-Fi
  wifiSetup();

  // Define as portas do ESP como saída
  pinMode(LAMPADA_1, OUTPUT);
  digitalWrite(LAMPADA_1, HIGH);

  pinMode(LAMPADA_2, OUTPUT);
  digitalWrite(LAMPADA_2, HIGH);

  pinMode(LAMPADA_3, OUTPUT);
  digitalWrite(LAMPADA_3, HIGH);

  pinMode(LAMPADA_4, OUTPUT);
  digitalWrite(LAMPADA_4, HIGH);

  // Cria o server para emular os dispositivos
  fauxmo.createServer(true);
  //Está usando a porta 80, caso estiver em uso, coloque outra
  fauxmo.setPort(80);


  // Permite que este dispositivo seja reconhecido pela Alexa
  fauxmo.enable(true);

  // Adiciona os devices para Alexa reconhecer
  fauxmo.addDevice(LAMP_1);
  fauxmo.addDevice(LAMP_2);
  fauxmo.addDevice(LAMP_3);
  fauxmo.addDevice(LAMP_4);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, LAMP_1) == 0) ) {
      //digitalWrite(LAMPADA_1, !digitalRead(LAMPADA_1));
      if (state) {
        digitalWrite(LAMPADA_1, HIGH);
      } else {
        digitalWrite(LAMPADA_1, LOW);
      }
    }
    
    if ( (strcmp(device_name, LAMP_2) == 0) ) {
      if (state) {
        digitalWrite(LAMPADA_2, HIGH);
      } else {
        digitalWrite(LAMPADA_2, LOW);
      }
    }
    
    if ( (strcmp(device_name, LAMP_3) == 0) ) {
      if (state) {
        digitalWrite(LAMPADA_3, HIGH);
      } else {
        digitalWrite(LAMPADA_3, LOW);
      }
    }
    if ( (strcmp(device_name, LAMP_4) == 0) ) {
      if (state) {
        digitalWrite(LAMPADA_4, HIGH);
      } else {
        digitalWrite(LAMPADA_4, LOW);
      }
    }
  });
}

void loop() {
  // Fica escutando os comandos da Alexa
  fauxmo.handle();
}
