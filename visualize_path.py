import numpy as np
import cv2

from gui import Gui, InteractGui
from read_serial_data import ReadSerial

class visualizeLocation():
	def __init__(self):
		self.gui = Gui()
		self.serial = ReadSerial()

	def location(self):
		imu_estimate = self.serial.read_serial()

		vehicle_pose = self.gui.transform(imu_estimate)

		self.gui.draw_transform(vehicle_pose, c_i=0)

class visualizeCam():
	def __init__(self):
		pass

	def visualize():
		pass

	def show_image(self, image, gui):
		gui.image_visualization(image)


def main():
	vis = visualizeLocation()
	vis.location()

if __name__ == "__main__":
	main()