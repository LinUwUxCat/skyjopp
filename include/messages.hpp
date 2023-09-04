#ifndef _MESSAGES_HPP
#define _MESSAGES_HPP
void exit_err(const char* message, int exitcode = 1);
void err(const char* message);
void log(const char* message);
void warn(const char* message);
#endif //_MESSAGES_HPP