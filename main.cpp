#include <windows.h>
#include <iostream>
#include <chrono>

int main() {
    MEMORYSTATUSEX mem = {};
    mem.dwLength = sizeof(mem);

    if (GlobalMemoryStatusEx(&mem)) {


        std::cout << "Total RAM: " << mem.ullTotalPhys / (1024 * 1024) << " MB\n";

        std::cout << "Available RAM: " << mem.ullAvailPhys / (1024 * 1024) << " MB\n";

        std::cout << "Used RAM: " << (mem.ullTotalPhys - mem.ullAvailPhys) / (1024 * 1024) << " MB\n";

        std::cout << "RAM usage: " << mem.dwMemoryLoad << "%\n";
    }

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    Sleep(1000); // Sleep for 1 second

    FILETIME idleTime2;
    FILETIME kernelTime2;
    FILETIME userTime2;

    GetSystemTimes(&idleTime2, &kernelTime2, &userTime2);

    //std::cout << idleTime.dwLowDateTime << std::endl;
    //std::cout << kernelTime.dwLowDateTime << std::endl;
    //std::cout << userTime.dwLowDateTime << std::endl;   

    ULARGE_INTEGER idle1;
    idle1.LowPart = idleTime.dwLowDateTime;
    idle1.HighPart = idleTime.dwHighDateTime;

    ULARGE_INTEGER idle2;
    idle2.LowPart = idleTime2.dwLowDateTime;
    idle2.HighPart = idleTime2.dwHighDateTime;

    ULARGE_INTEGER kernel1;
    kernel1.LowPart = kernelTime.dwLowDateTime;
    kernel1.HighPart = kernelTime.dwHighDateTime;

    ULARGE_INTEGER kernel2;
    kernel2.LowPart = kernelTime2.dwLowDateTime;
    kernel2.HighPart = kernelTime2.dwHighDateTime;

    ULARGE_INTEGER user1;
    user1.LowPart = userTime.dwLowDateTime;
    user1.HighPart = userTime.dwHighDateTime;

    ULARGE_INTEGER user2;
    user2.LowPart = userTime2.dwLowDateTime;
    user2.HighPart = userTime2.dwHighDateTime;

     unsigned long long idle =
        idle2.QuadPart - idle1.QuadPart;

    unsigned long long kernel =
        kernel2.QuadPart - kernel1.QuadPart;

    unsigned long long user =
        user2.QuadPart - user1.QuadPart;


    unsigned long long total = kernel + user;


    unsigned long long busy = total - idle;

    double cpuUsage = (double)busy / total * 100.0;

     std::cout << "CPU usage: "
              << cpuUsage
              << "%\n";
}