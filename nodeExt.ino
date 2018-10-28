#include <Relay.h>
#include <Contact.h>
#include <CnC.h>

const char nodeName[] PROGMEM = "ext";
const char sepName[] PROGMEM = " ";
const char hkName[] PROGMEM = "hk";
const char cmdGetName[] PROGMEM = "get";
const char cmdSetName[] PROGMEM = "set";

const char pingName[] PROGMEM = "ping";
const char waterMainRelayName[] PROGMEM = "waterMainRelay";
const char waterGardenRelayName[] PROGMEM = "waterGardenRelay";
const char waterSideRelayName[] PROGMEM = "waterSideRelay";
const char waterEastRelayName[] PROGMEM = "waterEastRelay";
const char waterWestRelayName[] PROGMEM = "waterWestRelay";
const char waterSouthRelayName[] PROGMEM = "waterSouthRelay";
const char tempNotUsedName[] PROGMEM = "tempNotUsed";

Relay waterMainRelay(waterMainRelayName, 13);
Relay waterGardenRelay(waterGardenRelayName, 3);
Relay waterSideRelay(waterSideRelayName, 7);
Relay waterEastRelay(waterEastRelayName, 6);
Relay waterWestRelay(waterWestRelayName, 5);
Relay waterSouthRelay(waterSouthRelayName, 4);
Contact tempNotUsed(tempNotUsedName, 2);

static uint32_t loopNb = 0;

void ping_cmdGet(int arg_cnt, char **args) {
  cnc_print_cmdGet_u32(pingName, loopNb);
}
void waterMainRelay_cmdGet(int arg_cnt, char **args) {
  waterMainRelay.cmdGet(arg_cnt, args);
}
void waterMainRelay_cmdSet(int arg_cnt, char **args) {
  waterMainRelay.cmdSet(arg_cnt, args);
}
void waterGardenRelay_cmdGet(int arg_cnt, char **args) {
  waterGardenRelay.cmdGet(arg_cnt, args);
}
void waterGardenRelay_cmdSet(int arg_cnt, char **args) {
  waterGardenRelay.cmdSet(arg_cnt, args);
}
void waterSideRelay_cmdGet(int arg_cnt, char **args) {
  waterSideRelay.cmdGet(arg_cnt, args);
}
void waterSideRelay_cmdSet(int arg_cnt, char **args) {
  waterSideRelay.cmdSet(arg_cnt, args);
}
void waterEastRelay_cmdGet(int arg_cnt, char **args) {
  waterEastRelay.cmdGet(arg_cnt, args);
}
void waterEastRelay_cmdSet(int arg_cnt, char **args) {
  waterEastRelay.cmdSet(arg_cnt, args);
}
void waterWestRelay_cmdGet(int arg_cnt, char **args) {
  waterWestRelay.cmdGet(arg_cnt, args);
}
void waterWestRelay_cmdSet(int arg_cnt, char **args) {
  waterWestRelay.cmdSet(arg_cnt, args);
}
void waterSouthRelay_cmdGet(int arg_cnt, char **args) {
  waterSouthRelay.cmdGet(arg_cnt, args);
}
void waterSouthRelay_cmdSet(int arg_cnt, char **args) {
  waterSouthRelay.cmdSet(arg_cnt, args);
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
}


void loop() {
  delay(1);
  waterMainRelay.run(false);
  waterGardenRelay.run(false);
  waterSideRelay.run(false);
  waterEastRelay.run(false);
  waterWestRelay.run(false);
  waterSouthRelay.run(false);
  cncPoll();
  loopNb++;
  if (1000000000 <= loopNb) {
    loopNb = 0;
  }
}

