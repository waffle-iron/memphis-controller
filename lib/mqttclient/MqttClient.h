/*
 * MqttClient.h
 *
 *  Created on: 09.04.2016
 *      Author: scan
 */

#ifndef PROD_SOCKETS_MQTTCLIENT_H_
#define PROD_SOCKETS_MQTTCLIENT_H_

#include <stdint.h>

class IoF_WiFiClient;
class FishActuator;
class PubSubClient;
class Timer;

//-----------------------------------------------------------------------------

class MqttClientAdapter
{
public:
  virtual ~MqttClientAdapter() { }

  /**
   * Get MAC Address.
   * @return macAddr c-String with the MAC address in the form "xx:xx:xx:xx:xx:xx" (memory allocated by callee)
   */
  virtual const char* getMacAddr() = 0;

  /**
   * Get information if the device already has received a configuration
   * @ return isConfigured returns true if the device has already received a configuration
   */
  virtual bool isConfigured() const = 0;

protected:
  MqttClientAdapter() { }
private:  // forbidden functions
  MqttClientAdapter(const MqttClientAdapter& src);              // copy constructor
  MqttClientAdapter& operator = (const MqttClientAdapter& src); // assignment operator
};

//-----------------------------------------------------------------------------

class MqttClient
{
public:
  MqttClient(const char* mqttServerDomain, unsigned short int mqttPort, MemphisWiFiClient* wifiClient, MqttClientAdapter* adapter = 0);
  virtual ~MqttClient();

  void attachAdapter(MqttClientAdapter* adapter);
  MqttClientAdapter* adapter();

  void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
  void startupClient();
  void reconnect();
  void subscribeToConfigTopic();
  void subscribeToAquariumTopic();
  void publishConfigID();
  void setPublishInfo(const char* country, const char* city);
  void publishCapTouched();
  void loop();

private:
  MemphisWiFiClient* m_wifiClient;
  MqttClientAdapter* m_adapter;
  PubSubClient* m_pubSubClient;
  Timer* m_mqttConnectTimer;
  bool m_wasConnectedBefore;
  char* m_clientCountry;
  char* m_clientCity;
  static const unsigned int s_maxCountrySize;
  static const unsigned int s_maxCitySize;
  static const int s_reconnectInterval_ms;

private:  // forbidden functions
  MqttClient(const MqttClient& src);              // copy constructor
  MqttClient& operator = (const MqttClient& src); // assignment operator
};

#endif /* PROD_SOCKETS_MQTTCLIENT_H_ */
