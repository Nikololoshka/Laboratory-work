import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import UserRepository 1.0
import "."


ColumnLayout {
    spacing: 8

    RowLayout {
        Layout.preferredHeight: 50
        Text {
            text: qsTr("Список пользователей")
            font.bold: true
            font.pointSize: 14
            bottomPadding: 10
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Добавить пользователя")
            icon.source: "qrc:///icons/add.png"
            highlighted: true

            onClicked: {
                _createDialog.show();
            }
        }
    }

    ListView {
        id: _users
        Layout.fillHeight: true
        Layout.fillWidth: true
        clip: true
        ScrollBar.vertical: ScrollBar {
            active: true
            policy: ScrollBar.AsNeeded
        }

        model: _repository.users()

        delegate: Button {

            contentItem: ColumnLayout {
                spacing: 8

                Text {
                    text: (modelData.isAdmin() ? qsTr("Администратор") :
                                                 qsTr("Пользователь")) + ": " + modelData.userLogin()
                    font.pointSize: 11
                }

                RowLayout {
                    spacing: 8

                    Text {
                        text: qsTr("Статус доступа: ") +
                              (modelData.isBlocked() ? "<font color='#AA0000'>" + qsTr("заблокирован") + "</font>" :
                                                  "<font color='#00AA00'>" + qsTr("доступ разрешен") + "</font>")
                        textFormat: Text.RichText
                        font.pointSize: 10
                    }

                    Text {
                        text: qsTr("Ограничение на пароль: ") +
                              (modelData.isPasswordLimit() ? "<font color='#00AA00'>" + qsTr("включено") + "</font>" :
                                                        "<font color='#AA0000'>" + qsTr("отключено") + "</font>")
                        textFormat: Text.RichText
                        font.pointSize: 10
                    }
                }

                Rectangle {
                    color: Material.color(Material.Grey)
                    Layout.preferredHeight: 1
                    Layout.fillWidth: true
                }
            }

            flat: true
            width: _users.width

            onClicked: {
                _editDialog.userLogin = modelData.userLogin();
                _editDialog.show();
            }
        }

        onCountChanged: {
            if (_users.count == 0) {
                _users.visible = false;
                _emptyLabel.visible = true;
            } else {
                _users.visible = true;
                _emptyLabel.visible = false;
            }
        }
    }

    Item {
        id: _emptyLabel
        visible: false
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            text: qsTr("Список пуст")
            font.pointSize: 14
            anchors.centerIn: parent
        }
    }

    CreateUserWindow {
        id: _createDialog
        onUserCreated: {
            _users.model = _repository.users();
        }
    }

    EditUserWindow {
        id: _editDialog
        onUserUpdated: {
            _users.model = _repository.users();
        }
    }

    UserRepository {
        id: _repository
    }
}

/*##^##
Designer {
    D{i:0;height:600;width:400}
}
##^##*/
