/*
 * eth_comm.h
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */

#ifndef INC_ETH_COMM_H_
#define INC_ETH_COMM_H_

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* parse packet function status */
enum{
	eth_packet_ok = 1,
	checksum_error,
	no_packet_found
}Eth_packet_status_t;

/* packet type for command packet */
enum{
	sensor_command  = 1,
	motor_command
}Comand_packet_type_t;

/* packet type for data packet */
enum{
	sensor_data_standart = 1,
	motor_data_standard
}Data_packet_type_t;


/* struct to hold packet variables */
typedef struct{

	uint8_t packet_type;
	uint8_t data_length;
	uint8_t data[30];
	uint16_t checksum;

}Eth_Packet;

/*************** QT -> H7 ******************/

/* function parse received ethernet packet */
uint8_t parse_eth_command(char * eth_data, uint16_t eth_data_length, Eth_Packet * eth_packet);

/*************** QT <- H7 ******************/

/* function to construct send data packet sensor standard */
void construct_eth_data_packet_sensor_standard(Eth_Packet * eth_packet); // tu trzeba dopisac pozostale dane wejsciowe

/* function to construct send data packet MOTOR STATE (speed od the motors) */
void construct_eth_data_packet_motor_state(Eth_Packet * eth_packet);

/* struct tcp packet to array to be send */
void convert_eth_packet_to_tcp_array(char * eth_packet_data, uint16_t * eth_data_len, Eth_Packet * eth_packet);

#endif /* INC_ETH_COMM_H_ */
