#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleTimeout() final;
    // IBtsEventsHandler interface
    void handleUnknownRecipientSMS()final;
    void handleReceivedCallAccept(common::PhoneNumber from) final;
    void handleReceivedCallReject(common::PhoneNumber from) final;
    void handleUnknownRecipient() final;
public:
    void handleDisconnected() final;
    void handleCallRequest(common::PhoneNumber from) final;
    void handleSendCallAccepted(common::PhoneNumber from) final;
    void handleSendCallDropped(common::PhoneNumber from) final;
    void handleSendCallRequest(common::PhoneNumber to) final;
};

}
