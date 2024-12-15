# 学生信息管理系统

数据结构大作业(1),一个基于C语言的学生信息管理系统(命令行)，支持成绩管理、数据可视化和批量处理功能。

## 功能特点

- 学生信息的增删改查
- 成绩统计与分析
- 数据可视化（成绩分布直方图）
- 批量数据处理
- 文件导入导出
- 堆排序实现的成绩排名

## 项目结构

```
student-management-system/
├── src/
│   ├── main.cpp              # 主程序入口
│   ├── function.cpp          # 核心功能实现
│   ├── function.h            # 函数声明和结构体定义
│   ├── heap_sort.cpp         # 堆排序实现
│   └── heap_sort.h           # 堆排序相关声明
├── plot_py/
│   ├── plot_histogram.py     # 直方图绘制脚本
│   └── xlsx2csv.py           # Excel转CSV工具
|   └── generate_data.py       # 生成多达10000的模拟测试数据(可以更改参数,生成任意大小的数据量)
├── data/
│   └── student_scores.csv    # 示例数据文件
├── README.md
└── LICENSE
```

## 数据结构

### 学生信息结构体
```cpp
typedef struct Student {
    char department[50];    // 系别
    char grade[10];         // 年级
    char class_name[20];    // 班级
    char id[20];           // 学号
    char name[50];         // 姓名
    char gender[10];       // 性别
    char birth_date[20];   // 出生年月日
    char major[50];        // 专业
    char education[20];    // 培养层次
    int years;             // 学制
    char campus[20];       // 校区
    int required_score;    // 必修成绩
    int elective_score;    // 选修成绩
    int second_score;      // 二课成绩
    int innovation_score;  // 创新创业成绩
    int total_score;       // 总成绩
    struct Student *next;  // 链表指针
} Student;
```

## 算法实现

### 1. 堆排序 (HeapSort)
- 时间复杂度：O(nlogn)
- 空间复杂度：O(n)
- 用途：对学生成绩进行排序
- 实现文件：heap_sort.cpp

### 2. 链表操作
- 查找：O(n)
- 插入：O(1)
- 删除：O(1)
- 实现文件：function.cpp

### 3. 文件操作
- CSV文件读写
- 数据持久化存储
- 实现文件：function.cpp

## 环境要求

> 使用前请确保已经激活了电脑对应的python环境,否则无法使用数据可视化功能

- C++编译器（支持C++11或更高版本）
- Python 3.x（用于数据可视化）
- Python包依赖：
  - matplotlib
  - pandas
  - numpy

## 编译与运行

### 编译

Windows:
```bash
g++ -fexec-charset=GB2312 main.cpp function.cpp heap_sort.cpp -o student_management
```

Linux/MacOS:
```bash
g++ main.cpp function.cpp heap_sort.cpp -o student_management
```

### 运行
```bash
student_management.exe
```

## 使用说明

1. 首次运行时，系统会要求输入数据文件名
2. 主菜单提供以下功能：
   - 显示所有学生信息
   - 按学号查找学生
   - 按姓名查找学生
   - 修改学生成绩
   - 保存到文件
   - 从CSV导入学生信息
   - 绘制成绩分布直方图
   - 批量修改学生信息
   - 堆排序并显示成绩排名
   - 退出系统

## 数据文件格式

CSV文件格式要求：
```
系别,年级,班级,学号,姓名,性别,出生年月日,专业,培养层次,学制,校区,必修成绩,选修成绩,二课成绩,创新创业成绩
```

## 贡献指南

1. Fork 本仓库
2. 创建新的分支
3. 提交更改
4. 发起 Pull Request

## 许可证

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。


