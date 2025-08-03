#pragma once
#include <string>

namespace bluetoothDriver{
    void sendLog(std::string log);
    std::string executeCommand(std::string cmd);
    void init();
}