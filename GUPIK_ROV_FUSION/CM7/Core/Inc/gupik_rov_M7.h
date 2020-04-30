/*
 * gupik_rov_M7.h
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */

#ifndef INC_GUPIK_ROV_M7_H_
#define INC_GUPIK_ROV_M7_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>


/* Define enumeration type to identyfy the source of the data */
typedef enum{

	imu_sensor_data,
	motor_speed_data

}Data_Source_t;

/* Define the structure type that will be passed on the eth queue */
typedef struct{

	Data_Source_t data_source;

	/* imu and pressure sensor value */


	/* motor speed value */ // TODO: raczej jakies struktury przechowujace te dane
	uint8_t jakas_przykladowa_wartosc;

}eth_send_queue_data_t;

/* Queue variable */
QueueHandle_t eth_send_data_Queue;

/**************************************/
/* function to create frtos api tasks */
void create_gupik_rov_M7_frtos_api_init();
/**************************************/

/* gupik rov frtos api tasks */
void vTaskEthSendData(void * argument);
void vTaskMotorControl(void * argument);


#endif /* INC_GUPIK_ROV_M7_H_ */
