//
// Created by 延年易廋 on 2025/8/20.
//
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void debug_file_access(const string& filename) {
    cout << "=== 文件访问调试信息 ===" << endl;

    // 1. 显示当前工作目录
    cout << "1. 当前工作目录: " << fs::current_path() << endl;

    // 2. 检查文件是否存在
    cout << "2. 文件 '" << filename << "' 存在: "
         << (fs::exists(filename) ? "是" : "否") << endl;

    // 3. 如果是相对路径，显示绝对路径
    if (fs::exists(filename)) {
        cout << "3. 绝对路径: " << fs::absolute(filename) << endl;
    }

    // 4. 检查文件权限
    if (fs::exists(filename)) {
        auto perms = fs::status(filename).permissions();
        cout << "4. 文件权限: ";
        cout << ((perms & fs::perms::owner_read) != fs::perms::none ? "可读" : "不可读");
        cout << endl;
    }

    // 5. 尝试打开文件
    ifstream file(filename);
    cout << "5. 文件打开: " << (file.is_open() ? "成功" : "失败") << endl;

    if (file.is_open()) {
        file.close();
    }

    // 6. 列出当前目录所有文件
    cout << "6. 当前目录文件列表:" << endl;
    try {
        for (const auto& entry : fs::directory_iterator(".")) {
            cout << "   " << entry.path().filename() << endl;
        }
    } catch (const exception& e) {
        cerr << "   无法列出目录: " << e.what() << endl;
    }

    cout << "==========================" << endl;
}

// 使用示例
int main() {
    string filename = "speech.csv";
    debug_file_access(filename);

    // 如果文件存在但打不开，尝试其他方法
    if (fs::exists(filename)) {
        // 方法1：使用绝对路径
        string absolute_path = fs::absolute(filename).string();
        cout << "尝试使用绝对路径: " << absolute_path << endl;

        ifstream file(absolute_path);
        if (file.is_open()) {
            cout << "使用绝对路径成功！" << endl;
            // 读取文件内容...
            file.close();
        } else {
            cerr << "即使使用绝对路径也无法打开" << endl;
        }
    }

    return 0;
}