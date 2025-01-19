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

## 循环引用问题可以通过前向声明规避

## 核心渲染逻辑
```C++
color camera::cal_pixel_color_(const hittable_list& entities, const ray& r, int depth) const {
  if (depth<0){
    return color(0,0,0);
  }
  hit_record record;
  color c;
  if (entities.hit(r, interval(0, 1000), record)){
    // Get the Normalize Vector 
    /*
    vec3 sphere_normal = record.normal;
    c = color(0.5*(sphere_normal.x()+1), 0.5*(sphere_normal.y()+1), 0.5*(sphere_normal.z()+1));
    */
    color attenuation;
    ray scattered;
    /*
    vec3 sphere_normal = record.normal;
    vec3 rand_direc = random_unit_vector_hemisphere(sphere_normal);
    vec3 lambert_direc = rand_direc+sphere_normal;
    lambert_direc.normalize_vec();
    ray rand_ray = ray(record.p, lambert_direc);
    */
    // This recurancy Means
    /**
     * 
     * 
     *         o
     *          \  ________________
     *           \ |              |
     *  0.125sky  \| 0.5sky       |
     *         \  /|              |
     * _________\/_|______________|______________
     *         0.25sky 
     */ 
    if (record.mat->scatter(r, record.p, record.normal, attenuation, scattered)){
      return attenuation*this->cal_pixel_color_(entities, scattered, depth-1);
    }
    // color c = this->cal_pixel_color_(entities, rand_ray, depth-1);
    // c.garmmar_correction(this->gammar_coe_);    
    return color(0,0,0);
  } else {
    // Not Hit just the blue gradient
    // Here is Environment Light
    double a = 0.5*(r.direction().y() + 1.0);    
    c = color (
      (1.0-a)+0.5*a,
      (1.0-a)+0.7*a,
      (1.0-a)+1.0*a
    );
  }
  return c;
}
```

当产生未碰撞情况的时候，直接放回天空的颜色，当有碰撞的时候是一路叠色，直到最大搜索深度。

## CMake 中的PUBLIC PRIVATE关键字
在 CMake 中，PUBLIC 和 PRIVATE 是用于定义目标属性的传播范围的关键字，主要用于 target_include_directories 和 target_link_libraries 指令中。它们控制头文件路径、编译选项和链接库等信息是否传播到依赖该目标的其他目标。

PRIVATE
表示属性仅适用于当前目标，不会传播到依赖它的其他目标。

适用场景
当前目标需要某些头文件或库，但这些依赖不需要被其他目标使用。
使用示例
```cmake

target_include_directories(MyLib PRIVATE include/mylib)
target_link_libraries(MyLib PRIVATE SomeLibrary)
```
头文件路径：include/mylib 只对 MyLib 可见。
链接库：SomeLibrary 只在构建 MyLib 时链接，依赖 MyLib 的其他目标不会自动链接 SomeLibrary。
PUBLIC
表示属性适用于当前目标和依赖该目标的其他目标。

适用场景
当前目标的头文件、库或编译选项也需要被其依赖的目标使用。
使用示例
```cmake

target_include_directories(MyLib PUBLIC include/mylib)
target_link_libraries(MyLib PUBLIC SomeLibrary)
```
头文件路径：include/mylib 对 MyLib 和依赖 MyLib 的其他目标都可见。
链接库：SomeLibrary 会被 MyLib 和依赖 MyLib 的目标链接。
