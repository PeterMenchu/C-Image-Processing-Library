// Created by Peter Menchu on 2/7/20.
// Image processing library for bitmap images

#ifndef DIGIMAGEPROC_IMGPROC_H
#define DIGIMAGEPROC_IMGPROC_H
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// static image size
static const int IMG_SIZE = 262144; // 512x512 image size
static const int BMP_COLORTABLE_SIZE = 1024;
static const int BMP_HEADER_SIZE = 54;
static const int MAX_COLOR = 255;
static const int MIN_COLOR = 0;
// variables for binarizing image data
static const int WHITE = MAX_COLOR;
static const int BLACK = MIN_COLOR;

class ImgProc {
    public:
        // constructor, assign class variables
        ImgProc(const char *_inputImg, const char *_outputImg, int *_height,
                int *_width, int *_bitDepth, unsigned char *_header,
                unsigned char *_colorTable, unsigned char *_inBuffer, unsigned char *_outBuffer
                );
        // class functionality
        void readImg();
        void writeImg();
        void copyImgData(unsigned char *_srcBuffer, unsigned char *_destBuffer, int bufferSize);
        void brightenImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int brightnessFactor);
        void darkenImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int darknessFactor);
        void binarizeImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int threshold);
        // destructor
        virtual ~ImgProc();
    private:
        const char *inputImg;
        const char *outputImg;
        int *height;
        int *width;
        int *bitDepth;
        unsigned char *header;
        unsigned char *colorTable;
        unsigned char *inBuffer;
        unsigned char *outBuffer;
};
// Peter Menchu 2020
#endif //DIGIMAGEPROC_IMGPROC_H
