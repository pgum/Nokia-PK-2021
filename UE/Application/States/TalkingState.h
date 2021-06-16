

#include "BaseState.hpp"

namespace ue
{
class TalkingState : public BaseState {

public:
    TalkingState(Context & context,common::PhoneNumber partnerPhoneNumber);

    //IUserEventsHandler
    void handleSendCallTalk(common::PhoneNumber to, const std::string &msg) final;
    void handleSendCallDropped(common::PhoneNumber from) final;
    void handleTimeout() final;
    // IBtsEventsHandler interface
    void handleCallRequest(common::PhoneNumber from) final;
    void handleReceivedCallTalk(const std::string &text) final;
    void handleReceivedCallReject(common::PhoneNumber from) final;
    void handleUnknownRecipient() final;

};
}

