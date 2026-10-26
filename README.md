# speech_contest

C++ 演讲比赛练习，菜单实现包含比赛模拟、查看历史成绩与清空记录，使用 CSV 保存比赛数据。

## 内容导航

- [menu.cpp](./menu.cpp)：比赛菜单与评分流程
- [menu.h](./menu.h)：选手数据结构与函数声明
- [speech.csv](./speech.csv)：成绩记录
- [main.cpp](./main.cpp)：当前默认构建入口
- [CMakeLists.txt](./CMakeLists.txt)：CMake 3.31 / C++20 配置

## 当前状态

当前 `main.cpp` 的 `main()` 为空；CMake 目标仅编译该文件，尚未接入 `menu.cpp`。因此默认构建不会显示比赛菜单。要继续完成项目，需要在入口调用菜单函数并将实现加入构建目标。

代码使用了 Windows 控制台命令，其他平台需要调整。清空菜单会修改成绩文件，试用前可备份 `speech.csv`。
