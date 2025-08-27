---
comments: true
---

## 写在前面

工作室电机请一定要先恢复出厂设置。如果使用串口，请检查跳线帽是否安装正确，因为有一部分是我切换为 CAN 模式的。

张大头固件 V5.1.5 版本串口通讯有严重 Bug，如果工作室的电机版本为 V5.1.5，请务必升级到 V5.1.6 或更高版本。

升级教程以及更多资料请加入张大头 QQ 群 761548421

## 一些容易踩坑的点

电机通讯 CAN 和串口必须等待电机发出的应答后才能发送下一条指令或者等待响应命令，否则会出现电机不响应的情况。

在位置模式下，必须等待电机到位后才能发送下一条位置命令，否则会出现打断电机执行当前命令。

如果启用多机同步，必须在所有电机命令发送完毕后，发送多机同步命令，否则电机不会运动。

绝对位置是以电机上电时的位置或使用命令清零后的位置为零点的，所以电机的运动方向需要在电机上设置，命令的正反转将失效。

相对位置的零点是以电机当前的位置为零点。

不要使用电机的位置模式来控制电机底盘，因为电机内部的 PID 会使得四个电机运动不一致而导致底盘跑偏。

## 电机的 CAN 控制代码

在张大头 QQ 群里的 F4 例程有 HAL 库版本的例程，但是在例程中没有提供接收消息的代码，所以我这里补充一下。

[Emm_V5.c](%E4%BB%A3%E7%A0%81/Emm_V5.c)
[Emm_V5.h](%E4%BB%A3%E7%A0%81/Emm_V5.h)

`SUCCESSRECEIVE`和`FAILRECEIVE`是在main.h中定义的宏

打开CAN接收中断

![中断.png](%E5%9B%BE%E7%89%87/%E4%B8%AD%E6%96%AD.png)

CAN 接收回调函数在接收到消息后会调用 `Emm_V5_Pos_Status_ReadCalback` 函数，数据存储在 `Emm_V5_Pos_Status` 结构体中

```c
// CAN 接收回调函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
  /* Get RX message */
  if (HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &RxHeader, CANRxBuff) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }

  Emm_V5_Pos_Status_ReadCalback(&Emm_V5_Pos_Status,CANRxBuff);
	can.rxFrameFlag = true;

}
```

`can.rxFrameFlag` 为判断是否接收到消息的标志位。

```c
//可以直接放在 can_SendCmd 函数里面
while(can.rxFrameFlag == false); can.rxFrameFlag = false;//在每次发送命令后等待接收消息

```

`CAN.h` 中的CAN 结构体

```c
typedef struct {
  __IO CAN_RxHeaderTypeDef CAN_RxMsg;
  __IO uint8_t rxData[32];

  __IO CAN_TxHeaderTypeDef CAN_TxMsg;
  __IO uint8_t txData[32];

  __IO bool rxFrameFlag;
}CAN_t;

extern __IO CAN_t can;
```

---
