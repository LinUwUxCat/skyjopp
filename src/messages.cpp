#include "messages.hpp"
#include <iostream>

void err(const char* message){
    printf("ERR : %s", message);
}
void exit_err(const char* message, int exitcode){
    err(message);
    exit(exitcode);
}
void log(const char* message){
    printf("LOG : %s", message);
}
void warn(const char* message){
    printf("WARN : %s", message);
}