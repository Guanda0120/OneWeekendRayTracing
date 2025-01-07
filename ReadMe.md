## Github
[Github](https://github.com/RayTracing/raytracing.github.io/)

## Week1
[文档链接](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  

## Output a Image  
### Differencce Between `cout` and `clog`  

区别总结
    用途不同：std::cout 用于普通输出，std::clog 用于日志输出。
    输出目标不同：std::cout 默认输出到标准输出（stdout），std::clog 默认输出到标准错误（stderr），但在大多数实现中，它们都输出到标准输出（stdout）。
    使用场景不同：std::cout 适合用于显示程序的正常输出信息，而 std::clog 适合用于记录程序的运行日志和调试信息。

## `inline` keywords
通常情况下，声明inline函数有两种可能：  
一种是仅有头文件的类和对象，防止重复编译。
另一种是提示编译器这个是一个常用到的函数，可以直接把他放到调用的地方，防止调用开销。  
`inline` 必须放在头文件当中。

## Export a ppm Image
```Powershell
 .\build\one_weekend_ray_tracing.exe | set-content image.ppm -encoding  String
```

## Constructor
```c++
class MyClass {
public:
    MyClass(SomeType obj) : obj_(obj) {}
};

class MyClass {
public:
    MyClass(SomeType& obj) : obj_(obj) {}
};
```

两者的主要差别
| 特性             | SomeType& obj               | SomeType obj               |
|------------------|-----------------------------|----------------------------|
| 是否拷贝对象     | 不拷贝，直接引用传入对象    | 会拷贝传入对象             |
| 成员变量类型     | 引用（SomeType&）           | 独立对象（SomeType）       |
| 性能开销         | 性能高，没有拷贝            | 性能较低，需要拷贝传入对象 |
| 生命周期要求     | 需要确保传入对象的生命周期比类实例长 | 不依赖传入对象的生命周期   |
| 修改传入对象     | 会影响原始对象              | 不会影响原始对象           |

## Static Library and Dynamic Library

在编译完成之后，静态库的链接是包含于可执行文件当中的，而动态库是链接到的。