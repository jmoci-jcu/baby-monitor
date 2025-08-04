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

void bluetoothDriver::sendLog(std::string log){
    uart_puts(BT_UART_INSTANCE,log.c_str());
}

std::string bluetoothDriver::executeCommand(std::string cmd){
    std::string ret = "";
    //todo : uart must be clear for 100ms before entering command mode, 
    //but we may opt for a solution that does not block for 100ms.
    sleep_ms(100);
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