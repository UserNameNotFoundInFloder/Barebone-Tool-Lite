# 系统工具箱 v4.0 / System Tools v4.0 / System-Toolbox v4.0

## 中文版 (Chinese)

功能说明：
定时关机：设置电脑在指定分钟后自动关机，调用系统 shutdown -s 命令。
取消关机：取消已设置的定时关机任务，调用 shutdown -a 命令。
杀进程：根据进程 PID 或映像名称终止进程，支持杀进程树（/T 参数），使用 taskkill 命令。
文件扫描器：递归扫描指定文件夹，统计文件数量与总大小，并可选择是否显示每个文件的路径和大小。
检测网址连接：通过 ping 命令测试目标域名或IP的丢包率和平均延迟，并根据国内/国外不同阈值给出网络质量评价（优秀、良好、一般、较差）。
下载：多线程下载文件，需要提供 URL、线程数和输出路径，依赖 DownLoad.h 实现（已包含在项目中）。
帮助：显示各功能的简要说明。
退出：退出程序。

编译与运行：
环境要求：操作系统为 Windows（因为调用了 taskkill、shutdown、_popen 等 Windows 专用 API）。编译器需支持 C++17 标准，如 MSVC 或 MinGW-w64。所有依赖项（DownLoad.h 及所需 DLL）均已包含在项目中，无需额外配置。
编译命令示例：使用 MSVC 时，在开发者命令提示符中执行 cl /EHsc /std:c++17 SystemTools.cpp。使用 MinGW-w64 时，执行 g++ -std=c++17 SystemTools.cpp -o SystemTools.exe。若 DownLoad.h 不在当前目录，请添加 -I 包含路径并链接相应库。

使用方法：
运行编译生成的 SystemTools.exe，根据主菜单提示输入数字 1 到 8 选择功能。各功能会进一步提示输入参数，如时间、路径、PID 等，按提示操作即可。

源码结构：
SystemTools.cpp 包含所有功能函数和主循环。DownLoad.h 及其对应的 DLL 已包含在项目中，用于实现多线程下载功能。

注意事项：
杀进程功能使用 /F 强制终止，请谨慎操作，避免误杀系统关键进程。文件扫描会遍历所有子目录，扫描大文件夹时可能耗时较长。网络检测依赖系统 ping 命令，输出解析基于中英文两种格式，若系统语言非中英文可能导致解析失败。本工具仅供学习与日常辅助，请勿用于非法或破坏性行为。

许可证：本程序使用 MIT 开源许可证。

---

## English Version (English)

Feature descriptions:
Scheduled shutdown: Set the computer to automatically shut down after a specified number of minutes, using the system command shutdown -s.
Cancel shutdown: Cancel an already scheduled shutdown task using shutdown -a.
Kill process: Terminate a process by PID or image name, with support for killing process trees (/T switch), using taskkill.
File scanner: Recursively scan a folder, count the total number of files and total size, and optionally display each file's path and size.
Network connection test: Use ping to test packet loss and average latency to a target domain or IP, and give a quality rating (Excellent, Good, Fair, Poor) based on different thresholds for domestic or foreign servers.
Download: Multi‑threaded file download, requiring URL, thread count, and output path; implemented via DownLoad.h (already included in the project).
Help: Display brief descriptions of all functions.
Exit: Quit the program.

Compilation and execution:
System requirements: Windows OS (since it uses Windows‑specific APIs like taskkill, shutdown, and _popen). A C++17‑compatible compiler such as MSVC or MinGW‑w64 is required. All dependencies (DownLoad.h and the required DLLs) are already included in the project; no additional setup is needed.
Compilation examples: With MSVC, run cl /EHsc /std:c++17 SystemTools.cpp in a Developer Command Prompt. With MinGW‑w64, run g++ -std=c++17 SystemTools.cpp -o SystemTools.exe. If DownLoad.h is not in the current directory, add the appropriate -I include path and link any necessary libraries.

Usage:
Run the compiled SystemTools.exe, then enter a number from 1 to 8 according to the main menu prompts. Each function will ask for further parameters (time, path, PID, etc.) as needed.

Source structure:
SystemTools.cpp contains all function implementations and the main loop. DownLoad.h and its corresponding DLLs are included in the project for the multi‑threaded download functionality.

