import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12

import UserRepository 1.0

Window {
    id: _root
    title: qsTr("Создание пользователя")
    modality: Qt.WindowModal
    minimumWidth: 350
    minimumHeight: 250

    signal userCreated()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: qsTr("Имя нового пользователя")
            font.pointSize: 9
        }

        TextField {
            id: _userLogin
            Layout.fillWidth: true
            placeholderText: "Логин"
            selectByMouse: true
            Layout.preferredWidth: 250
            Layout.bottomMargin: 10
        }

        Text {
            text: qsTr("Пароль (не обязательно)")
            font.pointSize: 9
        }

        TextField {
            id: _userPassword
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
                text: qsTr("Создать")
                highlighted: true

                onClicked: {
                    _repository.create(_userLogin.text, _userPassword.text);
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
        id: _createDialog
        title: qsTr("Добавление пользователя")
        width: 320
        height: 140
        visible: false

        contentItem: ColumnLayout {

            anchors.fill: parent
            anchors.margins: 10
            spacing: 2

            Text {
                text: qsTr("Новый пользователь успешно добавлен!")
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
                    _createDialog.close();
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

        onCreateSuccessfully: {
            _root.userCreated();
            _createDialog.visible = true;
        }

        onCreateError: {
            _error.text = errorMessage;
        }
    }
}
