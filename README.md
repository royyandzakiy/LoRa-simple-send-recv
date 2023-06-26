# LoRa Simple Send Receive

This project uses the library [sandeepmistry/LoRa](https://github.com/sandeepmistry/arduino-LoRa) as driver for LoRa module.

### Important Note
- If NodeID never set in EEPROM before, activate line `EEPROM.write(EEPROM_ADDRESS_NODEID, NODEID);`, and define NODEID in `global.h`

### LoRa functions
- `void sendMsg(const String)`  : send any kind of string message
- `void recvMsg()`              : receive and print message received
- `sendMsg` and `recvMsg` is callled within the main `loop()`

## Getting Started
- Install [VSCode](https://code.visualstudio.com/download)
- Install PlatformIO (PIO) Extension in VSCode
    - Go to `Extensions` on the left side bar, search for PlatformIO
- Build, Compile in PlatformIO