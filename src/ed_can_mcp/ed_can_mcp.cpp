// // CAN Receive Example
// //
// #include "Arduino.h"
// #include <mcp_can.h>
// #include "ed_can_mcp.h"
// #include "srv_com_can/srv_com_can_matrix.h"

// #define CAN_MESSAGE_LEN 8

// long unsigned int rxId;
// long unsigned int txId;

// unsigned char dd_can_msg_len = CAN_MESSAGE_LEN;
// uint8_t dd_can_rx_data[CAN_MESSAGE_LEN];
// uint8_t dd_can_tx_data[CAN_MESSAGE_LEN];
// // uint8_t dd_can_tx_data[CAN_MESSAGE_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

// char msgString[128]; // Array to store serial string

// MCP_CAN CAN0(CAN0_CS); // Set CS to pin 10

// //=============================================================
// // Can Setup
// void ed_can_mcp_setup()
// {

//   // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
//   if (CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ) == CAN_OK)
//     Serial.println(F("MCP2515 Initialized Successfully!"));
//   else
//     Serial.println(F("Error Initializing MCP2515..."));
//   // Change to normal mode to allow messages to be transmitted
//   CAN0.setMode(MCP_NORMAL);
//   // CAN0.setMode(MCP_LOOPBACK);

//   // Configuring pin for /INT input (optional)
//   pinMode(CAN0_INT, INPUT);

//   Serial.println(F("MCP2515 Driver started..."));
// }

// //=============================================================
// // Receiving Process
// void ed_can_mcp_recv_loop()
// {
//   // Check if data is received
//   if (CAN_MSGAVAIL == CAN0.checkReceive())
//   // if (!digitalRead(CAN0_INT)) // If CAN0_INT pin is low, read receive buffer
//   {
//     // Read data: len = data length, buf = data byte(s)
//     CAN0.readMsgBuf(&rxId, &dd_can_msg_len, dd_can_rx_data);
//     // Determine if ID is standard (11 bits) or extended (29 bits)
//     if ((rxId & 0x80000000) == 0x80000000)
//     {
//       // sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), dd_can_msg_len);
//     }
//     else
//     {
//       // sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, dd_can_msg_len);
//     }
//     Serial.print(msgString);

//     // // print message buffer in hex
//     // for (int i = 0; i < dd_can_msg_len; i++)
//     // {
//     //   sprintf(msgString, " %.2X", dd_can_rx_data[i]);
//     //   Serial.print(msgString);
//     // }

//     // Serial.println();

//     // Determine if message is a remote request frame.
//     if ((rxId & 0x40000000) == 0x40000000)
//     {
//       sprintf(msgString, " REMOTE REQUEST FRAME");
//       // Serial.print(msgString);
//     }
//     else
//     {
//       // ed_can_mcp_rx_buff_print();
//       rxId &= (~CAN_ID_EXTENDED);
//       dd_can_matrix_rx_set(rxId, dd_can_rx_data, dd_can_msg_len);
//     }
//   }
// }


// //=============================================================
// // Sending Process
// void ed_can_mcp_send_loop()
// {
//   for (int tx_id_it = 0; tx_id_it < TX_CAN_ID_NR_OF; tx_id_it++)
//   {
//     uint32_t *tx_id_list = ed_can_mcp_get_tx_can_list_ref();

//     txId = tx_id_list[tx_id_it];

//     // Serial.println("HERE 1");
//     // Serial.println(txId,HEX);

//     uint8_t msg_stat = dd_can_matrix_tx_get(txId, dd_can_tx_data, dd_can_msg_len);

//     // Serial.println("HERE 1");
//     // Serial.println(msg_stat,HEX);

//     byte sndStat;
//     int retryCount = 0;
//     const int maxRetries = 5;
//     if (msg_stat == CAN_MESSAGE_UPDATED || msg_stat == CAN_MESSAGE_RECURENT)
//     {

//       do
//       {
//         sndStat = CAN0.sendMsgBuf(txId, 1, dd_can_msg_len, dd_can_tx_data);
//         if (sndStat != CAN_OK)
//         {
//           Serial.println("Send message timeout, retrying...");
//           Serial.println(sndStat);

//           delay(10);
//           retryCount++;
//         }
//       } while (sndStat != CAN_OK && retryCount < maxRetries);

//       if (sndStat == CAN_OK)
//       {
//         // Serial.println("Message sent successfully!");
//       }
//       else
//       {
//         Serial.print("Failed to send message after retries, status: ");
//         Serial.println(sndStat);
//       }
//     }
//     if (msg_stat == CAN_MESSAGE_UPDATED || msg_stat == CAN_MESSAGE_RECURENT)
//     {
//       // send data to the CAN network
//       byte sndStat = CAN0.sendMsgBuf(txId,            // ID = 0x100,
//                                      1,               // Standard CAN Frame,
//                                      dd_can_msg_len,  // Data length = dd_can_msg_len bytes,
//                                      dd_can_tx_data); // 'data' = array of data bytes to send

//       //   Serial.print("CAN TX ID: 0x");
//       //   Serial.print(txId, HEX);
//       //   Serial.print(" Data:");
//       //   for (int i = 0; i < dd_can_msg_len; i++) {
//       //     Serial.print(" ");
//       //     Serial.print(dd_can_tx_data[i], HEX);
//       //   }
//       //   Serial.println();

//       // Serial.println(sndStat);

//       // Check the status for sending
//       if (sndStat == CAN_OK)
//       {
//         // Serial.println(F("Message Sent Successfully!");
//         // ed_can_mcp_tx_buff_print();
//         dd_can_matrix_tx_set(txId, dd_can_tx_data, dd_can_msg_len);
//       }
//       else
//       {
//         Serial.println(F("Error Sending Message..."));
//       }
//     }
//   }
// }
// /*********************************************************************************************************
//   END FILE
// *********************************************************************************************************/
// char can_msg_string[256]; // Array to store serial string

// void ed_can_mcp_tx_buff_print()
// {
//   Serial.println(F("CAN_TX report:"));

//   sprintf(can_msg_string, "CAN_TX ID: 0x%.4X Data:", (uint16_t)txId);
//   Serial.print(can_msg_string);

//   for (int i = 0; i < dd_can_msg_len; i++)
//   {
//     sprintf(can_msg_string, " %.2X", dd_can_tx_data[i]);
//     Serial.print(can_msg_string);
//   }
//   Serial.println();
// }
// void ed_can_mcp_rx_buff_print()
// {
//   Serial.println(F("CAN_RX report:"));

//   sprintf(can_msg_string, "CAN_RX ID: 0x%.4X Data:", (uint16_t)txId);
//   Serial.print(can_msg_string);

//   for (int i = 0; i < dd_can_msg_len; i++)
//   {
//     sprintf(can_msg_string, " %.2X", dd_can_rx_data[i]);
//     Serial.print(can_msg_string);
//   }
//   Serial.println();
// }
// void ed_can_mcp_buff_print(uint16_t can_id, uint8_t *can_data)
// {
//   Serial.println(F("CAN_BUFF report:"));

//   sprintf(can_msg_string, "CAN_RX ID: 0x%.4X Data:", can_id);
//   Serial.print(can_msg_string);

//   for (int i = 0; i < dd_can_msg_len; i++)
//   {
//     sprintf(can_msg_string, " %.2X", can_data[i]);
//     Serial.print(can_msg_string);
//   }
//   Serial.println();
// }
