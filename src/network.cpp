#include "network.h"
#include "ga.h"
#include "json.h"

#include <gdk.h>

#include <QDesktopServices>
#include <QUrl>

namespace {

QString GetNetworkKey(const QJsonObject& data)
{
    const auto mainnet = data.value("mainnet").toBool();
    const auto liquid = data.value("liquid").toBool();
    if (mainnet && !liquid) return "bitcoin";
    if (mainnet && liquid) return "liquid";
    if (!mainnet && !liquid) return "testnet";
    if (!mainnet && liquid) return "testnet-liquid";
    Q_UNREACHABLE();
}

}

Network::Network(const QJsonObject& data, QObject *parent)
    : QObject(parent)
    , m_data(data)
    , m_id(data.value("network").toString())
    , m_key(GetNetworkKey(data))
    , m_name(data.value("name").toString())
{
}

QString Network::explorerUrl() const
{
    Q_ASSERT(m_data.contains("tx_explorer_url"));
    auto tx_explorer_url = m_data.value("tx_explorer_url").toString();
    Q_ASSERT(tx_explorer_url.endsWith("/"));
    return tx_explorer_url;
}

bool Network::isLiquid() const
{
    return m_data.value("liquid").toBool();
}

void Network::openTransactionInExplorer(const QString& hash)
{
    QDesktopServices::openUrl(QUrl(explorerUrl() + hash));
}
