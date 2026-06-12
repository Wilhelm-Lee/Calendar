# Calendar - 命令行日历事件管理器

一个用C语言编写的简单而强大的命令行日历工具，用于管理个人日程和事件。

## 功能特性
- ✅ 创建、删除、查询日历事件
- ✅ 按时间戳管理事件
- ✅ 实时事件状态跟踪（进行中、已过期）
- ✅ 错误处理和内存管理
- ✅ 支持命令行参数
- ✅ 简洁的终端输出

## 安装和构建

### 依赖
- CMake 3.31.6 或更高版本
- C99 兼容的编译器 (GCC, Clang)
- 标准C库

### 构建步骤
```bash
# 1. 创建构建目录
mkdir build
cd build

# 2. 配置并构建
cmake ..
cmake --build .

# 3. 安装到系统（可选）
sudo cmake --install .
```

## 使用方法

### 基本命令格式
```bash
./Calendar [命令] [参数...]
```

### 可用命令

#### 添加事件
```bash
./Calendar add "事件标题" "描述文本" <开始时间戳> <持续时间(秒)>
```

示例：
```bash
./Calendar add "团队会议" "每周项目进度讨论" 1680000000 3600
```

#### 删除事件
```bash
./Calendar del "事件标题"
```

示例：
```bash
./Calendar del "团队会议"
```

#### 查询事件剩余时间
```bash
./Calendar remain "事件标题"
```

示例：
```bash
./Calendar remain "团队会议"
```

#### 列出所有事件
```bash
./Calendar list
```

#### 列出当前正在进行的事件
```bash
./Calendar ongoing
```

#### 列出今天的事件
```bash
./Calendar today
```

#### 列出指定日期的事件
```bash
./Calendar date <年份> <月份> <日期>
```

示例：
```bash
./Calendar date 2026 2 14
```

### 事件数据格式
- **标题**: 最多50个字符
- **描述**: 最多512个字符  
- **时间戳**: Unix时间戳（自1970年1月1日以来的秒数）
- **持续时间**: 以秒为单位

## 示例

### 创建购物事件
```bash
./Calendar add "购物" "去超市买日用品" $(date +%s) 7200
```

### 查询事件状态
```bash
# 列出所有事件
./Calendar list

# 查看购物还剩多少时间
./Calendar remain "购物"
```

### 检查当前活动事件
```bash
./Calendar ongoing
```

## 项目结构
```
Calendar/
├── CMakeLists.txt     # CMake构建配置
├── README.md         # 项目文档
├── LICENSE           # GPL-2.0许可证
├── include/          # 头文件目录
│   ├── struct.h      # 数据结构定义
│   ├── event.h       # 事件管理接口
│   ├── write_event.h # 事件持久化接口
│   └── err_handle.h  # 错误处理接口
└── src/              # 源代码目录
    ├── main.c        # 主程序入口
    ├── event.c       # 事件管理实现
    ├── err_handle.c  # 错误处理实现
    └── write_event.c # 事件持久化实现
```

## 开发

### 代码风格
- 使用标准C99语法
- 遵循清晰的命名约定
- 包含详细的错误处理
- 内存管理严谨

### 文件说明
- `struct.h`: 定义事件、时间结构和枚举类型
- `event.h/.c`: 事件创建、删除和链表管理
- `write_event.h/.c`: 事件数据的文件存储和读取
- `err_handle.h/.c`: 统一错误处理机制
- `main.c`: 命令行界面和主逻辑

## 许可证
本项目采用 GNU General Public License v2.0 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 贡献
欢迎提交Pull Request或报告问题。

## 故障排除
- **内存不足**: 系统资源不足
- **事件不存在**: 尝试操作不存在的标题
- **时间格式错误**: 使用无效的时间戳参数

## 联系方式
如有问题，请通过GitHub Issues提交。
```

现在让我修复write_event.c文件，实现事件的持久化存储：



<｜DSML｜function_calls>
<｜DSML｜invoke name="env_command_fileControl">
<｜DSML｜parameter name="id" string="true">ef2crj34Rp