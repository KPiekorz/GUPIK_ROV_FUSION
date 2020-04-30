/*
 * gupik_rov_M7.c
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */


#include "gupik_rov_M7.h"

extern uart3_msg[300];

/**********************************************/

/* function to create frtos api tasks */
void create_gupik_rov_M7_frtos_api_init(){




	// create eth send data task
	xTaskCreate(vTaskEthSendData, "TaskEthSendData", 1000, NULL, 2, NULL);

	// create eth motor control task
	xTaskCreate(vTaskMotorControl, "vTaskMotorControl", 1000, NULL, 2, NULL);


}
/**********************************************/

/* gupik rov frtos api tasks implementation */

void vTaskEthSendData(void * argument){


	for(;;){

		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
	vTaskDelete(NULL);
}



void vTaskMotorControl(void * argument){


	for(;;){

		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		vTaskDelay(pdMS_TO_TICKS(2000));

	}
	vTaskDelete(NULL);
}
