cd unit
cmake --build cmake-build-debug --target monitor
cd ..

cd viewer
cmake --build cmake-build-debug --target qt
cd ..
