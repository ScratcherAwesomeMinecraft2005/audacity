import QtQuick

Item {
    id: root

    property alias active: selRect.visible
    property real minSelection: 12 // px  4left + 4 + 4right

    signal selected(x1 : real, x2 : real)
    signal reset()

    Rectangle {
        id: selRect

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        visible: false

        opacity: 0.4
    }

    MouseArea {
        id: selMa
        anchors.fill: parent

        property real startX: 0

        onPressed: function(mouse) {

            if (selRect.visible) {
                root.reset()
            }

            selMa.startX = mouse.x
            selRect.visible = false
            leftMa.enabled = false
            rightMa.enabled = false
        }

        onPositionChanged: function(mouse) {
            var x = mouse.x
            if (x > selMa.startX) {
                selRect.x = selMa.startX
                selRect.width = x - selMa.startX
            } else {
                selRect.x = x
                selRect.width = selMa.startX - x
            }

            selRect.visible = selRect.width > root.minSelection
        }

        onReleased: {
            if (selRect.visible) {
                root.selected(selRect.x, selRect.x + selRect.width)

                leftMa.x = selRect.x
                leftMa.enabled = true

                rightMa.x = selRect.x + selRect.width - rightMa.width
                rightMa.enabled = true
            }
        }
    }

    MouseArea {
        id: leftMa

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: 4
        cursorShape: Qt.SizeHorCursor

        property real startX: 0
        property real startW: 0

        onPressed: function(mouse) {
            leftMa.cursorShape = Qt.ArrowCursor
            leftMa.startX = selRect.x
            leftMa.startW = selRect.width
        }

        onPositionChanged: function(mouse) {
            var newWidth = leftMa.startW + (mouse.x * -1)
            if (newWidth > root.minSelection) {
                selRect.x = leftMa.startX + mouse.x
                selRect.width = newWidth
            }
        }

        onReleased: {
            root.selected(selRect.x, selRect.x + selRect.width)
            leftMa.x = selRect.x
            leftMa.cursorShape = Qt.SizeHorCursor
        }
    }

    MouseArea {
        id: rightMa

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: 4
        cursorShape: Qt.SizeHorCursor

        property real startX: 0
        property real startW: 0

        onPressed: function(mouse) {
            rightMa.cursorShape = Qt.ArrowCursor
            rightMa.startW = selRect.width
        }

        onPositionChanged: function(mouse) {
            var newWidth = rightMa.startW + mouse.x
            if (newWidth > root.minSelection) {
                selRect.width = newWidth
            }
        }

        onReleased: {
            root.selected(selRect.x, selRect.x + selRect.width)
            rightMa.x = selRect.x + selRect.width - rightMa.width
            rightMa.cursorShape = Qt.SizeHorCursor
        }
    }
}
