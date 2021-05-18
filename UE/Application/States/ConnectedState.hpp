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
    void handleCallRequest(common::PhoneNumber from) final;
    void handleAcceptCall(common::PhoneNumber from) final;
    void handleRejectCall(common::PhoneNumber from) final;
    void handleSendCallRequest(common::PhoneNumber to) final;
};

}
