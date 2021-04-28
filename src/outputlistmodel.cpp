#include "account.h"
#include "resolver.h"
#include "output.h"
#include "outputlistmodel.h"

#include <QDebug>

OutputListModel::OutputListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

OutputListModel::~OutputListModel()
{

}

void OutputListModel::setAccount(Account *account)
{
    if (!m_account.update(account)) return;
    beginResetModel();
    m_get_outputs_activity.update(nullptr);
    m_outputs.clear();
    endResetModel();
    emit accountChanged(m_account);
    fetch();
    if (m_account) {
        m_account.track(QObject::connect(m_account, &Account::notificationHandled, this, [this](const QJsonObject& notification) {
            const auto event = notification.value("event").toString();
            if (event == "transaction") {
                fetch();
                return;
            }
            if (event == "block") {
                fetch();
                return;
            }
        }));
    }
}

void OutputListModel::fetch()
{
    if (!m_account) return;
    if (m_get_outputs_activity) return;

    m_get_outputs_activity.update(new AccountGetUnspentOutputsActivity(m_account, 0, true, this));
    m_account->wallet()->pushActivity(m_get_outputs_activity);

    m_get_outputs_activity.track(QObject::connect(m_get_outputs_activity, &Activity::finished, this, [this] {
        beginResetModel();
        m_outputs = m_get_outputs_activity->outputs();
        endResetModel();
        m_get_outputs_activity->deleteLater();
        m_get_outputs_activity.update(nullptr);
        emit fetchingChanged();
    }));

    m_get_outputs_activity->exec();
    emit fetchingChanged();
}

QHash<int, QByteArray> OutputListModel::roleNames() const
{
    return {
        { Qt::UserRole, "output" }
    };
}

int OutputListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_outputs.size();
}

int OutputListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant OutputListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::UserRole) return QVariant::fromValue(m_outputs.at(index.row()));
    return QVariant();
}

