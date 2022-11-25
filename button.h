#ifndef BUTTON_H
#define BUTTON_H
#include "list.h"

#define FALSE 0
#define flase FALSE
#define TRUE 1
#define true TRUE
/**
 * 按键类
 */
typedef enum
{
	KEY_IDLE,		  //空闲
	KEY_PRESS,		  //按下
	KEY_RELEASE,	  //释放
	KEY_SHORT_CLICK,  //短按
	KEY_LONG_CLICK,	  //长按
	KEY_DOUBLE_CLICK, //双击
	KEY_LONG_HOLD,	  //长按保持
} KEY_STATE;
#define KEY_LONGPRESS_TICK 200
/* 按键检测函数指针 */
typedef uint8_t (*det_func)(void);
/* 按键状态变化函数指针 */
typedef void (*handle_func)(uint8_t key_id, uint8_t key_state);
typedef struct Key_t
{
	Node node;					   //节点
	uint8_t key_id;				   //按键ID
	uint8_t state;				   //按键状态
	det_func detFunc;		   	   //按键检测函数
	handle_func handleFunc; 	   //状态变化回调函数
	uint16_t tick;				   //按键tick
} Key;
/**
 * @brief 按键链表初始化
 * @param list 按键链表
 */
void Key_ModInit(void);
/**
 * @brief 按键初始化 
 * @param key 按键对象
 * @param key_list 需要加入的按键链表
 */
void Key_Init(Key *key,uint8_t id,det_func detfunc,handle_func handlefunc);
/**
 * @brief 按键检测任务
 */
void Key_Task(uint16_t tick);
#endif