#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "PPMImage.h"
#include <math.h>  
#include <iomanip>
#include <ctime>
#include <windows.h> 

PPMImage::PPMImage() {
	//Array size to hold all pixels
	//RGB = new int[WIDTH*HEIGHT * 3];
}

PPMImage::~PPMImage() {
	delete[] RGB;
	RGB = nullptr;
}
void PPMImage::setMagicNumber(std::string number) {
	MAGIC_NUMBER = number;
}
void PPMImage::setWidth(int wid) {
	WIDTH = wid;
}
void PPMImage::setHeight(int hi) {
	HEIGHT = hi;
}
void PPMImage::setMaxColor(int maxc) {
	MAX_COLOR = maxc;
}
std::string PPMImage::getMagicNumber() {
	return MAGIC_NUMBER;
}

int PPMImage::getWidth() {
	return WIDTH;
}
int PPMImage::getHeight() {
	return HEIGHT;
}
int PPMImage::getMaxColor() {
	return MAX_COLOR;
}

int getDecimal(std::string binary) {
	int total = 0, j = binary.size() - 1;

	for (int i = 0;i < binary.size();i++) {
		total += (binary.at(i) - 48)*pow(2, j);
		j--;
	}
	return total;
}
std::string getBinary(int number) {
	int num = 0;
	std::string bina = "";
	for (int i = 0;i < 8;i++) {
		num = number % 2;
		if (num == 0) {
			bina.append("0");
		}
		else if (num == 1) {
			bina.append("1");
		}
		number = number >> 1;
	}
	std::reverse(bina.begin(), bina.end());
	return bina;
}
void PPMImage::hideData(std::string message) {
	std::vector<int> msg_char_int(0);
	int color_index = 0;
	int LSB = 0;
	int size = WIDTH*HEIGHT * 3;
	std::string binary = "";
	bool msg_encoded = false;
	//int collection of characters
	for (int i = message.size() - 1;i >= 0;i--) {
		msg_char_int.insert(msg_char_int.begin(), (int)((unsigned char)message.at(i)));
	}
	for (int i = 0;i < message.size();i++) {
		//get binary representation of the character <string>
		binary = getBinary(msg_char_int.at(i));

		for (int j = 0;j < binary.size();j++) {
			LSB = RGB[color_index] & 1;			
			int comparator = static_cast<int>(binary.at(j))-48;			
			if (LSB !=comparator) {
				if (comparator == 0 && LSB==1) {				
					RGB[color_index] &= ~1;					
				}
				else if(comparator ==1 && LSB==0){				
					RGB[color_index] ^= 1;				
				}
			}
			color_index++;
		}	
	}
}
std::string PPMImage::recoverData() {
	std::string recoveredMessage,binary_char;
	bool found = false;
	int LSB = 0,counter=1,color_index=0;
	int next_char = 0;
	do {
		binary_char = "";
		for (int i = 0;i < 8;i++) {
			LSB = RGB[color_index] & 1;
			color_index++;
			binary_char.append(std::to_string(LSB));		
		}
		int decimal = getDecimal(binary_char);
		if ((unsigned char)decimal != '\\') {
			recoveredMessage.push_back((unsigned char)decimal);
		}
		else {
			next_char = color_index;
			binary_char = "";
			for (int i = 0;i < 8;i++) {
				LSB = RGB[next_char] & 1;
				next_char++;
				binary_char.append(std::to_string(LSB));		
			}
			int decimal_next = getDecimal(binary_char);
			if ((unsigned char)decimal == '0') {
				recoveredMessage.push_back((unsigned char)decimal);
			}
			else {
				found = true;
			}
		}
	} while (!found);
	return recoveredMessage;
}

