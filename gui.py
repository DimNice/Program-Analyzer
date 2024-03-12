from PyQt5.QtWidgets import *
import re
from collections import defaultdict
import test_libs
class FileInfo:
    def __init__(self, path, source):
        self.path = path
        self.source = source
        self.detectors = set()
        self.vulns = defaultdict(list)  # a set of lines for each vuln_code

        # Parse vulnerability markers.
        # Lines like "// !test vuln_code" tell that this detector
        # should be enabled for this file.
        # Lines like "// !vuln vuln_code" show the line with a vulnerability.
        # TODO Make use of "// !novuln".
        for i, line in enumerate(source):
            if m := re.search("// !test (\w+)", line):
                self.detectors.add(m[1])
            elif m := re.search("// !vuln (\w+)", line):
                self.vulns[m[1]].append(i)


class GUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Статический анализатор уязвимостей кода на языке С++")
        self.resize(1280, 1000)
        self.target_files = list()
        self.full_log = ""
        self.gen_test_num = 1

        # buttons
        top_panel = QHBoxLayout()
        col1 = QVBoxLayout()
        top_panel.addLayout(col1)
        col1.addWidget(QLabel("Тестируемые файлы"))
        butt = QPushButton("Добавить")
        butt.clicked.connect(self.openFiles)
        col1.addWidget(butt)
        butt = QPushButton("Исключить")
        butt.clicked.connect(self.deleteFile)
        col1.addWidget(butt)

        col2 = QVBoxLayout()
        top_panel.addLayout(col2)
        col2.addWidget(QLabel("Сгенерировать тест"))
        butt = QPushButton("Случайный")
        butt.clicked.connect(self.genRandTest)
        col2.addWidget(butt)
        butt = QPushButton("С выбранными уязвимостями")
        butt.clicked.connect(self.genRegTest)
        col2.addWidget(butt)

        col3 = QVBoxLayout()
        top_panel.addLayout(col3)
        col3.addWidget(QLabel("Запустить анализ кода"))
        butt = QPushButton("Выбранный файл")
        butt.clicked.connect(self.analyzeOne)
        col3.addWidget(butt)
        butt = QPushButton("Все файлы")
        butt.clicked.connect(self.analyzeAll)
        col3.addWidget(butt)

        col4 = QVBoxLayout()
        top_panel.addLayout(col4)
        col4.addWidget(QLabel("Сохранить на диск"))
        butt = QPushButton("Выбранный файл")
        butt.clicked.connect(self.saveFile)
        col4.addWidget(butt)
        butt = QPushButton("Лог действий")
        butt.clicked.connect(self.saveLog)
        col4.addWidget(butt)

        # file list
        left_panel = QVBoxLayout()
        left_panel.addWidget(QLabel("Путь к файлу:"))
        self.file_list = QListWidget()
        self.file_list.clicked.connect(self.showFileContent)
        left_panel.addWidget(self.file_list)

        # vulnerabilities
        left_panel.addWidget(QLabel("Выберите уязвимости для поиска:"))
        self.vulns = {k: QCheckBox(v) for k, v in test_libs.vuln_dict.items()}
        for cb in self.vulns.values():
            left_panel.addWidget(cb)

        # code display
        right_panel = QVBoxLayout()
        self.code_label = QLabel()
        right_panel.addWidget(self.code_label)
        self.code_text = QTextEdit()
        self.code_text.setFontFamily("monospace")
        self.code_text.setReadOnly(True)
        right_panel.addWidget(self.code_text)

        # log
        self.log = QTextEdit()
        self.log.setReadOnly(True)
        self.log.setFontFamily("monospace")
        self.log.append("Добро пожаловать в анализатор уязвимостей от бригады №4 группы 6411!")

        # combined layout
        panels = QHBoxLayout()
        panels.addLayout(left_panel, 25)
        panels.addLayout(right_panel, 75)
        layout = QVBoxLayout()
        layout.addLayout(top_panel)
        layout.addLayout(panels)
        layout.addWidget(self.log)
        self.setLayout(layout)

        self.showFileContent()
        self.show()

    def openFiles(self):
        paths, _ = QFileDialog.getOpenFileNames(self, None, "tests/")
        for file_path in paths:
            with open(file_path) as f:
                source = f.read().split("\n")
            self.addFile(FileInfo(file_path, source))

    def addFile(self, file):
        self.file_list.addItem(file.path)
        self.file_list.setCurrentRow(self.file_list.count() - 1)
        self.target_files.append(file)
        self.showFileContent()

    def deleteFile(self):
        row = self.file_list.currentRow()
        if row != -1:
            self.file_list.takeItem(row)
            self.target_files.pop(row)
            self.showFileContent()

    def genRandTest(self):
        self.genTest(None)

    def genRegTest(self):
        self.genTest([name for name, cb in self.vulns.items() if cb.isChecked()])

    def genTest(self, vulns):
        source = TestGenerator.gen_test(vulns).split("\n")
        self.addFile(FileInfo(f"gen-tests/test{self.gen_test_num}.cpp", source))
        self.gen_test_num += 1