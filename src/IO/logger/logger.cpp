#include "logger.h"
#include "stdio.h"

#include "drivers/flash/flash.h"

namespace logger{
    SoundLevelAlert::SoundLevelAlert(){
        classifier = "Sound Threshold";
    };
    std::string SoundLevelAlert::getLogString() {
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        char stringBuff[128];
        std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
        std::string result(stringBuff);
        return result;
    }
    //Vibration Implementation
    VibrationLevelAlert::VibrationLevelAlert(){
        classifier = "Vibration Threshold";
    };
    std::string VibrationLevelAlert::getLogString() {
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        char stringBuff[128];
        std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
        std::string result(stringBuff);
        return result;
    }
    //Motion Implementation
    MotionAlert::MotionAlert(){
        classifier = "Motion Threshold";
    };
    std::string MotionAlert::getLogString() {
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        char stringBuff[128];
        std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
        std::string result(stringBuff);
        return result;
    }
    //Temperature Implementation
    TemperatureLevel::TemperatureLevel(uint8_t temperature){
        classifier = "Temperature Level";
        this->temperature = temperature;
    };
    std::string TemperatureLevel::getLogString(){
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        char stringBuff[128];
        std::sprintf(stringBuff,"%u-%s-%u\n", time_ms, classifier.c_str(), temperature);
        std::string result(stringBuff);
        return result;
    }
    //Humidty Implementation
    HumidityLevel::HumidityLevel(uint8_t humidity){
        classifier = "Humidity Level";
        this->humidity = humidity;
    };
    std::string HumidityLevel::getLogString(){
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        char stringBuff[128];
        std::sprintf(stringBuff,"%u-%s-%u\n", time_ms, classifier.c_str(), humidity);
        std::string result(stringBuff);
        return result;
    }

    

    void log(Loggable& logData){
        uint32_t time_ms = to_ms_since_boot(get_absolute_time());
        std::string logString = logData.getLogString();
        //printf("%s",logString.c_str());

        //assume not in bt mode for now
        flashDriver::writeNewLog(logString);
    }
}