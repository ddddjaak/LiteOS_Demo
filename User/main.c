#include "stm32f10x.h"

/*LiteOS h file*/
#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"
#include "target_config.h"

/*bsp file*/
#include "led.h"
#include "delay.h"
#include "usart.h"
/*board config file*/


#if SYSTEM_SUPPORT_OS
UINT32 Task1_Handle;

static UINT32 Creat_Task(void);
static UINT32 Creat_LED_Task(void);
static void led_task(void);

int main(void)
{
	//UINT8 *pucAddr;
	UINT32 ret = LOS_OK;
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	uart_init(115200);
	delay_init();
 	LED_Init();
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	
	//pucAddr = (UINT8 *)0;
	//*pucAddr = 0;
	
	ret = LOS_KernelInit();
	if(ret != LOS_OK)
	{
		printf("creat task fail");
		return LOS_NOK;
	}
	ret = Creat_Task();
	if(ret != LOS_OK)
	{
		printf("task creat fail!\n");
		return LOS_NOK;
	}
	LOS_Start();
}
#else

#endif

static UINT32 Creat_Task(void)
{
	UINT32 ret = LOS_OK;
	
	ret = Creat_LED_Task();
	if(ret != LOS_OK)
	{
		printf("creat led task fail\n");
		return LOS_NOK;
	}
	return ret;
}	

static UINT32 Creat_LED_Task()
{
	UINT32 ret = LOS_OK;
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;
	task_init_param.pcName = "led_task";
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)led_task;
	task_init_param.uwStackSize = 0x1000;
	
	ret = LOS_TaskCreate(&Task1_Handle,&task_init_param);
	return ret;
}

static void led_task(void)
{
	while(1)
	{
		if (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5) == 0)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			printf("high gpiob pin 5\n");
		}
		else
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			printf("low gpiob pin 5\n");
		}
		//delay_ms(1000);
		LOS_TaskDelay(1000);		
	}
}