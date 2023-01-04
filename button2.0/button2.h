#ifndef BUTTON_2_H
#define BUTTON_2_H
#include "stdint.h"
/* 按键状态 */
typedef enum
{
    BUTTON_STATE_IDLE,
    BUTTON_STATE_RELEASE,
    BUTTON_STATE_HOLD,
    BUTTON_STATE_PRESS,
    BUTTON_STATE_SHORT_CLICK,
    BUTTON_STATE_LONG_CLICK,
}BUTTON_STATE_TYPE;
#define BUTTON_LONGHOLD_TIMEOUT 500
#define BUTTON_LONGCLICK_TIMEOUT 2000
/**
 * @brief 获取按键状态函数指针 
 * @return TRUE 按键被触发 FALSE 按键被释放
 */
typedef uint8_t (*func_GetButtonState)(void);
/* 按键类 */
typedef struct Button_T
{
    uint8_t ButtonId;                     //按键的ID信息
    uint8_t state;                        //按键当前状态
    uint32_t tick;                        //按键时间参数
    uint32_t hold_tick;                   //长按保持时间参数
    func_GetButtonState func_ButtonState; //获取按键状态的函数成员
} Button;
/* 按键模块的事件回调函数指针 */
typedef void (*func_ButStateChangeHandle)(uint8_t but_id, uint8_t state);
/* 按键模块类 */
typedef struct Mod_Button_t
{
    uint8_t ButtonNum;                          //按键个数
    Button **ButtonList;                        //按键列表的地址
    func_ButStateChangeHandle func_EventHandle; //按键模块的事件回调函数
} Mod_Button;
/**
 * @brief 按键模块初始化
 * @param butMod 按键模块对象
 * @param butNum 按键总个数
 * @param butList 按键列表的指针
 * @param eventHandle 按键模块的事件处理函数
 */
void Mod_ButtonInit(Mod_Button *butMod, uint8_t butNum, Button **butList, func_ButStateChangeHandle eventHandle);
/**
 * @brief 按键检测任务
 * @param butMod 按键模块对象
 * @param Systick 需要传入检测任务的时间参数
 */
void Mod_ButtonTask(Mod_Button *butMod, uint32_t Systick);
#endif