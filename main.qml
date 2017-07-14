import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.7

Window {
    id: window
    visible: true
    title: "Raspberry Pi Photobooth"

    minimumWidth: 720
    minimumHeight: 480

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
            onClicked: {
                if(photoPreview.displayed) {
                    resetPreview();
                }
                else
                {
                    countdown.start();
                }
            }
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
        interval: 10000
        onTriggered: resetPreview()
    }

    function resetPreview()
    {
        if(photoPreview.displayed) {
            photoPreview.displayed = false;
            photoPreview.source = '';
        }
    }
}
