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

// Tool 4: File Scanner
void tool4() {
    string path;
    cout << "Enter the folder path to scan: ";
    cin.ignore();
    getline(cin, path);
    if (path.empty()) {
        cout << "Path cannot be empty!" << endl;
        return;
    }
    int pathSize = path.size();
    string pathTail(1, path.back());
    if (pathTail != "\\" && pathTail != "/") {
        path += "\\";
    }
    error_code ec;
    if (!exists(path, ec) || !is_directory(path, ec)) {
        cout << "Invalid path or not a folder!" << endl;
        return;
    }

    char choice;
    cout << "Show all files? (y/n, default n): ";
    cin >> choice;
    bool listFiles = (choice == 'y' || choice == 'Y');

    cout << "Scanning..." << endl;
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
                cout << entry.path().string() << "  (" << size << " bytes)" << endl;
            }
            fileCount++;
            totalSize += size;
        }

        it.increment(ec);
    }

    if (ec) {
        cout << "Error during scanning: " << ec.message() << endl;
    }

    cout << "\nScan complete! Found " << fileCount << " files, total size " << totalSize << " bytes" << endl;
    if (skippedDirs > 0) {
        cout << "Skipped " << skippedDirs << " directories" << endl;
    }
    if (!listFiles) {
        cout << "File list not shown. To see it, please rerun and enter 'y'." << endl;
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// Tool 3: Kill Process
int tool3() {
    string input;
    string PIDKill;
    string IMKill;
    string help = "Process Killer Help\nPID: Kill by Process ID\nIM: Kill by Image Name\nT: Kill process tree (including children)\n? Show this help\nQUIT Exit";

    while (true) {
        cout << "\nEnter kill method (PID, IM, T, ? for help, QUIT): ";
        cin >> input;
        if (input == "PID") {
            system("tasklist");
            cout << "Enter the PID to kill: ";
            cin >> PIDKill;
            string cmd = "taskkill /PID " + PIDKill + " /F";
            int ret = system(cmd.c_str());
            if (ret == 0)
                cout << "Process killed successfully!" << endl;
            else
                cout << "Failed to kill process: " << ret << endl;
        }
        else if (input == "IM") {
            cout << "Enter the process name (e.g., test.exe): ";
            cin >> IMKill;
            string cmd = "taskkill /IM " + IMKill + " /F";
            int ret = system(cmd.c_str());
            if (ret == 0)
                cout << "Process killed successfully!" << endl;
            else
                cout << "Failed to kill process: " << ret << endl;
        }
        else if (input == "T") {
            cout << "Enter kill method (PID or IM): ";
            cin >> input;
            if (input == "PID") {
                system("tasklist");
                cout << "Enter the PID to kill: ";
                cin >> PIDKill;
                string cmd = "taskkill /PID " + PIDKill + " /T /F";
                int ret = system(cmd.c_str());
                if (ret == 0)
                    cout << "Process killed successfully!" << endl;
                else
                    cout << "Failed to kill process: " << ret << endl;
            }
            else if (input == "IM") {
                cout << "Enter the process name (e.g., test.exe): ";
                cin >> IMKill;
                string cmd = "taskkill /IM " + IMKill + " /T /F";
                int ret = system(cmd.c_str());
                if (ret == 0)
                    cout << "Process killed successfully!" << endl;
                else
                    cout << "Failed to kill process: " << ret << endl;
            }
            else {
                cout << "Invalid method!" << endl;
            }
        }
        else if (input == "?") {
            cout << help << endl;
        }
        else if (input == "QUIT") {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid input!" << endl;
        }
    }
    return 0;
}

// Tool 1: Shutdown
int tool1() {
    int minutes;
    cout << "Enter shutdown delay in minutes (e.g., 90): ";
    cin >> minutes;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
        cin >> minutes;
    }
    int seconds = minutes * 60;
    string command = "shutdown -s -t " + to_string(seconds);
    cout << "Shutdown scheduled in " << minutes << " minutes" << endl;
    system(command.c_str());
    return 0;
}

