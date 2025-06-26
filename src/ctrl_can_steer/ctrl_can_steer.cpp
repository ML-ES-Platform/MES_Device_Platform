#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0_STEER(10);  // SPI CS pin (adjust as needed)

#define BASE_SEND_ID   0x0600000
#define BASE_RETURN_ID 0x0580000

// Generic CAN send function
bool sendCanMessage(uint32_t baseID, uint32_t motorID, byte* data, uint8_t len) {
  uint32_t canID = baseID + motorID;
  byte status = CAN0_STEER.sendMsgBuf(canID, 1, len, data);
  if (status == CAN_OK) {
    Serial.print("Message sent successfully. CAN ID: 0x");
    Serial.println(canID, HEX);
    return true;
  } else {
    Serial.print("Failed to send message. CAN ID: 0x");
    Serial.print(canID, HEX);
    Serial.print(" Status: ");
    Serial.println(status);
    return false;
  }
}

// Read and parse CAN feedback
bool readCanFeedback(uint32_t motorID, byte* rxData, uint8_t* rxLen) {
  long unsigned int rxId;
  byte len = 0;
  byte buf[8];

  if (CAN0_STEER.checkReceive() == CAN_MSGAVAIL) {
    if (CAN0_STEER.readMsgBuf(&rxId, &len, buf) == CAN_OK) {
      uint32_t expectedId = BASE_RETURN_ID + motorID;
      if (rxId == expectedId) {
        if (rxLen) *rxLen = len;
        if (rxData) {
          for (byte i = 0; i < len; i++) {
            rxData[i] = buf[i];
          }
        }

        Serial.print("Feedback from motor 0x");
        Serial.print(motorID, HEX);
        Serial.print(": ");
        for (byte i = 0; i < len; i++) {
          Serial.print(buf[i], HEX);
          Serial.print(" ");
        }
        Serial.println();

        // Basic feedback parsing
        if (len > 1 && buf[0] == 0x60) {
          switch (buf[1]) {
            case 0x0D: Serial.println("Motor Enabled"); break;
            case 0x0C: Serial.println("Motor Disabled"); break;
            case 0x00: Serial.println("Speed feedback"); break;
            case 0x02: Serial.println("Position feedback"); break;
            case 0x01: Serial.println("Status query feedback"); break;
            default: Serial.println("Unknown feedback"); break;
          }
        }
        return true;
      }
    }
  }
  return false;
}

// Send command and read feedback helper
bool sendCommandAndReadFeedback(uint32_t motorID, byte* data, uint8_t len, byte* rxData, uint8_t* rxLen) {
  // Send command
  bool sendOk = sendCanMessage(BASE_SEND_ID, motorID, data, len);
  if (!sendOk) return false;

  // Wait briefly for device response
  delay(50);

  // Try reading feedback with timeout
  unsigned long startTime = millis();
  const unsigned long timeout = 200;  // ms
  while (millis() - startTime < timeout) {
    if (readCanFeedback(motorID, rxData, rxLen)) {
      return true;
    }
    delay(10);
  }

  Serial.println("No feedback received after sending command.");
  return false;
}

// Command functions using send+read helper

bool canEnableMotor(uint32_t motorID) {
  byte data[8] = {0x23, 0x0D, 0x20, 0x01, 0, 0, 0, 0};
  byte rxData[8];
  uint8_t rxLen;
  return sendCommandAndReadFeedback(motorID, data, 8, rxData, &rxLen);
}

bool canDisableMotor(uint32_t motorID) {
  byte data[8] = {0x23, 0x0C, 0x20, 0x01, 0, 0, 0, 0};
  byte rxData[8];
  uint8_t rxLen;
  return sendCommandAndReadFeedback(motorID, data, 8, rxData, &rxLen);
}

bool canSetSpeed(uint32_t motorID, int16_t speed) {
  byte data[8] = {
    0x23, 0x00, 0x20, 0x01,
    (byte)(speed >> 8), (byte)(speed & 0xFF),
    0, 0
  };
  byte rxData[8];
  uint8_t rxLen;
  return sendCommandAndReadFeedback(motorID, data, 8, rxData, &rxLen);
}

bool canSetPosition(uint32_t motorID, int32_t position) {
  byte data[8] = {
    0x23, 0x02, 0x20, 0x01,
    (byte)((position >> 24) & 0xFF),
    (byte)((position >> 16) & 0xFF),
    (byte)((position >> 8) & 0xFF),
    (byte)(position & 0xFF)
  };
  byte rxData[8];
  uint8_t rxLen;
  return sendCommandAndReadFeedback(motorID, data, 8, rxData, &rxLen);
}

bool canSendStatusQuery(uint32_t motorID) {
  byte data[8] = {0x40, 0x01, 0x21, 0x01, 0, 0, 0, 0};
  byte rxData[8];
  uint8_t rxLen;
  return sendCommandAndReadFeedback(motorID, data, 8, rxData, &rxLen);
}





void ctrl_can_steer_setup() {
  Serial.begin(115200);
  Serial.println("Starting CAN...");

  delay(1000);

  while (CAN0_STEER.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("CAN init failed, retrying...");
    delay(1000);
  }

  CAN0_STEER.setMode(MCP_NORMAL);
  Serial.println("CAN initialized and set to normal mode.");
}

void ctrl_can_steer_loop() {
  uint32_t motorID = 1;

  if (canEnableMotor(motorID)) {
    Serial.println("Enable command completed.");
  } else {
    Serial.println("Enable command failed.");
  }
  delay(100);

  if (canSetSpeed(motorID, 500)) {
    Serial.println("Speed command completed.");
  } else {
    Serial.println("Speed command failed.");
  }
  delay(1000);

  if (canSetPosition(motorID, 10000)) {
    Serial.println("Position command completed.");
  } else {
    Serial.println("Position command failed.");
  }
  delay(1000);

  if (canSendStatusQuery(motorID)) {
    Serial.println("Status query completed.");
  } else {
    Serial.println("Status query failed.");
  }
  delay(100);

  if (canDisableMotor(motorID)) {
    Serial.println("Disable command completed.");
  } else {
    Serial.println("Disable command failed.");
  }
  delay(1000);
}
