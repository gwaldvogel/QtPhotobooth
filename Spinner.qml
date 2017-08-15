import QtQuick 2.0

Rectangle {
    color: 'black'
    anchors.fill: parent
    Image {
        source: 'cog.png'
        anchors.centerIn: parent
        RotationAnimation on rotation {
            loops: Animation.Infinite
            from: 0
            to: 360
            duration: 3600
        }
    }

}
