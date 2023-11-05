// TASK 1 HW-2 PVCR Srinivas Peri & Sriram Pandi 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <dirent.h>

using namespace std;
using namespace cv;

// Function to compute the sum-of-squared-difference
double ssd(const Mat& a, const Mat& b) {
    double sum = 0;
    for (int i = 0; i < a.rows; i++) {

        for (int j = 0; j < a.cols; j++) {
            sum += (a.at<uchar>(i, j) - b.at<uchar>(i, j)) * (a.at<uchar>(i, j) - b.at<uchar>(i, j));
        }
    }
    return sum;
}

// Structure to store image information
struct ImageData {
    string filename;
    double distance;
};

// Comparison function for sorting the image data
bool comp(const ImageData& a, const ImageData& b) {
    return a.distance < b.distance;
}

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " target_image directory_of_images number_of_results" << endl;
        return -1;
    }

    // Load the target image
    Mat target = imread(argv[1]);
    if (!target.data) {
        cout << "Error: could not load target image" << endl;
        return -1;
    }

    // Crop the target image to the 9x9 square in the middle
    Rect roi(target.cols / 2 - 8, target.rows / 2 - 8, 9, 9);
    Mat target_cropped = target(roi);

    // Vector to store the image data
    vector<ImageData> images;

    // Read all the images in the directory
    DIR* dir = opendir(argv[2]);
    if (dir == NULL) {
        cout << "Error: could not open directory" << endl;
        return -1;
    }
    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        // Skip the current and parent directories
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        // Load the image
        Mat image = imread(argv[2] + string("/") + ent->d_name);
        if (!image.data) {
            cout << "Error: could not load image " << ent->d_name << endl;
            continue;
        }

        // Crop the image to the 9x9 square in the middle
        Mat image_cropped = image(roi);

        // Compute the sum-of-squared-difference
        double distance = ssd(target_cropped, image_cropped);

        // Store the image data
        ImageData data;
        data.filename = argv[2] + string("/") + ent->d_name;
        data.distance = distance;
        images.push_back(data);
    }
    closedir(dir);

    // Sort the images based on their distance from the target image
    sort(images.begin(), images.end(), comp);
    //makepair
    // Get the number of results requested
    int n = atoi(argv[3]);
    if (n > images.size()) {
        n = images.size();
    }

    // Print the top N results
    cout << "Top " << n << " results:" << endl;
    for (int i = 0; i < n; i++) {
        cout << images[i].filename << " " << images[i].distance << endl;
        cv::Mat image = cv::imread(images[i].filename);
        cv::Mat imaget = cv::imread(argv[0]);

        cv::imshow(images[i].filename, image);


    }
    cv::waitKey(0);

    return 0;
}