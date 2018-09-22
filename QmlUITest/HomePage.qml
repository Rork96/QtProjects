import QtQuick 2.4
import QtQuick.Dialogs 1.2

HomePageForm {
    login.onClicked: {
        var msg = "Your login: " + email.text + "\r\nYour password: " + password.text

        dlg.text = msg
        dlg.open()
    }

    password.echoMode: TextInput.Password

    MessageDialog {
        id: dlg
        title: "Login information"
        onAccepted: MessageDialog.Apply
    }
}
