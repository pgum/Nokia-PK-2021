//
// Created by jacob on 13.05.2021.
//

#include "TalkingState.h"

namespace ue
{
    TalkingState::TalkingState(Context &context,common::PhoneNumber from)
    : BaseState(context,"TalkingState")
    {
        logger.logInfo("sending Call Accept");
        context.bts.sendCallRespond(context.phoneNumber, from,
                                    common::MessageId::CallAccepted);
        //        context.user.setCallMode();

    }
}