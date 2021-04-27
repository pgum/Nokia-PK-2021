#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "SmsForDatabase/Sms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

}
