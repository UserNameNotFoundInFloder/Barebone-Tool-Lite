#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <limits>
#include <cstdio>
#include <regex>
#include "DownLoad.h"

using namespace std;
using namespace std::filesystem;

void tool4() {
    string path;
    
    cout << "请输入要扫描的文件夹路径: ";
    cin.ignore();
    getline(cin, path);
    if (path.empty()) {
        cout << "路径不能为空！" << endl;
        return;
    }
    int pathSize = path.size();
    string pathTail(1, path.back());
    if (pathTail != "\\" && pathTail != "/") {
        path += "\\";
    }
    error_code ec;
    if (!exists(path, ec) || !is_directory(path, ec)) {
        cout << "路径无效或不是文件夹！" << endl;
        return;
    }

    char choice;
    cout << "是否显示全部文件(y/n,默认为n): ";
    cin >> choice;
    bool listFiles = (choice == 'y' || choice == 'Y');

    cout << "扫描中..." << endl;
    size_t fileCount = 0;
    uintmax_t totalSize = 0;
    size_t skippedDirs = 0;

    for (auto it = recursive_directory_iterator(path, ec); it != recursive_directory_iterator(); ) {
        if (ec) {
            it.disable_recursion_pending();
            skippedDirs++;
            continue;
        }

        const auto& entry = *it;
        if (is_regular_file(entry.status())) {
            auto size = file_size(entry);
            if (listFiles) {
                cout << entry.path().string() << "  (" << size << " 字节)" << endl;
            }
            fileCount++;
            totalSize += size;
        }

        it.increment(ec);
    }

    if (ec) {
        cout << "扫描过程中发生错误: " << ec.message() << endl;
    }

    cout << "\n扫描完成！共找到 " << fileCount << " 个文件，总大小 " << totalSize << " 字节" << endl;
    if (skippedDirs > 0) {
        cout << "跳过 " << skippedDirs << " 个目录" << endl;
    }
    if (!listFiles) {
        cout << "未显示文件列表。如需显示，请输入 y" << endl;
    }

    cout << "按回车键继续...";
    cin.ignore();
    cin.get();
}

int tool3() {
    string input;
    string PIDKill;
    string IMKill;
    string help = "欢迎使用杀进程工具\nPID: 通过进程ID杀进程\nIM: 通过进程名杀进程\nT: 杀进程树（含子进程）\n? 显示此帮助\nQUIT 退出";

    while (true) {
        cout << "\n请输入你的杀进程方法(可选(请大写) PID, IM, T, ?(查看本工具如何使用), QUIT): ";
        cin >> input;
        if (input == "PID") {
            system("tasklist");
            cout << "请输入要杀死的进程PID: ";
            cin >> PIDKill;
            string cmd = "taskkill /PID " + PIDKill + " /F";
            int ret = system(cmd.c_str());
            if (ret == 0)
                cout << "进程杀死成功！" << endl;
            else
                cout << "进程杀死失败: " << ret << endl;
        }
        else if (input == "IM") {
            cout << "请输入要杀死的进程名称(如test.exe): ";
            cin >> IMKill;
            string cmd = "taskkill /IM " + IMKill + " /F";
            int ret = system(cmd.c_str());
            if (ret == 0)
                cout << "进程杀死成功！" << endl;
            else
                cout << "进程杀死失败: " << ret << endl;
        }
        else if (input == "T") {
            cout << "请输入要杀死的进程方法(可选(请大写) PID, IM): ";
            cin >> input;
            if (input == "PID") {
                system("tasklist");
                cout << "请输入要杀死的进程PID: ";
                cin >> PIDKill;
                string cmd = "taskkill /PID " + PIDKill + " /T /F";
                int ret = system(cmd.c_str());
                if (ret == 0)
                    cout << "进程杀死成功！" << endl;
                else
                    cout << "进程杀死失败: " << ret << endl;
            }
            else if (input == "IM") {
                cout << "请输入要杀死的进程名称(如test.exe): ";
                cin >> IMKill;
                string cmd = "taskkill /IM " + IMKill + " /T /F";
                int ret = system(cmd.c_str());
                if (ret == 0)
                    cout << "进程杀死成功！" << endl;
                else
                    cout << "进程杀死失败: " << ret << endl;
            }
            else {
                cout << "无效的进程方法！" << endl;
            }
        }
        else if (input == "?") {
            cout << help << endl;
        }
        else if (input == "QUIT") {
            cout << "退出工具" << endl;
            break;
        }
        else {
            cout << "无效的输入！" << endl;
        }
    }
    return 0;
}

int tool1() {
    int minutes;
    cout << "请输入关机时间(分钟，例如90): ";
    cin >> minutes;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "输入无效，请输入一个有效的数字: ";
        cin >> minutes;
    }
    int seconds = minutes * 60;
    string command = "shutdown -s -t " + to_string(seconds);
    cout << "关机时间设置为 " << minutes << " 分钟" << endl;
    system(command.c_str());
    return 0;
}