// Tool 2: Cancel Shutdown
int tool2() {
    string input;
    cout << "Enter O to cancel shutdown: ";
    cin >> input;
    if (input == "O" || input == "o") {
        system("shutdown -a");
        cout << "Shutdown cancelled!" << endl;
    } else {
        cout << "Not cancelled." << endl;
    }
    return 0;
}

// Tool 7: Help
int tool7() {
    cout << "Help:\n"
         << "1. Shutdown: Schedule auto shutdown after specified minutes.\n"
         << "2. Cancel shutdown: Cancel a scheduled shutdown.\n"
         << "3. Kill process: Terminate a process by PID or name, optionally with its process tree.\n"
         << "4. File scanner: Scan a folder and its subfolders, showing total file count and size.\n"
         << "5. Network test: Ping a URL or IP and display packet loss and average latency.\n"
         << "6. Download: Download a file from a URL with multi-thread support.\n"
         << "7. Help: Show this help message.\n"
         << "8. Exit: Quit the program.\n\n";
    return 0;
}

// Helper function for network quality rating
void tool5use(int havePkg, float avg, int place) {
    switch (havePkg) {
        case 0:
            if (place == 0) { // Domestic
                if (avg <= 70)      cout << "Domestic network quality: Excellent" << endl;
                else if (avg <= 85) cout << "Domestic network quality: Good" << endl;
                else if (avg <= 90) cout << "Domestic network quality: Fair" << endl;
                else                cout << "Domestic network quality: Poor" << endl;
            } else { // Foreign
                if (avg <= 80)      cout << "Foreign network quality: Excellent" << endl;
                else if (avg <= 95) cout << "Foreign network quality: Good" << endl;
                else if (avg <= 105) cout << "Foreign network quality: Fair" << endl;
                else                cout << "Foreign network quality: Poor" << endl;
            }
            break;
        case 1:
            if (place == 0) {
                if (avg <= 50)      cout << "Domestic network quality: Excellent" << endl;
                else if (avg <= 60) cout << "Domestic network quality: Good" << endl;
                else if (avg <= 80) cout << "Domestic network quality: Fair" << endl;
                else                cout << "Domestic network quality: Poor" << endl;
            } else {
                if (avg <= 65)      cout << "Foreign network quality: Excellent" << endl;
                else if (avg <= 75) cout << "Foreign network quality: Good" << endl;
                else if (avg <= 90) cout << "Foreign network quality: Fair" << endl;
                else                cout << "Foreign network quality: Poor" << endl;
            }
            break;
        case 2:
            if (place == 0) {
                if (avg <= 55)      cout << "Domestic network quality: Excellent" << endl;
                else if (avg <= 65) cout << "Domestic network quality: Good" << endl;
                else if (avg <= 80) cout << "Domestic network quality: Fair" << endl;
                else                cout << "Domestic network quality: Poor" << endl;
            } else {
                if (avg <= 60)      cout << "Foreign network quality: Excellent" << endl;
                else if (avg <= 72) cout << "Foreign network quality: Good" << endl;
                else if (avg <= 85) cout << "Foreign network quality: Fair" << endl;
                else                cout << "Foreign network quality: Poor" << endl;
            }
            break;
        case 3:
            if (place == 0) {
                if (avg <= 50)      cout << "Domestic network quality: Excellent" << endl;
                else if (avg <= 60) cout << "Domestic network quality: Good" << endl;
                else if (avg <= 75) cout << "Domestic network quality: Fair" << endl;
                else                cout << "Domestic network quality: Poor" << endl;
            } else {
                if (avg <= 55)      cout << "Foreign network quality: Excellent" << endl;
                else if (avg <= 65) cout << "Foreign network quality: Good" << endl;
                else if (avg <= 80) cout << "Foreign network quality: Fair" << endl;
                else                cout << "Foreign network quality: Poor" << endl;
            }
            break;
        case 4:
            if (place == 0) {
                if (avg <= 45)      cout << "Domestic network quality: Excellent" << endl;
                else if (avg <= 55) cout << "Domestic network quality: Good" << endl;
                else if (avg <= 70) cout << "Domestic network quality: Fair" << endl;
                else                cout << "Domestic network quality: Poor" << endl;
            } else {
                if (avg <= 38)      cout << "Foreign network quality: Excellent" << endl;
                else if (avg <= 48) cout << "Foreign network quality: Good" << endl;
                else if (avg <= 62) cout << "Foreign network quality: Fair" << endl;
                else                cout << "Foreign network quality: Poor" << endl;
            }
            break;
        default:
            cerr << "Unable to determine network quality." << endl;
            break;
    }
}

