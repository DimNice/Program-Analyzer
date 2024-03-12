import sys

from PyQt5.QtWidgets import QApplication

from gui import GUI

app = QApplication(sys.argv)
gui = GUI()
sys.exit(app.exec_())
