/*
 * gupik_rov_M7.c
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */


#include "gupik_rov_M7.h"

// debug uart msg
extern char uart3_msg[300];

/* ETH struct communication information */
struct netconn *newconn;


/* Queue variable */
QueueHandle_t send_eth_data_queue;

QueueHandle_t motor_command_queue;

QueueHandle_t intercore_command_queue;

/**********************************************/

/* function to create frtos api tasks */
void create_gupik_rov_M7_frtos_api_init(){

	/* create queue to transmit data to ethernet send task */
	send_eth_data_queue = xQueueCreate( 5, sizeof(Eth_Packet));


	// create eth send data task
	xTaskCreate(vTaskEthSendData, "TaskEthSendData", 1000, NULL, 2, NULL);

	// create eth receive command task
	xTaskCreate(vTaskEthReceiveCommand, "TaskEthReceiveCommand", 1000, NULL, 2, NULL);

	// create eth motor control task
	xTaskCreate(vTaskMotorControl, "vTaskMotorControl", 1000, NULL, 2, NULL);


}
/**********************************************/

/* gupik rov frtos api tasks implementation */

void vTaskEthReceiveCommand(void * argument){

	/* tcp connection variable */
	struct netconn *conn;
	err_t err, accept_err;
	struct netbuf *buf;
	void *data;
	uint16_t len;
	err_t recv_err;

	/* tcp packet struct */
	Eth_Packet tcp_command;

	for(;;){

		/* Infinite loop */
		/* Create a new connection identifier. */
		conn = netconn_new(NETCONN_TCP);

		if (conn != NULL) {

			/* Bind connection to well known port number. */
			err = netconn_bind(conn, NULL, 4242);

			if (err == ERR_OK) {

				/* Tell connection to go into listening mode. */
				netconn_listen(conn);

				while (1) {

					/* Grab new connection. */
					accept_err = netconn_accept(conn, &newconn);

					/* Process the new connection. */
					if (accept_err == ERR_OK) {

						while ((recv_err = netconn_recv(newconn, &buf)) == ERR_OK) {

							do {

								/* receive command from control station */
								netbuf_data(buf, &data, &len);

								/* parse received command that control ROV */
								if(parse_eth_command((char *) data, len, &tcp_command) == eth_packet_ok){

									// debug
									sprintf(uart3_msg, "Received command number: %d\n\r", tcp_command.packet_type);
									HAL_UART_Transmit(&huart3,(uint8_t*) uart3_msg, strlen(uart3_msg), HAL_MAX_DELAY);

									// wyslanie komend do odpowiednich taskow, na podstawie numeru komendy i parametrow danej komendy
									// wszystko dzieje sie w switch case



								}



							} while (netbuf_next(buf) >= 0);

							netbuf_delete(buf);

						}

						/* Close connection and discard connection identifier. */
						netconn_close(newconn);
						netconn_delete(newconn);
					}
				}

			} else {
				netconn_delete(newconn);
			}

		}

	}
	vTaskDelete(NULL);
}

void vTaskEthSendData(void * argument){

	Eth_Packet eth_send_data_packet;

	// status of netconn send
	err_t tcp_send_data_status;

	// data to be send
	char eth_packet_data[200];
	uint16_t eth_packet_data_len = 0;


	for(;;){

		// wait for data receive from eth data queue which receive only Eth_packet struct data to send
		xQueueReceive(send_eth_data_queue, &eth_send_data_packet, portMAX_DELAY);

		/* convert eth packet */
		convert_eth_packet_to_tcp_array(eth_packet_data, &eth_packet_data_len, &eth_send_data_packet);

		/* send data packet with netconn_write function */
		tcp_send_data_status = netconn_write(newconn, eth_packet_data, eth_packet_data_len, NETCONN_COPY);


		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);


	}
	vTaskDelete(NULL);
}



void vTaskMotorControl(void * argument){

	Eth_Packet motor_data_packet;


	for(;;){

		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		vTaskDelay(pdMS_TO_TICKS(2000));

		/*
		motor_data_packet.data[0] = 123;

		xQueueSendToBack(send_eth_data_queue, &motor_data_packet, 0);
		*/

		// kolejka do oczekiwania na komende, ktora jest w standardowej formie struktury pakietowej


		// przerobienie struktury na normalna forma komendy


		// wywolanie funkcja z biblioteki do sterowania silnikami



	}
	vTaskDelete(NULL);
}









