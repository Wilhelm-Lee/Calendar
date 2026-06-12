#!/bin/bash
# 日历事件管理器构建脚本

set -e  # 遇到错误时退出

echo "=== 构建日历事件管理器 ==="

# 检查是否已安装CMake
if ! command -v cmake &> /dev/null; then
    echo "错误: 未找到CMake，请先安装CMake"
    echo "Ubuntu/Debian: sudo apt-get install cmake"
    echo "macOS: brew install cmake"
    echo "Windows: 从官网下载安装 https://cmake.org/download/"
    exit 1
fi

# 创建构建目录
if [ -d "build" ]; then
    echo "清理旧的构建目录..."
    rm -rf build
fi

echo "创建构建目录..."
mkdir -p build
cd build

# 配置项目
echo "配置CMake..."
cmake ..

# 构建项目
echo "构建项目..."
cmake --build .

# 检查是否构建成功
if [ -f "bin/Calendar" ]; then
    echo "✅ 构建成功！"
    echo "可执行文件位置: $(pwd)/bin/Calendar"
    
    echo -e "\n=== 测试程序 ==="
    echo "1. 显示帮助信息:"
    ./bin/Calendar help
    
    echo -e "\n2. 显示版本信息:"
    ./bin/Calendar version
    
    echo -e "\n=== 安装到系统（可选）==="
    read -p "是否安装到系统？(y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        sudo cmake --install .
        echo "✅ 安装完成！您现在可以在终端中使用 'Calendar' 命令"
    fi
    
    echo -e "\n=== 运行示例 ==="
    echo "要查看使用示例，请运行:"
    echo "cd .. && ./examples.sh"
else
    echo "❌ 构建失败！"
    exit 1
fi

cd ..

echo -e "\n=== 快速开始 ==="
echo "要运行程序:"
echo "cd build && ./bin/Calendar help"
echo ""
echo "或者添加到PATH后直接运行:"
echo "Calendar help"