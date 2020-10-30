import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import UserRepository 1.0
import "."


Item {
    id: _root
    signal changeSource(string source)

    property int loginCount: 0

    UserRepository {
        id: _repository

        onLoginSuccessfully: {
            SingletonHelper.currentUser = user;
            if (user.isFirstLogin()) {
                _firstLoginWindow.show();

            } else {
                loginCount = 0;
                _loginStatus.text = "";
                _root.changeSource("workspace.qml");
            }
        }

        onLoginError: {
            loginCount = loginCount + 1;
            if (loginCount == 3) {
                applicationWindow.close()
            }

            _loginStatus.text = errorMessage + qsTr("Попыток: ") + (3 - loginCount);

        }
    }

    FirstLoginWindow {
        id: _firstLoginWindow

        onUserLogin: {
            loginCount = 0;
            _loginStatus.text = "";
            _loginField.text = "";
            _passwordField.text = "";
        }

        onUserCancel: {
            console.log("Cancel the user login when the user was first logged in")
        }
    }


    Pane {
        anchors.centerIn: parent
        horizontalPadding: 30
        Material.elevation: 4

        ColumnLayout {

            Text {
                text: qsTr("Логин пользователя")
                font.pointSize: 9
            }

            TextField {
                id: _loginField
                placeholderText: qsTr("Логин")
                selectByMouse: true
                Layout.preferredWidth: 250
            }

            Text {
                text: qsTr("Пароль")
                font.pointSize: 9
                Layout.topMargin: 10
            }

            TextField {
                id: _passwordField
                placeholderText: "********"
                echoMode: TextInput.Password
                passwordCharacter: "*"
                selectByMouse: true
                Layout.preferredWidth: 250
            }

            Text {
                id: _loginStatus
                color: Material.color(Material.Red)
            }

            Button {
                text: qsTr("Вход")
                highlighted: true
                Layout.topMargin: 5

                onClicked: {
                    if (_loginField.text.length == 0) {
                        _loginStatus.text = qsTr("Пустое поле с логином");

                    } else {
                        _repository.login(_loginField.text, _passwordField.text);
                    }
                }
            }
        }
    }
}



