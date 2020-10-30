import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import UserRepository 1.0
import User 1.0
import "."

ApplicationWindow {
    id: applicationWindow
    minimumWidth: 1000
    minimumHeight: 600
    visible: true
    title: qsTr("Laboratory work")

    // Material.accent: Material.Purple

    header: ToolBar {

        RowLayout {
            anchors.fill: parent

            // Space item
            Text {
                id: _toolbarTitle
                text: qsTr("Авторизация")
                font.pointSize: 14
                color: "#FFFFFF"
                Layout.fillWidth: true
                Layout.leftMargin: 16
            }

            // Info button
            ToolButton {
                id: _infoButton
                text: qsTr("Справка")
                display: AbstractButton.IconOnly
                icon.source: "qrc:///icons/info_button.png"
                onClicked: _infoMenu.open()

                Menu {
                    id: _infoMenu
                    y: _infoButton.height

                    MenuItem {
                        text: qsTr("О программе")
                        onClicked: {
                            var component = Qt.createComponent("about.qml");
                            var window = component.createObject(applicationWindow);
                            window.show();
                        }
                    }
                }
            }
        }
    }

    PassphraseWindow {
        id: _passphraseWindow

        onPassphraseError: {
            console.log("Exit...");
            applicationWindow.close();
        }
    }

    Timer {
        id: _timer
        interval: 200
        onTriggered: {
            _passphraseWindow.show();
        }
    }

    Loader {
        id: _mainLoader
        anchors.fill: parent
        source: "login.qml"
    }

    Connections {
        target: _mainLoader.item
        ignoreUnknownSignals: true

        function onChangeSource(source) {
            _mainLoader.source = source;
        }
    }

    Connections {
        target: SingletonHelper

        function onCurrentUserChanged() {
            if (SingletonHelper.currentUser.isNull()) {
                _toolbarTitle.text = qsTr("Авторизация");
            } else {
                _toolbarTitle.text = qsTr("Рабочее пространство");
            }
        }
    }

    Component.onCompleted: {
        _timer.start()
    }
}
