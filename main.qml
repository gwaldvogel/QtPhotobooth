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
                    photoPreview.displayed = false;
                    photoPreview.source = '';

                }
                else
                {
                    camera.imageCapture.capture();
                }
            }
        }
    }
    Image {
        id: photoPreview
        property bool displayed: false
        anchors.fill: parent
    }
}
