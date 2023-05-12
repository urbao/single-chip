#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

// 定義 DHT 資料傳輸的腳位
#define DHTPIN 23

// 選擇使用的 DHT 溫溼度計種類
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);  // 啟動 DHT 程式庫

const char* ssid = "QAQ";               // Wi-Fi 網路名稱
const char* password = "E24b46435298";  // Wi-Fi 密碼

// 初始化溫度與濕度的變數
float t = 0.0;
float h = 0.0;

// 建立一個非同步伺服器在通訊埠 80
AsyncWebServer server(80);

// 紀錄量測間隔時間，因為數值較大，用 unsigned long
unsigned long previousMillis = 0;

// 每 n 秒量測，1000->1秒，2000->2秒
const long interval = 2000;

// 建立網頁
// 網頁大小相對大但是架構不會變，一般存變數的動態記憶體不足
// 要存在儲存程式程序的flash記憶體中，所以呼叫PROGMEM
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!--設定字體-->
  <style>   
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p  { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<!--建立網頁內容-->
<body>    
  <h2>ESP32 DHT11 Server</h2>
  <p>
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>    
</body>
<script>
setInterval(function ( ) {    <!--將溫度資料傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {    <!--將濕度資料，傳入伺服器顯示在瀏覽器上-->
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementByID("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 1000 ) ;
</script>
</html>)rawliteral";

// 抓取最新的溫溼度資料
String processor(const String& var) {
  //Serial.println(var);
  if (var == "TEMPERATURE") {
    return String(t);
  } else if (var == "HUMIDITY") {
    return String(h);
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  // To do.
  WiFi.mode(WIFI_STA);  //設置 Wi-Fi 模式
  WiFi.begin(ssid, password);

  Serial.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //delay(500);
  }

  Serial.println("");
  Serial.print("Wi-Fi Connected.");

  // 查詢 ESP32 的 local IP 並印出，在瀏覽器輸入此 IP 即可看到畫面
  // To do.
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  // 在伺服器上建立網頁
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });  //建立主網頁
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", String(t).c_str());
  });  //建立溫度顯示的網頁
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", String(h).c_str());
  });

  server.begin();  // 啟動伺服器
  dht.begin();     // 啟動 DHT 感測器
}

void loop() {
  // 建立量測溫溼度的迴圈
  // 因為網頁伺服器不能使用 delay 函數，所以用 millis
  // millis 用運算的次數來計算時間，更為準確，也不會阻擋程式運作
  // delay 函數運作時會完全停止程式運作，使網頁伺服器出錯

  //使用 DHT11 讀取環境溫濕度
  //使用 millis 做間隔，每 2 秒讀一次
  //To do.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // 如果上次時間點到這次時間點已經大於間隔時間，就開始量測
    // 將上次的時間記錄更新成這次的時間點儲存
    previousMillis = currentMillis;
    // 讀濕度
    float humidity = dht.readHumidity();
    // 讀溫度
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {  // 如果讀取到的溫溼度有異
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    t = temperature;  // t 為要給 server 的溫度變數，temperature 來自 DHT11 的讀值
    Serial.print(F("Temperature: "));
    Serial.println(t);
    h = humidity;
    Serial.print(F("Humidity: "));
    Serial.println(h);
  }
}