import QtQuick 2.12
import QtQuick.Window 2.12
import amf1k.models 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15

Window {
    id: root
    width: 1024
    height: 800
    visible: true
    title: Qt.application.name

    DownloaderModel {
        id: downloaderModel
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: true
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            downloaderModel.upload(fileDialog.fileUrl)
        }
        onRejected: {
            console.log("Canceled choose file or directory")
        }
    }

    Row {
        id: controlRow
        anchors {
            top: parent.top
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 15
        Button {
            id: downloadBtn
            text: "Download"
            onClicked: {
                fileDialog.visible = true
            }
        }
        ComboBox {
            textRole: "text"
            valueRole: "selectFolder"
            Component.onCompleted: currentIndex = indexOfValue(
                                       fileDialog.selectFolder)
            onActivated: fileDialog.selectFolder = currentValue
            model: ListModel {
                ListElement {
                    text: "Upload File"
                    selectFolder: false
                }
                ListElement {
                    text: "Upload Directory"
                    selectFolder: true
                }
            }
        }
    }

    ListView {
        id: fileList
        anchors {
            top: controlRow.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 15
        }
        model: downloaderModel
        clip: true
        delegate: TableRowDelegate {
            width: fileList.width
            fileNameValue: model.name
            uploadProgress: model.uploadProgress
            isFinished: model.isFinished
            isErrored: model.isErrored
        }
    }
}
