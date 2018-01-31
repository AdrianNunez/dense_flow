Modified tool to accept a folder with a sequence of images instead of a video and convert the sequence of images to optical flow images.

####Depencies:
- LibZip: 
to install on ubuntu ```apt-get install libzip-dev``` on mac ```brew install libzip```

###Install
```
git clone --recursive http://github.com/yjxiong/dense_flow
mkdir build && cd build
cmake .. && make -j
```

###Usage
Instructions:
* Create a 'build' folder to compile the project.
* Use the generateOF.py script to automatically generate optical flow images.  Change the 'data_folder' and 'ouput_path' variables inside the script.
* Alternative option from the terminal, use the following command:

```
build/extract_cpu -f=video_folder -x=flow_x -y=flow_y -i=tmp/image -b=20 -t=1 -d=0 -s=1 -o=dir
```
- `video_folder`: path to the folder where the image sequence is stored (image sequence extracted from a video).
- `flow_x`: path to the folder where the the horizontal components of the optical flow will be saved.
- `flow_y`: path to the folder where the the vertical components of the optical flow will be saved. Can be the same as the previous one to put everything inside the same folder.

