#include <Relay.h>
#include <Contact.h>
#include <CnC.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char nodeName[] PROGMEM = "ext";
const char sepName[] PROGMEM = " ";
const char hkName[] PROGMEM = "val";
const char cmdGetName[] PROGMEM = "get";
const char cmdSetName[] PROGMEM = "set";

const char pingName[] PROGMEM = "ping";
const char waterMainRelayName[] PROGMEM = "waterMainRelay";
const char waterGardenRelayName[] PROGMEM = "waterGardenRelay";
const char waterSideRelayName[] PROGMEM = "waterSideRelay";
const char waterEastRelayName[] PROGMEM = "waterEastRelay";
const char waterWestRelayName[] PROGMEM = "waterWestRelay";
const char waterSouthRelayName[] PROGMEM = "waterSouthRelay";
const char tempSensorsName[] PROGMEM = "tempSensors";
const char windSpeedName[] PROGMEM = "windSpeed";
const char rainFlowName[] PROGMEM = "rainFlow";

Relay waterMainRelay(waterMainRelayName, 13);
Relay waterGardenRelay(waterGardenRelayName, 5);
Relay waterSideRelay(waterSideRelayName, 9);
Relay waterEastRelay(waterEastRelayName, 7);
Relay waterWestRelay(waterWestRelayName, 8);
Relay waterSouthRelay(waterSouthRelayName, 6);

OneWire oneWire(4);
DallasTemperature tempSensors(&oneWire);

uint32_t previousTime_1s = 0;
uint32_t previousTime_10s = 0;
uint32_t currentTime = 0;
uint32_t currentWindSpeedValue = 0;
uint32_t previousWindSpeedValue = 0;
uint32_t currentRainFlowValue = 0;

void ping_cmdGet(int arg_cnt, char **args) { cnc_print_cmdGet_u32(pingName, currentTime); }
void waterMainRelay_cmdGet(int arg_cnt, char **args) { waterMainRelay.cmdGet(arg_cnt, args); }
void waterMainRelay_cmdSet(int arg_cnt, char **args) { waterMainRelay.cmdSet(arg_cnt, args); }
void waterGardenRelay_cmdGet(int arg_cnt, char **args) { waterGardenRelay.cmdGet(arg_cnt, args); }
void waterGardenRelay_cmdSet(int arg_cnt, char **args) { waterGardenRelay.cmdSet(arg_cnt, args); }
void waterSideRelay_cmdGet(int arg_cnt, char **args) { waterSideRelay.cmdGet(arg_cnt, args); }
void waterSideRelay_cmdSet(int arg_cnt, char **args) { waterSideRelay.cmdSet(arg_cnt, args); }
void waterEastRelay_cmdGet(int arg_cnt, char **args) { waterEastRelay.cmdGet(arg_cnt, args); }
void waterEastRelay_cmdSet(int arg_cnt, char **args) { waterEastRelay.cmdSet(arg_cnt, args); }
void waterWestRelay_cmdGet(int arg_cnt, char **args) { waterWestRelay.cmdGet(arg_cnt, args); }
void waterWestRelay_cmdSet(int arg_cnt, char **args) { waterWestRelay.cmdSet(arg_cnt, args); }
void waterSouthRelay_cmdGet(int arg_cnt, char **args) { waterSouthRelay.cmdGet(arg_cnt, args); }
void waterSouthRelay_cmdSet(int arg_cnt, char **args) { waterSouthRelay.cmdSet(arg_cnt, args); }
uint8_t tempSensorsNb = 0;

void ISR_windSpeed(void) {
  currentWindSpeedValue++;
}

void ISR_rainFlow(void) {
  currentRainFlowValue++;
}

void setup() {
  Serial.begin(115200);
  cncInit(nodeName);
  cnc_hkName_set(hkName);
  cnc_cmdGetName_set(cmdGetName);
  cnc_cmdSetName_set(cmdSetName);
  cnc_sepName_set(sepName);
  cnc_cmdGet_Add(pingName, ping_cmdGet);
  cnc_cmdGet_Add(waterMainRelayName, waterMainRelay_cmdGet);
  cnc_cmdSet_Add(waterMainRelayName, waterMainRelay_cmdSet);
  cnc_cmdGet_Add(waterGardenRelayName, waterGardenRelay_cmdGet);
  cnc_cmdSet_Add(waterGardenRelayName, waterGardenRelay_cmdSet);
  cnc_cmdGet_Add(waterSideRelayName, waterSideRelay_cmdGet);
  cnc_cmdSet_Add(waterSideRelayName, waterSideRelay_cmdSet);
  cnc_cmdGet_Add(waterEastRelayName, waterEastRelay_cmdGet);
  cnc_cmdSet_Add(waterEastRelayName, waterEastRelay_cmdSet);
  cnc_cmdGet_Add(waterWestRelayName, waterWestRelay_cmdGet);
  cnc_cmdSet_Add(waterWestRelayName, waterWestRelay_cmdSet);
  cnc_cmdGet_Add(waterSouthRelayName, waterSouthRelay_cmdGet);
  cnc_cmdSet_Add(waterSouthRelayName, waterSouthRelay_cmdSet);
  previousTime_1s = millis();
  previousTime_10s = previousTime_1s;
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR_rainFlow, CHANGE);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), ISR_windSpeed, CHANGE);
}


void loop() {
  currentTime = millis(); cncPoll();
  /* HK @ 1.0Hz */
  if((uint32_t)(currentTime - previousTime_1s) >= 1000) {
    waterMainRelay.run(true); cncPoll();
    waterGardenRelay.run(true); cncPoll();
    waterSideRelay.run(true); cncPoll();
    waterEastRelay.run(true); cncPoll();
    waterWestRelay.run(true); cncPoll();
    waterSouthRelay.run(true); cncPoll();
    previousTime_1s = currentTime;
  }
  /* HK @ 0.1Hz */
  if((uint32_t)(currentTime - previousTime_10s) >= 10000) {
    cnc_print_hk_u32(windSpeedName, currentWindSpeedValue - previousWindSpeedValue);
    previousWindSpeedValue = currentWindSpeedValue;
    cnc_print_hk_u32(rainFlowName, currentRainFlowValue);
    tempSensors.begin();
    tempSensorsNb = tempSensors.getDeviceCount();
    tempSensors.requestTemperatures();
    for(uint8_t i=0; i<tempSensorsNb; i++)  {
      DeviceAddress sensorAddr;
      tempSensors.getAddress(sensorAddr, i);
      cnc_print_hk_temp_sensor(tempSensorsName, sensorAddr, tempSensors.getTempCByIndex(i));
    }
    previousTime_10s = currentTime;
  }
}
