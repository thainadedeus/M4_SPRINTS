#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <stdio.h>
#include <String>

//Vetores com nomes de rede e senhas dos Access Points
const char* SSIDS = "Inteli-COLLEGE";
const char* PWD = "QazWsx@123";

char * mensagem;

char conversao(char ch, int key) {

  if(!isalpha(ch)) return ch;
  char offset = isupper(ch) ? 'A' : 'a';
  return(char)((((ch + key) - offset) % 26) + offset);
}

String criptografar(String entrada, int key) {
  String saida = "";
  size_t len = entrada.length();
  for (size_t i = 0; i < len; i++){
    saida += conversao(entrada[i], key);
  }
  return saida;
}

void postDataToServer() {

  Serial.println("Enviando os dados Json para o servidor...");
  String mensagem_criptografada = criptografar("Essa é uma mensagem criptografada.", 12);
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;

    // Add values in the document
    //
    doc["Nome"] = "Thainá";
    doc["Turma"] = 3;
    doc["Grupo"] = 1;
    doc["Mensagem"] = "Essa é uma mensagem criptografada.";
    doc["Mensagem_Criptografada"] = mensagem_criptografada;
     // Add an array.
    //

    JsonArray data = doc.createNestedArray("data");
    
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
     
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSIDS,PWD);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Tentando novamente!");
      delay(2000);
    }

  WiFi.mode(WIFI_STA); 
}

void loop() {
  Serial.println("Enviando dados: ");
  Serial.println("");
  postDataToServer();
  delay(2000);
}