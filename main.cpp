// Program constructed and owned by Peter Menchu
// Copies a bitmap file
// (Here is a test implementation of the functions)
#include <iostream>
#include "ImgProc.h"

using namespace std;

int main() {
    // variables for basic main functionality
    int operation = 0; // user input, selection from menu
    int brightenInput = 0;
    int darkenInput = 0;
    bool runProgram = true;// flag to indicate if the program should continue execution
    // variables for the image header
    int width, height, bitDepth;
    unsigned char header[BMP_HEADER_SIZE];
    unsigned char colorTab[BMP_COLORTABLE_SIZE];
    unsigned char inBuffer[IMG_SIZE];
    unsigned char outBuffer[IMG_SIZE];

    // enter .bmp image file name below, full path needed when not next to executable
    const char name[] = "/Users/peter/Documents/Peter's Programs/Cpp-Image-Processing-Library/images/lena512.bmp";
    // next line is where the output image will go
    const char newName[] = "/Users/peter/Documents/Peter's Programs/Cpp-Image-Processing-Library/images/lena512_dark.bmp";
    // create the image representation
    auto *image = new ImgProc(
                name,
                newName,
                &height,
                &width,
                &bitDepth,
                &header[0],
                &colorTab[0],
                &inBuffer[0],
                &outBuffer[0]
            );
    cout << "------------------------------------------------------\nMENU\n";
    cout << "What operation would you like to perform on an image?\n";
    cout << "\t1. Copy\n\t2. Brighten\n\t3. Darken\n\t4. Binarize\n\t5. Exit\n";
    do{
        cout << "Command: ";
        cin >> operation;
        if (operation == 1) {
            // perform functions on the image data
            image->readImg();
            image->copyImgData(inBuffer, outBuffer, IMG_SIZE);
            image->writeImg();
            // success
            cout << "Image copied into " << newName << ", ending program.\n";
        } else if (operation == 2) {
            cout << "Enter brightness factor: ";
            cin >> brightenInput;
            image->readImg();
            image->brightenImg(inBuffer, outBuffer, IMG_SIZE, brightenInput);
            image->writeImg();
            cout << "Image brightened by factor " << brightenInput << " and copied into " << newName << endl;
        } else if (operation ==3) {
            cout << "Enter darkness factor: ";
            cin >> darkenInput;
            image->readImg();
            image->darkenImg(inBuffer, outBuffer, IMG_SIZE, darkenInput);
            image->writeImg();
            cout << "Image darkened by factor " << darkenInput << " and copied into " << newName << endl;
        } else if (operation == 4){
            // gg
        }else { // on exit input or invalid input the program will end
                // cout << "Exiting Peter's image processor.\n";
                runProgram = false;// set exit flag
        }
    }while (runProgram); // shorthand for true
    delete image;
    cout << "------------------------------------------------------\n";
    return 42;// The correct answer will be returned on proper exit from the main process
}
// Peter Menchu 2020