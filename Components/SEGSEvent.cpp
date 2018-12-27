/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

/*!
 * @addtogroup Components
 * @{
 */

#include "SEGSEvent.h"
#include "SEGSEventFactory.h"

using namespace SEGSEvents;
Finish *Finish::s_instance(new Finish());

const char *Event::info()
{
    return event_name(this->m_type);
}

//! @}