void PPMImage::grayScale() {
	unsigned int
		rLocal = 0, 
		gLocal = 0,
		bLocal = 0;
	unsigned int 
		redResult=0,
		greenResult=0,
		blueResult=0;
	int size = WIDTH * HEIGHT * 3;
	int index_1 = 0,index_2=0;	

	do {
		redResult = 0, greenResult = 0, blueResult = 0;
		rLocal = 0, gLocal = 0, bLocal = 0;
		rLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		gLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		bLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		//RED
		// 0.2989*red + 0.5870*green + 0.1140*blue
		redResult =(.2989*rLocal) + (0.5870*gLocal) + (0.1140*bLocal);
		if (redResult >= 255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = redResult;
		}
		index_2++;

		//GREEN
		greenResult = (.2989*rLocal) + (0.5870*gLocal) + (0.1140*bLocal);
		if (greenResult >= 255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = greenResult;
		}
		index_2++;

		//BLUE
		blueResult = (.2989*rLocal) + (0.5870*gLocal) + (0.1140*bLocal);
		if (blueResult >= 255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = blueResult;
		}	
		index_2++;
	} while (index_1<size);
}
void PPMImage::sepia() {
	unsigned int rLocal = 0, gLocal = 0, bLocal = 0;
	unsigned int redResult=0, greenResult=0, blueResult=0;
	int size = WIDTH * HEIGHT * 3;
	int index_1 = 0, index_2 = 0;
	do {
		redResult = 0, greenResult = 0, blueResult = 0;
		rLocal = 0, gLocal = 0, bLocal = 0;
		rLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;		
		gLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;	
		bLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;		
		//RED
		redResult = (rLocal*.393) + (gLocal*.769 )+ (bLocal*.189);
		if (redResult >= 255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = redResult;
		}
		//std::cout << RGB[index_2] << "\t";
		index_2++;
		//GREEN
		greenResult =( rLocal*.349 )+ (gLocal*.686 )+ (bLocal*.168);
		if (greenResult>=255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = greenResult;
		}
		//std::cout << RGB[index_2] << "\t";
		index_2++;
		//BLUE
		blueResult = (rLocal*.272 )+ (gLocal*.534 )+ (bLocal*.131);
		if (blueResult>=255) {
			RGB[index_2] = 255;
		}
		else {
			RGB[index_2] = blueResult;
		}
		//std::cout << bLocal << "\t\n";
		index_2++;
		//system("pause");
	} while (index_1<size);
}
void PPMImage::negative() {
	unsigned int rLocal = 0, gLocal = 0, bLocal = 0;
	unsigned int redResult, greenResult, blueResult;
	int size = WIDTH * HEIGHT * 3;
	int index_1 = 0, index_2 = 0;
	do {
		redResult = 0, greenResult = 0, blueResult = 0;
		rLocal = 0, gLocal = 0, bLocal = 0;
		rLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		gLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		bLocal = (int)((unsigned char)RGB[index_1]);
		index_1++;
		//RED
		redResult = 255 - rLocal;
		RGB[index_2] = redResult;		
		//std::cout << RGB[index_2] << "\t";
		index_2++;		
		//GREEN
		greenResult = 255-gLocal;
		RGB[index_2] = greenResult;
		//std::cout << RGB[index_2] << "\t";
		index_2++;

		//BLUE
		blueResult = 255-bLocal;
		RGB[index_2] = blueResult;
		//std::cout << RGB[index_2] << "\t";
		index_2++;
		//system("pause");
	} while (index_1<size);
}
std::ostream&  operator <<(std::ostream& outputStream, PPMImage &ppmObject) {
	//Write all data to file!
	system("cls");
	outputStream << ppmObject.getMagicNumber()<<"\n";
	outputStream << ppmObject.getWidth() <<" "<<ppmObject.HEIGHT<<"\n";
	outputStream << ppmObject.getMaxColor() <<"\n";
	int size = 0;
	//outputStream << "\n";
	size = ppmObject.HEIGHT*ppmObject.WIDTH * 3;
	clock_t startTime = clock();
	outputStream.write(ppmObject.RGB, size);
	clock_t endTime = clock();
	clock_t ticks = endTime - startTime;
	double timeInSeconds = ticks / (double)CLOCKS_PER_SEC;
	std::cout << "\n\n\tProcessing completed successfully!\n\n";
	std::cout << " \t";
	system("pause");
	system("cls");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int j = 0;
	srand(time(NULL));
	std::cout << "\t OUTPUT IMAGE PROPERTIES\t|     \tCONTENT SNAPSHOT\n-----------------------------------------------------------------------------\n";

	std::cout << "  TOTAL RGB COLORS : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << size * 3 << "\t\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 15000];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";
	std::cout << "  MAGIC NUMBER     : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << ppmObject.getMagicNumber() << "\t\t\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 15000];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";

	std::cout << "  WIDTH            : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << ppmObject.getWidth() << "\t\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 200];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";	
	std::cout << "  HEIGHT           : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << ppmObject.getHeight() << "\t\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 500];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";
	std::cout << "  MAX COLOR        : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << ppmObject.getMaxColor() << "\t\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 1000];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";
	std::cout << "  IMAGE SIZE       : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << size << " Pixels\t";
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 15000];
	}
	SetConsoleTextAttribute(hConsole, j + 7);
	std::cout << "|\n";
	std::cout << "  PROCESSING TIME  : ";
	SetConsoleTextAttribute(hConsole, j + 2);
	std::cout << timeInSeconds << " Seconds\t";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "|";
	for (int i = 0;i < 35;i++) {
		SetConsoleTextAttribute(hConsole, rand() % 16);
		std::cout << ppmObject.RGB[rand() % 15000];
	}
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "|\n";
	system("pause");
	return outputStream;
}

