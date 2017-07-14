import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.7

Window {
    id: window

    property bool cooldown: false

    visible: true
    title: "Raspberry Pi Photobooth"

    minimumWidth: 720
    minimumHeight: 480

    color: 'black'

    Camera {
        id: camera
        imageCapture.onImageCaptured: {
            photoPreview.source = preview
            photoPreview.displayed = true;
        }
    }

    VideoOutput {
        source: camera
        anchors.fill: parent
        focus: visible
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    Image {
        id: photoPreview
        property bool displayed: false
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    Countdown {
        id: countdown
        anchors.fill: parent
        onFinished: {
            camera.imageCapture.capture();
            resetPreviewTimer.start();
        }
    }

    Timer {
        id: resetPreviewTimer
        interval: 30000
        onTriggered: resetPreview()
    }

    Timer {
        id: cooldownTimer
        interval: 5000
        onTriggered: {
            window.cooldown = false;
        }
    }

    function resetPreview()
    {
        if(photoPreview.displayed) {
            photoPreview.displayed = false;
            photoPreview.source = '';
        }
    }

    function trigger()
    {
        if(!window.cooldown && !countdown.running && !resetPreviewTimer.running)
        {
            console.log('Triggered', 'Preview:', photoPreview.displayed);
            if(photoPreview.displayed) {
                resetPreview();
            }
            else
            {
                countdown.start();
            }
        }
        window.cooldown = true;
        cooldownTimer.start();
    }

    Connections {
        target: raspberry
        onButtonPressedChanged: trigger()
    }
}
