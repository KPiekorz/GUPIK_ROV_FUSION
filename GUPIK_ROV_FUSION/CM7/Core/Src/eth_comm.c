/*
 * eth_comm.c
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */


#include "eth_comm.h"

extern char uart3_send[200];


/* function parse received ethernet packet */
uint8_t parse_eth_command(char * eth_data, uint16_t eth_data_length, Eth_Packet * eth_packet){

	uint16_t index = 0;
	uint16_t calc_checksum = 0;

	// find start new packet in ethernet data
	while((index < eth_data_length) && (*(eth_data+index) != 's')) index++; calc_checksum += (uint8_t)'s';

	if(index >= eth_data_length) return no_packet_found;

	index++; if( *(eth_data+index) != 'n' ) return no_packet_found; calc_checksum += (uint8_t)'n';
	index++; if( *(eth_data+index) != 'p' ) return no_packet_found; calc_checksum += (uint8_t)'p';

	//read command number and save in packet type variable
	index++; eth_packet->packet_type = (uint8_t) *(eth_data+index); calc_checksum += (uint8_t)eth_packet->packet_type;

	//read number of parameters
	index++; eth_packet->data_length = (uint8_t) *(eth_data+index); calc_checksum += (uint8_t)eth_packet->data_length;

	//read parameters value
	int i;
	for(i=0; i<eth_packet->data_length; i++){
		index++;
		eth_packet->data[i] =  (uint8_t) *(eth_data+index); calc_checksum += (uint8_t)eth_packet->data_length;
	}

	// calcualte receive checksum
	uint16_t buf = 0;
	index++; buf = (uint8_t) *(eth_data+index); buf = buf << 8;
	index++; buf |= (uint8_t) *(eth_data+index);
	eth_packet->checksum = buf;

	if(calc_checksum != eth_packet->checksum) return checksum_error;

//	sprintf(uart3_send, "Packet type: %d\n\rData length: %d\r\nPara: %d\r\nChecksum: %d\n\rCalc_checksum: %d\n\r", eth_packet->pacet_type, eth_packet->data_length, eth_packet->data[0], eth_packet->checksum, calc_checksum);
//	HAL_UART_Transmit(&huart3, (uint8_t*) uart3_send, strlen(uart3_send), HAL_MAX_DELAY);

	return eth_packet_ok;
}


/* function to construct send data packet SENSOR STANDARD */
void construct_eth_data_packet_sensor_standard(Eth_Packet * eth_packet){

	// to sa generalnie funckje do konsruowania eth struct pakietów z danych prosto z czujnikow

}


/* function to construct send data packet MOTOR STATE (speed od the motors) */
void construct_eth_data_packet_motor_state(Eth_Packet * eth_packet){ // TODO: dodac reszte zmiennych wejsciowych




}


/* convert struct tcp packet to array to be send */
void convert_eth_packet_to_tcp_array(char * eth_packet_data, uint16_t * eth_data_len,Eth_Packet * eth_packet){

	uint16_t index = 0;
	uint16_t checksum = 0;
	(*eth_data_len) = (char)3 + 1 + 1 + eth_packet->data_length + 2 + 1;

	*(eth_packet_data+index) = 's'; index++; checksum += (int)'s';
	*(eth_packet_data+index) = 'n';	index++; checksum += (int)'n';
	*(eth_packet_data+index) = 'p'; index++; checksum += (int)'p';
	*(eth_packet_data+index) = (char)eth_packet->packet_type; index++; checksum += eth_packet->packet_type;  // packet type
	*(eth_packet_data+index) = (char)eth_packet->data_length; index++; checksum += eth_packet->data_length; // packet lenght

	int i;
	for(i = 0; i<eth_packet->data_length; i++){
		*(eth_packet_data+index) = (char)eth_packet->data[i]; index++; checksum += eth_packet->data[i]; // add data from eth packet
	}

	/* Calculate checksum of the packet */
	*(eth_packet_data+index) = (char)(checksum>>8); index++;
	*(eth_packet_data+index) = (char)(checksum&0xFF); index++;

	*(eth_packet_data+index) = '\0';

	sprintf(uart3_send, "Calc_checksum: %d \n\r", checksum);
	HAL_UART_Transmit(&huart3, (uint8_t*) uart3_send, strlen(uart3_send), HAL_MAX_DELAY);

}






