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

        public:
            SMS(std::string message,common::PhoneNumber from,bool read);
    };
}




