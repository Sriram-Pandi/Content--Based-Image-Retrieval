//4th Task Srinivas Peri & Sriram Pandi
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
    float intersectionss;
};

// Comparison function for sorting the image data
bool comp(const ImageData& a, const ImageData& b) {
    return a.intersectionss < b.intersectionss;
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
    /*Mat targaryconv;
    cvtColor(target, targaryconv, COLOR_BGR2GRAY);*/
    Mat gardx, gardy, gardMag;
    Mat abs_grad_x, abs_grad_y;
    Sobel(target, gardx, CV_32F, 1, 0);
    Sobel(target, gardy, CV_32F, 0, 1);
    /*magnitude(gardx, gardy, gardMag);*/
    convertScaleAbs(gardx, abs_grad_x);
    convertScaleAbs(gardy, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, gardMag);
    imshow("sobmag", gardMag);
    //compute histogarma on target image
    Mat his_tarcrp;
    his_tarcrp = calc_rgb_hist(gardMag, his_tarcrp);
    //convert mat to flaot datatype 
    vector<float> flo_tcrp = matToVector(his_tarcrp);


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

       /* Mat comgaryconv;
        cvtColor(image, comgaryconv, COLOR_BGR2GRAY);*/

        Mat c_gardx, c_gardy, c_gardMag;
        Mat c_abs_grad_x, c_abs_grad_y;
        Sobel(image, c_gardx, CV_32F, 1, 0);
        Sobel(image, c_gardy, CV_32F, 0, 1);
        convertScaleAbs(c_gardx, c_abs_grad_x);
        convertScaleAbs(c_gardy, c_abs_grad_y);
        addWeighted(c_abs_grad_x, 0.5, c_abs_grad_y, 0.5, 0, c_gardMag);
        
       

        // Compute the histogram
        Mat ihis_intens;
        ihis_intens = calc_rgb_hist(c_gardMag, ihis_intens);
        
        // convert Mat to Float
        vector<float> flo_dcrp = matToVector(ihis_intens);
        // compute intersection
        float insa = intersection(flo_tcrp, flo_dcrp);

        // Store the image data
        ImageData data;
        data.filename = argv[2] + string("/") + ent->d_name;
        data.intersectionss = insa;
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
        cout << images[i].filename << " " << images[i].intersectionss << endl;
        cv::Mat image = cv::imread(images[i].filename);
        cv::Mat imaget = cv::imread(argv[0]);

        cv::imshow(images[i].filename, image);


    }
    cv::waitKey(0);

    return 0;
}
