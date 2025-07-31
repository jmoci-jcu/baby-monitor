#include "uart_terminal.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware_params.h"
#include "drivers/flash/flash.h"

std::string UartTerminal::line;

void UartTerminal::onUartRx(){
   while (uart_is_readable(UART_INSTANCE)) {
      char c = uart_getc(UART_INSTANCE);
      printf("%c",c);
      if(c=='\r'){
        volatile char buff[10];
        for(int i = 0; i < UartTerminal::line.length(); i++){
            buff[i] = UartTerminal::line[i];
        }
        if(UartTerminal::line == "flush"){
            std::string logs = flashDriver::flushLogs();
            printf("%s\n", logs.c_str()); 
        }else{
            printf("Unknown Command use flush to get logs\n");
        }
        UartTerminal::line = "";
      }else{
        UartTerminal::line += c;
      }
      
   }
}
void UartTerminal::init(){
    uart_set_irq_enables(UART_INSTANCE,true,false);
    irq_set_exclusive_handler(UART_INSTANCE_IRQ,UartTerminal::onUartRx);
    irq_set_enabled(UART_INSTANCE_IRQ,true);
}