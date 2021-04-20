#include "SMS.hpp"

namespace ue {

SMS::SMS(std::string message,common::PhoneNumber from,common::PhoneNumber to,bool read,bool received):
    read(read),
    message(message),
    from(from),
    to(to),
    received(received)
{}

std::string SMS::getMessage(){
    return this->message;
}

bool SMS::getRead(){
    return this->read;
}

common::PhoneNumber SMS::getPhoneNumberTo(){
    return this->to;
}
common::PhoneNumber SMS::getPhoneNumberFrom(){
    return this->from;
}
void SMS::setRead(){
    this->read=true;
}
void SMS::setNotReceived(){
    this->received=false;
}

}


