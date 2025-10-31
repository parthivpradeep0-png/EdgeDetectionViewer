#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <android/log.h>

using namespace cv;

#define LOG_TAG "EdgeDetectionJNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_edgedetectionviewer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string msg = "C++ and OpenCV loaded successfully!";
    return env->NewStringUTF(msg.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_edgedetectionviewer_MainActivity_detectEdges(
        JNIEnv* env,
        jobject /* this */,
        jstring imagePath) {

    const char* path = env->GetStringUTFChars(imagePath, nullptr);
    Mat img = imread(path, IMREAD_GRAYSCALE);

    if (img.empty()) {
        LOGE("Failed to load image from %s", path);
        env->ReleaseStringUTFChars(imagePath, path);
        return env->NewStringUTF("Error: Image not found or can't be opened!");
    }

    Mat edges;
    Canny(img, edges, 100, 200);

    std::string outPath = std::string(path).substr(0, std::string(path).find_last_of("/")) + "/edges.jpg";

    bool success = imwrite(outPath, edges);

    env->ReleaseStringUTFChars(imagePath, path);

    if (!success) {
        LOGE("Failed to save edge image to %s", outPath.c_str());
        return env->NewStringUTF("Error: Failed to save edge image!");
    }

    return env->NewStringUTF(("Edge detection done! Saved to: " + outPath).c_str());
}

