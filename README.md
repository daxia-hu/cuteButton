# cuteButton
按键检测组件

[模块设计说明](https://hudaxia.top/2022/11/17/%E7%BB%84%E4%BB%B6-%E6%8C%89%E9%94%AE%E6%A3%80%E6%B5%8B%E5%AE%9E%E7%8E%B0/)

## v1版本
- 版本采用链表实现，需要了解简单的链表知识
- 应用流程：
    1. 调用Key_ModInit对按键调度器进行初始化
    2. 调用Key_Init添加按键
    3. 轮询调用Key_Task函数对按键进行扫描

## v2版本
- 采用指针数组实现，比较简单高效
- 应用流程：
    1. 调用Mod_ButtonInit初始化按键调度器初始化
    2. 轮询执行Mod_ButtonTask对扫描按键