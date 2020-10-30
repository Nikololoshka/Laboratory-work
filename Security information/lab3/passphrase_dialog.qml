import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12

import UserRepository 1.0


Window {
    id: _root
    title: qsTr("Ввод парольной фразы")
    modality: Qt.WindowModal
    minimumWidth: 350
    minimumHeight: 250
    flags: Qt.Window | Qt.WindowTitleHint

    signal passphraseError()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: qsTr("Парольная фраза")
            font.pointSize: 9
        }

        TextField {
            id: _passPhrase
            Layout.fillWidth: true
            placeholderText: "********"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            selectByMouse: true
            Layout.preferredWidth: 250
            Layout.bottomMargin: 10
        }

        Item {
            Layout.fillHeight: true
        }

        Row {
            spacing: 10

            Button {
                text: qsTr("Войти")
                highlighted: true

                onClicked: {
                    _repository.setPassphrase(_passPhrase.text);
                }
            }

            Button {
                text: qsTr("Отмена")

                onClicked: {
                    _root.close();
                    _root.passphraseError();
                }
            }
        }
    }

    UserRepository {
        id: _repository

        onPassphraseValid: {
            _root.close();
            if (!valid) {
                _root.passphraseError();
            }
        }
    }
}
