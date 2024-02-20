import sys
import serial.tools.list_ports
import serial
from PyQt6.QtCore import pyqtSignal, QThread
from PyQt6.QtWidgets import QApplication, QLabel, QWidget, QVBoxLayout, \
                            QComboBox, QHBoxLayout, QPushButton, QGridLayout, \
                            QTextEdit, QTImer
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class ParentWindow(QWidget):
    Update = pyqtSignal(str, int, str)  # Assuming parity is a string

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Terminal Window")
        self.setGeometry(600, 400, 600, 400)
        self.PlotWindow = None

        # Initialize Widgets
        self.PortSelect = PortSelection(self)
        self.ConfirmButton = QPushButton("Connect")
        self.PlotButton = QPushButton("Plot")
        self.PlotButton.clicked.connect(self.PlotPopup)
        self.Terminal = TerminalWindow(self)

        # Setup Signals/Slots
        self.ConfirmButton.clicked.connect(self.ChangeDetected)
        self.Update.connect(self.Terminal.connect)

        # Add Everything to Layout
        self.layout = QGridLayout()
        self.setLayout(self.layout)

        self.layout.setColumnStretch(0, 4)  # Give the terminal area more space
        self.layout.setColumnStretch(1, 1)  # Smaller area for the controls

        self.layout.addWidget(self.Terminal, 0, 0, 5, 1)  # Span 5 rows, 1 column

        self.layout.addWidget(self.PortSelect, 0, 1, 1, 1)  # Takes up 1 row, 1 column
        self.layout.addWidget(self.ConfirmButton, 1, 1, 1, 1)  # Same as above
        self.layout.addWidget(self.PlotButton, 2, 1, 1, 1)  # Same as above

        # Timer to refresh the plot
        self.plotRefreshTimer = QTimer(self)
        self.plotRefreshTimer.timeout.connect(self.refreshPlot)
        self.plotRefreshTimer.start(1000)  # Refresh every 1000 ms

        self.setLayout(self.layout)

    def refreshPlot(self):
        if self.PlotWindow:
            self.PlotWindow.update_plot(self.serialData)

    def ChangeDetected(self):
        port, baudrate, parity = self.PortSelect.GetChoices()
        self.Update.emit(port, baudrate, parity)

    def PlotPopup(self, data):
        if self.PlotWindow is None or not self.plotWindow.isVisible():
            self.PlotWindow = PlotWindow()
            self.PlotWindow.show()

            # Example data, replace with actual serial data handling
            example_data = [1, 2, 3, 4, 5]
            self.PlotWindow.update_plot(example_data)
        else:
            self.PlotWindow.raise_()
            self.PlotWindow.activateWindow()


