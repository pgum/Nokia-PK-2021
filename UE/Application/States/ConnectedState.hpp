#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    // IBtsEventsHandler interface
public:
    void handleDisconnected() final;

    void handleSmsReceived(common::PhoneNumber phoneNumber, std::string msg) final;
    void handleCallRequest(common::PhoneNumber from);


    void handleSendMessage(common::PhoneNumber from, std::string message) final;

};

}
