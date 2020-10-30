import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12

import UserRepository 1.0


Window {
    id: _root
    title: qsTr("Редактирование пользователя")
    modality: Qt.WindowModal
    minimumWidth: 450
    minimumHeight: 250

    signal userUpdated()
    property string userLogin: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: qsTr("Имя пользователя")
            font.pointSize: 9
        }

        TextField {
            id: _userLogin
            Layout.fillWidth: true
            placeholderText: "Логин"
            selectByMouse: true
            Layout.preferredWidth: 250
        }

        Text {
            id: _error
            color: Material.color(Material.Red)
        }

        GridLayout {
            columns: 2

            Switch {
                id: _blocked
                text: qsTr("Блокировка")
                Layout.fillWidth: true
            }

            Switch {
                id: _passwordLimit
                text: qsTr("Парольное ограничение")
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Row {
            spacing: 12

            Button {
                text: qsTr("Изменить")
                highlighted: true
                icon.source: "qrc:///icons/edit_user.png"

                onClicked: {
                    _repository.updateUser(userLogin, _userLogin.text, _blocked.checked, _passwordLimit.checked);
                }
            }

            Button {
                text: qsTr("Удалить")
                highlighted: true
                icon.source: "qrc:///icons/remove_user.png"

                onClicked: {
                    _repository.removeUser(userLogin);
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

    UserRepository {
        id: _repository

        onUserUpdatedSuccessfully: {
            _root.userUpdated();
            _root.close();
        }

        onUserUpdatedError: {
            _error.text = errorMessage;
        }

        onUserRemoved: {
            _root.userUpdated();
            _root.close();
        }
    }

    onUserLoginChanged: {
        var user = _repository.user(userLogin);
        _userLogin.text = userLogin;

        _blocked.checked = user.isBlocked();
        _passwordLimit.checked = user.isPasswordLimit();
    }
}
