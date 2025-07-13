# Programming_Paradigms_Assignments
2024同济大学程序设计范式课程作业和五子棋期中作业

## 仓库组成

[第一次作业](https://github.com/ycc250303/Programming_Paradigms_Assignments/tree/main/Assignment_1)

[第二次作业](https://github.com/ycc250303/Programming_Paradigms_Assignments/tree/main/Assignment_2) 

[第三次作业](https://github.com/ycc250303/Programming_Paradigms_Assignments/tree/main/Assignment_3)

[第四次作业](https://github.com/ycc250303/Programming_Paradigms_Assignments/tree/main/Assignment_4)

[五子棋](https://github.com/ycc250303/Programming_Paradigms_Assignments/tree/main/gomoku)

```mermaid
flowchart TD
    A[用户程序调用系统调用]
      --> B[库函数设置参数并执行 ecall<br/>user/usys.S]
      --> C[CPU切换到内核模式，进入 usertrap]
      --> D[syscall 分发与参数获取]
      --> E[执行 sys_* 内核实现]
      --> F{是否返回数据?}
    F -- 是 --> G[copyout 复制数据到用户空间]
    F -- 否 --> H[直接设置返回值]
    G --> I[trap 返回，恢复用户态]
    H --> I
    I --> J[用户程序获得结果]
```
