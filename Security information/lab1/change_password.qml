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
    minimumWidth: 350
    minimumHeight: 350

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: qsTr("Старый пароль")
            font.pointSize: 9
        }

        TextField {
            id: _oldPassword
            Layout.fillWidth: true
            placeholderText: "********"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            selectByMouse: true
            Layout.preferredWidth: 250
        }

        Text {
            text: qsTr("Новый пароль")
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
            text: qsTr("Повторите новый пароль")
            font.pointSize: 9
            Layout.topMargin: 10
        }

        TextField {
            id: _confirmNewPassword
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
                text: qsTr("Изменить")
                highlighted: true
                onClicked: {
                    _repository.updateCurrentUserPassword(
                                _oldPassword.text,
                                _newPassword.text,
                                _confirmNewPassword.text
                                );
                }
            }

            Button {
                text: qsTr("Отмена")
                onClicked: {
                    _root.close();
                }
            }
        }
    }

    Dialog {
        id: _passwordChangeDialog
        title: qsTr("Пароль изменен")
        width: 320
        height: 140
        visible: false

        contentItem: ColumnLayout {

            anchors.fill: parent
            anchors.margins: 10
            spacing: 2

            Text {
                text: qsTr("Пароль успешно изменен!")
                textFormat: Text.RichText
                font.pointSize: 10
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Button {
                text: qsTr("ОК")
                highlighted: true
                font.capitalization: Font.Capitalize
                Layout.alignment: Qt.AlignRight

                onClicked: {
                    _passwordChangeDialog.close();
                }
            }
        }

        onVisibleChanged: {
            // if visible - close window
            _root.close();
        }
    }

    UserRepository {
        id: _repository

        onChangePasswordSuccessfully: {
            _passwordChangeDialog.visible = true;
        }

        onChangePasswordError: {
            _error.text = errorMessage;
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
