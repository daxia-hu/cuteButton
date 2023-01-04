#include "button2.h"
#include "stdio.h"
typedef enum
{
    BUT_1 = 0x01,
    BUT_2 = 0x02,
    BUT_3 = 0x04,
    BUT_BUTT,
}BUT_ID;
uint8_t func_GetBut1State(void)
{
    return 0;
}
Button but1 = 
{
    .ButtonId = BUT_1,
    .func_ButtonState = func_GetBut1State,
};

uint8_t func_GetBut2State(void)
{
    return 0;
}
Button but2 = 
{
    .ButtonId = BUT_2,
    .func_ButtonState = func_GetBut2State,
};
uint8_t func_GetBut3State(void)
{
    return 0;
}
Button but3 = 
{
    .ButtonId = BUT_3,
    .func_ButtonState = func_GetBut3State,
};
static void func_But1EventHandle(uint8_t state)
{
    switch (state)
    {
    case BUTTON_STATE_HOLD:
        break;
    case BUTTON_STATE_PRESS:
        break;
    case BUTTON_STATE_SHORT_CLICK:
        break;
    case BUTTON_STATE_LONG_CLICK:
        break;
    default:
        break;
    };
}
static void func_But2EventHandle(uint8_t state)
{

}
static void func_But3EventHandle(uint8_t state)
{

}
void ModBut_EventHandle(uint8_t but_id, uint8_t state)
{
    switch (but_id)
    {
    case BUT_1:
        func_But1EventHandle(state);
        break;
    case BUT_2:
        func_But2EventHandle(state);
        break;
    case BUT_3:
        func_But3EventHandle(state);
        break;
    default:
        break;
    };
}
Button * but_list[] = 
{
        &but1,
        &but2,
};
Mod_Button mod_but;
int main()
{
    uint32_t tick = 0;
    Mod_ButtonInit(&mod_but,BUT_BUTT,but_list,ModBut_EventHandle);
    while(1)
    {
        Mod_ButtonTask(&mod_but,++tick);
    }
}