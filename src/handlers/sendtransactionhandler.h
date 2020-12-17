#ifndef GREEN_SENDTRANSACTIONHANDLER_H
#define GREEN_SENDTRANSACTIONHANDLER_H

#include "handler.h"

class SendTransactionHandler : public Handler
{
    const QJsonObject m_details;
    void call(GA_session* session, GA_auth_handler** auth_handler) override;
public:
    SendTransactionHandler(Wallet* wallet, const QJsonObject& details);
};

#endif // GREEN_SENDTRANSACTIONHANDLER_H
