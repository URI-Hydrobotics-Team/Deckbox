import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QVBoxLayout, QHBoxLayout,
    QProgressBar, QGroupBox, QGridLayout, QPushButton
)
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import Qt


class AUV_GUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("AUV Control Panel")

        # Dunno if you guys want it to go full screen so I just have it arbitrarily at 800,600
        self.setGeometry(100, 100, 800, 600)

        # Main layout
        main_layout = QHBoxLayout()  # Horizontal layout to prioritize cameras

        # Left panel for smaller widgets
        left_panel = QVBoxLayout()

        # DVL Sensor
        dvl_group = self.create_sensor_group("DVL Sensor", ["X Velocity", "Y Velocity", "Z Velocity"], [0, 0, 0])

        # IMU Sensor
        imu_group = self.create_sensor_group("IMU Sensor", ["Roll", "Pitch", "Yaw"], [0, 0, 0,])

        # Leak Sensor
        self.leak_status_label = QLabel("Leak Status: No Leak Detected")
        self.leak_status_label.setStyleSheet("color: green; font-weight: bold;")
        leak_group = QGroupBox()
        leak_layout = QVBoxLayout()
        leak_layout.addWidget(self.leak_status_label)

        # Button to simulate leak detection
        leak_button = QPushButton("Simulate Leak")
        leak_button.clicked.connect(self.simulate_leak)
        leak_layout.addWidget(leak_button)

        leak_group.setLayout(leak_layout)

        # Pressure Sensor
        pressure_group = self.create_sensor_group("Pressure Sensor", ["Depth"], [0])

        # Battery Monitor
        battery_group = QGroupBox()
        battery_layout = QVBoxLayout()
        battery_progress = QProgressBar()
        battery_progress.setValue(75)  # Example battery level
        battery_layout.addWidget(QLabel("Battery Level"))
        battery_layout.addWidget(battery_progress)
        battery_group.setLayout(battery_layout)

        # Kill Switch
        self.kill_switch_label = QLabel("Kill Switch: Deactivated")
        self.kill_switch_label.setStyleSheet("color: black; font-weight: bold;")
        kill_switch_button = QPushButton("Activate Kill Switch")
        kill_switch_button.setStyleSheet("background-color: red; color: white; font-weight: bold;")
        kill_switch_button.clicked.connect(self.activate_kill_switch)

        kill_switch_group = QGroupBox()
        kill_switch_layout = QVBoxLayout()
        kill_switch_layout.addWidget(self.kill_switch_label)
        kill_switch_layout.addWidget(kill_switch_button)
        kill_switch_group.setLayout(kill_switch_layout)

        # Add smaller widgets to the left panel
        left_panel.addWidget(dvl_group)
        left_panel.addWidget(imu_group)
        left_panel.addWidget(leak_group)
        left_panel.addWidget(pressure_group)
        left_panel.addWidget(battery_group)
        left_panel.addWidget(kill_switch_group)
        left_panel.addStretch()  # Push everything to the top

        # Right panel for cameras
        right_panel = QVBoxLayout()

        cameras_group = QGroupBox()
        cameras_layout = QHBoxLayout()

        # Camera 1
        camera1_layout = QVBoxLayout()
        camera1_label = QLabel("Camera 1")
        camera1_label.setAlignment(Qt.AlignBottom | Qt.AlignHCenter)

        # Actual Camera 1 output
        self.camera1_feed = QLabel()
        self.camera1_feed.setStyleSheet("background-color: black;")
        self.camera1_feed.setScaledContents(False)  # Maintain aspect ratio

        camera1_layout.addWidget(camera1_label)
        camera1_layout.addWidget(self.camera1_feed)

        # Camera 2
        camera2_layout = QVBoxLayout()
        camera2_label = QLabel("Camera 2")
        camera2_label.setAlignment(Qt.AlignBottom | Qt.AlignHCenter)

        # Actual Camera 2 Output
        self.camera2_feed = QLabel()
        self.camera2_feed.setStyleSheet("background-color: black;")
        self.camera2_feed.setScaledContents(False)  # Maintain aspect ratio

        camera2_layout.addWidget(camera2_label)
        camera2_layout.addWidget(self.camera2_feed)

        cameras_layout.addLayout(camera1_layout)
        cameras_layout.addLayout(camera2_layout)
        cameras_group.setLayout(cameras_layout)

        right_panel.addWidget(cameras_group)

        # Add left and right panels to the main layout
        main_layout.addLayout(left_panel, 1)  # Smaller weight
        main_layout.addLayout(right_panel, 4)  # Larger weight for cameras

        self.setLayout(main_layout)

    def create_sensor_group(self, title, labels, values):
        """Creates a group box for displaying sensor data."""
        group = QGroupBox(title)
        layout = QGridLayout()

        for i, (label_text, value) in enumerate(zip(labels, values)):
            label = QLabel(f"{label_text}: {value}")
            layout.addWidget(label, i, 0)

        group.setLayout(layout)
        return group

    def simulate_leak(self):
        """Simulates a leak detection and updates the label."""
        self.leak_status_label.setText("Leak Status: Leak Detected!")
        self.leak_status_label.setStyleSheet("color: red; font-weight: bold;")

    def activate_kill_switch(self):
        """Activates the kill switch and updates the label."""
        self.kill_switch_label.setText("Kill Switch: Activated!")
        self.kill_switch_label.setStyleSheet("color: red; font-weight: bold;")

    def resizeEvent(self, event):
        """Resize the camera feeds while maintaining aspect ratio."""
        super().resizeEvent(event)
        window_width = self.width()
        camera_width = int(window_width * 0.4)  # 40% of the window's width
        camera_height = int(camera_width * 3 / 4)  # Maintain 4:3 aspect ratio

        self.camera1_feed.setFixedSize(camera_width, camera_height)
        self.camera2_feed.setFixedSize(camera_width, camera_height)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = AUV_GUI()
    window.show()
    sys.exit(app.exec_())
