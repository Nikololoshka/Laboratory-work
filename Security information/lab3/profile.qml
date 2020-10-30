import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import UserRepository 1.0


Column {
    spacing: 8

    Text {
        text: qsTr("Данные профиля")
        font.bold: true
        font.pointSize: 14
        bottomPadding: 10
    }

    Text {
        id: _user
        font.pointSize: 11
    }

    Text {
        id: _role
        font.pointSize: 11
    }

    Text {
        id: _blocked
        textFormat: Text.RichText
        font.pointSize: 11
    }

    Text {
        id: _passwordLimit
        textFormat: Text.RichText
        font.pointSize: 11
    }

    Button {
        text: qsTr("Изменить пароль")
        font.capitalization: Font.Capitalize
        icon.source: "qrc:///icons/edit.png"

        onClicked: {
            var component = Qt.createComponent("change_password.qml");
            var window = component.createObject(applicationWindow);
            window.show();
        }
    }


    Component.onCompleted: {
        var user = SingletonHelper.currentUser;

        _user.text = qsTr("Пользователь: ") + user.userLogin();
        _role.text = qsTr("Роль: ") + (user.isAdmin() ? qsTr("администратор") : qsTr("пользователь"))
        _blocked.text = qsTr("Статус доступа: ") +
                (user.isBlocked() ? "<font color='#AA0000'>" + qsTr("заблокирован")     + "</font>" :
                                    "<font color='#00AA00'>" + qsTr("доступ разрешен") + "</font>");
        _passwordLimit.text = qsTr("Ограничение на пароль: ") +
                (user.isPasswordLimit() ? "<font color='#00AA00'>" + qsTr("включено") + "</font>" :
                                          "<font color='#AA0000'>" + qsTr("отключено") + "</font>");

        _blocked.visible = !user.isAdmin();
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
