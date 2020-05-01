/*
 * gupik_rov_M4.h
 *
 *  Created on: Apr 30, 2020
 *      Author: kpiek
 */

#ifndef INC_GUPIK_ROV_M4_H_
#define INC_GUPIK_ROV_M4_H_

// frtos include
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/**************************************/
/* function to create frtos api tasks on M4 */
void create_gupik_rov_M4_frtos_api_init();
/**************************************/

/* gupik rov frtos api tasks on M4 */

void vTaskIMUSensor(void * argument);

#endif /* INC_GUPIK_ROV_M4_H_ */
