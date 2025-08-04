#include "drivers/bluetooth/bluetooth.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include <string>

#include "hardware_params.h"

// send a character over uart
void bluetoothDriver::init(){
    gpio_set_function(BT_GPIO_TX,GPIO_FUNC_UART);
    gpio_set_function(BT_GPIO_RX,GPIO_FUNC_UART);
    uart_init(BT_UART_INSTANCE,115200);
}

/*This function must be called no more than once every 100ms*/
void bluetoothDriver::sendLog(std::string log){
    uart_puts(BT_UART_INSTANCE,log.c_str());
}

/*This function requires a clear line for 100ms before being called. 
Beware if sending data without using the sendLog function*/
std::string bluetoothDriver::executeCommand(std::string cmd){
    std::string ret = "";
    uart_puts(BT_UART_INSTANCE,"$$$");

    //wait for 'CMD> '
    while(true){
        char c = uart_getc(BT_UART_INSTANCE);
        if(c==' '){
            break;
        }
    }

    cmd += '\r';
    uart_puts(BT_UART_INSTANCE,cmd.c_str());

    //collect response
    while(true){
        char c = uart_getc(BT_UART_INSTANCE);
        if(c=='\r'){
            break;
        }
        ret += c;
    }

    //wait for 'CMD> '
    char charBuff[2] = {'\0','\0'};
    while(true){
        char c = uart_getc(BT_UART_INSTANCE);
        charBuff[0] = charBuff[1];
        charBuff[1] = c;
        if(charBuff[0] == '>' && charBuff[1] == ' '){
            break;
        }
    }

    uart_puts(BT_UART_INSTANCE,"---\r");

    //wait for 'END\r\n'
    while(true){
        char c = uart_getc(BT_UART_INSTANCE);
        if(c=='\n'){
            break;
        }
    }

    return ret;
}