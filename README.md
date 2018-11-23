Modified tool to accept a folder with a sequence of images instead of a video and convert the sequence of images to optical flow images. Only CPU version is adapted, GPU version cannot be used for images.

#### Depencies

- LibZip: 
to install on ubuntu ```apt-get install libzip-dev``` on mac ```brew install libzip```

#### Install

```
git clone --recursive https://github.com/AdrianNunez/dense_flow.git
mkdir build && cd build
cmake .. && make -j
```

#### Usage

Instructions:
* Use the generateOF.py script to automatically generate optical flow images.  Change the 'data_folder' and 'ouput_path' variables inside the script: the first one is the path to the folder where your data is stored and the second one is the path where the generated optical flow images will be stored.
* Alternatively, from the terminal, use the following command:

```
build/extract_cpu -f=video_folder -x=flow_x -y=flow_y -i=tmp/image -b=20 -t=1 -d=0 -s=1 -o=dir
```
- `video_folder`: path to the folder where the image sequence is stored (image sequence extracted from a video).
- `flow_x`: path to the folder where the the horizontal components of the optical flow will be saved.
- `flow_y`: path to the folder where the the vertical components of the optical flow will be saved. Can be the same as the previous one to put everything inside the same folder.

