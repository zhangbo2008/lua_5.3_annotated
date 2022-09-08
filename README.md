https://github.com/hilarryxu/lua-5.3-annotated 原始地址.

 apt-get install libreadline-dev 
 make

我们跟着这个教程走.
https://blog.csdn.net/initphp/category_9293184.html




一些关键理解点我直接写这里面.


0. 关羽项目如何debug方法.
    首先我在src里面写了test.lua
    然后在.vscode/launch.json里面配置了运行参数.
    之后加断点运行即可.这样就进入了按照c语言来调试这个项目.就能看到代码运行的细节了.
    想debug什么lua打地面就修改test.lua即可.
1. 我们来理解 #define getstr(ts) \
    check_exp(sizeof((ts)->extra), cast(char *, (ts)) + sizeof(UTString)) 这份代码.
    首先添加lua代码结合lua.c里面让他编译之后直接调试lua代码. 
    启动编译之后控制台输入代码.然后断点在lua.c里面main函数即可.
    首先理解一下整个流程:
    lua.c:416行加断点. lua:314行会进入读取一行命令.
    luaS_newlstr这个代码.进入lstring:192就会发现.字符串写入的位置就是这个getstr的位置.
    原来是这样.数据就是放在他的struct结构体后面紧跟数据即可.不用定义什么struct啥的!!!!!!!这样做确实非常节省内存.是最优的方法!





总流程:
    首先教程先直接粗略读一遍做一个整体把握.然后跟着教程顺序研究源码.
    上来就是lua.h 研究里面头文件. 看个大概即可.不是c文件都看个大概.知道都有什么就完事.
    lmem.c   , lmem.h
    然后lstate.c 看个大概.
    lobject.h
    lstring.c
    ldo.c   lapi.c 可以先看看字符串, table的实现.这些数据结构比较简单.
    ltable.c
    代码的核心是虚拟机.
        这部分要看lua设计与实现.pdf因为内容很多,博客讲的更不细.
        debug点在lcode.c:293即可. test.lua里面写一个最简单的local a=1然后debug.

        再参考这个https://blog.csdn.net/liutianshx2012/article/details/77394832
        先调用pmain做一些预处理.然后研究handle_script代码即可.
        parser里面需要一直参考lopcodes.h 里面的操作表.





## Lua源码阅读顺序

### 1. **lmathlib.c, lstrlib.c:**
>get familiar with the external C API. Don't bother with the pattern matcher though. Just the easy functions.

### 2. **lapi.c:**
>Check how the API is implemented internally. Only skim this to get a feeling for the code. Cross-reference to *lua.h* and *luaconf.h* as needed.

### 3. **lobject.h:**
>tagged values and object representation. skim through this first. you'll want to keep a window with this file open all the time.

### 4. **lstate.h:**
>state objects. ditto.

### 5. **lopcodes.h:**
>bytecode instruction format and opcode definitions. easy.

### 6. **lvm.c:**
>scroll down to luaV_execute, the main interpreter loop. see how all of the instructions are implemented. skip the details for now. reread later.

### 7. **ldo.c:**
>calls, stacks, exceptions, coroutines. tough read.

### 8. **lstring.c:**
>string interning. cute, huh?

### 9. **ltable.c:**
>hash tables and arrays. tricky code.

### 10. **ltm.c:**
>metamethod handling, reread all of *lvm.c* now.

### 11. **lapi.c**

### 12. **ldebug.c:**
>surprise waiting for you. abstract interpretation is used to find object names for tracebacks. does bytecode verification, too.

### 13. **lparser.c, lcode.c:**
>recursive descent parser, targetting a register-based VM. start from chunk() and work your way through. read the expression parser and the code generator parts last.

### 14. **lgc.c:**
>incremental garbage collector. take your time.

---
Read all the other files as you see references to them. Don't let your stack get too deep though.

"# lua5-annotated" 
"# lua_5.3_annotated" 
