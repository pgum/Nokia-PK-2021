#include "SMS.hpp"

namespace ue {

SMS::SMS(std::string message, common::PhoneNumber from, common::PhoneNumber to, smsRead read, smsReceived received):
    read(read),
    message(message),
    from(from),
    to(to),
    received(received)
{}
SMS::SMS(){
    this->read=smsRead::NotRead;
    this->received=smsReceived::NotReceived;
    this->from=common::PhoneNumber{0};
    this->to=common::PhoneNumber{0};
    this->message="";
}
bool SMS::operator==(const SMS& sms2) const
{
    return from==sms2.from and to==sms2.to and message==sms2.message and read==sms2.read and received==sms2.received;
}
}


