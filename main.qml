import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.7

Window {
    id: window

    property bool cooldown: false
    property bool twoPictures: true
    property bool secondPicture: false

    property string firstPictureText: "Schritt 1: Rahmen nehmen und bereit machen. \nSchritt 2: Knopf drücken \nSchritt 3: Lächeln!"
    property string secondPictureText: "Und gleich nochmal!"

    visible: true
    title: "Raspberry Pi Photobooth"

    minimumWidth: 720
    minimumHeight: 480

    color: 'black'

    Camera {
        id: camera
        imageCapture.onImageSaved: {

            spinner.visible = false;

            console.log('Image saved', path);
            cloud.uploadPhoto(path);
            if(window.twoPictures && !window.secondPicture)
            {
                trigger(true);
                window.secondPicture = true;
            }
            else
            {
                window.secondPicture = false;
            }
        }
    }

    Item {
        id: container

        anchors.fill: parent
        anchors.margins: 10

        Item {
            id: tutorial

            anchors.left: parent.left
            width: parent.width * 0.5
            height: parent.height
            visible: false

            Text {
                text: !window.secondPicture ? window.firstPictureText : window.secondPictureText
                color: 'white'
                font.pixelSize: 25
                width: parent.width * 0.6
                wrapMode: Text.WordWrap
                anchors.centerIn: parent
            }
        }

        VideoOutput {
            id: videoOutput

            source: camera
            focus: visible
            orientation: 90

            //anchors.left: tutorial.right
            //height: container.height
            //width: container.width * 0.5
            anchors.fill: parent

            Rectangle {
                id:dummyVideo
                anchors.fill: parent
                color: Qt.rgba(0,0,0,1)
                onColorChanged: console.log(color)
                visible: !videoOutput.enabled

                Timer {
                    id: dummyVideoTimer

                    property double r: 0
                    property double g: 0
                    property double b: 0

                    interval: 50
                    running: dummyVideo.visible
                    repeat: true

                    onTriggered: {
                        var rand = Math.random() * 1000;
                        if(rand < 333)
                        {
                            r = r + 0.1;
                            if(r > 1)
                                r = 0;
                        }
                        else if(rand >= 333 && rand < 666)
                        {
                            g = g + 0.1;
                            if(g > 1)
                                g = 0;
                        }
                        else
                        {
                            b = b + 0.1;
                            if(b > 1)
                                b = 0;
                        }
                        dummyVideo.color = Qt.rgba(r,g,b,1);
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: trigger(false)
            }
        }
    }



    Countdown {
        id: countdown
        anchors.fill: parent
        onFinished: {
            spinner.visible = true;
            camera.imageCapture.capture();
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

    Spinner {
        id: spinner
        visible: false
    }

    Timer {
        id: cooldownTimer
        interval: 5000
        onTriggered: {
            window.cooldown = false;
        }
    }


    function trigger(again)
    {
        console.log("Triggered", again);
        if(again)
        {
            window.cooldown = false;
        }

        if(!window.cooldown && !countdown.running)
        {
            if(again)
                countdown.startWithLength(3);
            else
                countdown.start();
        }
        window.cooldown = true;
        cooldownTimer.start();
    }

    Connections {
        target: raspberry
        onButtonPressedChanged: {
            if(raspberry.buttonPressed) {
                trigger(false);
            }
        }
    }
}
