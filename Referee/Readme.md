# **SCUT-RobotLab: 2021年SRML_Referee实现维护**
该工程仅用于便利维护人之间的进度同步，代码功能经过适当完善、测试后会及时同步到SRML

## **维护人**
- **21-电控-谢凌梓；1357657340@qq.com**
- **21-电控-何政茂；**

## **等待完善的功能**
- [x] 21年新增数据包更新
- [x] 客户端绘制小陀螺、超级电容使能时的提示符号
- [x] 字符串绘制debug，目前能在2021客户端上绘制
- [ ] 浮点数、整数绘制debug，目前只能在2020客户端上绘制（待官方更新客户端）
- [x] UI准星、车界线的绘制
- [ ] 图传控制数据的解包函数接口（对应机器人图传发送端上有3pin线）
- [x] 添加英雄专用榴弹标尺及工程的矿物对准框
- [x] 添加英雄剩余可发弹丸数提示
- [ ] 【大改】优化drawing_pack为类成员，减少静态全局变量的使用
- [ ] 【大改】C++继承特性对整个类进行重构
- [ ] 【小改】优化底层速率控制逻辑并验证，压速到30Hz

## **版本变更记录**

### **v5.1.0(2021/03/23)**
- **添加了21年规则的新增数据包定义（小地图、图传控制数据、飞镖客户端数据、自定义控制数据）**
- **依据官方21年规则修改了已有数据包的部分数据类型及名称**
- **修复了蓝方车间通信时，数据段接收数组溢出的bug，但未测试**

### **v5.1.1(2021/03/26)**
- **更改了绘制简单图形的函数接口，利用指针及memcpy函数可以在一个数据包里绘制多个图形，实现带宽的充分利用：**
```
//定义绘图数据包，这里为两个图形数据包长度，即一次性绘制两个图形
static uint8_t data_pack[DRAWING_PACK*2] = {0};  

//数据包填充
memcpy(data_pack, (uint8_t*)arc_drawing(1, ADD_PICTURE, 1400,840,20,20,180,270,BLUE, spin_name1), DRAWING_PACK);
memcpy(&data_pack[DRAWING_PACK], (uint8_t*)arc_drawing(1, ADD_PICTURE, 1400,840,20,20,0,90,BLUE, spin_name2), DRAWING_PACK);

//数据包下发到底层发送函数，注意绘制ID为：Drawing_2_ID
pack_send_robotData(Drawing_2_ID, robot_client_ID.client, (uint8_t*)data_pack, DRAWING_PACK*2);
```
- **实现了小陀螺、超级电容静态标志符号**
- **实现了简单UI（一次数据包完成绘制）**
- **实现字符串、浮点数、整数在旧版客户端的绘制**

### **v5.1.2(2021/03/29)**
- **添加了电容电压百分比显示**

### **v5.2.0(2021/04/01)**
- **添加了弹仓开启标志**
- **暴露了上述标志、车界线、准心的位置接口，用户可根据操作手习惯自行调整标志位置及颜色**

### **v5.2.1(2021/04/04)**
- **添加Task Example**

### **v5.2.2(2021/04/08)**
- **添加了英雄用的榴弹UI标尺**

### **v5.3.0(2021/04/13)**
- **重新测试了UI绘制和车间通信的丢包率，优化底层的速率控制逻辑**
- **目前UI丢包率：66.7%**
- **目前车间通信丢包率：3.03%**

### **v5.3.1(2021/04/15)**
- **添加了工程专用的矿石对准框**