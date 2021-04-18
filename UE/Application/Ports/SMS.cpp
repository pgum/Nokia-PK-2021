#include "SMS.hpp"

namespace ue {

SMS::SMS(std::string message,common::PhoneNumber from,bool read=false):
    read(read),
    message(message),
    from(from)
{}

std::string SMS::getMessage(){
    return this->message;
}

bool SMS::getRead(){
    return this->read;
}

common::PhoneNumber SMS::getPhoneNumber(){
    return this->from;
}

void SMS::setRead(){
    this->read=true;
}

}


