#include "SMS.hpp"

namespace ue {

SMS::SMS(std::string message,common::PhoneNumber from,common::PhoneNumber to,bool read,bool received):
    read(read),
    message(message),
    from(from),
    to(to),
    received(received)
{}
SMS::SMS(){
    this->read=false;
    this->received=false;
    this->from=common::PhoneNumber{0};
    this->to=common::PhoneNumber{0};
    this->message="";
}
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
SMS SMS::setRead(){
    this->read=true;
    return *this;
}
void SMS::setNotReceived(){
    this->received=false;
}
bool SMS::operator==(const SMS& sms2) const
{
    if(from==sms2.from and to==sms2.to and message==sms2.message and read==sms2.read and received==sms2.received)
            return true;
    else return false;
}
}


