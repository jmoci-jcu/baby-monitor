#include <string>

// Handles logic for putty commands (flush prints and clears logs from flash)
class UartTerminal{
    public:
    static void init();
    static std::string line;
    
    private:
    static void onUartRx();
};