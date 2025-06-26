#ifndef ED_RELAY_TERM_H
#define ED_RELAY_TERM_H

// Include any necessary libraries or headers
#include "ecu_config.h"

// Define any constants or macros

// Declare any function prototypes

// Function to report the state of the relays
void ed_relay_report();
// Function to display help for relay commands
void ed_relay_cmd_help();
// Function to handle commands related to relays
void ed_relay_term_cmd(char cmd);

#endif // ED_RELAY_TERM_H
