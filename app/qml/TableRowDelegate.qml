import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    height: 30
    property string fileNameValue: ""
    property int uploadProgress: 0
    property bool isFinished: false
    property bool isErrored: false

    Rectangle {
        id: background
        anchors.fill: parent
        opacity: 0.6
        states: [
            State {
                name: "IN_PROGRESS"
                when: !isFinished && !isErrored
                PropertyChanges {
                    target: background
                    color: "blue"
                }
            },
            State {
                name: "IS_ERROR"
                when: isFinished && isErrored
                PropertyChanges {
                    target: background
                    color: "red"
                }
            },
            State {
                name: "SUCCESS_UPLOAD"
                when: isFinished && !isErrored
                PropertyChanges {
                    target: background
                    color: "green"
                }
            }
        ]
    }

    Row {
        anchors.fill: parent
        Rectangle {
            height: parent.height
            width: parent.width * 0.5
            border.color: "black"
            Text {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 5
                    rightMargin: 5
                }
                text: root.fileNameValue
            }
        }
        Rectangle {
            height: parent.height
            width: parent.width * 0.5
            border.color: "black"
            color: "transparent"
            ProgressBar {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 5
                    rightMargin: 5
                    verticalCenter: parent.verticalCenter
                }
                from: 0
                to: 100
                value: root.uploadProgress
            }
        }
    }
}
