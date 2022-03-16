#include <iostream>
#include "logger.hpp"

using std::cout;
using std::endl;
using ilrd::Logger;
//using ilrd::Logger::Severity;

int main()
{

    std::string fileName = "log_file.txt";
    Logger s_logger(fileName, ilrd::Logger::INFO) ;
 
    s_logger.Log("Seting Severity to INFO\n\n", ilrd::Logger::INFO);
 
    s_logger.Log("Logged info\n", ilrd::Logger::INFO);
    s_logger.Log("Logged bug\n", ilrd::Logger::DEBUG);
    s_logger.Log("Logged error\n", ilrd::Logger::ERROR);

    //s_logger.Log("Seting Severity to DEBUG\n\n", ilrd::Logger::INFO);
   // s_logger.SetSeverity(ilrd::Logger::DEBUG);
    
    s_logger.Log("Logged info2\n", ilrd::Logger::INFO);
    s_logger.Log("Logged bug2\n", ilrd::Logger::DEBUG);
    s_logger.Log("Logged error2\n", ilrd::Logger::ERROR);
    
  
    return 0;
}
