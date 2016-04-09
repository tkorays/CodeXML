# CodeXML V2

自动内存管理
stack

一切都以句柄方式存在

1) 支持C语言动态库加载
<call lib="foo.bar" para=""/>
试图加载foo.dll foo.dylib fo.so ,并调用该模块中的bar函数.

handle (*call)(const char* para,size_t len);
参数获取函数

或者让程序自动扫描

 支持help输出导出函数



3) 支持调用系统脚本
<call script="abc.pl" bin="/usr/bin/perl"  para="" />



call
    lib -> call_lib(para)
    script -> call_script(bin = "", para)
    

4) 支持变量定义
变量类型,所有变量都是以字符串方式存在(句柄同样),程序自己自己转换.
作用域,每个闭合标签就是一个作用域.
GC,离开作用于后内存回收
命名需要规范
<val name="lib" value="aaaa"/>
usage:
<call lib="${abc}.bar" para="${para}"/>




<proc>
    < name="abc" para=""/>
</proc>