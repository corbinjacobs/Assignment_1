#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

double getVal(double B[], int N, int i, int j);
//double getVal(double* B, int i, int j); k = i*N + j this helps find a location in a matrix / 2d array.

class Matrix{ //matrix class contains the parametres 
public:
	Matrix getBlock(int startrow, int endrow, int startcolum, int endcolum);//memeber function for the getblock sections on the matrix
	void setvalues(int i, int j, double values){ data[i*N + j] = values; }//puts the values into the equation to place them in the crorect location in the matrix.
	double equation(int i, int j) const {	return data[i*N + j]; } //this is done in one line not outside of the class
	Matrix(const Matrix& C);
	Matrix(int sizeR, int sizeC, double val);
	Matrix(int sizeR, int sizeC, double* pData);
	//~Matrix();

private:
	int M; //number of rows
	int N; //number of columns
	double* data;

};

Matrix::Matrix(int sizeR, int sizeC, double Val) //original matrix values stack data
{
	M = sizeR;//declaring the parametres of the matrix
	N = sizeC;
	data = new double[M*N];//creating a new memory allocation in the heap.

	for (int i = 0; i < M; i++)//the for loop searches through each colloum and row.
	{
		for (int j = 0; j < N; j++)
		{
			data[i*N + j] = Val;
		}
	}
}

Matrix::Matrix(int sizeR, int sizeC, double* input_data) //heap data
{
	M = sizeR;//declaring the parametres of the matrix
	N = sizeC;
	data = new double[M*N];//creating a new memory allocation in the heap.

	for (int i = 0; i < M; i++)//the for loop searches through each colloum and row.
	{
		for (int j = 0; j < N; j++)
		{
			data[i*N + j] = input_data[i*N + j];//
		}
	}
}
Matrix::Matrix(const Matrix & obj)
{
	
};

Matrix Matrix::getBlock(int startrow, int endrow, int startcolum, int endcolum)//pulls out the requested block form the input values.
{
	Matrix C(endrow - startrow + 1, endcolum - startcolum + 1, 0.0);
	for (int i = startrow; i <= endrow; i++)
	{
		for (int j = startcolum; j <= endcolum; j++)
		{
			C.setvalues(i - startrow, j - startcolum, data[i*N + j]);
		}
	}
	return C;
};

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);


int main()
{
	// This part will show you how to use the two functions.
	
	//M and N represent the number of rows and columns in the image,
	//e.g. for task 1: logo_with_noise and logo_shuffled, M = 512, N = 512
	//e.g. for task 2, Cluttered_scene, M = 768, N = 1024
	//e.g. for task 2, Wally_grey, M = 49, N =  36
	const int M = 512; 
	const int N = 512;//the values of the matrix are constant.

	// input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed 
	// inside readTXT. readTXT will read an image (in .pgm format) of size MxN and will  store the result in input_data.
	// once you're done with data DO NOT forget to delete the memory as in the end of this main() function
	double* input_data = 0;
	
	cout << endl;
	cout << "Data from text file -------------------------------------------" << endl;
	
	// .pgm image is stored in inputFileName, change the path in your program appropriately
	char* inputFileName = "C:\\Users\\Corbin\\Downloads\\Assignment 1 - files\\Assignment 1 - files\\Task 1 - files\\logo_shuffled.txt"; 
	input_data = readTXT(inputFileName, M, N);
	
	Matrix A(M, N, input_data); //stating the values in the matrix and where the image is.

	cout << A.equation(4, 3) << endl;
	system("PAUSE");

	// for (int i = startrow; int i < 170 = 255 else 1; i <= endrow; i++) not sure if needed but trying to take the data and change its colour value
	//{
		//for (int j = startcolum; j <= endcolum; j++)
		//{
			//C.setvalues(i - startrow, j - startcolum, data[i*N + j]);
		//}
	//}
	//return C;
//};
	/*

	CODE TO PROCESS input_data SHOULD BE WRITTEN HERE!! (after removing the comments:)

	*/
	//forloop here for the matrix
	// writes data back to .pgm file stored in outputFileName
	char* outputFileName = "C:\\Users\\Corbin\\Downloads\\Assignment 1 - files\\Assignment 1 - files\\Task 1 - files\\logo_restored.pgm";
	// Use Q = 255 for greyscale images and 1 for binary images.
	int Q = 255; 
	WritePGM(outputFileName, input_data, M, N, Q); 

	delete [] input_data;

	cout << endl;
	system("PAUSE");

	return 0;
}


// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
        // cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file"; 
  //cout << i;

  return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

 int i, j;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out|ios::binary|ios::trunc);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();

 delete [] image;

}