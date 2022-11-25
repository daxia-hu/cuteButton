
#include "button.h"

static List KeyList;
/**
 * @brief 按键链表初始化
 * @param list 按键链表
 */
void Key_ModInit(void)
{
	List_Init(&KeyList);
}
/**
 * @brief 按键初始化 
 * @param key 按键对象
 * @param key_list 需要加入的按键链表
 */
void Key_Init(Key *key,uint8_t id,det_func detfunc,handle_func handlefunc)
{
	key->state = KEY_IDLE;
	key->tick = 0;
	key->key_id = id;
	key->detFunc = detfunc;
	key->handleFunc = handlefunc;
	List_Insert((Node *)(&(key->node)),&KeyList);
}
/**
 * @brief 按键检测任务
 */
void Key_Task(uint16_t sysTick)
{
	Key *key;
	Node *n = (Node *)(key);
	for (n = KeyList.head.next; ; n = n->next)
	{
		switch (key->state)
		{
		case KEY_IDLE:
			if (TRUE == key->detFunc())
			{
				key->state = KEY_PRESS;
				key->tick = sysTick;
				key->handleFunc(key->key_id, KEY_PRESS);
			}
			break;
		case KEY_PRESS:
			if (FALSE == key->detFunc())
			{
				key->state = KEY_RELEASE;
			}
			break;
		case KEY_RELEASE:
			key->handleFunc(key->key_id, key->state);
			if(sysTick - key->tick >= KEY_LONGPRESS_TICK)
			{
				key->state = KEY_LONG_CLICK;
			}
			else
			{
				key->state = KEY_SHORT_CLICK;
			}
			break;
		case KEY_SHORT_CLICK:
			key->handleFunc(key->key_id, key->state);
			key->tick = 0;
			key->state = KEY_IDLE;
			break;
		case KEY_LONG_CLICK:
			key->handleFunc(key->key_id, key->state);
			key->tick = 0;
			key->state = KEY_IDLE;
			break;
		default:
			break;
		}
		if(n->next == &KeyList.tail)
		{
			break;
		}
	}
}


void key_ListFor()
{
	Key *k;
	for (k = KeyList.head.next; k->node.next != &KeyList.tail; k = ((Node *)k)->next)
	{
		printf("k %d\r\n", k->key_id);
	}
}