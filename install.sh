cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release -- -j 16
sudo cmake --install . 
cmake --build . --target clean
battlesh1p
