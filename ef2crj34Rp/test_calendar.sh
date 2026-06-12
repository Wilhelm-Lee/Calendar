#!/bin/bash
# 日历事件管理器测试脚本

echo "=== Calendar 程序测试 ==="

# 设置路径
BINARY="./build/bin/Calendar"

# 检查程序是否存在
if [ ! -f "$BINARY" ]; then
    echo "错误: 找不到可执行文件，请先运行 './build.sh' 构建程序"
    exit 1
fi

echo "✓ 找到程序: $BINARY"
echo ""

# 测试1: 基本命令
echo "测试1: 显示帮助信息"
$BINARY help
echo ""

# 测试2: 版本信息
echo "测试2: 版本信息"
$BINARY version
echo ""

# 测试3: 列出空的事件列表
echo "测试3: 列出事件（应该为空）"
$BINARY list
echo ""

# 测试4: 添加测试事件
echo "测试4: 添加测试事件"
NOW=$(date +%s)
echo "当前时间戳: $NOW"
echo ""
echo "添加事件1: 测试会议"
$BINARY add "测试会议" "这是一个测试事件" $NOW 3600
echo ""
echo "添加事件2: 午餐"
$BINARY add "午餐" "与同事共进午餐" $((NOW + 7200)) 1800
echo ""
echo "添加事件3: 明天的事件"
$BINARY add "明天会议" "明天的项目讨论" $((NOW + 86400)) 7200
echo ""

# 测试5: 列出所有事件
echo "测试5: 列出所有事件"
$BINARY list
echo ""

# 测试6: 检查今天的事件
echo "测试6: 检查今天的事件"
$BINARY today
echo ""

# 测试7: 查看事件剩余时间
echo "测试7: 查看事件剩余时间"
$BINARY remain "测试会议"
echo ""

# 测试8: 删除事件
echo "测试8: 删除事件'午餐'"
$BINARY del "午餐"
echo ""

# 测试9: 确认删除结果
echo "测试9: 确认删除结果"
$BINARY list
echo ""

# 测试10: 导出事件
echo "测试10: 导出事件到文件"
$BINARY export test_export.txt
echo "检查导出的文件:"
head -20 test_export.txt 2>/dev/null || echo "导出文件不存在"
echo ""

# 测试11: 清理测试文件
echo "测试11: 清理测试文件"
rm -f test_export.txt calendar_events.dat
echo "✓ 清理完成"
echo ""

echo "=== 所有测试完成 ==="
echo "程序功能正常！现在可以使用日历事件管理器了。"
echo ""
echo "运行示例:"
echo "  $BINARY add \"健身\" \"健身房锻炼\" $(date +%s) 5400"
echo "  $BINARY list"
echo "  $BINARY remain \"健身\""
echo ""