#!/bin/bash
# 日历事件管理器使用示例

echo "=== 日历事件管理器示例 ===\n"

# 1. 显示帮助信息
echo "1. 显示帮助信息:"
echo "./Calendar help"
echo ""

# 2. 显示版本信息
echo "2. 显示版本信息:"
echo "./Calendar version"
echo ""

# 3. 添加事件
echo "3. 添加事件:"
NOW=$(date +%s)
echo "./Calendar add \"团队会议\" \"每周项目进度讨论\" $NOW 3600"
echo "./Calendar add \"购物\" \"去超市买日用品\" \$((NOW + 7200)) 1800"
echo "./Calendar add \"锻炼\" \"健身房锻炼\" \$((NOW + 86400)) 5400"
echo ""

# 4. 列出所有事件
echo "4. 列出所有事件:"
echo "./Calendar list"
echo ""

# 5. 列出今天的事件
echo "5. 列出今天的事件:"
echo "./Calendar today"
echo ""

# 6. 列出指定日期的事件（示例：2026年2月14日）
echo "6. 列出指定日期的事件:"
echo "./Calendar date 2026 2 14"
echo ""

# 7. 列出当前进行中的事件
echo "7. 列出当前进行中的事件:"
echo "./Calendar ongoing"
echo ""

# 8. 查看事件剩余时间
echo "8. 查看事件剩余时间:"
echo "./Calendar remain \"团队会议\""
echo ""

# 9. 删除事件
echo "9. 删除事件:"
echo "./Calendar del \"购物\""
echo ""

# 10. 导出事件
echo "10. 导出事件:"
echo "./Calendar export my_events.txt"
echo ""

# 11. 导入事件
echo "11. 导入事件（恢复之前导出的）:"
echo "./Calendar import my_events.txt"
echo ""

# 12. 完整的工作流程示例
echo "=== 完整工作流程示例 ==="
echo "# 1. 查看帮助"
echo "./Calendar help"
echo ""
echo "# 2. 添加几个事件"
echo "NOW=\$(date +%s)"
echo "./Calendar add \"晨会\" \"每日晨间例会\" \$NOW 1800"
echo "./Calendar add \"午餐\" \"与同事共进午餐\" \$((NOW + 14400)) 3600"
echo "./Calendar add \"代码审查\" \"审查团队代码\" \$((NOW + 25200)) 7200"
echo ""
echo "# 3. 检查今天有什么事件"
echo "./Calendar today"
echo ""
echo "# 4. 查看当前进行中的事件"
echo "./Calendar ongoing"
echo ""
echo "# 5. 查看晨会的剩余时间"
echo "./Calendar remain \"晨会\""
echo ""
echo "# 6. 导出所有事件"
echo "./Calendar export backup.txt"
echo ""
echo "# 7. 删除午餐事件"
echo "./Calendar del \"午餐\""
echo ""
echo "# 8. 确认删除结果"
echo "./Calendar list"
echo ""

echo "=== 使用提示 ==="
echo "• 时间戳可以使用 date +%s 命令获取"
echo "• 事件标题不能重复"
echo "• 默认数据文件: calendar_events.dat"
echo "• 支持导出/导入文本格式便于备份"
echo "• 程序会自动保存数据，无需手动保存"

echo "\n要运行这些示例，请先构建程序:"
echo "mkdir build && cd build"
echo "cmake .. && cmake --build ."
echo "cd .."
echo "./build/bin/Calendar help"