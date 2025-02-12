#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi Bilgileri
#define WLAN_SSID ""       // WiFi ağ adı
#define WLAN_PASS ""         // WiFi şifre

// OpenAI API Bilgileri
const char* openai_host = "api.openai.com";
const int httpsPort = 443; // HTTPS portu
const char* api_key = "";      // OpenAI API anahtarı

// Adafruit IO MQTT Bilgileri
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME ""
#define AIO_KEY ""

WiFiClient client; // WiFi istemcisi
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// MQTT Feed
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sau.saumqtt");

// LCD Ayarları (I2C Adresi: 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD: Adres 0x27, 16x2 boyutunda

// LM35 Sıcaklık Sensör Pin
const int lm35Pin = A0;

// Fonksiyon: LM35 sıcaklık sensöründen sıcaklık okuma
float readTemperature() {
  int analogValue = analogRead(lm35Pin);
  float voltage = analogValue * (3.3 / 1023.0); // 3.3V referansı
  float temperature = voltage * 100.0;         // LM35 her 10mV'de 1°C
  return temperature;
}

// Fonksiyon: Kullanıcıdan malzeme listesi al
String getIngredients() {
  Serial.println("Lütfen malzeme listesini girin (ornek: tomato, cheese, bread):");
  while (!Serial.available()); // Kullanıcı girişini bekle
  return Serial.readStringUntil('\n');
}

// Fonksiyon: Malzeme doğrulama (yalnızca harf, virgül ve boşluk içerir)
bool validateIngredients(const String& input) {
  for (char c : input) {
    if (!isAlpha(c) && c != ',' && c != ' ') {
      return false;
    }
  }
  return true;
}

// Fonksiyon: OpenAI API'den tarif önerisi al
/*String getRecipe(String ingredients, float temperature) {
  WiFiClientSecure client;
  client.setInsecure(); // Sertifika doğrulamasını kapat

  if (!client.connect(openai_host, httpsPort)) {
    Serial.println("OpenAI sunucusuna bağlanılamadı.");
    return "Baglanti hatasi.";
  }

  // OpenAI'ye gönderilecek JSON verisi
  String prompt = "Ingredients: " + ingredients + "\nTemperature: " + String(temperature, 1) + "\u00b0C\nSuggest a suitable recipe.";
  String jsonRequest = "{\"model\":\"gpt-4o\",\"prompt\":\"" + prompt + "\",\"max_tokens\":100}";
  //String jsonRequest = "{\"model\":\"gpt-4o-mini\",\"prompt\":\"Ingredients: tomato, eggplant, potato\\nTemperature: 1.6C\\nSuggest a suitable recipe.\",\"max_tokens\":100}";


  // HTTP isteği gönderimi
  client.println("POST /v1/completions HTTP/1.1");
  //client.println("Host: api.openai.com");
  client.println("Authorization: Bearer " + String(api_key));
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(jsonRequest.length()));
  client.println(); // Boş satır, header ile body'yi ayırır
  client.println(jsonRequest);


  // Yanıtı oku
  String response = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Boş bir satırdan sonra gövde başlar
  }

  while (client.available()) {
    response += client.readString();
  }

  Serial.println("API Yanıtı:");
  Serial.println(response);

  // Yanıtı kontrol et ve hata durumunda döndür
  if (response.isEmpty()) {
    Serial.println("API'den yanıt alınamadı.");
    return "API'den yanit alinmadi.";
  }

  // JSON yanıtından tarif önerisini ayrıştır
  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeJson(doc, response);
  if (error) {
    Serial.print("JSON ayrıştırma hatası: ");
    Serial.println(error.c_str());
    return "Tarif ayrıştırılamadı.";
  }

  // Yanıtın doğru geldiğinden emin olmak için kontrol
  if (!doc.containsKey("choices") || doc["choices"].size() == 0) {
    Serial.println("Yanıtta 'choices' bulunamadı.");
    Serial.println("Yanıt içeriği:");
    Serial.println(response);
    return "Tarif bulunamadi.";
  }
  // Tarif bilgisini ayıkla
  if (doc.containsKey("choices")) {
    String recipe = doc["choices"][0]["text"].as<String>();
    return recipe;
  } else {
    return "Tarif bulunamadi.";
  }

  String recipe = doc["choices"][0]["text"].as<String>();
  recipe.trim(); //Gereksiz boşlukları kaldırır
   return recipe.isEmpty() ? "Tarif bulunamadi." : recipe;

   Serial.println("Gönderilen JSON:");
  Serial.println(jsonRequest);
  Serial.println("API Yanıtı:");
  Serial.println(response);

  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeJson(doc, response);

  if (!error) {
    String recipe = doc["choices"][0]["text"].as<String>();
    recipe.trim(); // Gereksiz boşlukları kaldırır
    return recipe.isEmpty() ? "Tarif bulunamadi." : recipe;
  } else {
    Serial.println("JSON ayrıştırma hatası: " + String(error.c_str()));
    return "Tarif ayrıştırılamadı.";
  }

}*/


