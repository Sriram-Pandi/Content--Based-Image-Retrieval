//3rd Task Sriram Pandi & Srinivas Peri 

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <dirent.h>

using namespace std;
using namespace cv;

// Structure to store image information
struct ImageData {
    string filename;
    float intersections1;
    float intersections2;
};

// Comparison function for sorting the image data
bool comp(const ImageData& a, const ImageData& b) {
    return a.intersections1 < b.intersections1, a.intersections2 < b.intersections2;
}

float intersection(std::vector<float>& ha, std::vector<float>& hb)
{
    double intersection = 0.0;

    double suma = 0.0;
    double sumb = 0.0;
    for (int i = 0; i < ha.size(); i++) {
        suma += ha[i];
        sumb += hb[i];

    }

    for (int i = 0; i < ha.size(); i++) {
        double af = ha[i] / suma;
        double bf = hb[i] / sumb;
        intersection += af < bf ? af : bf;

    }
    return (1.0 - intersection);
}



cv::Mat calc_rgb_hist(cv::Mat& src, cv::Mat& hist) {

    int Hsize = 16;
    const int divisor = 256 / Hsize;

    int dim[3] = { Hsize, Hsize, Hsize };

    hist = cv::Mat::zeros(3, dim, CV_32F);

    for (int i = 0; i < src.rows; i++) {
        cv::Vec3b* sptr = src.ptr<cv::Vec3b>(i);
        for (int j = 0; j < src.cols; j++) {
            int r = sptr[j][2] / divisor;
            int g = sptr[j][1] / divisor;
            int b = sptr[j][0] / divisor;

            hist.at<float>(r, g, b)++;

        }
    }
    return hist;
}
    

std::vector<float> matToVector(const cv::Mat& mat) {
    std::vector<float> vec;
    /*vec.reserve(mat.rows * mat.cols * mat.channels());*/
    for (int i = 0; i < mat.size[0]; i++) {
        for (int j = 0; j < mat.size[1]; j++) {
            for (int c = 0; c < mat.size[2]; c++) {
                vec.push_back(mat.at<float>(i, j, c));

            }
        }
    }
    return vec;
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

    Mat left_half = target(Rect(0, 0, target.cols / 2, target.rows));
    Mat right_half = target(Rect(target.cols / 2, 0, target.cols / 2, target.rows));

    //To split as top and botton halves un commnet and use the below code.

    /*Mat left_half = target(Rect(0, 0, target.cols, target.rows / 2));
    Mat right_half = target(Rect(0, target.rows / 2, target.cols, target.rows / 2));*/
    
    // Calculate RGB histogram for each half
    Mat left_hist, right_hist;
    calc_rgb_hist(left_half, left_hist);
    calc_rgb_hist(right_half, right_hist);
    
    //convevrts Mat to flaot
    vector<float> flo_tcrp1 = matToVector(left_hist);
    vector<float> flo_tcrp2 = matToVector(right_hist);
    
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

        Mat left_half_comp = image(Rect(0, 0, image.cols / 2, image.rows));
        Mat right_half_comp = image(Rect(image.cols / 2, 0, image.cols / 2, image.rows));
        
        //To split as top and botton halves un commnet and use the below code.

        /*Mat left_half_comp = image(Rect(0, 0, image.cols, image.rows / 2));
        Mat right_half_comp = image(Rect(0, image.rows / 2, image.cols, image.rows / 2));*/
       
        // Compute the histogram
        Mat leftimh_hist, rightimg_hist;
        leftimh_hist = calc_rgb_hist(left_half_comp, leftimh_hist);
        rightimg_hist = calc_rgb_hist(left_half_comp, rightimg_hist);
          
        // convert Mat to Float
        vector<float> flo_dcrp1 = matToVector(leftimh_hist);
        vector<float> flo_dcrp2 = matToVector(rightimg_hist);
        // compute intersection
        float insa1 = intersection(flo_tcrp1, flo_dcrp1);
        float insa2 = intersection(flo_tcrp2, flo_dcrp2);

        // Store the image data
        ImageData data;
        data.filename = argv[2] + string("/") + ent->d_name;
        data.intersections1 = insa1;
        data.intersections2 = insa2;
        images.push_back(data);
    }
    closedir(dir);

    // Sort the images based on their distance from the target image
    sort(images.begin(), images.end(), comp);
    
    // Get the number of results requested
    int n = atoi(argv[3]);
    if (n > images.size()) {
        n = images.size();
    }

    // Print the top N results
    cout << "Top " << n << " results:" << endl;
    for (int i = 0; i < n; i++) {
        cout << images[i].filename << " " << images[i].intersections1 << endl;
        cout << images[i].filename << " " << images[i].intersections2 << endl;
        cv::Mat image = cv::imread(images[i].filename);
        cv::Mat imaget = cv::imread(argv[0]);

        cv::imshow(images[i].filename, image);


    }
    cv::waitKey(0);

    return 0;
}

