#ifndef DD_CAN_MATRIX_H_
#define DD_CAN_MATRIX_H_
#include <stdint.h>

#include "ecu_config.h"

#ifndef TX_CAN_ID_LIST
#define SRV_CAN_MATRIX_ID_NR_OF 0
#define TX_CAN_ID_LIST {}
#endif

#ifndef RX_CAN_ID_LIST
#define SRV_CAN_MATRIX_ID_NR_OF 0
#define RX_CAN_ID_LIST {}
#endif

// #define SRV_CAN_MATRIX_SIZE (SRV_CAN_MATRIX_ID_NR_OF + 1) // + 1 for a dummy msg
// #define SRV_CAN_MATRIX_SIZE (SRV_CAN_MATRIX_ID_NR_OF + 1) // + 1 for a dummy msg

#define CAN_MESSAGE_LEN 8
#define RX_MSG 0
#define TX_MSG 1
#define CAN_MESSAGE_RECURENT 0x20
#define CAN_MESSAGE_SINGLE 0x10

#define CAN_MESSAGE_INVALID 0x00
#define CAN_MESSAGE_VALID 0x01
#define CAN_MESSAGE_UPDATED 0x03
#define CAN_MESSAGE_NO_UPDATE 0x02

typedef struct can_message_t
{
    uint32_t id;
    uint32_t tx_counter;
    uint32_t rx_counter;
    uint8_t direction;
    uint8_t tx_msg[CAN_MESSAGE_LEN];
    uint8_t rx_msg[CAN_MESSAGE_LEN];
    uint8_t recurent;
    uint8_t updated;
    uint8_t readed;
    uint8_t overrided;

} can_message_t;


void dd_can_matrix_setup();


void dd_can_matrix_rx_set(uint32_t CanID, uint8_t *buff, uint16_t len );
void dd_can_matrix_tx_set(uint32_t CanID, uint8_t *buff, uint16_t len );
uint8_t dd_can_matrix_tx_get(uint32_t CanID, uint8_t *buff, uint16_t len );

can_message_t * dd_can_matrix_get_msg_ref(uint32_t matrix_id);
// can_message_t * dd_can_matrix_get_msg_ref(uint16_t matrix_id);

uint32_t* ed_can_mcp_get_tx_can_list_ref();
uint32_t* ed_can_mcp_get_rx_can_list_ref();

void dd_can_matrix_report();
// void dd_can_rx_matrix_print();

#endif