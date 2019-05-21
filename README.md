# BallGame
本项目是一个C++弹球游戏——纪念第一次C++大作业（用心趁热度，用脚写代码）
# 项目描述
此游戏本质上是一个平台弹球游戏，通过C++在控制台实现。基本功能可以实现，但是依然存在较大问题。

----
# 存在的问题
* 与障碍物的判定算法不够简洁优美
* 整体四不像（既不是面向对象，也不是面向过程）
* 当两段音频同时播放时，前一个音频播放进程会被中断
* 游戏体验过差（硬伤）
.......

----
# 待实现功能
* 真正可视化
* 判断算法优化
* 计分系统
.....

----
# 游玩指南
大家玩耍的时候，可以点开ball/release/ball.exe
## 操作方法
**记得将输入法调节为英文输入法**

**记得将输入法调节为英文输入法**

**记得将输入法调节为英文输入法**

> w键和s键：控制指针移动，进行选定要操作的功能；选定之后，按enter键进入。

> a键和d键：控制CXK移动

> q键：上一关

> e键：下一关

> o键：退出游戏

> p键：暂停游戏三秒钟，显示操作指南

## 自定义功能（**更改前务必看下面的更改指南**）
* ball/release中的1.txt、2.txt分别对应：第一关和第二关的障碍物分布。txt文件中每一行第一个数值对应障碍物的横坐标，第二个数值对应障碍物的纵坐标。大家可以自行更改里面的数值

* ball/release中的music0.wav、music1.wav、music2.wav分别对应：球碰到人的音频、球碰到障碍物的音频、球碰到边界的音频。

### 更改指南
* 音频数据修改要求：音频目前只支持.wav文件，而且音频长度需要超过1秒；**不能改变文件命名方式**。推荐在线音频剪辑工具：<https://mp3cut.net/cn/>

* txt修改总体要求：每一行只能输入两个数值，输入完第一个数值后**空格一次**，再输入第二数值，然后**换行**；txt文件最后必须为：-1 -1；并且不能有换行。**不能改变文件命名方式**

>横坐标：值的范围为1到53；且同一行相邻障碍物的横坐标需要加6，如：txt文件中第一行数值为：16 11，如果要做到障碍物相邻，那么相邻的障碍物数值为：22 11；以此类推。

>纵坐标：值的范围为1到14。
