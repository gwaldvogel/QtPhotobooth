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
        imageCapture.onImageSaved: {
            console.log('Image saved', path);
            cloud.uploadPhoto(path);
        }
    }

    VideoOutput {
        source: camera
        anchors.fill: parent
        focus: visible
        MouseArea {
            anchors.fill: parent
            onClicked: trigger()
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

    Image {
        source: "qrc:/power.png"
        width: 24
        height: 24
        opacity: 0.1
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    function resetPreview()
    {
        if(photoPreview.displayed) {
            photoPreview.displayed = false;
            photoPreview.source = '';
            console.log('Resetting preview');
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
        onButtonPressedChanged: {
            if(raspberry.buttonPressed) {
                trigger();
            }
        }
    }
}
