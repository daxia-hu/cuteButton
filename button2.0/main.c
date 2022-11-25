#include "button2.h"
#include "stdio.h"
typedef enum
{
    BUT_1 = 0x01,
    BUT_2 = 0x02,
    BUT_BUTT,
}BUT_ID;
uint8_t func_GetBut1State(void)
{
    return 0;
}
Button but1 = 
{
    .ButtonId = BUT_1,
    .state = BUTTON_STATE_RELEASE,
    .func_ButtonState = func_GetBut1State,
};

uint8_t func_GetBut2State(void)
{
    return 0;
}
Button but2 = 
{
    .ButtonId = BUT_2,
    .state = BUTTON_STATE_RELEASE,
    .func_ButtonState = func_GetBut2State,
};
void ModBut_EventHandle(uint8_t but_id, uint8_t state)
{
    printf("%d event %d\r\n",but_id,state);
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