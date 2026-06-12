#!/bin/bash
# 编译检查脚本

echo "=== 编译检查 ==="

# 创建临时目录
mkdir -p temp_compile
cd temp_compile

echo "1. 检查头文件的语法..."
cat > test_headers.c << 'EOF'
#include "../include/struct.h"
#include "../include/event.h"
#include "../include/write_event.h"
#include "../include/err_handle.h"

int main() {
    return 0;
}
EOF

gcc -c test_headers.c -I../include -o test_headers.o 2>&1
if [ $? -eq 0 ]; then
    echo "✅ 头文件语法正确"
else
    echo "❌ 头文件有语法错误"
    exit 1
fi

echo -e "\n2. 检查每个源文件的语法..."

# 检查 event.c
echo "检查 event.c..."
gcc -c ../src/event.c -I../include -o event.o -std=c99 2>&1
if [ $? -eq 0 ]; then
    echo "✅ event.c 语法正确"
else
    echo "❌ event.c 有语法错误"
    exit 1
fi

# 检查 err_handle.c
echo "检查 err_handle.c..."
gcc -c ../src/err_handle.c -I../include -o err_handle.o -std=c99 2>&1
if [ $? -eq 0 ]; then
    echo "✅ err_handle.c 语法正确"
else
    echo "❌ err_handle.c 有语法错误"
    exit 1
fi

# 检查 write_event.c
echo "检查 write_event.c..."
gcc -c ../src/write_event.c -I../include -o write_event.o -std=c99 2>&1
if [ $? -eq 0 ]; then
    echo "✅ write_event.c 语法正确"
else
    echo "❌ write_event.c 有语法错误"
    exit 1
fi

# 检查 main.c
echo "检查 main.c..."
gcc -c ../src/main.c -I../include -o main.o -std=c99 2>&1
if [ $? -eq 0 ]; then
    echo "✅ main.c 语法正确"
else
    echo "❌ main.c 有语法错误"
    exit 1
fi

echo -e "\n3. 尝试链接成可执行文件..."
gcc event.o err_handle.o write_event.o main.o -o calendar_test 2>&1
if [ $? -eq 0 ]; then
    echo "✅ 链接成功，编译检查通过！"
    echo "测试程序大小: $(wc -c < calendar_test) 字节"
else
    echo "❌ 链接失败"
    exit 1
fi

cd ..
rm -rf temp_compile

echo -e "\n=== 所有语法检查通过 ==="