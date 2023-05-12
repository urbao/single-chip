#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define LED 2  //使用 ESP32 內建 LED

#define DHTPIN 23  // 定義 DHT 資料傳輸的腳位

// 選擇使用的 DHT 溫溼度計種類
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);  // 啟動 DHT 程式庫

// 紀錄量測間隔時間，因為數值較大，用 unsigned long
unsigned long previousMillis = 0;

// 每 n 秒量測，1000->1秒，2000->2秒
const long interval = 2000;


const char* ssid = "QAQ";               // Wi-Fi 網路名稱
const char* password = "E24b46435298";  // Wi-Fi 密碼

// 建立 MQTT 連線所需的 client ID，可使用隨機生成
String mqtt_ClientID = "mqttClientID";

// 定義 MQTT 連線時，用來識別 publish/subscribe 資料類別的 topic
// 請依照組別更改groupX
const char* sub_topic = "group2/esp32mqtt";
const char* pub_led_topic = "group2/esp32s_led_state";  // 控制 ESP32 上的 LED
const char* pub_init_topic = "group2/esp32s_is_back";   // 確認 ESP32 與 MQTT broker 已連線
const char* pub_temp_topic = "group2/esp32s_temp";      // 傳輸溫度
const char* pub_humd_topic = "group2/esp32s_humd";      // 傳輸溫度


// EMQX MQTT broker 的連線資訊
const char* mqtt_server = "broker.emqx.io";  // broker 所在的網址
const char* mqtt_userName = "emqx";          // EMQX broker 的公用帳號
const char* mqtt_password = "public";        // EMQX broker 的公用密碼

// 初始 Wi-Fi client 與 MQTT client 連線
WiFiClient espClient;
PubSubClient client(espClient);

// 初始化儲存溫度與濕度的變數
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];



void setup_wifi() {  // 設定 Wi-Fi 連線
  delay(10);

  // Connect to Wi-Fi
  // To do.
  WiFi.mode(WIFI_STA);  //設置 Wi-Fi 模式
  WiFi.begin(ssid, password);

  Serial.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  randomSeed(micros());

  // 連線成功後將連線的 IP 資訊印出
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//接收 MQTT broker subscribe 來的資訊 (LED 亮暗)
void callback(char* topic, byte* payload, unsigned int length) {  // 資訊包含 topic 與 topic 內的資料
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  payload[length] = '\0';
  String message = (char*)payload;  // 儲存 topic 內的資料 payload 到 message 裡

  // 驗證傳來的 topic 是我定義中要求的 topic
  // strcmp 會比較()內兩個字串，相同的話回傳 0，不同的話會輸出差幾個字母數，並用正負表示哪邊比較大
  if (strcmp(topic, sub_topic) == 0) {
    if (message == "off") {
      digitalWrite(LED, LOW);  // 收到 off 關掉 ESP32 的 LED
      client.publish(pub_led_topic, "off");
    }
    if (message == "on") {
      digitalWrite(LED, HIGH);  // 收到 on 開啟 ESP32 的 LED
      client.publish(pub_led_topic, "on");
    }
  }
}

void reconnect() {
  // 對 MQTT 進行連線建立，若未建立成功會持續在此循環
  while (!client.connected()) {
    Serial.println("Attempting EMQX MQTT connection...");
    // 用亂數確保建立唯一的 ClientID
    mqtt_ClientID += String(random(0xffff), HEX);
    // 嘗試建立連線
    if (client.connect((mqtt_ClientID, mqtt_userName, mqtt_password))) {
      Serial.print(" connected with Client ID: ");
      Serial.println(mqtt_ClientID);
      // 若建立成功，可在其他裝置訂閱 pub_init_topic 收到 "Hi, I'm online!" 的訊息
      client.publish(pub_init_topic, "Hi, I'm online!");
      // 重新接收資料
      client.subscribe(sub_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      // 可於此查詢連線失敗原因編碼
      // https://github.com/knolleary/pubsubclient/blob/master/src/PubSubClient.h
      Serial.println(" try again in 5 seconds");
      // 若 MQTT 連線失敗，每 5 秒重試
      delay(5000);
    }
  }
}

void setup() {
  dht.begin();  //啟動 DHT 感測器

  pinMode(LED, OUTPUT);    // 將 LED Pin 腳位設為輸出
  digitalWrite(LED, LOW);  // 將 LED Pin 腳位設為數位輸出(0V/5V)，並預設為低(0V)

  Serial.begin(115200);

  setup_wifi();  // 進入設定 Wi-Fi 連線的 void function

  client.setServer(mqtt_server, 1883);  // 設定 MQTT broker 的連線
  client.setCallback(callback);         // 接收從其他 MQTT client 傳來的資料
}

void loop() {

  if (!client.connected()) {  // 若 MQTT 連線建立失敗就重新連線
    reconnect();
  }
  client.loop();


  //使用 DHT11 讀取環境溫濕度
  //使用 millis 做間隔，每 2 秒讀一次
  //To do.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // 如果上次時間點到這次時間點已經大於間隔時間，就開始量測
    // 將上次的時間記錄更新成這次的時間點儲存
    previousMillis = currentMillis;
    // 使用 DHT11 讀取環境溫濕度
    // 讀濕度
    float humidity = dht.readHumidity();
    // 讀溫度
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {  // 如果讀取到的溫溼度為空，表示 DHT11 有問題
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } else {                                                  // 如果溫溼度正常就publish給MQTT broker
      snprintf(msg, MSG_BUFFER_SIZE, "%.1lf°", temperature);  //印出溫度
      Serial.print("Publish message: ");
      Serial.print(msg);
      client.publish(pub_temp_topic, msg);  // 綁定 topic，發送溫度

      snprintf(msg, MSG_BUFFER_SIZE, "%.1lf°", humidity);  //印出溫度
      Serial.print("Publish message: ");
      Serial.print(msg);
      client.publish(pub_humd_topic, msg);  // 綁定 topic，發送溫度
    }
  }
}