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


/**********************************************/

/* function to create frtos api tasks */
void create_gupik_rov_M7_frtos_api_init(){

	/* create queue to transmit data to ethernet send task */
	send_eth_data_queue = xQueueCreate( 5, sizeof(eth_send_queue_data_t));


	// create eth send data task
	xTaskCreate(vTaskEthSendData, "TaskEthSendData", 1000, NULL, 2, NULL);

	// create eth motor control task
	xTaskCreate(vTaskMotorControl, "vTaskMotorControl", 1000, NULL, 2, NULL);


}
/**********************************************/

/* gupik rov frtos api tasks implementation */

void vTaskEthSendData(void * argument){

	eth_send_queue_data_t eth_send_data;

	for(;;){

		xQueueReceive(send_eth_data_queue, &eth_send_data, portMAX_DELAY);

		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

		switch (eth_send_data.data_source) {

			case imu_sensor_data:



				break;

			case motor_speed_data:

				sprintf(uart3_msg, "motor data to send\n\r");
				HAL_UART_Transmit(&huart3, (uint8_t*) uart3_msg, strlen(uart3_msg), HAL_MAX_DELAY);

				break;
		}

	}
	vTaskDelete(NULL);
}



void vTaskMotorControl(void * argument){

	eth_send_queue_data_t motor_data = {motor_speed_data, 12};

	for(;;){

		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		vTaskDelay(pdMS_TO_TICKS(2000));

		xQueueSendToBack(send_eth_data_queue, &motor_data, 0);


	}
	vTaskDelete(NULL);
}









