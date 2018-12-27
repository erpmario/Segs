/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "GameCommand.h"
#include "MapEventTypes.h"
#include "BitStream.h"

#include <QtCore/QString>

namespace SEGSEvents
{
// [[ev_def:type]]
class EmailMessageStatus final : public GameCommandEvent
{
public:
    explicit EmailMessageStatus() : GameCommandEvent(evEmailMessageStatus) {}
    EmailMessageStatus(const int status, const QString &recipient) : GameCommandEvent(evEmailMessageStatus),
        m_status(status),
        m_recipient(recipient)
    {
    }

    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1, type()-evFirstServerToClient);
        bs.StorePackedBits(1, m_status);
        bs.StoreString(m_recipient);
    }

    // [[ev_def:field]]
    int m_status;
    // [[ev_def:field]]
    QString m_recipient;
    EVENT_IMPL(EmailMessageStatus)
};
}
