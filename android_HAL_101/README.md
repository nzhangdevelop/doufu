本例的目标是展示如何实现最简单的HAL service。基于此可以加深对Camera HAL的理解。

HIDL: Hal Interface Discription Language，HIDL是用于指定HAL和HAL用户之间接口的接口定义语言。
HIDL是一种语言，有自己的语法规则。
interfaces.hal文件经编译后，会生成对应的.h和.cpp文件。

两种类型：
Passthrough，直通式。
Binderized，绑定式。（本例）

这个例子介绍Binderized HAL.

接口文件的位置：
hardware/interface/example/
一般我们还会按版本组织。

基本步骤：
1. 定义HIDL接口文件(.hal)。
2. 生成HAL相关文件。
3. 编写服务端代码。
4. 编写注册服务程序。
5. 编写测试代码。
6. 在真实环境测试。