std::istream&  operator >>(std::istream& inputStream, PPMImage &ppmObject) {
	std::string holder="";
	int size=0, height=0, width=0;
	while (inputStream >> holder) {
		if(holder=="P6")
		{
			ppmObject.setMagicNumber(holder);
		}
		else {
			std::cerr << "\nInvalid file format!!!\n";
		}
		//getting width from file
		inputStream >> holder;
		ppmObject.WIDTH = std::stoi(holder);
		width = std::stoi(holder);
		//getting height from file
		inputStream >> holder;
		ppmObject.HEIGHT = std::stoi(holder);
		height = std::stoi(holder);
		//getting max color from file
		inputStream >> holder;
		ppmObject.MAX_COLOR = std::stoi(holder);
		//RGB array size
		size = width*height * 3;
		
		if (ppmObject.RGB ==nullptr) {
			ppmObject.RGB = new char[size];
		}	
		//Ignore trailing white spaces
		inputStream.ignore();
		clock_t startTime = clock();
		std::cout << "\n\n\tLoading Image...Please wait!\n\r";
		inputStream.read(ppmObject.RGB,size);
		clock_t endTime = clock();
		system("cls");
		clock_t ticks = endTime - startTime;
		double timeInSeconds = ticks / (double)CLOCKS_PER_SEC;
		std::cout << "\n\n\tProcessing completed successfully!\n\n";
		std::cout << " \t";
		system("pause");
		system("cls");
		int size = ppmObject.getHeight()*ppmObject.getWidth();
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int j =0;
		srand(time(NULL));
		std::cout << "\tLOADED IMAGE PROPERTIES\t\t|     \tBINARY CONTENT\n-----------------------------------------------------------------------------\n";
		
		std::cout << "  TOTAL RGB COLORS : ";
		SetConsoleTextAttribute(hConsole, j+2);
		std::cout << size * 3 << "\t\t";	
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {	
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() %15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  MAGIC NUMBER     : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << ppmObject.getMagicNumber() << "\t\t\t";
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  WIDTH            : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << ppmObject.getWidth() << "\t\t";
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  HEIGHT           : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << ppmObject.getHeight() << "\t\t";
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  MAX COLOR        : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << ppmObject.getMaxColor() << "\t\t";
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  IMAGE SIZE       : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << size << " Pixels\t";
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, j + 7);
		std::cout << "|\n";
		std::cout << "  PROCESSING TIME  : ";
		SetConsoleTextAttribute(hConsole, j + 2);
		std::cout << timeInSeconds << " Seconds\t";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "|";
		for (int i = 0;i < 35;i++) {
			SetConsoleTextAttribute(hConsole, rand() % 16);
			std::cout << ppmObject.RGB[rand() % 15000];
		}
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "|\n";
		
		system("pause");		
	}
	return inputStream;
}
