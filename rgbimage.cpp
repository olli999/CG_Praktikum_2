#include "rgbimage.h"
#include "color.h"
#include "assert.h"


RGBImage::RGBImage(unsigned int Width, unsigned int Height) {
    m_Height = Height;
    m_Width = Width;
    m_Image = new Color[m_Width * m_Height];
}

RGBImage::~RGBImage() {
    delete[] m_Image;
}

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color &c) {
    if (x > m_Width || x < 0 || y > m_Height || y < 0) {
        return;
    }
    m_Image[m_Width * y + x] = c;
}

const Color &RGBImage::getPixelColor(unsigned int x, unsigned int y) const {
    if (x > m_Width || x < 0 || y > m_Height || y < 0) {
        return m_Image[y * m_Width + x];
    }
    return m_Image[y * m_Width + x];
}

bool RGBImage::saveToDisk(const char *Filename) {

    unsigned char generalHeader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char DIBHeader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int fileSize = 54 + m_Width * m_Height * 3;

    //Set the binary portion of the generalHeader, mainly just file size
    generalHeader[2] = (unsigned char) (fileSize);
    generalHeader[3] = (unsigned char) (fileSize >> 8);
    generalHeader[4] = (unsigned char) (fileSize >> 16);
    generalHeader[5] = (unsigned char) (fileSize >> 24);

    //The binary variable portion of the DIB header
    DIBHeader[4] = (unsigned char) (m_Width);
    DIBHeader[5] = (unsigned char) (m_Width >> 8);
    DIBHeader[6] = (unsigned char) (m_Width >> 16);
    DIBHeader[7] = (unsigned char) (m_Width >> 24);

    DIBHeader[8] = (unsigned char) (m_Height);
    DIBHeader[9] = (unsigned char) (m_Height >> 8);
    DIBHeader[10] = (unsigned char) (m_Height >> 16);
    DIBHeader[11] = (unsigned char) (m_Height >> 24);

    int picSize = 3 * m_Width * m_Height;
    DIBHeader[20] = (unsigned char) (picSize);
    DIBHeader[21] = (unsigned char) (picSize >> 8);
    DIBHeader[22] = (unsigned char) (picSize >> 16);
    DIBHeader[23] = (unsigned char) (picSize >> 24);

    FILE *f;
    f = fopen(Filename, "wb");
    fwrite(generalHeader, sizeof(unsigned char), sizeof(generalHeader), f);
    fwrite(DIBHeader, sizeof(unsigned char), sizeof(DIBHeader), f);

    for (int i = m_Height - 1; i >= 0; i--) {
        for (int j = 0; j < m_Width; j++) {
            unsigned char tmp[3];
            tmp[0] = convertColorChannel(m_Image[i*m_Width+j].B);
            tmp[1] = convertColorChannel(m_Image[i*m_Width+j].G);
            tmp[2] = convertColorChannel(m_Image[i*m_Width+j].R);
            fwrite(tmp, sizeof(unsigned char), 3, f);
        }
    }

    fclose(f);

    return true;
}

unsigned int RGBImage::width() const {
    return m_Width;
}

unsigned int RGBImage::height() const {
    return m_Height;
}

unsigned char RGBImage::convertColorChannel(float f) {
    if (f > 1)return 255;
    if (f < 0)return 0;

    return static_cast<unsigned char>(f * 255);
}

