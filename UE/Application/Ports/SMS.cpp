#include "SMS.hpp"

namespace ue {

SMS::SMS(std::string message,common::PhoneNumber from,bool read=false):
    read(read),
    message(message),
    from(from)
{}

}


