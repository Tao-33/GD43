# 2025年CIMC中国智能制造挑战赛-工业嵌入式系统开发赛项

# Program：CIMC_GD32_LED_driver

## 程序简介
- 工程名称：GD32F470 LED驱动
- 实验平台: CIMC IHD V0.4
- MDK版本：5.25
CIMC_GD32_Template

## 板载资源

 - GD32F470VET6 MCU
 - LED * 4
 
## 功能简介

程序模板，可以用来拷贝建立工程
利用GD32F470VET6单片机实现LED点亮和闪烁功能。

## 实验操作
下载程序后复位开发板，四颗LED间隔1秒顺次点亮后熄灭，
随后LED1间隔0.5秒闪烁。

## 引脚分配


		LED1   <--->     PA4
		LED2   <--->     PA5
		LED3   <--->     PA6
		LED4   <--->     PA7


## 程序版本

- 程序版本：V0.1
- 发布日期：2025-03-22

## 联系我们

- Copyright   : CIMC中国智能制造挑战赛
- Author      ：Lingyu Meng
- Website     ：www.siemenscup-cimc.org.cn
- Phone       ：15801122380

## 声明

**严禁商业用途，仅供学习使用。 **


## 目录结构

├─01 Readme		工程项目说明
├─CMSIS			内核驱动文件：Cortex Microcontroller Software Interface Standard
├─Function		用户程序
├─HardWare		硬件驱动
│  └─LED		LED驱动
├─HeaderFiles	头文件集合
├─Library		库文件
│  ├─GD32F4xx_standard_peripheral
│  ├─GD32F4xx_usb_library
│  └─Third_Party
├─project		工程文件（含生成的连接文件）
├─Protocol		协议程序
├─Startup		启动文件
├─System		
└─User