Cautions:
The kill‑process function uses /F to force termination; use it carefully to avoid killing critical system processes. The file scanner traverses all subdirectories and may take a long time on large folders. The network test relies on the system ping command and parses output in both Chinese and English; if your system language is neither, parsing may fail. This tool is intended for learning and everyday assistance only; do not use it for illegal or destructive purposes.

License: This project is licensed under the MIT License.

---

## Deutsche Version (German)

Funktionsbeschreibungen:
Geplantes Herunterfahren: Stellt den Computer so ein, dass er nach einer angegebenen Anzahl von Minuten automatisch heruntergefahren wird, unter Verwendung des Systembefehls shutdown -s.
Herunterfahren abbrechen: Bricht eine bereits geplante Herunterfahr-Aufgabe ab, mit shutdown -a.
Prozess beenden: Beendet einen Prozess anhand der PID oder des Imagenamens, unterstützt das Beenden von Prozessbäumen (/T-Schalter) mittels taskkill.
Datei-Scanner: Durchsucht einen Ordner rekursiv, zählt die Gesamtzahl der Dateien und die Gesamtgröße und kann optional den Pfad und die Größe jeder Datei anzeigen.
Netzwerkverbindungstest: Verwendet ping, um Paketverlust und durchschnittliche Latenz zu einer Ziel-Domain oder IP zu testen und gibt eine Qualitätsbewertung (Ausgezeichnet, Gut, Befriedigend, Schlecht) basierend auf unterschiedlichen Schwellwerten für Inlands- oder Auslandsserver ab.
Download: Mehrfädiger Dateidownload, erfordert URL, Anzahl der Threads und Ausgabepfad; implementiert über DownLoad.h (bereits im Projekt enthalten).
Hilfe: Zeigt kurze Beschreibungen aller Funktionen an.
Beenden: Beendet das Programm.

Kompilierung und Ausführung:
Systemanforderungen: Windows-Betriebssystem (da Windows-spezifische APIs wie taskkill, shutdown und _popen verwendet werden). Ein C++17-kompatibler Compiler wie MSVC oder MinGW‑w64 ist erforderlich. Alle Abhängigkeiten (DownLoad.h und die benötigten DLLs) sind bereits im Projekt enthalten; keine zusätzliche Konfiguration erforderlich.
Kompilierungsbeispiele: Mit MSVC führen Sie im Developer Command Prompt cl /EHsc /std:c++17 SystemTools.cpp aus. Mit MinGW‑w64 verwenden Sie g++ -std=c++17 SystemTools.cpp -o SystemTools.exe. Falls DownLoad.h nicht im aktuellen Verzeichnis liegt, fügen Sie den entsprechenden -I-Einbindepfad hinzu und linken Sie gegebenenfalls erforderliche Bibliotheken.

Verwendung:
Führen Sie die kompilierte SystemTools.exe aus und geben Sie dann gemäß dem Hauptmenü eine Zahl von 1 bis 8 ein. Jede Funktion fragt je nach Bedarf weitere Parameter ab (Zeit, Pfad, PID usw.).

Quellstruktur:
SystemTools.cpp enthält alle Funktionsimplementierungen und die Hauptschleife. DownLoad.h und die zugehörigen DLLs sind im Projekt enthalten und ermöglichen den mehrfädigen Download.

Hinweise:
Die Prozessbeenden-Funktion verwendet /F für erzwungenes Beenden; gehen Sie vorsichtig vor, um das Beenden kritischer Systemprozesse zu vermeiden. Der Datei-Scanner durchläuft alle Unterverzeichnisse und kann bei großen Ordnern viel Zeit in Anspruch nehmen. Der Netzwerktest stützt sich auf den systemeigenen ping-Befehl und wertet die Ausgabe sowohl auf Chinesisch als auch auf Englisch aus; wenn die Systemsprache keine dieser Sprachen ist, kann die Auswertung fehlschlagen. Dieses Werkzeug ist nur für Lernzwecke und den alltäglichen Gebrauch gedacht; verwenden Sie es nicht für illegale oder zerstörerische Zwecke.

Lizenz: Dieses Projekt ist unter der MIT-Lizenz lizenziert.