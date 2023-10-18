#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {

  int* SeamArr= new int[length];

	for(int k = 0; k < length; ++k){
		SeamArr[k] = 0;
	}

	return SeamArr;
}

void deleteSeam(int* seam) {

  delete[]seam;

}

bool loadImage(string filename, Pixel** image, int width, int height) {

  //open file
  ifstream ifs (filename);
  ifstream copy (filename);
  ifstream check (filename);

  //check stream opened
  if (ifs.is_open() == false){
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  //check for type 3
  char type[3];

  ifs >> type;

  if ((toupper(type[0]) != 'P')) {
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  if (type[1] != '3') {
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  copy >> type;
  check>> type;

  //check non integer value
  
  int w2 = 0;
  int h2 = 0;

  ifs >> w2;
  ifs >> h2;

  int wconv = 0;
  int hconv = 0;

  string w2str = "";
  string h2str = "";

  check >> w2 >> h2;
  copy >> w2str >> h2str;

  try{
    wconv = stoi(w2str);
    hconv = stoi(h2str);
  }
  catch(...){
    cout << "Error: read non-integer value";
    return false;
  }


  w2 = wconv;
  h2 = hconv;

  if ((h2 == height) == false) {
    cout << "Error: input height (" << height  << ") does not match value in file (" << h2 << ")" << endl;
    return false;
  }

  if ((w2 == width) == false) {
    cout << "Error: input width (" << width << ") does not match value in file (" << w2 << ")" << endl;
    return false;
  }
  



  //rgb check

  int numvals = (width * height) * 3; 
  int* values = new int[numvals]{};

  int colorVals = 0;


  string tester3;


  while (copy >> tester3) 
  {

    int rgbcheck = 0;
    string kstore = "";
    check >> kstore;


    try{
      rgbcheck = stoi(kstore);
    }
    catch(...){
      cout << "Error: read non-integer value";
      return false;
    }


    if(rgbcheck < 0){
      cout << "Error: invalid color value " << rgbcheck;
      return false;
    }else if (rgbcheck > 255){
      cout << "Error: invalid color value " << rgbcheck;
      return false;
    }

    colorVals = colorVals + 1;
  }

  if(colorVals > numvals){
    cout << "Error: too many color values";
    return false;
  }

  if(colorVals < numvals){
    cout << "Error: not enough color values";
    return false;
  }

  
  
  for(int i = 0; i < numvals; i++){
    ifs >> values[i];
  }
  
  int count = 0;

  for(int i = 0; i < h2; i++){


    for(int l = 0; l < w2; l++){
      
      
      int specific[3] = {};


      for(int r = 0; r < 3; r++){
        specific[r] = values[count];
        count++;
      }


      int re = specific[0];
      int gre = specific[1];
      int blu = specific[2];

      image[l][i] = {re, gre, blu};


    }

  }

  ifs.close();
  delete[] values;

  return true;
}

bool outputImage(string filename, const Pixel*const* image, int width, int height) {

  ofstream ofs (filename);

  if (!ofs.is_open()) {
    cout << "Error: failed to open input file " << filename << endl;
    return false;
  }

  ofs << "P3" << endl;
  ofs << width << " " << height << endl; 
	ofs << "255" << endl;

  for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
  }

  ofs.close();
  return true;
}


int energy(const Pixel*const* image, int column, int row, int width, int height) { 

    int toprow = row - 1;
    int bottomrow = row + 1;
    int leftcol = column - 1;
    int rightcol = column + 1;

    if (row == 0) {
        toprow = height - 1;
    }
    if (row == height - 1) {
        bottomrow = 0;
    }
    if (column == 0) {
        leftcol = width - 1;
    }
    if (column == width - 1) {
        rightcol = 0;
    }


  int rowDiffRed = image[column][bottomrow].r - image[column][toprow].r;
  int colDiffRed = image[rightcol][row].r - image[leftcol][row].r;

	int rowDiffGreen = image[column][bottomrow].g - image[column][toprow].g;
  int colDiffGreen = image[rightcol][row].g - image[leftcol][row].g;

	int rowDiffBlue = image[column][bottomrow].b - image[column][toprow].b;
  int colDiffBlue = image[rightcol][row].b - image[leftcol][row].b;

	int rowSum = pow(rowDiffRed, 2.0) + pow(rowDiffGreen, 2.0) + pow(rowDiffBlue, 2.0);
	int colSum = pow(colDiffRed, 2.0) + pow(colDiffGreen, 2.0) + pow(colDiffBlue, 2.0);
	
	return colSum + rowSum;

}




// implement for part 2


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  
  int sumSeamEn {};

  seam[0] = start_col;

  int v1 = start_col;

  int v2 = 0;

  sumSeamEn = energy(image,v1,v2,width,height);

  for(int i = 1; i < height; i++){
    
    v2+=1;

    if(v1 == (width-1)){

      if((energy(image,v1-1,v2,width,height)) < (energy(image,v1,v2,width,height))){
        sumSeamEn += energy(image,v1-1,v2,width,height);
        v1 --;
      }

      else if((energy(image,v1,v2,width,height) <= energy(image,v1-1,v2,width,height))){
        sumSeamEn += energy(image,v1,v2,width,height);
      }
    }
    
    else if(v1 == 0){

      if((energy(image,v1+1,v2,width,height) < energy(image,v1,v2,width,height))){

        sumSeamEn += energy(image,v1+1,v2,width,height);
        v1 ++;

      }

      else if((energy(image,v1,v2,width,height) <= energy(image,v1+1,v2,width,height))){

        sumSeamEn += energy(image,v1,v2,width,height);

      }

    }

    else{

      bool check1 = (energy(image,v1,v2,width,height) <= energy(image,v1+1,v2,width,height)) && (energy(image,v1,v2,width,height) <= energy(image,v1-1,v2,width,height));
      bool check2 = (energy(image,v1,v2,width,height) >= energy(image,v1+1,v2,width,height)) && (energy(image,v1-1,v2,width,height) >= energy(image,v1+1,v2,width,height));

      if(check1){

        sumSeamEn += energy(image,v1,v2,width,height);

      }

      else if(check2){
        sumSeamEn += energy(image,v1+1,v2,width,height);
        v1 ++;
      }

      else{
        sumSeamEn += energy(image,v1-1,v2,width,height);
        v1 --;
      }
    }

    seam[i] = v1;

  }

  return sumSeamEn;

}




int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {

  int sumSeamEn {};

  seam[0] = start_row;

  int v1 = 0;

  int v2 = start_row;

  sumSeamEn = energy(image,v1,v2,width,height);

  for(int i = 1; i < width; i++){
    
    v1+=1;

    if(v2 == (height-1)){

      if((energy(image,v1-1,v2,width,height)) < (energy(image,v1,v2,width,height))){
        sumSeamEn += energy(image,v1-1,v2,width,height);
        v2 --;
      }

      else if((energy(image,v1,v2,width,height) <= energy(image,v1-1,v2,width,height))){
        sumSeamEn += energy(image,v1,v2,width,height);
      }
    }
    
    else if(v2 == 0){

      if((energy(image,v1+1,v2,width,height) < energy(image,v1,v2,width,height))){

        sumSeamEn += energy(image,v1+1,v2,width,height);
        v2 ++;

      }

      else if((energy(image,v1,v2,width,height) <= energy(image,v1+1,v2,width,height))){

        sumSeamEn += energy(image,v1,v2,width,height);

      }

    }

    else{

      bool check1 = (energy(image,v1,v2,width,height) <= energy(image,v1+1,v2,width,height)) && (energy(image,v1,v2,width,height) <= energy(image,v1-1,v2,width,height));
      bool check2 = (energy(image,v1,v2,width,height) >= energy(image,v1+1,v2,width,height)) && (energy(image,v1-1,v2,width,height) >= energy(image,v1+1,v2,width,height));

      if(check1){

        sumSeamEn += energy(image,v1,v2,width,height);

      }

      else if(check2){
        sumSeamEn += energy(image,v1+1,v2,width,height);
        v2 ++;
      }

      else{
        sumSeamEn += energy(image,v1-1,v2,width,height);
        v2 --;
      }
    }

    seam[i] = v2;

  }

  return sumSeamEn;

}



int* findMinVerticalSeam(Pixel** image, int width, int height) {

  int* SeamSmall = createSeam(height);

	int* small = createSeam(height);

	int small2 = loadVerticalSeam(image, 0, width, height, SeamSmall);
  
    
	for(int c1 = 1; c1 < width; c1++){
		
    if(loadVerticalSeam(image, c1, width, height, small) < small2){

			small2 = loadVerticalSeam(image, c1, width, height, SeamSmall);

    }

  }
	
  //prevent memory overflow
	deleteSeam(small);

	return SeamSmall;

}



int* findMinHorizontalSeam(Pixel** image, int width, int height) {

  int* SeamSmall = createSeam(width);

	int* small = createSeam(width);

	int small2 = loadVerticalSeam(image, 0, width, height, SeamSmall);
  
    
	for(int c1 = 1; c1 < height; c1++){
		
    if(loadVerticalSeam(image, c1, width, height, small) < small2){

			small2 = loadVerticalSeam(image, c1, width, height, SeamSmall);

    }

  }
	
  //prevent memory overflow
	deleteSeam(small);

	return SeamSmall;

}



void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {

  for (int c1 = 0; c1 < height; c1+=1){

    for (int c2 = verticalSeam[c1]; c2 < (width - 1); c2++){

      image[c2][c1] = image[c2 + 1][c1];

    }

  }

}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  
  for (int c1 = 0; c1 < width; c1+=1){

    for (int c2 = horizontalSeam[c1]; c2 < (height - 1); c2++){

      image[c1][c2] = image[c1][c2 + 1];

    }

  }

}


