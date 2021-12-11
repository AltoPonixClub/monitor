Install [Pangolin](https://github.com/stevenlovegrove/Pangolin) (for 3d visualization)

```
git clone --recursive https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin 

# Install dependencies (as described above, or your preferred method)
./scripts/install_prerequisites.sh recommended

# Configure and build
mkdir build && cd build
cmake ..
cmake --build .

# GIVEME THE PYTHON STUFF!!!! (Check the output to verify selected python version)
cmake --build . -t pypangolin_pip_install

# Run me some tests! (Requires Catch2 which must be manually installed on Ubuntu.)
ctest
```

Install [Eigen]() (for matrix math)
