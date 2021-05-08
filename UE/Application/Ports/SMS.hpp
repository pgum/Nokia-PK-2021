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


            SMS(std::string message,common::PhoneNumber from,common::PhoneNumber to,smsRead read,smsReceived received);
            smsRead isRead();
            std::string getMessage();
            common::PhoneNumber getPhoneNumberTo();
            common::PhoneNumber getPhoneNumberFrom();

            SMS* setRead(smsRead read);
            SMS* setReceived(smsReceived received);
            SMS* setFrom(common::PhoneNumber from);
            SMS* setTo(common::PhoneNumber to);
            SMS* setMessage(std::string message);

            //for google tests
            SMS();
            bool operator==(const SMS &sms2) const;

    };
}




