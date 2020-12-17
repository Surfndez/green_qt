#include "json.h"
#include "sendtransactionhandler.h"

#include <gdk.h>

SendTransactionHandler::SendTransactionHandler(Wallet* wallet, const QJsonObject& details)
    : Handler(wallet)
    , m_details(details)
{
}

void SendTransactionHandler::call(GA_session* session, GA_auth_handler** auth_handler)
{
    auto details = Json::fromObject(m_details);
    int err = GA_send_transaction(session, details.get(), auth_handler);
    Q_ASSERT(err == GA_OK);
}
