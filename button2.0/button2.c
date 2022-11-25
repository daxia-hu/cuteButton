#include "button2.h"
/**
 * @brief 按键模块初始化
 * @param butMod 按键模块对象
 * @param butNum 按键总个数
 * @param butList 按键列表的指针
 * @param eventHandle 按键模块的事件处理函数
 */
void Mod_ButtonInit(Mod_Button *butMod, uint8_t butNum, Button **butList, func_ButStateChangeHandle eventHandle)
{
    butMod->ButtonNum = butNum;
    butMod->ButtonList = butList;
    butMod->func_EventHandle = eventHandle;
}
/**
 * @brief 按键检测任务
 * @param butMod 按键模块对象
 * @param Systick 需要传入检测任务的时间参数
 */
void Mod_ButtonTask(Mod_Button *butMod, uint32_t Systick)
{
    Button *but;
    uint8_t index;
    for (index = 0; index < butMod->ButtonNum; ++index)
    {
        but = butMod->ButtonList[index];
        switch (but->state)
        {
        case BUTTON_STATE_IDLE:
            if (but->func_ButtonState())
            {
                but->tick = Systick;
                but->state = BUTTON_STATE_PRESS;
            }
            break;
        case BUTTON_STATE_PRESS:
            if (!but->func_ButtonState())
            {
                but->state = BUTTON_STATE_RELEASE;
            }
            break;
        case BUTTON_STATE_RELEASE:
            if (Systick - but->tick >= BUTTON_LONGCLICK_TIMEOUT)
            {
                but->state = BUTTON_STATE_LONG_CLICK;
                but->tick = Systick;
            }
            else
            {
                but->state = BUTTON_STATE_SHORT_CLICK;
                but->tick = Systick;
            }
            break;
        case BUTTON_STATE_SHORT_CLICK:
            butMod->func_EventHandle(index, but->state);
            but->state = BUTTON_STATE_IDLE;
            break;
        case BUTTON_STATE_LONG_CLICK:
            butMod->func_EventHandle(index, but->state);
            but->state = BUTTON_STATE_IDLE;
            break;
        default:
            break;
        };
    }
}