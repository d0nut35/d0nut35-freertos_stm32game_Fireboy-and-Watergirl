#include "driver_timer.h"
#include "tim.h"
#include "bsp_system.h"
#include "queue.h"


/*传感器中断回调声明 */
extern void RotaryEncoder_IRQ_Callback(void);
extern void MPU6050_Callback(void);



/**********************************************************************
 * 函数名称： HAL_GPIO_EXTI_Callback
 * 功能描述： 外部中断的中断回调函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
    {
        case GPIO_PIN_15:
		{
			/*MPU6050中断处理函数 */
			MPU6050_Callback();
			break;
        }
		
        case GPIO_PIN_4:
		{
			/*旋转编码器中断处理函数 */
			RotaryEncoder_IRQ_Callback();
			break;
        }
		
		default:
        {
            break;
        }
    }


}
