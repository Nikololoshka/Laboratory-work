import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12


RowLayout {
    id: _root
    spacing: 4

    signal changeSource(string source)

    Pane {
        Layout.minimumWidth: 200
        Layout.fillHeight: true
        Material.elevation: 4

        ListView {
            id: _drawerMenu
            anchors.fill: parent

            delegate: Button {

                contentItem: Row {
                    spacing: 8

                    Image {
                        source: modelData.iconpath
                        width: 24
                        height: 24
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.name
                        font.pointSize: 12
                        font.capitalization: Font.Capitalize
                    }
                }

                flat: true
                width: _drawerMenu.width
                // visible: SingletonHelper.currentUser.isAdmin() || !requiredAdmin

                onClicked: {
                    _drawerMenu.elementClicked(modelData.event)
                }

            }

            property var menuModel: [
                {
                    event: "profile",
                    name: qsTr("Профиль"),
                    iconpath: "qrc:///icons/profile.png",
                    requiredAdmin: false
                },
                {
                    event: "users",
                    name: qsTr("Пользователи"),
                    iconpath: "qrc:///icons/users.png",
                    requiredAdmin: true
                },
                {
                    event: "exit",
                    name: qsTr("Выход"),
                    iconpath: "qrc:///icons/exit.png",
                    requiredAdmin: false
                }
            ]

            model: updateMenu()

            function elementClicked(event) {
                switch (event) {
                case "profile":
                    _contentLoader.source = "profile.qml"
                    break;

                case "users":
                    _contentLoader.source = "users.qml"
                    break

                case "exit":
                    SingletonHelper.logout();
                    _root.changeSource("login.qml");
                    break
                }
            }

            function updateMenu() {
                var admin = SingletonHelper.currentUser.isAdmin();
                var newMenu = menuModel.filter(item => !item.requiredAdmin || admin);
                return newMenu;
            }
        }
    }

    Loader {
        id: _contentLoader
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 16

        source: "profile.qml"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
