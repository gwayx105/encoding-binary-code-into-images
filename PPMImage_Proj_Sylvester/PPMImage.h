#ifndef PPMIMAGE_H
#define PPMIMAGE_H
#include <iostream>
#include <string>

class PPMImage {
private:
	std::string MAGIC_NUMBER;
	int WIDTH;
	int HEIGHT;
	int MAX_COLOR;
	char* RGB;
public:
	~PPMImage();
	PPMImage();
	void setMagicNumber(std::string);
	void setWidth(int);
	void setHeight(int);
	void setMaxColor(int);
	std::string getMagicNumber();
	int getWidth();
	int getHeight();
	int getMaxColor();
	void hideData(std::string);
	std::string recoverData();
	void grayScale();
	void sepia();
	void negative();
	friend std::ostream&  operator <<(std::ostream& outputStream, PPMImage &);
	friend std::istream&  operator >>(std::istream& inputStream, PPMImage &);
};

#endif