#include <iostream>
#include <string>
#include <fstream>
#include "PPMImage.h"
/*
	Name: Sylvester Zowonu
	Course: CS 332C
	Description: Image manipulation using bitwise operations to hide information.
	Instructor: Prof. Keenan Knaur
	Date: 3/2/2016
*/

unsigned int displayMenu();
unsigned int response = 0;
std::string 
	inputFileName = "",
	outputFileName = "",
	inputMessage = "",
	magicNumber="",
	picWidth = "",
	picHeight = "",
	maxColor = "";
int main() {	
	//input file object
	std::ifstream inFileHide,inFileShow,inFileGrayScale,inFileNegative,inFileSepia,inFileTest;
	//output file object
	std::ofstream outFileHide,outFileShow,outGrayScale,outNegative,outSepia,outFileTest;
	//PPMimage object
	PPMImage picture;
	std::string message = "";
	do {
		system("cls");
		response = displayMenu();
		switch (response) {
		case 1:
			//HIDE A MESSAGE
			inputMessage = "";
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;
			inFileHide.open(inputFileName, std::ios::binary);
			if (inFileHide.fail()) {
				inFileHide.clear();
				std::cerr << "No such file found!!!\n";
				//exit(0);
				system("pause");
			}
				std::cout << "\n Please enter your output PPM filename : ";
				std::cin >> outputFileName;
				outFileHide.open(outputFileName,  std::ios::binary);
				std::cout << "\n Please enter your MESSAGE : ";
				std::cin.ignore();
				std::getline(std::cin, inputMessage);
				inputMessage.append("\\0");
				inFileHide >> picture;
				inFileHide.close();
				picture.hideData(inputMessage);				
				outFileHide << picture;	
				outFileHide.close();						
			break;
		case 2:
			//RECOVER A MESSAGE
			inputMessage = "";
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;
			inFileShow.open(inputFileName, std::ios::binary);
			if (inFileShow.fail()) {
				inFileShow.clear();
				std::cerr << "No such file found!!!\n";
				//exit(0);
				system("pause");
			}
			inFileShow >> picture;
			inFileShow.close();
			
			message = picture.recoverData();
			system("cls");
			std::cout << "\n  \tRECOVERED MESSGE  \n-----------------------------------\n";
			std::cout << "  "<<message<<"\n\n  ";
			system("pause");
			break;
		case 3:
			//CONVERT TO GRAYSCALE
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;	
			inFileGrayScale.clear();
			inFileGrayScale.open(inputFileName, std::ios::binary);
			if (inFileGrayScale.fail()) {
				std::cerr << "\tNo such file found!!!\n\n";
				system("pause");
				//exit(0);
			}
			else {
				std::cout << "\nFile opened successfully!\n";
				if (inFileGrayScale.fail()) {
					inFileGrayScale.clear();
				}
				if (inFileGrayScale.is_open()) {
					inFileGrayScale >> picture;
					inFileGrayScale.close();
				}
				else {
					std::cout << "\nFailed to process file!!\n";
				}
				inFileGrayScale.~basic_ifstream();
				std::cout << "\n Please enter your output PPM filename : ";
				std::cin >> outputFileName;
				outGrayScale.open(outputFileName, std::ios::binary);
				
				//inFile.close();
				picture.grayScale();
				outGrayScale << picture;
				outGrayScale.close();
			}
			break;
		case 4:
			//CONVERT TO SEPIA
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;
			inFileSepia.clear();
			inFileSepia.open(inputFileName, std::ios::binary);
			if (inFileSepia.fail()) {
				std::cerr << "\tNo such file found!!!\n\n";
				system("pause");
				//exit(0);
			}
			else {
				std::cout << "\nFile opened successfully!\n";
				if (inFileSepia.fail()) {
					inFileSepia.clear();
				}
				if (inFileSepia.is_open()) {
					inFileSepia >> picture;
					inFileSepia.close();
				}
				else {
					std::cout << "\nFailed to process file!!\n";
				}
				std::cout << "\n Please enter your output PPM filename : ";
				std::cin >> outputFileName;
				outSepia.open(outputFileName,  std::ios::binary );
				picture.sepia();
				outSepia << picture;
				outSepia.close();
			}
			break;
		case 5:
			//CONVERT TO NEGATIVE
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;
			inFileNegative.clear();
			inFileNegative.open(inputFileName, std::ios::binary);
			if (inFileNegative.fail()) {
				std::cerr << "\tNo such file found!!!\n\n";
				system("pause");
				//exit(0);
			}
			else {
				std::cout << "\n\tFile opened successfully!\n";
				if (inFileNegative.fail()) {					
					inFileNegative.clear();
				}
				if (inFileNegative.is_open()) {				
					inFileNegative >> picture;				
					inFileNegative.close();		
					inFileNegative.~basic_ifstream();
				}
				else {
					std::cout << "\n\tFailed to process file!!\n";
					system("pause");
				}
				std::cout << "\n Please enter your output PPM filename : ";
				std::cin >> outputFileName;
				outNegative.open(outputFileName,std::ios::binary );
				picture.negative();
				outNegative << picture;
				outNegative.close();
			}
			break;
		case 6 :
			// Copy and Paste section
			std::cout << "\n Please enter your file source name : ";
			std::cin >> inputFileName;
			inFileTest.clear();
			inFileTest.open(inputFileName, std::ios::binary );
			if (inFileTest.fail()) {
				std::cerr << "\tNo such file found!!!\n\n";
				system("pause");
				//exit(0);
			}
			else {
				std::cout << "\n\tFile opened successfully!\n";
				if (inFileTest.fail()) {
					inFileTest.clear();
				}
				if (inFileTest.is_open()) {
					inFileTest >> picture;
					inFileTest.close();
					inFileTest.~basic_ifstream();
				}
				else {
					std::cout << "\n\tFailed to process file!!\n";
					system("pause");
				}
				outFileTest.open("_copy_and_paste.ppm",  std::ios::binary | std::ios::trunc);
				outFileTest << picture;
				outFileTest.close();
				system("cls");
				std::cout << "\n\tFile Copying Completed \n\t";
				system("pause");
			}
			break;
		default:
			break;
		}
		picture.~PPMImage();
	} while (response !=7 );

	return 0;
}
unsigned int  displayMenu() {
	std::cout << "\tNSA PPM Image Encryption Menu \n-------------------------------------------\n";
	std::cout << "\t1.) Hide a message.\n";
	std::cout << "\t2.) Recover a message.\n";
	std::cout << "\t3.) Convert image to grayscale.\n";
	std::cout << "\t4.) Convert image to sepia\n";
	std::cout << "\t5.) Convert image to negative.\n";
	std::cout << "\t6.) Test File I/O (Copy and Paste)\n";
	std::cout << "\t7.) Exit Program.\n";
	std::cout<<"-------------------------------------------\n  Pick your preferred Numbered choice\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\tRESPONSE : ";
	std::cin >> response;
	std::cout << "-------------------------------------------\n";
	return response;
}