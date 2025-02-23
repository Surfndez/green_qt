import Blockstream.Green 0.1
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.12

Page {
    required property Account account
    property alias model: list_view.model
    property alias label: label

    focusPolicy: Qt.ClickFocus
    id: self
    background: null
    spacing: constants.p1
    header: GHeader {
        Label {
            id: label
            text: qsTrId('id_assets')
            font.pixelSize: 20
            font.styleName: 'Bold'
        }
        HSpacer {
        }
    }
    contentItem: GListView {
        id: list_view
        clip: true
        model: self.account.balances
        spacing: 0
        implicitHeight: contentHeight
        delegate: AssetDelegate {
            balance: modelData
            width: ListView.view.contentWidth
            onClicked: if (hasDetails) balance_dialog.createObject(window, { balance }).open()
        }
    }

    Component {
        id: balance_dialog
        AssetView {
        }
    }
}
