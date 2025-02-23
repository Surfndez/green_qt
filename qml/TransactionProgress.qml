import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ProgressIndicator {
    required property string icon

    id: self

    Loader {
        opacity: 1 - check_image.opacity
        active: self.current < self.max
        anchors.centerIn: parent
        sourceComponent: RowLayout {
            spacing: 0
            Label {
                text: Math.min(self.current, self.max)
                font.pixelSize: 16
                font.family: 'Roboto'
                font.styleName: 'Light'
            }
            Label {
                Layout.alignment: Qt.AlignBottom
                text: '/' + self.max
                font.pixelSize: 12
                font.family: 'Roboto'
                font.styleName: 'Light'
            }
        }
    }

    Image {
        id: check_image
        opacity: self.current < self.max ? 0 : 1
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.OutCubic
                duration: 500
            }
        }

        source: self.icon
        anchors.centerIn: parent
        sourceSize.width: 24
        sourceSize.height: 24
    }
}