int tool2() {
    string input;
    cout << "请输入取消关机的命令(O): ";
    cin >> input;
    if (input == "O" || input == "o") {
        system("shutdown -a");
        cout << "取消关机成功！" << endl;
    } else {
        cout << "未取消。" << endl;
    }
    return 0;
}

int tool7() {
    cout << "帮助信息: \n"
         << "1. 定时关机: 设置电脑在指定分钟后自动关机。\n"
         << "2. 取消关机: 取消已设置的定时关机。\n"
         << "3. 杀进程: 根据进程ID或映像名终止进程,可选择杀进程树。\n"
         << "4. 文件扫描器: 扫描指定文件夹及其子文件夹中的所有文件，并显示总数和大小。\n"
         << "5. 检测网址连接: 测试指定网址的网络连接情况，包括丢包率和平均延迟。\n"
         << "6. 下载: 下载一个URL的文件到本地，支持多线程下载。\n"
         << "7. 帮助: 显示此帮助信息。\n"
         << "8. 退出: 退出系统工具箱程序。\n\n";
    return 0;
}

void tool5use(int havePkg,float avg,int place){
    switch(havePkg){
        case 0:
            if (place == 0){
                if (avg <= 70) {
                    cout << "国内网络质量优秀" << endl;
                } else if (avg <= 85) {
                    cout << "国内网络质量良好" << endl;
                } else if (avg <= 90) {
                    cout << "国内网络质量一般" << endl;
                } else {
                    cout << "国内网络质量较差" << endl;
                }
            }else if (place == 1){
                if (avg <= 80) {
                    cout << "国外网络质量优秀" << endl;
                } else if (avg <= 95) {
                    cout << "国外网络质量良好" << endl;
                } else if (avg <= 105) {
                    cout << "国外网络质量一般" << endl;
                } else {
                    cout << "国外网络质量较差" << endl;
                }
            }break;
        case 1:
            if (place == 0){
                if (avg <= 50) {
                    cout << "国内网络质量优秀" << endl;
                } else if (avg <= 60) {
                    cout << "国内网络质量良好" << endl;
                } else if (avg <= 80) {
                    cout << "国内网络质量一般" << endl;
                } else {
                    cout << "国内网络质量较差" << endl;
                }
            }else if (place == 1){
                if (avg <= 65) {
                    cout << "国外网络质量优秀" << endl;
                } else if (avg <= 75) {
                    cout << "国外网络质量良好" << endl;
                } else if (avg <= 90) {
                    cout << "国外网络质量一般" << endl;
                } else {
                    cout << "国外网络质量较差" << endl;
                }
            }break;
        case 2:
            if (place == 0){
                if (avg <= 55) {
                    cout << "国内网络质量优秀" << endl;
                } else if (avg <= 65) {
                    cout << "国内网络质量良好" << endl;
                } else if (avg <= 80) {
                    cout << "国内网络质量一般" << endl;
                } else {
                    cout << "国内网络质量较差" << endl;
                }
            }else if (place == 1){
                if (avg <= 60) {
                    cout << "国外网络质量优秀" << endl;
                } else if (avg <= 72) {
                    cout << "国外网络质量良好" << endl;
                } else if (avg <= 85) {
                    cout << "国外网络质量一般" << endl;
                } else {
                    cout << "国外网络质量较差" << endl;
                }
            }break;
        case 3:
            if (place == 0){
                if (avg <= 50) {
                    cout << "国内网络质量优秀" << endl;
                } else if (avg <= 60) {
                    cout << "国内网络质量良好" << endl;
                } else if (avg <= 75) {
                    cout << "国内网络质量一般" << endl;
                } else {
                    cout << "国内网络质量较差" << endl;
                }
            }else if (place == 1){
                if (avg <= 55) {
                    cout << "国外网络质量优秀" << endl;
                } else if (avg <= 65) {
                    cout << "国外网络质量良好" << endl;
                } else if (avg <= 80) {
                    cout << "国外网络质量一般" << endl;
                } else {
                    cout << "国外网络质量较差" << endl;
                }
            }break;
        case 4:
            if (place == 0){
                if (avg <= 45) {
                    cout << "国内网络质量优秀" << endl;
                } else if (avg <= 55) {
                    cout << "国内网络质量良好" << endl;
                } else if (avg <= 70) {
                    cout << "国内网络质量一般" << endl;
                } else {
                    cout << "国内网络质量较差" << endl;
                }
            }else if (place == 1){
                if (avg <= 38) {
                    cout << "国外网络质量优秀" << endl;
                } else if (avg <= 48) {
                    cout << "国外网络质量良好" << endl;
                } else if (avg <= 62) {
                    cout << "国外网络质量一般" << endl;
                } else {
                    cout << "国外网络质量较差" << endl;
                }
            }break;
        default:
            cerr << "无法判断网络质量" << endl;
            break;
    }
    return;
}

