/*
 * gupik_rov_M4.c
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */


#include "gupik_rov_M4.h"



/**************************************/

/* function to create frtos api tasks on M4 */
void create_gupik_rov_M4_frtos_api_init(){

	// create imu sensor task
	xTaskCreate(vTaskIMUSensor, "TaskIMUSensor", 1000, NULL, 2, NULL);

}

/**************************************/


/* gupik rov frtos api tasks on M4 */

void vTaskIMUSensor(void * argument){


	for(;;){

		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
	vTaskDelete(NULL);
}
