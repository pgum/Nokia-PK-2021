//
// Created by jacob on 13.05.2021.
//

#include "TalkingState.h"

namespace ue
{
    TalkingState::TalkingState(Context &context)
    : BaseState(context,"TalkingState")
    {
        logger.logInfo("sending Call Accept");
        //        context.user.setCallMode();

    }
}