import QtQuick

Window {
    objectName: "mainWindow"
    width: 400
    height: 400
    visible: true

    // Hide the window instead of closing it when the close button is clicked
    // @disable-check M16
    onClosing: close => {
                   hide()
                   close.accepted = false
               }
}
