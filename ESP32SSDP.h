/*
ESP32 Simple Service Discovery
Copyright (c) 2015 Hristo Gochkov

Original (Arduino) version by Filippo Sallemi, July 23, 2014.
Can be found at: https://github.com/nomadnt/uSSDP

License (MIT license):
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/
#ifndef ARDUINO_ARCH_ESP32
#error ESP32SSPD is support ESP32 only
#endif

#ifndef ESP32SSDP_H
#define ESP32SSDP_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define SSDP_UUID_SIZE              37
#define SSDP_SCHEMA_URL_SIZE        64
#define SSDP_DEVICE_TYPE_SIZE       64
#define SSDP_FRIENDLY_NAME_SIZE     64
#define SSDP_SERIAL_NUMBER_SIZE     32
#define SSDP_PRESENTATION_URL_SIZE  128
#define SSDP_MODEL_NAME_SIZE        64
#define SSDP_MODEL_URL_SIZE         128
#define SSDP_MODEL_VERSION_SIZE     32
#define SSDP_MANUFACTURER_SIZE      64
#define SSDP_MANUFACTURER_URL_SIZE  128

typedef enum {
  NONE,
  SEARCH,
  NOTIFY
} ssdp_method_t;


struct SSDPTimer;

class SSDPClass{
  public:
    SSDPClass();
    ~SSDPClass();

    bool begin();
    void end();

    SSDPClass& schema(WiFiClient client);

    SSDPClass& setDeviceType(const String& deviceType) { return setDeviceType(deviceType.c_str()); }
    SSDPClass& setDeviceType(const char *deviceType);
    SSDPClass& setName(const String& name) { return setName(name.c_str()); }
    SSDPClass& setName(const char *name);
    SSDPClass& setURL(const String& url) { return setURL(url.c_str()); }
    SSDPClass& setURL(const char *url);
    SSDPClass& setSchemaURL(const String& url) { return setSchemaURL(url.c_str()); }
    SSDPClass& setSchemaURL(const char *url);
    SSDPClass& setSerialNumber(const String& serialNumber) { return setSerialNumber(serialNumber.c_str()); }
    SSDPClass& setSerialNumber(const char *serialNumber);
    SSDPClass& setSerialNumber(const uint32_t serialNumber);
    SSDPClass& setModelName(const String& name) { return setModelName(name.c_str()); }
    SSDPClass& setModelName(const char *name);
    SSDPClass& setModelNumber(const String& num) { return setModelNumber(num.c_str()); }
    SSDPClass& setModelNumber(const char *num);
    SSDPClass& setModelURL(const String& url) { return setModelURL(url.c_str()); }
    SSDPClass& setModelURL(const char *url);
    SSDPClass& setManufacturer(const String& name) { return setManufacturer(name.c_str()); }
    SSDPClass& setManufacturer(const char *name);
    SSDPClass& setManufacturerURL(const String& url) { return setManufacturerURL(url.c_str()); }
    SSDPClass& setManufacturerURL(const char *url);
    SSDPClass& setHTTPPort(uint16_t port);
    SSDPClass& setTTL(uint8_t ttl);

  protected:
    void _send(ssdp_method_t method);
    void _update();
    void _startTimer();
    void _stopTimer();
    static void _onTimerStatic(SSDPClass* self);
    IPAddress localIP();
     WiFiUDP *_server;
     SSDPTimer* _timer;
    uint16_t _port;
    uint8_t _ttl;

    IPAddress _respondToAddr;
    uint16_t  _respondToPort;

    bool _pending;
    unsigned short _delay;
    unsigned long _process_time;
    unsigned long _notify_time;

    char _schemaURL[SSDP_SCHEMA_URL_SIZE];
    char _uuid[SSDP_UUID_SIZE];
    char _deviceType[SSDP_DEVICE_TYPE_SIZE];
    char _friendlyName[SSDP_FRIENDLY_NAME_SIZE];
    char _serialNumber[SSDP_SERIAL_NUMBER_SIZE];
    char _presentationURL[SSDP_PRESENTATION_URL_SIZE];
    char _manufacturer[SSDP_MANUFACTURER_SIZE];
    char _manufacturerURL[SSDP_MANUFACTURER_URL_SIZE];
    char _modelName[SSDP_MODEL_NAME_SIZE];
    char _modelURL[SSDP_MODEL_URL_SIZE];
    char _modelNumber[SSDP_MODEL_VERSION_SIZE];
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SSDP)
extern SSDPClass SSDP;
#endif

#endif