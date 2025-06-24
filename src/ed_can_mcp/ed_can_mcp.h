#ifndef ED_CAN_MCP_H_
#define ED_CAN_MCP_H_

#include "ecu_config.h"
#include "stdint.h"

#ifndef CAN0_INT 
#define CAN0_INT 2 // Set INT to pin 2
#endif

#ifndef CAN0_CS
#define CAN0_CS 10 // Set CS to pin 2
#endif

void ed_can_mcp_setup();
void ed_can_mcp_recv_loop();
void ed_can_mcp_send_loop();
void ed_can_mcp_tx_buff_print();
void ed_can_mcp_rx_buff_print();
void ed_can_mcp_buff_print(uint16_t can_id, uint8_t* can_data);

#endif