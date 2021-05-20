#include "ConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}


//void ConnectedState::handleSms(common::PhoneNumber from, std::string text)
//{
//    logger.logInfo("Received SMS from ", from, ": «", text, "»");
//    context.user.showNewSms();
//}

}
