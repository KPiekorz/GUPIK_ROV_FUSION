/*
 * gupik_rov_M7.c
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */


#include "gupik_rov_M7.h"

// debug uart msg
extern char uart3_msg[300];

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

	// create eth motor control task
	xTaskCreate(vTaskMotorControl, "vTaskMotorControl", 1000, NULL, 2, NULL);


}
/**********************************************/

/* gupik rov frtos api tasks implementation */

void vTaskEthReceiveCommand(void * argument){


	for(;;){



	}
	vTaskDelete(NULL);
}

void vTaskEthSendData(void * argument){

	Eth_Packet eth_send_data_packet;

	for(;;){

		// wait for data receive from eth data queue which receive only Eth_packet struct data to send
		xQueueReceive(send_eth_data_queue, &eth_send_data_packet, portMAX_DELAY);

		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

		sprintf(uart3_msg, "Speed data: %d\n\r", eth_send_data_packet.data[0]);
		HAL_UART_Transmit(&huart3,(uint8_t*) uart3_msg, strlen(uart3_msg), HAL_MAX_DELAY);


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









