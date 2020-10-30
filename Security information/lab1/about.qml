import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window {
    id: root
    modality: Qt.WindowModal
    minimumWidth: 350
    minimumHeight: 250
    title: qsTr("О программе")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 2

        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true

            textFormat: Text.RichText
            font.pointSize: 10
            wrapMode: Text.WordWrap
            text: qsTr("Автор программы: <b>Верещагин Н.М.</b> <br><br>
                        Индивидульное задание:
                        <ul>
                            <li>
                                1 ЛР: наличие цифр и знаков арифметических операций
                            </li>
                            <li>
                                2 ЛР: блочный тип шифрования, режим шифрования - электронная
                                кодовая книга, добавление к ключю случайное значение, алгорит - MD4
                            </li>
                        </ul>
                       ")
        }

        Button {
            Layout.alignment: Qt.AlignRight

            text: qsTr("Выйти")
            highlighted: true
            font.capitalization: Font.Capitalize

            onClicked: {
                root.close()
            }
        }
    }
}
