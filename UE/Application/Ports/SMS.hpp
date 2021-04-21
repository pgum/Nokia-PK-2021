#pragma once
#include <string>
#include "Messages/PhoneNumber.hpp"

namespace ue {

    class SMS
    {
        private:
            bool                read;
            std::string         message;
            common::PhoneNumber from;
            common::PhoneNumber to;
            bool                received;

        public:
            SMS(std::string message,common::PhoneNumber from,common::PhoneNumber to,bool read,bool received);
            bool getRead();
            std::string getMessage();
            common::PhoneNumber getPhoneNumberTo();
            common::PhoneNumber getPhoneNumberFrom();
            SMS setRead();
            void setNotReceived();

    };
}




