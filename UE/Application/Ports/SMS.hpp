#pragma once
#include <string>
#include "Messages/PhoneNumber.hpp"

namespace ue {

enum class smsRead
{
    Read,
    NotRead
};
enum class smsReceived
{
    Received,
    NotReceived
};

struct SMS
    {

            smsRead             read;
            std::string         message;
            common::PhoneNumber from;
            common::PhoneNumber to;
            smsReceived         received;

            SMS();
            SMS(std::string message,common::PhoneNumber from,common::PhoneNumber to,smsRead read,smsReceived received);            
            bool operator==(const SMS &sms2) const;

    };
}




