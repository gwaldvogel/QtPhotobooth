import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: settings

    property bool shown: false
    visible: false

    anchors.fill: parent
    color: 'white'

    Item {
        anchors.fill: parent
        anchors.margins: 20

        Column {
            Text {
                text: "Anzahl an Bilder:"
            }

            Row {
                ExclusiveGroup {
                    id: photoCount
                }
                RadioButton {
                    text: "1"
                    checked: true
                    exclusiveGroup: photoCount
                }
                RadioButton {
                    text: "2"
                    exclusiveGroup: photoCount
                }
                RadioButton {
                    text: "3"
                    exclusiveGroup: photoCount
                }
            }
        }
    }

    transitions: Transition {
        PropertyAnimation {
            properties: "visible"; easing.type: Easing.InOutQuad
        }
    }

    function show() {
        settings.visible = true;
    }

    function hide() {
        settings.visible = false;
    }

    function toggle() {
        if(shown)
            hide();
        else
            show();
    }
}