class PlotWindow(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout()
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        layout.addWidget(self.canvas)
        self.setLayout(layout)
        self.ax = self.figure.add_subplot(111)
        self.ax.set_title('Serial Data Plot')
        self.ax.set_xlabel('Sample')
        self.ax.set_ylabel('Value')

    def update_plot(self, data):
        self.ax.clear()
        self.ax.plot(data)
        self.ax.set_title('Serial Data Plot')
        self.ax.set_xlabel('Sample')
        self.ax.set_ylabel('Value')
        self.canvas.draw()


class PortSelection(QWidget):
    def __init__(self, parent: QWidget = None):
        super().__init__(parent)
        self.layout = QVBoxLayout()

        # Find the available ports through the operating systems
        available_ports = [port.device for port in serial.tools.list_ports.comports()]

        # Set up Port Options
        portLayout = QHBoxLayout()
        self.PortDescription = QLabel("Port: ")
        self.PortSelection = QComboBox()
        for port in available_ports:
            self.PortSelection.addItem(port)
        portLayout.addWidget(self.PortDescription)
        portLayout.addWidget(self.PortSelection)

        # Set up Baud Rate Options
        baudRateLayout = QHBoxLayout()
        self.BaudRateDescription = QLabel("Baud Rate: ")
        self.BaudRateSelection = QComboBox()
        common_baud_rates = [1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200]  # Common baud rates
        for rate in common_baud_rates:
            self.BaudRateSelection.addItem(str(rate))
        baudRateLayout.addWidget(self.BaudRateDescription)
        baudRateLayout.addWidget(self.BaudRateSelection)

        # Set up Parity Options
        parityLayout = QHBoxLayout()
        self.ParityDescription = QLabel("Parity: ")
        self.ParitySelection = QComboBox()
        parity_options = ['None', 'Even', 'Odd', 'Mark', 'Space']  # Common parity options
        for parity in parity_options:
            self.ParitySelection.addItem(parity)
        parityLayout.addWidget(self.ParityDescription)
        parityLayout.addWidget(self.ParitySelection)

        # Add Widgets to layout vertically
        self.layout.addLayout(portLayout)
        self.layout.addLayout(baudRateLayout)
        self.layout.addLayout(parityLayout)
        self.setLayout(self.layout)

    def GetChoices(self):
        port = self.PortSelection.currentText()
        baudrate = int(self.BaudRateSelection.currentText())
        parity = self.ParitySelection.currentText()
        return port, baudrate, parity


class SerialThread(QThread):
    """
    This thread is responsible for reading data from the serial port and emitting a signal when data is received.
    """
    received = pyqtSignal(str)

    def __init__(self, serial_instance):
        super().__init__()
        self.serial_instance = serial_instance
        self.running = True

    def run(self):
        while self.running:
            if self.serial_instance.isOpen() and self.serial_instance.in_waiting:
                text = self.serial_instance.read(self.serial_instance.in_waiting).decode('utf-8', 'ignore')
                self.received.emit(text)

    def stop(self):
        self.running = False


class TerminalWindow(QWidget):
    def __init__(self, parent: QWidget = None):
        super().__init__(parent)
        self.activeserial = None
        layout = QVBoxLayout()
        self.textEdit = QTextEdit()
        self.textEdit.setReadOnly(True)  # Make the QTextEdit read-only

        # Create a horizontal layout for the clear button
        topLayout = QHBoxLayout()
        self.clearButton = QPushButton("Clear")
        self.clearButton.clicked.connect(self.clearClicked)
        topLayout.addWidget(self.clearButton)
        topLayout.addStretch()  # This will push the button to the right

        layout.addLayout(topLayout)
        layout.addWidget(self.textEdit)
        self.setLayout(layout)

    def handleChange(self, port, baudrate, parity):
        if self.activeserial is not None:
            self.activeserial.close()
        self.clearClicked()
        self.connect(port, baudrate, parity)

    def connect(self, port: str, baudrate: int, parity: str):
        parity_map = {
            "None": serial.PARITY_NONE,
            "Even": serial.PARITY_EVEN,
            "Odd": serial.PARITY_ODD,
            "Mark": serial.PARITY_MARK,
            "Space": serial.PARITY_SPACE
        }
        try:
            self.activeserial = serial.Serial(
                port=port,
                baudrate=baudrate,
                parity=parity_map[parity],
                stopbits=serial.STOPBITS_ONE,
                bytesize=serial.EIGHTBITS,
                timeout=0
            )
            self.serialThread = SerialThread(self.activeserial)
            self.serialThread.received.connect(self.setText)
            self.serialThread.start()
            print("Connected to: " + self.activeserial.portstr)
        except serial.SerialException as e:
            self.textEdit.append(f"Failed to connect to {port}: {e}")

    def setText(self, terminaltext: str):
        self.textEdit.append(terminaltext)  # Append new text to the QTextEdit

    def clearClicked(self):
        self.textEdit.clear()  # Clear the QTextEdit

    def closeEvent(self, event):
        if self.activeserial and self.activeserial.isOpen():
            self.activeserial.close()
        if self.serialThread and self.serialThread.isRunning():
            self.serialThread.stop()
            self.serialThread.wait()
        super().closeEvent(event)


if __name__ == "__main__":
    app = QApplication([])
    window = ParentWindow()
    window.show()
    sys.exit(app.exec())
