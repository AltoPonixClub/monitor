# To Run

```
./BUILD.sh # to compile
./RUN.sh # to run
```

# For First Time Lib Install

### Install [Pangolin](https://github.com/stevenlovegrove/Pangolin) (for 3d visualization)

```
git clone --recursive https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin 

# Install dependencies (as described above, or your preferred method)
./scripts/install_prerequisites.sh recommended

# Configure and build
mkdir build && cd build
cmake ..
cmake --build .
```

### Install [Eigen](https://gitlab.com/libeigen/eigen) (for matrix math)

```
sudo apt install libeigen3-dev
```

### Install [OpenCV](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html) (for computer vision stuffs)

```
sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

mkdir ~/opencv_build && cd ~/opencv_build
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git


cd ~/opencv_build/opencv
mkdir -p build && cd build


cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..
    
make -j8
sudo make install

# To test if working

pkg-config --modversion opencv4
```

### Install [libcurl](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
```
sudo apt install libcurl4-openssl-dev
```


