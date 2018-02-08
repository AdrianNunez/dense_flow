import os
import cv2
import glob
import sys

data_folder = '/home/adrian/Downloads/prueba/'
output_path = '/home/adrian/Downloads/prueba_of/'
use_video = True

if not os.path.exists(output_path):
    os.mkdir(output_path)

folders = [f for f in os.listdir(data_folder) if os.path.isdir(os.path.join(data_folder, f))]
folders.sort()
for folder in folders:
	video_folders = [f for f in os.listdir(data_folder + folder) if os.path.isdir(os.path.join(data_folder + folder + '/', f))]
	video_folders.sort()
	for video_folder in video_folders:
		path = data_folder + folder + '/' + video_folder
		flow = output_path + folder + '/' + video_folder
		if not os.path.exists(flow):
			os.makedirs(flow)
      
		os.system('build/extract_cpu -f={} -x={} -y={} -i=tmp/image -b=20 -t=1 -d=0 -s=1 -o=dir'.format(path, flow + '/flow_x', flow + '/flow_y'))
