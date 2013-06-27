//
//  logger.h
//  FEX
//
//  Created by FancyZero on 13-6-18.
//
//

#ifndef FEX_logger_h
#define FEX_logger_h
#include "FE.h"

FE_NS_BEGIN
class logcandy
{
public:
    logcandy( const char* str, ... )
    {
        va_list vl;
        va_start(vl, str);
        vsprintf(buff, str, vl);
        va_end(vl);
    }
    
    char buff[4096];
};

class logger
{
public:
    logger(const Name& category)
    {
        cout << "[" << category << "]" << ":";
    }
    
    logger& operator<<(basic_ostream<char>& (*__pf)(basic_ostream<char>&))
    {
        cout << __pf;
        return *this;
        }
        
        logger& operator<<(basic_ios<char, char_traits<char>>&
                           (*__pf)(basic_ios<char, char_traits<char>>&))
        {
            cout << __pf;
            return *this;
        }
        
        logger& operator<<(ios_base& (*__pf)(ios_base&))
        {
            cout << __pf;
            return *this;
        }
        
        template<class T>
        logger& operator<<( const T& t)
        {
            cout << t;
            return *this;
        }
        
        logger& operator<<( const logcandy& t)
        {
            cout << t.buff;
            return *this;
        }
        
        logger& operator<<(basic_streambuf<char, char_traits<char>>* __sb)
        {
            cout << __sb;
            return *this;
        }
        };
        
        FE_NS_END
#endif