/*String getRecipe(String ingredients, float temperature) {
  WiFiClientSecure client;
  client.setInsecure(); // Sertifika doğrulamasını kapat

  if (!client.connect(openai_host, httpsPort)) {
    Serial.println("OpenAI sunucusuna bağlanılamadı.");
    return "Bağlantı hatası.";
  }

  // JSON formatında OpenAI'ye gönderilecek veri
  String prompt = "Ingredients: " + ingredients + "\nTemperature: " + String(temperature, 1) + "°C\nSuggest a suitable recipe.";
  String jsonRequest = "{\"model\":\"gpt-4\",\"prompt\":\"" + prompt + "\",\"max_tokens\":100}";

  // HTTP isteği başlıkları ve gövdesi
  client.println("POST /v1/completions HTTP/1.1");
  client.println("Host: " + String(openai_host));
  client.println("Authorization: Bearer " + String(api_key));
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(jsonRequest.length()));
  client.println();
  client.println(jsonRequest);

  // Sunucudan gelen yanıtı oku
  String response = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Boş bir satırdan sonra yanıt gövdesi başlar
  }

  while (client.available()) {
    response += client.readString();
  }

  Serial.println("API Yanıtı:");
  Serial.println(response);

  // Yanıtı JSON olarak ayrıştır
  DynamicJsonDocument responseDoc(2048);
  DeserializationError error = deserializeJson(doc, response);
  if (error) {
    Serial.print("deserializeJson() hatası: ");
    Serial.println(error.c_str());
    Serial.println("Yanıt: " + response);
    return "Tarif ayrıştırılamadı.";
  }

  String recipe = doc["choices"][0]["text"].as<String>();
  return recipe;

  DynamicJsonDocument responseDoc(4096);
  DeserializationError error = deserializeJson(responseDoc, response);
  if (error) {
    Serial.print("JSON ayrıştırma hatası: ");
    Serial.println(error.c_str());
    return "Tarif ayrıştırılamadı.";
  }

  if (responseDoc.containsKey("choices") && responseDoc["choices"].size() > 0) {
    String recipe = responseDoc["choices"][0]["text"].as<String>();
    recipe.trim();
    return recipe.isEmpty() ? "Tarif bulunamadi." : recipe;
  } else {
    return "Tarif bulunamadi.";
  }

}*///JSON ayrıştırma hatası: InvalidInput veriyor

String getRecipe(String ingredients, float temperature) {
  WiFiClientSecure client;
  client.setInsecure(); // Sertifika doğrulamasını kapat

  if (!client.connect(openai_host, httpsPort)) {
    Serial.println("OpenAI sunucusuna bağlanılamadı.");
    return "Bağlantı hatası.";
  }

  // OpenAI'ye gönderilecek JSON verisi
  String prompt = "Ingredients: " + ingredients + "\nTemperature: " + String(temperature, 1) + "°C\nSuggest a suitable recipe.";
  String jsonRequest = "{\"model\":\"gpt-4o\",\"prompt\":\"" + prompt + "\",\"max_tokens\":100}";

  // HTTP isteği
  client.println("POST /v1/completions HTTP/1.1");
  client.println("Host: " + String(openai_host));
  client.println("Authorization: Bearer " + String(api_key));
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(jsonRequest.length()));
  client.println();
  client.println(jsonRequest);

  // Yanıtı oku
  String response = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Boş bir satırdan sonra gövde başlar
  }

  while (client.available()) {
    response += client.readString();
  }

  // JSON yanıtından tarif önerisini ayrıştır
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);
  String recipe = doc["choices"][0]["text"];
  return recipe;
} //önerilen tarif:null dönüyor

// MQTT bağlantısını kontrol eden fonksiyon
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) return;

  Serial.print("MQTT'ye bağlanıyor...");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("5 saniye içinde tekrar deneniyor...");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println("MQTT Bağlandı!");
}

void scrollText(String text, int delayMs) {
  int len = text.length();
  for (int i = 0; i < len + 16; i++) {
    lcd.clear();
    if (i < len) {
      lcd.setCursor(0, 0);
      lcd.print(text.substring(i, min(i + 16, len)));
    }
    delay(delayMs);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  // WiFi bağlantısı kurulana kadar bekle
  Serial.print("WiFi'ye bağlanıyor");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi bağlantısı kuruldu!");

  // LCD başlatma
  lcd.init();
  lcd.backlight();
  lcd.print("WiFi Baglandi");

  // MQTT abonelikleri başlat
  mqtt.subscribe(NULL);
}

void loop() {
  static unsigned long lastTemperatureCheck = 0;
  unsigned long currentMillis = millis();

  // Her 2 dakikada bir sıcaklık ölç ve MQTT'ye gönder
  if (currentMillis - lastTemperatureCheck >= 120000) {
    lastTemperatureCheck = currentMillis;

    float temperature = readTemperature();
    Serial.println("Sicaklik olculdu: " + String(temperature) + "\u00b0C");

    if (!feed.publish(temperature)) {
      Serial.println("Sıcaklık Adafruit IO'ya gönderilemedi.");
    }
  }

  // Kullanıcıdan malzeme girdisini bekle ve tarifi al
  if (Serial.available() > 0) {
    String ingredients = getIngredients();
    ingredients.trim();
    Serial.println("Malzemeler: " + ingredients);

    // Malzeme doğrulaması
    if (!validateIngredients(ingredients)) {
      Serial.println("Geçersiz giriş! Lütfen yalnızca malzeme listesi girin.");
      lcd.clear();
      lcd.print("Gecersiz girdi!");
      delay(2000);
      lcd.clear();
      return;
    }

    float temperature = readTemperature();
    String recipe = getRecipe(ingredients, temperature);
    Serial.println("Önerilen Tarif: \n" + recipe);

    // Tarifi LCD'ye kayan metin olarak yazdır
    scrollText(recipe, 500);
  }

  // MQTT bağlantısını kontrol et
  MQTT_connect();
}