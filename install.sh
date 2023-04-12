cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug -- -j 16
sudo cmake --install . 
cmake --build . --target clean
battlesh1p
