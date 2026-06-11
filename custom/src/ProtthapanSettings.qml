import QtQuick
import QtQuick.Controls
import QGroundControl.Controls
import QGroundControl.Palette

Rectangle {
    color: "#050A07"

    Column {
        anchors.fill: parent
        anchors.margins: 28
        spacing: 18

        Row {
            spacing: 18
            Image {
                source: "qrc:/custom/res/Images/protthapan-logo-toolbar.png"
                width: 140
                height: 70
                fillMode: Image.PreserveAspectFit
            }
            Column {
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    text: "Protthapan Technologies"
                    color: "#00FF88"
                    font.pixelSize: 26
                    font.bold: true
                }
                Text {
                    text: "Ground Control System Settings"
                    color: "#00D4FF"
                    font.pixelSize: 16
                }
            }
        }

        Rectangle { width: parent.width; height: 1; color: "#1FFF9A" }

        Text { text: "Theme"; color: "#00FF88"; font.pixelSize: 18; font.bold: true }
        Text { text: "Futuristic tactical dark interface with map-first workflow."; color: "#D8FFE6"; font.pixelSize: 14 }

        Text { text: "Enabled Modules"; color: "#00FF88"; font.pixelSize: 18; font.bold: true }
        Text { text: "Mapping, telemetry, vehicle status, operator-supervised mission monitoring."; color: "#D8FFE6"; font.pixelSize: 14 }

        Text { text: "Recommended Toolbar Items"; color: "#00FF88"; font.pixelSize: 18; font.bold: true }
        Text { text: "Logo, Connect, Map, Mode, Arm Status, GPS, Battery, Telemetry Link, RTL/Land."; color: "#D8FFE6"; font.pixelSize: 14 }

        Rectangle {
            width: parent.width
            height: 82
            radius: 10
            color: "#AA0E1A12"
            border.color: "#00FF88"
            border.width: 1
            Text {
                anchors.centerIn: parent
                text: "Protthapan Technologies | Where Innovations Take Flight"
                color: "#D8FFE6"
                font.pixelSize: 18
                font.bold: true
            }
        }
    }
}
