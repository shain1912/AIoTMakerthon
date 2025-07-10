# 🧠 Task 1 분석 리포트

**대상 URL**: https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/

**생성 일시**: 2025-07-10

---

## 📘 본문 텍스트 (원문)

Getting Started with ESP32 Bluetooth Low Energy (BLE) on Arduino IDE

The ESP32 comes not only with Wi-Fi but also with Bluetooth and Bluetooth Low Energy (BLE). This post is a quick introduction to BLE with the ESP32. First, we’ll explore what’s BLE and what it can be used for, and then we’ll take a look at some examples with the ESP32 using Arduino IDE. For a simple introduction we’ll create an ESP32 BLE server, and an ESP32 BLE scanner to find that server.

Updated 11 June 2024

Introducing Bluetooth Low Energy

For a quick introduction to BLE, you can watch the video below, or you can scroll down for a written explanation.

Recommended reading: learn how to use ESP32 Bluetooth Classic with Arduino IDE to exchange data between an ESP32 and an Android smartphone.

What is Bluetooth Low Energy?

Bluetooth Low Energy, BLE for short, is a power-conserving variant of Bluetooth. BLE’s primary application is short distance transmission of small amounts of data (low bandwidth). Unlike Bluetooth that is always on, BLE remains in sleep mode constantly except for when a connection is initiated.

This makes it consume very low power. BLE consumes approximately 100x less power than Bluetooth (depending on the use case).

Additionally, BLE supports not only point-to-point communication, but also broadcast mode, and mesh network.

Take a look at the table below that compares BLE and Bluetooth Classic in more detail.

View Image Souce

Due to its properties, BLE is suitable for applications that need to exchange small amounts of data periodically running on a coin cell. For example, BLE is of great use in healthcare, fitness, tracking, beacons, security, and home automation industries.

BLE Server and Client

With Bluetooth Low Energy, there are two types of devices: the server and the client. The ESP32 can act either as a client or as a server.

The server advertises its existence, so it can be found by other devices, and contains the data that the client can read. The client scans the nearby devices, and when it finds the server it is looking for, it establishes a connection and listens for incoming data. This is called point-to-point communication.

As mentioned previously, BLE also supports broadcast mode and mesh network:

Broadcast mode: the server transmits data to many clients that are connected;
Mesh network: all the devices are connected, this is a many to many connection.

Even though the broadcast and mesh network setups are possible to implement, they were developed very recently, so there aren’t many examples implemented for the ESP32 at this moment.

GATT

GATT stands for Generic Attributes and it defines an hierarchical data structure that is exposed to connected BLE devices. This means that GATT defines the way that two BLE devices send and receive standard messages. Understanding this hierarchy is important, because it will make it easier to understand how to use the BLE and write your applications.

BLE Service

The top level of the hierarchy is a profile, which is composed of one or more services. Usually, a BLE device contains more than one service.

Every service contains at least one characteristic, or can also reference other services. A service is simply a collection of information, like sensor readings, for example.

There are predefined services for several types of data defined by the SIG (Bluetooth Special Interest Group) like: Battery Level, Blood Pressure, Heart Rate, Weight Scale, etc. You can check here other defined services.

View Image Souce

BLE Characteristic

The characteristic is always owned by a service, and it is where the actual data is contained in the hierarchy (value). The characteristic always has two attributes: characteristic declaration (that provides metadata about the data) and the characteristic value.

Additionally, the characteristic value can be followed by descriptors, which further expand on the metadata contained in the characteristic declaration.

The properties describe how the characteristic value can be interacted with. Basically, it contains the operations and procedures that can be used with the characteristic:

Broadcast
Read
Write without response
Write
Notify
Indicate
Authenticated Signed Writes
Extended Properties
UUID

Each service, characteristic and descriptor have an UUID (Universally Unique Identifier). An UUID is a unique 128-bit (16 bytes) number. For example:

55072829-bc9e-4c53-938a-74a6d4c78776

There are shortened UUIDs for all types, services, and profiles specified in the SIG (Bluetooth Special Interest Group).

But if your application needs its own UUID, you can generate it using this UUID generator website.

In summary, the UUID is used to uniquely identify information. For example, it can identify a particular service provided by a Bluetooth device.

BLE with ESP32

The ESP32 can act as a BLE server or as a BLE client. There are several BLE examples for the ESP32 in the ESP32 BLE library for Arduino IDE. This library comes installed by default when you install the ESP32 on the Arduino IDE.

