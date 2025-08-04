#include "logger.h"
#include "stdio.h"

#include "drivers/flash/flash.h"
#include "drivers/bluetooth/bluetooth.h"

std::vector<std::string> Logger::logBuffer; 

Logger::SoundLevelAlert::SoundLevelAlert(){
    classifier = "Sound Threshold";
};
std::string Logger::SoundLevelAlert::getLogString() {
    uint32_t time_ms = to_ms_since_boot(get_absolute_time());
    char stringBuff[128];
    std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
    std::string result(stringBuff);
    return result;
}
//Vibration Implementation
Logger::VibrationLevelAlert::VibrationLevelAlert(){
    classifier = "Vibration Threshold";
};
std::string Logger::VibrationLevelAlert::getLogString() {
    uint32_t time_ms = to_ms_since_boot(get_absolute_time());
    char stringBuff[128];
    std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
    std::string result(stringBuff);
    return result;
}
//Motion Implementation
Logger::MotionAlert::MotionAlert(){
    classifier = "Motion Threshold";
};
std::string Logger::MotionAlert::getLogString() {
    uint32_t time_ms = to_ms_since_boot(get_absolute_time());
    char stringBuff[128];
    std::sprintf(stringBuff,"%u-%s\n", time_ms, classifier.c_str());
    std::string result(stringBuff);
    return result;
}
//Temperature Implementation
Logger::TemperatureLevel::TemperatureLevel(uint8_t temperature){
    classifier = "Temperature Level";
    this->temperature = temperature;
};
std::string Logger::TemperatureLevel::getLogString(){
    uint32_t time_ms = to_ms_since_boot(get_absolute_time());
    char stringBuff[128];
    std::sprintf(stringBuff,"%u-%s-%u\n", time_ms, classifier.c_str(), temperature);
    std::string result(stringBuff);
    return result;
}
//Humidty Implementation
Logger::HumidityLevel::HumidityLevel(uint8_t humidity){
    classifier = "Humidity Level";
    this->humidity = humidity;
};
std::string Logger::HumidityLevel::getLogString(){
    uint32_t time_ms = to_ms_since_boot(get_absolute_time());
    char stringBuff[128];
    std::sprintf(stringBuff,"%u-%s-%u\n", time_ms, classifier.c_str(), humidity);
    std::string result(stringBuff);
    return result;
}



 void Logger::log(Loggable& logData){
    logBuffer.push_back(logData.getLogString());
 }

    void Logger::flushLogBuffer() {
    if(bluetoothDriver::executeCommand("GK") != "none"){
        for (int i = 0; i < logBuffer.size(); i++) { 
            std::string logString = logBuffer[i];
        //todo maybe checking only when a log is sent is not good enough. Maybe we should flush logs also when
        //a new connection is detected.
    
            //bluetooth is connected
            bluetoothDriver::sendLog(logString);
            //todo check if any logs are stored in flash, if so, send them instead of flush.
            printf("%s",flashDriver::flushLogs().c_str());
        }
    }else{
        //bluetooth is not connected
        for (int i = 0; i < logBuffer.size(); i++) {
            std::string logString = logBuffer[i];
            flashDriver::writeNewLog(logString);
        }
    }

}

    
