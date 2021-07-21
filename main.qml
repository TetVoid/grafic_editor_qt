import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls
import QtQuick.Layouts
import Figure 1.0 
import Qt.labs.platform 1.1

ApplicationWindow {
    visible: true
    width: 1000
    height: 480
    title: qsTr("Hello World")

    

    QFigureDrawer {
        id: aFigureDrawer
       
        width: parent.width
        height: parent.height
        

        MouseArea {
        id: ma
        width: parent.width
        height: parent.height
        onPressed: {
            aFigureDrawer.start_create()
        }
        onReleased: {
             aFigureDrawer.stop_create()
        }
        onPositionChanged:{
        aFigureDrawer.update_canvas()
        }
        }
       
    }

    FileDialog {
    id: fileSaveDialog
    currentFile: document.source
    folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    fileMode :FileDialog.SaveFile
    onAccepted:  aFigureDrawer.save(fileSaveDialog.file)
    nameFilters: ["Text files (*.txt)", "Grafic editor files (*.gef)"]
}

 FileDialog {
    id: fileLoadDialog
    currentFile: document.source
    folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    fileMode :FileDialog.OpenFile

    onAccepted: { 
      aFigureDrawer.load(fileLoadDialog.file)
      aFigureDrawer.update_canvas()}
    nameFilters: ["Text files (*.txt)", "Grafic editor files (*.gef)"]
}

     header: ToolBar {
        RowLayout {
            anchors.fill: parent

              Row{
                    ToolButton {
                        width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/circle.png"
                       
                        onClicked: aFigureDrawer.setType("ellips")
                    }
           
                    ToolButton {
                       width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/rect.png"

                        onClicked: aFigureDrawer.setType("rect")
                    }

                       ToolButton {
                        width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/treangle.png"

                        onClicked: aFigureDrawer.setType("triangle")
                    }
            }


              Row {
                    

                      ToolButton {
                        width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/line.png"

                        onClicked: aFigureDrawer.setType("arrow")
                    }

                       ToolButton {
                       width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/hand.png"

                        onClicked: aFigureDrawer.setType("NO")
                    }
              }

                Row {
            

                      ToolButton {
                        width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/load.png"

                        onClicked: fileLoadDialog.open()
                    }
            

                       ToolButton {
                        width: 32
                        height: 32
                        icon.source: "file:///C:/Users/nikbo/Desktop/grafict_editor_v2/imges/save.png"

                        onClicked:  fileSaveDialog.open()
                        
                
                        
                   }


            }
        }
    }
        
    
        
  
}
