// Created by Peter Menchu on 2/7/20.
// Image processing library for bitmap image
// An unsigned character is a character stored in 1 byte, which is a convenient memory management and visualization
// convention when dealing with bytes of data (multiples of 8 bits).
#include "ImgProc.h"
// Constructor function
// Note that constructor variables have _ in the name, these are
// assigned to private variables when creating an instance.
ImgProc::ImgProc(const char *_inputImg, const char *_outputImg, int *_height,
        int *_width, int *_bitDepth, unsigned char *_header,
        unsigned char *_colorTable, unsigned char *_inBuffer, unsigned char *_outBuffer
        ){
    inputImg = _inputImg;
    outputImg = _outputImg;
    height = _height;
    width = _width;
    bitDepth = _bitDepth;
    header = _header;
    colorTable = _colorTable;
    inBuffer = _inBuffer;
    outBuffer = _outBuffer;
}
// read image data
void ImgProc::readImg(){
    int i;
    FILE *inStream;
    // open file to read
    inStream = fopen(inputImg, "rb");
    if(inStream == (FILE *)0){
        cout << "Input file did not open successfully, exiting program. path: " << inputImg << endl;
        exit(0);
    }
    // bitmap header is 54 bytes
    for(i = 0; i < BMP_HEADER_SIZE; i++){
        header[i] = getc(inStream);
    }
    // read img data via header offsets
    *width = *(int *)&header[18]; // read width from img header
    *height = *(int *)&header[22]; // read height then bit depth
    *bitDepth = *(int *)&header[28];
    // check for color table
    if(*bitDepth <= 8){
        fread(colorTable, sizeof(unsigned char), BMP_COLORTABLE_SIZE, inStream);
    }
    // read pixel data
    fread(inBuffer, sizeof(unsigned char), IMG_SIZE, inStream);
    fclose(inStream);
}
// write image data
void ImgProc::writeImg(){
    FILE *outStream;
    outStream = fopen(outputImg, "wb");
    // write header
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, outStream);
    // check for / write color table
    if(*bitDepth <= 8){
        fwrite(colorTable, sizeof(unsigned char), BMP_COLORTABLE_SIZE, outStream);
    }
    // write pixel data
    fwrite(outBuffer, sizeof(unsigned char), IMG_SIZE, outStream);
    fclose(outStream);
}
// fn for copying image data
void ImgProc::copyImgData(unsigned char *_srcBuffer, unsigned char *_destBuffer, int bufferSize){
    for(int i = 0; i < bufferSize; i++){
        _destBuffer[i] = _srcBuffer[i];
    }
}
// convert the image data to binary data
void ImgProc::binarizeImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int threshold) {
    for(int i = 0; i < imgSize; ++i){
        _outData[i] = (_inData[i] > threshold) ? WHITE : BLACK;
    }
}
// fn for increasing brightness of an image
void ImgProc::brightenImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int brightnessFactor){
    int buffer;
    for(int i = 0; i < imgSize; i++){
        buffer = _inData[i]+brightnessFactor;
        // Must check if color brightness exceeds max and if so set to max (truncate to 255), else
        // write the calculated sum.
        if (buffer >= MAX_COLOR){
            _outData[i] = MAX_COLOR;
        } else {
            _outData[i] = buffer;
        }
    }
}
// darken image
void ImgProc::darkenImg(unsigned char *_inData, unsigned char *_outData, int imgSize, int darknessFactor) {
    int buffer;
    for(int i = 0; i < imgSize; i++){
        buffer = _inData[i]-darknessFactor;
        // Must check if color darkness exceeds min and if so set to min (truncate to 0), else
        // write the calculated difference.
        if (buffer <= MIN_COLOR){
            _outData[i] = MIN_COLOR;
        } else {
            _outData[i] = buffer;
        }
    }
}
// destructor
ImgProc::~ImgProc(){
    cout << "Exiting Peter's image processor.\n";
}

// Peter Menchu 2020