// Tool 5: Network Test
void tool5() {
    string region;
    cout << "Select test region (domestic/foreign): ";
    cin >> region;
    if (region != "domestic" && region != "foreign") {
        cout << "Invalid input. Please enter 'domestic' or 'foreign'." << endl;
        return;
    }
    string url;
    cout << "Enter domain or IP address to test: ";
    cin >> url;

    cout << "Test results:" << endl;

    string cmd = "ping -n 4 " + url;
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        cout << "Ping command failed." << endl;
        return;
    }

    string output;
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr)
        output += buf;
    _pclose(pipe);

    if (output.empty()) {
        cout << "No ping output. Please check your network or domain." << endl;
        return;
    }

    regex lossR(R"(丢失 = \d+\s*\((\d+)% 丢失\))");
    smatch lossM;
    string loss = "Packet loss parse failed";
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
    string avg = "Average latency parse failed";
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

    cout << "Region: " << region << endl;
    cout << "Target: " << url << endl;
    cout << "Packet loss: " << loss << endl;
    cout << "Average latency: " << avg << endl;

    if (lossNum.empty() || avgNum.empty()) {
        cout << "No valid data. Check your network or domain." << endl;
        return;
    }

    float lossFloat = 0.0f;
    float avgFloat = 0.0f;
    try {
        lossFloat = stof(lossNum);
        avgFloat = stof(avgNum);
    } catch (const exception& e) {
        cout << "Data conversion error: " << e.what() << endl;
        return;
    }

    int lossInt = (int)lossFloat;
    int havePkg;
    int place = 0;

    if (region == "domestic") {
        place = 0;
    } else if (region == "foreign") {
        place = 1;
    }

    switch (lossInt) {
        case 0:   havePkg = 4; break;
        case 25:  havePkg = 3; break;
        case 50:  havePkg = 2; break;
        case 75:  havePkg = 1; break;
        case 100: havePkg = 0; break;
        default:  havePkg = 0; break;
    }

    tool5use(havePkg, avgFloat, place);
}

// Tool 6: Multi-threaded Download
void tool6() {
    string url;
    int segment;
    string output;
    cout << "Enter URL..." << endl;
    cin >> url;
    cout << "Enter number of threads..." << endl;
    cin >> segment;
    cout << "Enter output file path (must include correct extension)..." << endl;
    cin >> output;
    bool ok = DownloadFileMulti(url.c_str(), output.c_str(), segment);
    if (ok) {
        cout << "Download successful!" << endl;
    } else {
        cout << "Download failed: " << GetLastErrorMsg() << endl;
    }
}

// Main menu loop
void RunSystemTools() {
    int run = 0;
    if (run > 0) {
        cout << "\n\n";
    }
    while (true) {
        int inp;
        cout << "\n===== System Tools v4.0 =====\n"
             << "1. Shutdown (minutes)\n"
             << "2. Cancel shutdown\n"
             << "3. Kill process\n"
             << "4. File scanner\n"
             << "5. Network test\n"
             << "6. Download\n"
             << "7. Help\n"
             << "8. Exit\n"
             << "===========================\n"
             << "Enter your choice: ";
        cin >> inp;
        run ++;
        while (cin.fail() || inp < 1 || inp > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number (1~8): ";
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
                cout << "Exiting..." << endl;
                return;
            default: break;
        }
    }
}

int main() {
    RunSystemTools();
    return 0;
}