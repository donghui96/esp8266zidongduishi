#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define LED 2
String payload = ""; 
String str = "";//获取数据储存变量
String com, tem1, tem2, humi, temnow, sta, state1, state2, time0, time1, time2, english;
String webadd = "http://flash.weather.com.cn/wmaps/xml/zhengzhou.xml";    //天气接口地址
String time_url = "http://quan.suning.com/getSysTime.do";   //时间接口地址
String english_url = "http://open.iciba.com/dsapi/";   //英语接口地址
String daytime = "";
void smartConfig()
{
  WiFi.mode(WIFI_STA);
  Serial.println("\r\nWait for Smartconfig");
  WiFi.beginSmartConfig();
  while (1)
  {
    Serial.print(".");
    digitalWrite(LED, 0);

    delay(500);
    digitalWrite(LED, 1);
    delay(500);
    if (WiFi.smartConfigDone())
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      break;
    }
  }
}
void setup()
{
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  smartConfig();
}


/*****************************************http数据获取*******************************************/
void http() {
  HTTPClient http;
  http.begin(webadd);
  int httpCode = http.GET();
  if (httpCode > 0) {
    payload = http.getString();
    //Serial.println(payload);
    int a = payload.indexOf("101180101");//自己搜索链接可知指定城市的id郑州市的id为‘101180101’
    //indexof();在字符串中中查找字符位置，返回值为给定字符的第一个位置，查找失败返回-1
    com = payload.substring(a - 280, a + 12);
    //字符串解析函数：substring(?,...),返回值为指定位置的字符串值
    //Serial.println(com);
    //<city cityX="376" cityY="184" cityname="郑州市" centername="郑州市" fontColor="FFFF00" pyName="" state1="0" state2="1" stateDetailed="晴转多云" tem1="37" tem2="24" temNow="33" windState="南风3-4级" windDir="西南风" windPower="2级" humidity="39%" time="11:00" url="101180101"/>
  }
  http.end();
}
/*********************************获取时间**************************************/
void get_time()
{
  HTTPClient http;
  http.begin(time_url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    payload = http.getString();
    str= payload.substring(41,57);
     delay(1000);
    Serial.println(str);
   
  }
  http.end();
}
/*************************获取每日英语*******************/
/**************************************天气判断**************************************************/
/*************************************截取字符数据处理*******************************************/
void data() {
  int i = 0;
  i = com.indexOf("tem1");
  tem1 = com.substring(i + 6, i + 8);
  i = 0;
  i = com.indexOf("tem2");  //tem2="24"
  tem2 = com.substring(i + 6, i + 8);
  i = 0;
  i = com.indexOf("temNow");
  temnow = com.substring(i + 8, i + 10);
  i = 0;
  i = com.indexOf("humidity");
  humi = com.substring(i + 10, i + 13); //humidity="27%"
  i = 0;
  i = com.indexOf("state1");
  state1 = com.substring(i + 8, i + 9);
  i = 0;
  i = com.indexOf("state2");
  state2 = com.substring(i + 7, i + 11);
  i = 0;
}
/*********************************************屏幕显示**************************************************/
void loop()
{
  digitalWrite(LED, 1);
  
  get_time();
  http();
  
  data();
  
 // show();


  
  delay(200);
}
