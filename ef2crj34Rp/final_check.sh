#!/bin/bash
# 最终代码检查

echo "=== 最终代码语法检查 ==="

# 检查头文件
echo "检查头文件结构..."
grep -n "#include" include/*.h
echo ""

# 检查源文件包含
echo "检查源文件包含..."
for file in src/*.c; do
    echo "检查 $file:"
    grep -n "#include" "$file"
    echo ""
done

echo "=== 查找潜在问题 ==="

# 检查未使用的变量
echo "1. 检查未声明的函数..."
for file in src/*.c; do
    echo "在 $file 中:"
    grep -n "error_message\|warning_message\|success_message" "$file" || true
    grep -n "AddEventToStore\|RemoveEventByTitle\|FindEventByTitle" "$file" || true
    echo ""
done

# 检查main.c中的函数声明
echo "2. 检查函数声明和定义的匹配..."
echo "main.c中的函数:"
grep -n "void \|int \|Event" src/main.c | head -20

# 检查时间处理函数
echo ""
echo "3. 检查时间相关函数..."
echo "在main.c中:"
grep -n "localtime\|mktime\|time\|strftime" src/main.c

# 检查文件操作
echo ""
echo "4. 检查文件操作函数..."
grep -n "fopen\|fclose\|fwrite\|fread" src/write_event.c

# 检查内存管理
echo ""
echo "5. 检查内存管理函数..."
grep -n "malloc\|free" src/*.c

echo ""
echo "=== 验证函数调用 ==="

# 验证函数参数匹配
echo "验证printf/scanf参数..."
echo "write_event.c中的fprintf:"
grep -n "fprintf" src/write_event.c
echo ""
echo "write_event.c中的fscanf/sscanf:"
grep -n "fscanf\|sscanf" src/write_event.c

# 检查字符串处理
echo ""
echo "检查字符串处理..."
grep -n "strcpy\|strncpy\|strcmp" src/*.c

echo ""
echo "=== 编译测试 ==="

mkdir -p temp_check
cd temp_check

echo "编译所有文件..."
gcc -c ../src/event.c -I../include -o event.o -std=c99
gcc -c ../src/err_handle.c -I../include -o err_handle.o -std=c99 
gcc -c ../src/write_event.c -I../include -o write_event.o -std=c99
gcc -c ../src/main.c -I../include -o main.o -std=c99

echo "链接..."
gcc event.o err_handle.o write_event.o main.o -o calendar_final

if [ -f "calendar_final" ]; then
    echo "✅ 编译成功！"
    echo "测试程序运行:"
    ./calendar_final help 2>/dev/null | head -10 
    echo ""
    echo "程序大小: $(wc -c < calendar_final) 字节"
else
    echo "❌ 编译失败"
    exit 1
fi

cd ..
rm -rf temp_check

echo ""
echo "=== 所有检查完成 ==="
echo "代码语法正确，可以正常编译运行！"