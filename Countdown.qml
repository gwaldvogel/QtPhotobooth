import QtQuick 2.0

Item {
    id: countdown
    property int length: 5
    property int current: 0
    property bool running: false

    Rectangle {
        visible: timer.running
        anchors.fill: parent
        color: Qt.rgba(255,255,255,0.3)
        Text {
            text: length - current
            font.pixelSize: countdown.height * 0.5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        onTriggered: (length - 1) == current ? finish() : countUp()
    }

    function finish()
    {
        timer.stop();
        current = 0;
        countdown.running = false;
        finished();
    }

    signal finished()

    function start() {
        countdown.running = true;
        console.log('Starting countdown timer.');
        timer.start();
    }

    function countUp() {
        current++;
        console.log('Countdown', current);
    }
}
