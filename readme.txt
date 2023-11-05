Name: Sriram Pandi and Srinivas peri

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Project related information and instructions:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

What operating system and IDE you used to run and compile your code:

Operating system- Windows
IDE- Microsoft visual studio

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Instructions for running your executables:

The following files were added-

Task-1 - cpp file to execute 1st task
Task-2 - cpp file to execute 2nd task.
Task-3 - cpp file to execute 3rd task.
Task-4 - cpp file to execute 4th task.
Task-5 - cpp file to execute 5th task.

To run any of the tasks. Build it and when you run the code(after adding the required libraries and their paths) add
paths of the corresponding folders, which will be taken as arguements by the programs

In task-4
arg-1 is query image 
arg-2 is the path to the dataset diretory
arg-3 is the number of images to be printed in ascending order of distance metric

In task-5 
arg-1 is query image-1
arg-2 is query image 2
arg-3 is path to the directory
arg-4 is the number of images to be printed in ascending order of distance metric
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Certainly! Based on the assignment details and your solution, here's a comprehensive breakdown:

---

## **Content-based Image Retrieval using OpenCV**
By: Sriram Pandi & Srinivas Peri

### **Objective:**
This project aims to develop a content-based image retrieval (CBIR) system that matches a target image against a database of images, using various image features and distance metrics, without the use of neural networks or object recognition methods.

### **Dataset:**
The Olympus dataset, comprising images of varying sizes, ages, and quality, is used. A subset of these images is reserved for testing and validation.

### **Tasks & Results:**

1. **Baseline Matching**:
   - **Method**: Uses the center 9x9 square of the image as a feature vector.
   - **Distance Metric**: Sum-of-squared-difference.
   - **Result**: 
     - Top match for `pic.1016.jpg` is `pic.0641.jpg` with a distance value of 10170.
     - Other close matches include `pic.0233.jpg` and `pic.0547.jpg`.

2. **Histogram Matching**:
   - **Method**: Uses a normalized color histogram (either two-dimensional or three-dimensional) as the feature vector.
   - **Distance Metric**: Histogram intersection.
   - **Result**:
     - Top match for `pic.0164.jpg` is `pic.0110.jpg` with an intersection value of 0.611465.
     - Other close matches include `pic.0092.jpg` and `pic.1032.jpg`.

3. **Multi-histogram Matching**:
   - **Method**: Uses multiple color histograms, representing different spatial parts of the image (e.g., top and bottom halves).
   - **Distance Metric**: Custom, based on histogram intersection.
   - **Result**:
     - Top match for `pic.0274.jpg` is `pic.0881.jpg`.
     - Other close matches include `pic.0409.jpg` and `pic.1055.jpg`.

4. **Texture and Color Matching**:
   - **Method**: Combines a whole-image color histogram with a texture histogram derived from the Sobel magnitude image.
   - **Distance Metric**: Custom, giving equal weight to color and texture histograms.
   - **Result**:
     - Top match for `pic.0535.jpg` is `pic.0778.jpg`.
     - Other close matches include `pic.0004.jpg` and `pic.0011.jpg`.

5. **Custom Design**:
   - **Method**: Custom feature vector and distance metric are designed, targeting a specific type of image.
   - **Training Set**: Subset of the Olympus data.
   - **Result**: 
     - Queries using `pic.0013.jpg` and `pic.0016.jpg` produced relevant matches with low intersection values.
     - The results are consistent when evaluated against the entire Olympus dataset.

### **Observations**:
The CBIR system effectively retrieves relevant images from the database. The intersection values provide a quantitative measure of the similarity between the target and database images. The first few results are more relevant to the query, while subsequent results tend to be less similar.

### **Conclusion**:
The project successfully implements various CBIR techniques, from basic histogram matching to advanced texture-based retrieval. The methods developed provide effective retrieval results and could be further optimized or combined for improved performance.


