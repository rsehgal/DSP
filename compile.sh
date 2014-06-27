rm -rf build
mkdir build
cd build
cmake -DMAKETEST=ON ..
make clean
make
cd ..
