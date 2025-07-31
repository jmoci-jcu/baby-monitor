#include <string>

class UartTerminal{
    public:
    static void init();
    static std::string line;
    
    private:
    static void onUartRx();
};