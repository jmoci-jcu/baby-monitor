#include <unordered_map>
#include <string>
#include "pico/stdlib.h"

namespace logger{

//Loggable Abstract Class (you can't use this)
class Loggable{
public:
    virtual std::string getLogString() = 0;
    virtual ~Loggable() = default;
    std::string classifier;
};
//Loggable Concrete Classes (use these)
class SoundLevelAlert : public logger::Loggable{
    public:
    SoundLevelAlert();
    std::string getLogString() override;
};
class TemperatureLevel : public logger::Loggable{
    public:
    uint8_t temperature;
    TemperatureLevel(uint8_t temperature);
    std::string getLogString() override;
};

//Accepts a reference to a Loggable data structure. Should be called when any data is ready to be logged/sent.
//Handles all logging behavior including Bluetooth, USB and flash automatically.

//# Example:
//SoundLevelAlert logData = SoundLevelAlert(); <- create a SoundLevelAlert
//log(logData); <- pass into logger
// WARNING (do not use the line "new SoundLevelAlert()" even if GPT says to)
void log(Loggable& logData);
}