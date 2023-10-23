#include "stm32f10x.h"

/*LiteOS h file*/
#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"

/*bsp file*/
#include "led.h"

UINT32 Task1_Handle;

static UINT32 Creat_Test_Task(void);
static void test_task(void);

int main(void)
{
	UINT32 ret = LOS_OK;
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	//uart_init(115200);
 	LED_Init();
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	
	ret = LOS_KernelInit();
	if(ret != LOS_OK)
	{
		printf("creat task fail");
		return LOS_NOK;
	}
	ret = Creat_Test_Task();
	if(ret != LOS_OK)
	{
		printf("task creat fail!\n");
		return LOS_NOK;
	}
	LOS_Start();
}

static UINT32 Creat_Test_Task()
{
	UINT32 ret = LOS_OK;
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;
	task_init_param.pcName = "test_task";
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)test_task;
	task_init_param.uwStackSize = 0x1000;
	
	ret = LOS_TaskCreate(&Task1_Handle,&task_init_param);
	return ret;
}

static void test_task(void)
{
	while(1)
	{
		if (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5) == 0)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		else
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		LOS_TaskDelay(1000);		
	}
}