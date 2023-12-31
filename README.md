# ps2x_smart_car

![(logo)](./logo.png)
===
![Pages](https://img.shields.io/badge/v-1.0.0-brightgreen.svg?style=flat-square)
===

> PWM（Pulse Width Modulation）调速是一种通过调节脉冲宽度的方式来控制电机或其他设备的转速或输出功率的技术。
通过调整PWM信号的占空比（高电平与低电平时间的比例），可以改变电机的平均电压或电流，从而控制电机的转速。<br>
根据手柄的摇杆或按钮状态来实现智能车的调速、前进、后退、转向、平移、斜行、旋转等操作。

## 支持轮型:
- [x] [普通轮子](https://en.wikipedia.org/wiki/Wheel)
- [x] [麦克纳姆轮](https://en.wikipedia.org/wiki/Mecanum_wheel)

## 硬件清单 
|名称|型号|备注|
| ------- | ------- | ------- |
|芯片|ATmega328P|[Document](https://www.microchip.com/en-us/product/atmega328p#document-table)|
|驱动|L298N x2|[Schemetics](./PS2X_smartCar/L298DriveModuleSchematicDiagram.pdf)|
|稳压|LM2596|DC-DC|
|电池|9.6V 8000MA|大田宫端头|
|电机|TT Motor|麦轮推荐使用闭环测速|
|车架|Acrylic||
|手柄|ps2||

## 驱动板
<details>
  <summary>右前电机</summary>

|定义|L298N-a|IO|
| ------- | ------- | ------- |
|io_0|IN1|A0|
|io_1|IN2|A1|
|pwm1|INA|D6|
</details>

<details>
  <summary>右后电机</summary>

|定义|L298N-a|IO|
| ------- | ------- | ------- |
|io_2|IN3|A2|
|io_3|IN4|A3|
|pwm2|INB|D10|
</details>

<details>
  <summary>左前电机</summary>

|定义|L298N-b|IO|
| ------- | ------- | ------- |
|io_4|IN1|D2|
|io_5|IN2|D3|
|pwm3|INA|D11|
</details>

<details>
  <summary>左后电机</summary>

|定义|L298N-b|IO|
| ------- | ------- | ------- |
|io_6|IN3|D4|
|io_7|IN4|D5|
|pwm4|INB|D9|
</details>



## 接收器
|接口|端口|线色|IO|
| ---: | ---: | ---: | ---: |
|Data|①|橙|D12|
|Command|②|黄|D8|
|Ground|④|褐|GND|
|Power|⑤|红|3V3|
|Attention|⑥|绿|D7|
|Clock|⑦|蓝|D13|

<img src="./ps2_wireless_receiver.jpeg" style="height: 200px; border-radius:15px">
<img src="./Arduino-Nano-Pinout.png" style="border-radius:15px">

## 实物展示
To view video, you can check out the link [here](https://www.bilibili.com/video/BV1ty4y1A7vB)
<img src="./ps2_controller&smart_car.jpg">

## 联系方式
* E-mail: niyongsheng@Outlook.com
* Weibo: [@Ni永胜](https://weibo.com/u/7317805089)
