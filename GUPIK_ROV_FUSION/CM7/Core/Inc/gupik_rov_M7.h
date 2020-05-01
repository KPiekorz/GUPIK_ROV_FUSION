/*
 * gupik_rov_M7.h
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */

#ifndef INC_GUPIK_ROV_M7_H_
#define INC_GUPIK_ROV_M7_H_

// frtos include
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

// standard library include
#include <stdio.h>
#include <string.h>
#include "usart.h"

// eth communication include
#include "eth_comm.h" // my include eth file



/**************************************/
/* function to create frtos api tasks on M7 */
void create_gupik_rov_M7_frtos_api_init();
/**************************************/

/* gupik rov frtos api tasks on M7 */

// task to eth communication
void vTaskEthReceiveCommand(void * argument); // task to control eth connection, receive command
void vTaskEthSendData(void * argument); // task to send eth data (motor speed, imu value, press etc.)

// task to motor control
void vTaskMotorControl(void * argument);


#endif /* INC_GUPIK_ROV_M7_H_ */
