import sys
from PyQt4 import QtCore, QtGui

app = QtGui.QApplication(sys.argv)

widget = QtGui.QWidget()
widget.resize(250, 250)
widget.setWindowTitle("Test")
widget.show()

sys.exit(app.exec_())
