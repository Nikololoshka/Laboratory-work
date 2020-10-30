import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12

import UserRepository 1.0

Window {
    id: _root
    title: qsTr("Смена пароля")
    modality: Qt.WindowModal
    minimumWidth: 450
    minimumHeight: 350

    signal userLogin()
    signal userCancel()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: qsTr("Старый пароль")
            font.pointSize: 9
            Layout.topMargin: 10
        }

        TextField {
            id: _oldPassword
            Layout.fillWidth: true
            placeholderText: "********"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            selectByMouse: true
            Layout.preferredWidth: 250
            Layout.bottomMargin: 10
        }

        Text {
            text: qsTr("Новый пароля")
            font.pointSize: 9
            Layout.topMargin: 10
        }

        TextField {
            id: _newPassword
            Layout.fillWidth: true
            placeholderText: "********"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            selectByMouse: true
            Layout.preferredWidth: 250
            Layout.bottomMargin: 10
        }

        Text {
            text: qsTr("Повторите пароль")
            font.pointSize: 9
            Layout.topMargin: 10
        }

        TextField {
            id: _newPasswordConfirm
            Layout.fillWidth: true
            placeholderText: "********"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            selectByMouse: true
            Layout.preferredWidth: 250
            Layout.bottomMargin: 10
        }

        Text {
            id: _error
            color: Material.color(Material.Red)
        }

        Item {
            Layout.fillHeight: true
        }

        Row {
            spacing: 10

            Button {
                text: qsTr("Установить")
                highlighted: true
                onClicked: {
                    _repository.firstLogin(
                                _oldPassword.text,
                                _newPassword.text,
                                _newPasswordConfirm.text
                                );
                }
            }

            Button {
                text: qsTr("Отмена")
                onClicked: {
                    _root.userCancel();
                    _root.close();
                }
            }
        }
    }

    UserRepository {
        id: _repository

        onChangePasswordSuccessfully: {
            _root.userLogin();
            _root.close();
        }

        onChangePasswordError: {
            _error.text = errorMessage;
        }
    }
}
