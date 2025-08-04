#include "logger.h"
#include "stdio.h"

#include "drivers/flash/flash.h"
#include "drivers/bluetooth/bluetooth.h"

std::vector<std::string> Logger::logBuffer;
repeating_timer_t Logger::flushTimerInfo;

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

bool flushTimerCallback(repeating_timer_t *timer){
    Logger::flushLogBuffer();
    return true;
}

void Logger::init(){
    add_repeating_timer_ms(LOGGER_FLUSH_FREQ_MS,flushTimerCallback,NULL,&Logger::flushTimerInfo);
}


 void Logger::log(Loggable& logData){
    logBuffer.push_back(logData.getLogString());
    return;
 }

void Logger::flushLogBuffer() {
    if(bluetoothDriver::executeCommand("GK") != "none"){
        for (int i = 0; i < logBuffer.size(); i++) { 
            std::string logString = logBuffer[i];
        //todo maybe checking only when a log is sent is not good enough. Maybe we should flush logs also when
        //a new connection is detected.
    
            //bluetooth is connected
            bluetoothDriver::sendLog(logString);
            std::string logs = flashDriver::flushLogs();
            bluetoothDriver::sendLog(logs); //can send multiple logs as one separated by \n
        }
    }else{
        //bluetooth is not connected
        for (int i = 0; i < logBuffer.size(); i++) {
            std::string logString = logBuffer[i];
            flashDriver::writeNewLog(logString);
        }
        printf("%s\n","Bluetooth Disconnected"); //disable for testing
    }
    logBuffer.clear();

}
    
