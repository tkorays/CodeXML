# CodeXML
CodeXML是一个有意思的库,它可以使用定义好的XML文件完成编程语言所能完成的功能.

## 特点
* 除了库定义的基本数据类型,使用者可以使用XML定义数据类型.
* 除了库定义的基本执行函数,使用者可以利用XML自定义函数,自定义函数是基本操作的有机集合.
* 支持插件机制,可以自动加载动态链接库,扩展功能.

## 基本原理
### 处理过程
标签:<proc></proc>

处理流程里面调用系统函数和自定义函数.

proc可以嵌套:

```
<proc>
    ...
    <proc>
        ...
    </proc>
</proc>
```

### 自定义函数
自定义函数结构如下:

```
<cmds>
    <cmd name="cmd_name">
        <fopen handle="@handle" file="@file"/>
    </cmd>
</cmds>
```

定义好后可以通过`<cmd_name handle="hd" file="test.txt"/>`
方式调用.函数定义中属性值以`@`开头用于参数传递,表示使用调用标签
所传入的参数值.


## 系统函数
这里只介绍一些,其它的参考代码.
### fopen
属性:

* handle,必需,句柄名称
* file,必需,文件路径
* mode,可选,打开模式

### fwrite
属性:
* handle,必需,句柄名称
* data,和memory二选一,写入字符串
* newline,可选,值为true或false,是否换行
* memory,和data二选一,将内存数据写入

### fclose
属性:
* handle,必需,句柄名称

.....
.....

### setmem
属性:
* memory,必需,内存名称
* offset,可选,默认为0,内存偏移字节
* byte,必需,写入的byte十进制值


## 关于
Author: tkorays

Email: tkorays@hotmail.com
