#ifndef GREEN_WALLETMANAGER_H
#define GREEN_WALLETMANAGER_H

#include <QJsonObject>
#include <QObject>
#include <QQmlListProperty>
#include <QVector>

class Network;
class Wallet;

class WalletManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Wallet> wallets READ wallets NOTIFY changed)
public:
    explicit WalletManager();
    virtual ~WalletManager();
    static WalletManager* instance();

    Q_INVOKABLE Wallet* createWallet();
    Q_INVOKABLE Wallet* wallet(const QString& id) const;

    void addWallet(Wallet *wallet);

    Q_INVOKABLE void insertWallet(Wallet* wallet);
    Q_INVOKABLE void removeWallet(Wallet* wallet);

    QQmlListProperty<Wallet> wallets();

    QString newWalletName(Network* network) const;

signals:
    void changed();
    void walletAdded(Wallet* wallet);
    void aboutToRemove(Wallet* wallet);

public slots:
    QJsonObject parseUrl(const QString &url);
public:
    QVector<Wallet*> m_wallets;
};

#endif // GREEN_WALLETMANAGER_H