Note: You need to have the ESP32 add-on installed on the Arduino IDE. Follow the next tutorial to prepare your Arduino IDE to work with the ESP32, if you haven’t already.

Installing ESP32 Board in Arduino IDE 2 (Windows, Mac OS X, Linux)

In your Arduino IDE, you can go to File > Examples > BLE and explore the examples that come with the BLE library.

Note: to see the ESP32 examples, you must have the ESP32 board selected on Tools > Board.

For a brief introduction to the ESP32 with BLE on the Arduino IDE, we’ll create an ESP32 BLE server, and then an ESP32 BLE scanner to find that server. We’ll use and explain the examples that come with the BLE library.

To follow this example, you need two ESP32 development boards. We’ll be using the ESP32 DOIT DEVKIT V1 Board.

ESP32 BLE Server

To create an ESP32 BLE Server, open your Arduino IDE and go to File > Examples > BLE and select the Server example. The following code should load:

/*
  Complete Getting Started Guide: https://RandomNerdTutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
  Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}


View raw code

For creating a BLE server, the code should follow the next steps:

Create a BLE Server. In this case, the ESP32 acts as a BLE server.
Create a BLE Service.
 Create a BLE Characteristic on the Service.
Create a BLE Descriptor on the Characteristic.
Start the Service.
 Start advertising, so it can be found by other devices.
How the code works

Let’s take a quick look at how the BLE server example code works.

It starts by importing the necessary libraries for the BLE capabilities.

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

Then, you need to define a UUID for the Service and Characteristic.

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

You can leave the default UUIDs, or you can go to uuidgenerator.net to create random UUIDs for your services and characteristics.

In the setup(), it starts the serial communication at a baud rate of 115200.

Serial.begin(115200);

Then, you create a BLE device called “MyESP32”. You can change this name to whatever you like.

// Create the BLE Device
BLEDevice::init("MyESP32");

In the following line, you set the BLE device as a server.

BLEServer *pServer = BLEDevice::createServer();

After that, you create a service for the BLE server with the UUID defined earlier.

 BLEService *pService = pServer->createService(SERVICE_UUID);

Then, you set the characteristic for that service. As you can see, you also use the UUID defined earlier, and you need to pass as arguments the characteristic’s properties. In this case, it’s: READ and WRITE.

BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                     CHARACTERISTIC_UUID,
                                     BLECharacteristic::PROPERTY_READ |
                                     BLECharacteristic::PROPERTY_WRITE
                                     );

After creating the characteristic, you can set its value with the setValue() method.

pCharacteristic->setValue("Hello World says Neil");

In this case we’re setting the value to the text “Hello World says Neil”. You can change this text to whatever your like. In future projects, this text can be a sensor reading, or the state of a lamp, for example.

Finally, you can start the service, and the advertising, so other BLE devices can scan and find this BLE device.

BLEAdvertising *pAdvertising = pServer->getAdvertising();
pAdvertising->start();

This is just a simple example on how to create a BLE server. In this code nothing is done in the loop(), but you can add what happens when a new client connects (check the Notify example for some guidance).

ESP32 BLE Scanner

Creating an ESP32 BLE scanner is simple. Grab another ESP32 (while the other is running the BLE server sketch). In your Arduino IDE, go to File > Examples > BLE and select the Scan example. The following code should load.

/*
  Complete Getting Started Guide: https://RandomNerdTutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
  Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // in seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices->getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}


View raw code

This code initializes the ESP32 as a BLE device and scans for nearby devices. Upload this code to your ESP32. You might want to temporarily disconnect the other ESP32 from your computer, so you’re sure that you’re uploading the code to the right ESP32 board.

Once the code is uploaded and you should have the two ESP32 boards powered on:

One ESP32 with the “BLE_server” sketch;
Other with ESP32 “BLE_scan” sketch.

Go to the Serial Monitor with the ESP32 running the “BLE_scan” example, press the ESP32 (with the “BLE_scan” sketch) ENABLE button to restart and wait a few seconds while it scans.

The scanner found two devices: one is the ESP32 (it has the name “MyESP32“), and the other is a smart watch.

Testing the ESP32 BLE Server with Your Smartphone

Most modern smartphones should have BLE capabilities. I was using a OnePlus, but most smartphones should also work.

You can scan your ESP32 BLE server with your smartphone and see its services and characteristics. For that, we’ll be using a free app called nRF Connect for Mobile from Nordic, it works on Android (Google Play Store) and iOS (App Store).

Go to Google Play Store or App Store and search for “nRF Connect for Mobile”. Install the app and open it.

Don’t forget go to the Bluetooth settings and enable Bluetooth adapter in your smartphone. You may also want to make it visible to other devices to test other sketches later on.

Once everything is ready in your smartphone and the ESP32 is running the BLE server sketch, in the app, tap the scan button to scan for nearby devices. You should find an ESP32 with the name “MyESP32”.

Click the “Connect” button.

As you can see in the figure below, the ESP32 has a service with the UUID that you’ve defined earlier. If you tap the service, it expands the menu and shows the Characteristic with the UUID that you’ve also defined.

The characteristic has the READ and WRITE properties, and the value is the one you’ve previously defined in the BLE server sketch. So, everything is working fine.

Wrapping Up

In this tutorial we’ve shown you the basic principles of Bluetooth Low Energy and shown you some examples with the ESP32. We’ve explored the BLE server sketch and the BLE scan sketch. These are simple examples to get you started with BLE.

The idea is using BLE to send or receive sensor readings from other devices.

Other Bluetooth-related tutorials that you may like:

ESP32 with Bluetooth and Bluetooth Low Energy: The Ultimate Guide
ESP32 BLE Server and Client (Bluetooth Low Energy)
ESP32 Wi-Fi Provisioning via BLE (Bluetooth Low Energy) – Arduino IDE
ESP32 Web Bluetooth (BLE): Getting Started Guide
ESP32 Bluetooth Classic with Arduino IDE – Getting Started

This is an excerpt from our course: Learn ESP32 with Arduino IDE. If you like ESP32 and you want to learn more about it, we recommend enrolling in Learn ESP32 with Arduino IDE course.

You might also like reading:

Learn ESP32 with Arduino IDE
ESP32 Bluetooth Classic with Arduino IDE – Getting Started
ESP32 Data Logging Temperature to MicroSD Card
ESP32 with DC Motor and L298N Motor Driver – Control Speed and Direction

Thanks for reading.





SMART HOME with Raspberry Pi, ESP32, ESP8266 [eBook]
Learn how to build a home automation system and we’ll cover the following main subjects: Node-RED, Node-RED Dashboard, Raspberry Pi, ESP32, ESP8266, MQTT, and InfluxDB database DOWNLOAD »
Recommended Resources

Build a Home Automation System from Scratch » With Raspberry Pi, ESP8266, Arduino, and Node-RED.

Home Automation using ESP8266 eBook and video course » Build IoT and home automation projects.

Arduino Step-by-Step Projects » Build 25 Arduino projects with our course, even with no prior experience!

What to Read Next…
ESP32 with MPU-6050 Accelerometer, Gyroscope and Temperature Sensor (Arduino)
Raspberry Pi Publishing MQTT Messages to ESP8266
MicroPython: WS2812B Addressable RGB LEDs with ESP32 and ESP8266


Enjoyed this project? Stay updated by subscribing our newsletter!
SUBSCRIBE

---

## 🖼️ 추출된 이미지 URL 목록

- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2024/06/ESP32-BLE-Getting-Started-1.jpg?resize=828%2C466&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/BLE-Intro.png?resize=828%2C251&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/Bluetooth-vs-BLE.png?resize=818%2C650&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/ble-applications.png?resize=750%2C189&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/BLE-server-and-client.png?resize=828%2C169&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/GATT-BLE-ESP32.png?resize=750%2C421&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/gatt-services.png?resize=828%2C572&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP32-File-Examples-BLE-Arduino.png?resize=750%2C713&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/scan-server-esp32.jpg?resize=750%2C393&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/esp32-scan-enable-button.jpg?resize=750%2C690&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/esp32-scan.jpg?resize=753%2C443&quality=100&strip=all&ssl=1
- https://i0.wp.com/rntlab.com/wp-content/uploads/2018/02/nRF-connect.jpg?w=828&quality=100&strip=all&ssl=1
- https://i0.wp.com/rntlab.com/wp-content/uploads/2018/02/enable-bluetooth-nrf-e1519725728543.jpg?w=828&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/ble-server-found.jpg?resize=750%2C672&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/06/BLE-server-service.jpg?resize=450%2C599&quality=100&strip=all&ssl=1
- https://randomnerdtutorials.com/wp-content/uploads/2022/03/728x280.jpg
- https://randomnerdtutorials.com/wp-content/uploads/elementor/thumbs/Smart-Home-Raspberry-Pi-ESP32-ESP8266-eBook500px-pupj8i6e7hlzpgwxe82jjd8skst9vmrjt9lpqb0v0g.jpg
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/10/home-automation-sb-img.jpg?fit=400%2C225&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/10/esp8266-sb-img.jpg?fit=400%2C225&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/10/arduino-sb-img.jpg?fit=400%2C225&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/12/ESP32-MPU6050-Module-Accelerometer-Gyroscope-Temperature-Sensor-Arduino.jpg?fit=1280%2C720&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/02/featured-image-raspberry-pi-esp8266-mqtt-output.jpg?fit=1280%2C720&quality=100&strip=all&ssl=1
- https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/02/ws2812b-micropython-esp8266-esp32.jpg?fit=1280%2C720&quality=100&strip=all&ssl=1
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=
- data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPGcgY2xpcC1wYXRoPSJ1cmwoI2NsaXAwKSI+CjxwYXRoIGQ9Ik0xMS45MiAxMC43Mkw2LjgwMDAxIDAuNDhDNi40ODAwMSAtMC4xNiA1LjYwMDAxIC0wLjE2IDUuMjgwMDEgMC40OEwwLjA4MDAwNTMgMTAuNzJDLTAuMjM5OTk1IDExLjI4IDAuMjQwMDA1IDEyIDAuODgwMDA1IDEySDExLjEyQzExLjc2IDEyIDEyLjE2IDExLjI4IDExLjkyIDEwLjcyWk02LjAwMDAxIDEwLjRDNS4zNjAwMSAxMC40IDQuODAwMDEgOS44NCA0LjgwMDAxIDkuMkM0LjgwMDAxIDguNTYgNS4yODAwMSA4IDYuMDAwMDEgOEM2LjcyMDAxIDggNy4yMDAwMSA4LjU2IDcuMjAwMDEgOS4yQzcuMjAwMDEgOS45MiA2LjY0MDAxIDEwLjQgNi4wMDAwMSAxMC40Wk02LjgwMDAxIDcuMkg1LjIwMDAxTDQuODAwMDEgNC40QzQuODAwMDEgNC4xNiA0Ljk2MDAxIDQgNS4yMDAwMSA0SDYuODAwMDFDNy4wNDAwMSA0IDcuMjAwMDEgNC4xNiA3LjIwMDAxIDQuNEw2LjgwMDAxIDcuMloiIGZpbGw9IiMwMDAwMDAiLz4KPC9nPgo8ZGVmcz4KPGNsaXBQYXRoIGlkPSJjbGlwMCI+CjxyZWN0IHdpZHRoPSIxMiIgaGVpZ2h0PSIxMiIgZmlsbD0id2hpdGUiLz4KPC9jbGlwUGF0aD4KPC9kZWZzPgo8L3N2Zz4K

---

## 💻 추출된 코드 블록

### Code Block 1
```cpp
55072829-bc9e-4c53-938a-74a6d4c78776
```

### Code Block 2
```cpp
/*
  Complete Getting Started Guide: https://RandomNerdTutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
  Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}

```

### Code Block 3
```cpp
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
```

### Code Block 4
```cpp
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
```

### Code Block 5
```cpp
Serial.begin(115200);
```

### Code Block 6
```cpp
// Create the BLE Device
BLEDevice::init("MyESP32");
```

### Code Block 7
```cpp
BLEServer *pServer = BLEDevice::createServer();
```

### Code Block 8
```cpp
 BLEService *pService = pServer->createService(SERVICE_UUID);
```

### Code Block 9
```cpp
BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                     CHARACTERISTIC_UUID,
                                     BLECharacteristic::PROPERTY_READ |
                                     BLECharacteristic::PROPERTY_WRITE
                                     );
```

### Code Block 10
```cpp
pCharacteristic->setValue("Hello World says Neil");
```

### Code Block 11
```cpp
BLEAdvertising *pAdvertising = pServer->getAdvertising();
pAdvertising->start();
```

### Code Block 12
```cpp
/*
  Complete Getting Started Guide: https://RandomNerdTutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
  Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // in seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices->getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}

```

