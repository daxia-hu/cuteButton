#include "button2.h"

void Mod_ButtonInit(Mod_Button *butMod, uint8_t butNum, Button **butList, func_ButStateChangeHandle eventHandle)
{
    butMod->ButtonNum = butNum;
    butMod->ButtonList = butList;
    butMod->func_EventHandle = eventHandle;
}

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
            else if(but->tick > BUTTON_LONGHOLD_TIMEOUT)
            {
                but->state = BUTTON_STATE_HOLD;
                but->hold_tick = Systick;
            }
            break;
        case BUTTON_STATE_HOLD:
            if (!but->func_ButtonState())
            {
                but->state = BUTTON_STATE_RELEASE;
                break;
            }
            else if((Systick - but->hold_tick) > BUTTON_LONGCLICK_TIMEOUT)
            {
                but->hold_tick = Systick;
                butMod->func_EventHandle(index, BUTTON_STATE_HOLD);
            }
            break;
        case BUTTON_STATE_RELEASE:
            if (Systick - but->tick >= BUTTON_LONGCLICK_TIMEOUT)
            {
                butMod->func_EventHandle(index, BUTTON_STATE_LONG_CLICK);
                but->tick = Systick;
                but->state = BUTTON_STATE_IDLE;
            }
            else
            {
                butMod->func_EventHandle(index, BUTTON_STATE_SHORT_CLICK);
                but->tick = Systick;
                but->state = BUTTON_STATE_IDLE;
            }
            break;
        default:
            break;
        };
    }
}