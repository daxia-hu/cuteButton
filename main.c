#include "stdio.h"
#include "button.h"
typedef enum{
    KEY_ID_1 = 10,
    KEY_ID_2,
    KEY_ID_3,
}KEY_ID;

uint8_t key1_getState(void)
{
    return 1;
}
uint8_t key2_getState(void)
{
    return 0;
}
uint8_t key3_getState(void)
{
    return 0;
}
void key1_eventCb(uint8_t key_id,uint8_t key_state)
{
    printf("key1:%d\r\n",key_state);
}
void key2_eventCb(uint8_t key_id,uint8_t key_state)
{
    printf("key2:%d\r\n",key_state);
}
void key3_eventCb(uint8_t key_id,uint8_t key_state)
{
    printf("key3:%d\r\n",key_state);
}
int main()
{
    Key key1 = {0};
    Key key2 = {0};
    Key key3 = {0};
    uint16_t tick = 0;
    Key_ModInit();
    Key_Init(&key1,KEY_ID_1,key1_getState,key1_eventCb);
    Key_Init(&key2,KEY_ID_2,key2_getState,key2_eventCb);
    Key_Init(&key3,KEY_ID_3,key3_getState,key3_eventCb);
    key_ListFor();
    while(1)
    {
        tick++;
        Key_Task(tick);
    }
}
