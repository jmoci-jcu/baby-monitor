#include "logger.h"
#include "stdio.h"

#include "drivers/flash/flash.h"
#include "drivers/bluetooth/bluetooth.h"

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
        //todo maybe checking only when a log is sent is not good enough. Maybe we should flush logs also when
        //a new connection is detected.
        if(bluetoothDriver::executeCommand("GK") != "none"){
            //bluetooth is connected
            bluetoothDriver::sendLog(logString);
            //todo check if any logs are stored in flash, if so, send them instead of flush.
            printf("%s",flashDriver::flushLogs().c_str());

        }else{
            //bluetooth is not connected
            flashDriver::writeNewLog(logString);
        }
    }
}