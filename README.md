# Content-Based Image Retrieval with OpenCV

Course project by Sriram Pandi and Srinivas Peri. Five C++ experiments rank reference images by visual similarity using methods including central pixels, color histograms, and texture features.

Read the [report](Project-2_PRCV_Final.pdf) for example matches and the [original instructions](readme.txt) for task arguments. Build the desired `Task-*.cpp` as a separate OpenCV program and supply the image collection and query files. Task 4 takes one query image, the dataset directory, and a result count. Task 5 takes two query images, the dataset directory, and a result count.

## Build and run an example

On a system with POSIX directory headers and OpenCV 4 development files, build with `c++ Task-5.cpp -o retrieve5 $(pkg-config --cflags --libs opencv4)`. Run `./retrieve5 QUERY_A QUERY_B IMAGE_DIR 5` from a graphical session. Tasks 1–4 use one query and take the image directory and count after it. The programs print ranked paths and scores and show result images.