void tool5() {
    string region;
    cout << "请选择测试区域(国内/国外): ";
    cin >> region;
    if (region != "国内" && region != "国外") {
        cout << "输入无效，请输入'国内'或'国外'" << endl;
        return;
    }
    string url;
    cout << "请输入要测试的域名或IP地址: ";
    cin >> url;

    cout << "测试结果: " << endl;

    string cmd = "ping -n 4 " + url;
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        cout << "ping 执行失败" << endl;
        return;
    }

    string output;
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr)
        output += buf;
    _pclose(pipe);

    if (output.empty()) {
        cout << "ping 命令无输出，请检查网络连接或域名是否正确。" << endl;
        return;
    }

    regex lossR(R"(丢失 = \d+\s*\((\d+)% 丢失\))");
    smatch lossM;
    string loss = "丢包率解析失败";
    string lossNum;
    if (regex_search(output, lossM, lossR)) {
        loss = lossM[1].str() + "%";
        lossNum = lossM[1].str();
    } else {
        regex lossREn(R"(Lost = \d+\s*\((\d+)% loss\))");
        if (regex_search(output, lossM, lossREn)) {
            loss = lossM[1].str() + "%";
            lossNum = lossM[1].str();
        }
    }

    regex avgR(R"(平均 = (\d+\.?\d*)ms)");
    smatch avgM;
    string avg = "平均延迟解析失败";
    string avgNum;
    if (regex_search(output, avgM, avgR)) {
        avg = avgM[1].str() + " ms";
        avgNum = avgM[1].str();
    } else {
        regex avgREn(R"(Average = (\d+\.?\d*)ms)");
        if (regex_search(output, avgM, avgREn)) {
            avg = avgM[1].str() + " ms";
            avgNum = avgM[1].str();
        }
    }

    cout << "测试区域: " << region << endl;
    cout << "测试地址: " << url << endl;
    cout << "丢包率: " << loss << endl;
    cout << "平均延迟: " << avg << endl;

    if (lossNum.empty() || avgNum.empty()) {
        cout << "未解析到有效的测试数据，请检查网络连接或域名是否正确。" << endl;
        return;
    }

    float lossFloat = 0.0f;
    float avgFloat = 0.0f;
    try {
        lossFloat = stof(lossNum);
        avgFloat = stof(avgNum);
    } catch (const exception& e) {
        cout << "数值转换异常: " << e.what() << endl;
        return;
    }
    
    int lossInt = (int)lossFloat;

    int havePkg;

    int place = 0;

    if (region == "国内") {
        place = 0;
    } else if (region == "国外") {
        place = 1;
    }

    switch(lossInt){
        case 0:
            havePkg = 4;break;
        case 25:
            havePkg = 3;break;
        case 50:
            havePkg = 2;break;
        case 75:
            havePkg = 1;break;
        case 100:
            havePkg = 0;break;
        default:
            havePkg = 0;break;
    }
    tool5use(havePkg,avgFloat,place);
}

void tool6(){
    string url;
    int segment;
    string output;
    cout << "请输入URL..." << std::endl;
    cin >> url;
    cout << "请输入线程数..." << std::endl;
    cin >> segment;
    cout << "请输入输出文件路径(需包含正确的扩展名否则文件失效)..." << endl;
    cin >> output;
    bool ok = DownloadFileMulti(url.c_str(),output.c_str(), segment);
    if (ok) {
        cout << "文件下载成功" << endl;
    } else {
        cout << "文件下载失败: " << GetLastErrorMsg() << endl;
    }
}

void RunSystemTools() {
    int run = 0;
    if (run > 0){
        cout << "\n\n";
    }
    while (true) {
        int inp;
        cout << "\n===== 系统工具箱 v4.0 =====\n"
             << "1. 定时关机(单位:分钟)\n"
             << "2. 取消关机\n"
             << "3. 杀进程\n"
             << "4. 文件扫描器\n"
             << "5. 检测网址连接\n"
             << "6. 下载\n"
             << "7. 帮助\n"
             << "8. 退出\n"
             << "===========================\n"
             << "输入数字以选择功能: ";
        cin >> inp;
        run ++;
        while (cin.fail() || inp < 1 || inp > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "请输入有效的数字 (1~8): ";
            cin >> inp;
        }

        switch (inp) {
            case 1: tool1(); break;
            case 2: tool2(); break;
            case 3: tool3(); break;
            case 4: tool4(); break;
            case 5: tool5(); break;
            case 6: tool6(); break;
            case 7: tool7(); break;
            case 8:
                cout << "退出系统工具" << endl;
                return;
            default: break;
        }
    }
}

int main() {
    RunSystemTools();
    return 0;
}