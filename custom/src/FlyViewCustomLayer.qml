import QtQuick
import QtQuick.Controls
import QGroundControl
import QGroundControl.Controls
import QGroundControl.Palette

Item {
    anchors.fill: parent

    readonly property color tacticalBg: "#AA050A07"
    readonly property color tacticalPanel: "#CC0E1A12"
    readonly property color accentGreen: "#00FF88"
    readonly property color accentCyan: "#00D4FF"
    readonly property color textColor: "#D8FFE6"
    readonly property color warnAmber: "#FFB000"

    // Top identity strip. This is intentionally an overlay, so it is less likely
    // to break across different QGroundControl versions than replacing MainToolBar.qml.
    Rectangle {
        id: topIdentity
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 14
        width: Math.min(parent.width * 0.72, 820)
        height: 58
        radius: 10
        color: tacticalBg
        border.color: accentGreen
        border.width: 1

        Row {
            anchors.centerIn: parent
            spacing: 14

            Image {
                source: "qrc:/custom/res/Images/protthapan-logo-toolbar.png"
                width: 120
                height: 44
                fillMode: Image.PreserveAspectFit
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 1

                Text {
                    text: "PROTTHAPAN TECHNOLOGIES"
                    color: accentGreen
                    font.pixelSize: 18
                    font.bold: true
                    letterSpacing: 1.4
                }

                Text {
                    text: "TACTICAL GROUND CONTROL SYSTEM"
                    color: accentCyan
                    font.pixelSize: 12
                    letterSpacing: 1.2
                }
            }
        }
    }

    // Left mission panel
    Rectangle {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 22
        width: 265
        height: 210
        radius: 12
        color: tacticalPanel
        border.color: accentGreen
        border.width: 1

        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 10

            Text {
                text: "MAP OPERATIONS"
                color: accentGreen
                font.bold: true
                font.pixelSize: 17
                letterSpacing: 1.2
            }

            Rectangle { width: parent.width; height: 1; color: "#335544" }

            Text { text: "View: Mapping + Telemetry"; color: textColor; font.pixelSize: 14 }
            Text { text: "Status: Vehicle Monitor"; color: textColor; font.pixelSize: 14 }
            Text { text: "Mode: Operator Supervised"; color: warnAmber; font.pixelSize: 14 }
            Text { text: "Theme: Tactical Dark"; color: accentCyan; font.pixelSize: 14 }
        }
    }

    // Right compact radar style visual indicator
    Item {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 34
        anchors.bottomMargin: 34
        width: 178
        height: 178

        Rectangle {
            anchors.fill: parent
            radius: width / 2
            color: "#2200FF88"
            border.color: accentGreen
            border.width: 2
        }
        Rectangle {
            anchors.centerIn: parent
            width: 118
            height: 118
            radius: 59
            color: "transparent"
            border.color: "#6600D4FF"
            border.width: 1
        }
        Rectangle {
            anchors.centerIn: parent
            width: 58
            height: 58
            radius: 29
            color: "transparent"
            border.color: "#6600FF88"
            border.width: 1
        }
        Rectangle { anchors.horizontalCenter: parent.horizontalCenter; y: 0; width: 1; height: parent.height; color: "#6600FF88" }
        Rectangle { anchors.verticalCenter: parent.verticalCenter; x: 0; width: parent.width; height: 1; color: "#6600FF88" }

        Text {
            anchors.centerIn: parent
            text: "MAP
LOCK"
            color: accentGreen
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 16
            font.bold: true
            letterSpacing: 1.0
        }
    }
}
