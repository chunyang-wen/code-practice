/**********************************************************
* matrixMul.cpp
* to get the result of the multiplication of two matrices
* it uses a divide and conquer method to do the trick.
* suppose x = [A B; C D] y = [E F;G H]
* then x*y = [AE + BG AF + BH;CE + DG CF + DH]
* author: Zebras Wen
* date: 2012.09.28
* version: 0.0
* reference: 1969,the German mathematician Volker Strassen
***********************************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void print2DArr(int** a,int col, int row);

class Matrix {
private:
    int** head; // start element of matrix.
    int col;   // columns
    int row;   // rows
	int shift_row; // rows and columns to be shifted from head
	int shift_col;
	int **data; // data position, can be optimized using head
public: 
    Matrix(int** a, int col, int row, 
           int shift_row, int shift_col){
        this->col = col;
        this->row = row;
		head = a;
		data = new int*();
        // get the address of matrix.
        *data = *(a + shift_row) + shift_col; 
		this->shift_row = shift_row;
		this->shift_col = shift_col;
    }
    /**
     * matrices product function
     * a, b are the matrices to multiplied, c is the result.
     * There are initialized outside the function
     * 
     */
    void mul(Matrix a, Matrix b, Matrix c) {
        // quit the recursive method condition
        if (a.col == 1 && a.row == 1 &&
            b.col == 1 && b.row == 1) {
                **(c.data) = **(c.data) + 
                           **(a.data) * (**(b.data));
                return;
        }
        
        // declare the variable to save the splited matrix
        Matrix *a_1st = NULL;
        Matrix *a_2nd = NULL;
        Matrix *a_3rd = NULL;
        Matrix *a_4th = NULL;
        
        Matrix *b_1st = NULL;
        Matrix *b_2nd = NULL;
        Matrix *b_3rd = NULL;
        Matrix *b_4th = NULL;
        
        Matrix *c_1st = NULL;
        Matrix *c_2nd = NULL;
        Matrix *c_3rd = NULL;
        Matrix *c_4th = NULL;
        
        // split the matirx, 
        // if no split is made, use the variable directly.
        if (1 == b.row) {
            // one row, multiple columns
            if (1 != b.col) {
				b_1st = new Matrix(b.head, b.col/2, b.row,
                b.shift_row, b.shift_col);
                // int** q = NULL;
				// q = new int*();
                // *q = *(b.head) + b.col/2;
				b_2nd = new Matrix(b.head, b.col - b.col/2,
                b.row,b.shift_row,b.shift_col + b.col/2);
            }
         }
         else {
            // multiple columns and rows
             if (1 != b.col) {
				 b_1st = new Matrix(b.head, b.col/2, b.row/2,
                       b.shift_row,b.shift_col);
				 b_2nd = new Matrix(b.head,
                       b.col - b.col/2, b.row/2,
                       b.shift_row,b.shift_col+b.col/2);
				 b_3rd = new Matrix(b.head, b.col/2,
                       b.row - b.row/2,
                       b.shift_row+b.row/2,b.shift_col);
				 b_4th = new Matrix(b.head, b.col - b.col/2, 
                       b.row - b.row/2,b.shift_row+b.row/2,
                       b.shift_col+b.col/2);              
             }
             else {
                // one colum, multiple rows
				 b_1st = new Matrix(b.head, b.col, b.row/2,
                 b.shift_row,b.shift_col);
				 b_3rd = new Matrix(b.head, 
                       b.col, b.row - b.row/2,
                       b.shift_row+b.row/2,b.shift_col); 
             }
         }
         
         // repeat from b
         if (1 == a.row) {
            if (1 != a.col) {
				a_1st = new Matrix(a.head, a.col/2, a.row, 
                a.shift_row, a.shift_col);
				a_2nd = new Matrix(a.head, 
                      a.col - a.col/2, a.row,
                      a.shift_row,a.shift_col + a.col/2);
            }
         }
         else {
             if (1 != a.col) {
				 a_1st = new Matrix(a.head, a.col/2, a.row/2,
                 a.shift_row,a.shift_col);
				 a_2nd = new Matrix(a.head, a.col - a.col/2, 
                 a.row/2,a.shift_row,a.shift_col+a.col/2);
				 a_3rd = new Matrix(a.head,
                       a.col/2, a.row - a.row/2,
                       a.shift_row+a.row/2,a.shift_col);
				 a_4th = new Matrix(a.head, a.col - a.col/2, 
                       a.row - a.row/2,
                       a.shift_row+a.row/2,
                       a.shift_col+a.col/2);              
             }
             else {
                b_1st = new Matrix(a.head, a.col, a.row/2,
                a.shift_row,a.shift_col);
				a_3rd = new Matrix(a.head, 
                      a.col, a.row - a.row/2,
                      a.shift_row+a.row/2,a.shift_col); 
             }
         }
         
         // repeat from b;
		 if (1 == c.row) {
            if (1 != c.col) {
				c_1st = new Matrix(c.head, c.col/2, c.row, 
                c.shift_row, c.shift_col);
				c_2nd = new Matrix(c.head, c.col - c.col/2, 
                c.row,c.shift_row,c.shift_col + c.col/2);
            }
			else {
				c_1st = &c;
				c_2nd = &c;
				c_3rd = &c;
				c_4th = &c;
			}
         }
         else {
             if (1 != c.col) {
				 c_1st = new Matrix(c.head, c.col/2, c.row/2,
                 c.shift_row,c.shift_col);
				 c_2nd = new Matrix(c.head, c.col - c.col/2, 
                 c.row/2,c.shift_row,c.shift_col+c.col/2);
				 c_3rd = new Matrix(c.head, 
                      c.col/2, c.row - c.row/2,
                 c.shift_row+c.row/2,c.shift_col);
				 c_4th = new Matrix(c.head, c.col - c.col/2, 
                       c.row - c.row/2, 
                       c.shift_row+c.row/2,
                       c.shift_col+c.col/2);              
             }
             else {
                c_1st = new Matrix(c.head, c.col, c.row/2,
                c.shift_row,c.shift_col);
				c_3rd = new Matrix(c.head, c.col,
                      c.row - c.row/2,
                      c.shift_row+c.row/2,c.shift_col); 
             }
         }
         
         // calculation, when rows and columns are mentioned,
         // we mean blocks.
        if (a_1st == NULL) {
            // no decomposition
            if (b_2nd == NULL) {
                mul(a, *b_1st, *c_1st);
                mul(a, *b_3rd, *c_3rd);
            }
            else if (b_3rd == NULL) {
                mul(a, *b_1st, *c_1st);
                mul(a, *b_2nd, *c_2nd);
            }
            else {
                mul(a, *b_1st, *c_1st);
                mul(a, *b_2nd, *c_2nd);
                mul(a, *b_3rd, *c_3rd);
                mul(a, *b_4th, *c_4th);
            }
        }
        else if (a_2nd == NULL) {
            if (b_1st == NULL) {
                // no decomposition
                mul(*a_1st, b, *c_1st);
                mul(*a_3rd, b, *c_3rd);
            }
            // two rows
            else if (b_2nd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_1st, *b_3rd, *c_1st);
                mul(*a_3rd, *b_1st, *c_3rd);
                mul(*a_3rd, *b_3rd, *c_3rd);
            }
            // two columns
            else if (b_3rd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_3rd, *b_1st, *c_3rd);
                mul(*a_3rd, *b_2nd, *c_4th);
            }
            // two columns and two rows
            else {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_1st, *b_3rd, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_1st, *b_4th, *c_2nd);
                mul(*a_2nd, *b_1st, *c_3rd);
                mul(*a_2nd, *b_3rd, *c_3rd);
                mul(*a_2nd, *b_2nd, *c_4th);
                mul(*a_2nd, *b_4th, *c_4th);
            }
        }
        // the same caterogy as a
        else if (a_3rd == NULL) {
            if (b_1st == NULL) {
                // no decomposition
                mul(*a_1st, b, *c_1st);
                mul(*a_2nd, b, *c_2nd);
            }
            // two rows
            else if (b_2nd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_3rd, *c_1st);
            }
            // two columns
            else if (b_3rd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_1st, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_2nd, *b_2nd, *c_2nd);
            }
            // two columns and two rows.
            else {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_3rd, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_2nd, *b_4th, *c_2nd);
            }
        }
        // a full blocks
        else {
            // no decomposition
            if (b_1st == NULL) {
                mul(*a_1st, b, *c_1st);
                mul(*a_2nd, b, *c_1st);
                mul(*a_3rd, b, *c_3rd);
                mul(*a_4th, b, *c_3rd);
            }
            // two rows
            else if (b_2nd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_3rd, *c_1st);
                mul(*a_3rd, *b_1st, *c_3rd);
                mul(*a_4th, *b_3rd, *c_3rd);
            }
            // tow columns
            else if (b_3rd == NULL) {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_1st, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_2nd, *b_2nd, *c_2nd);
                mul(*a_3rd, *b_1st, *c_3rd);
                mul(*a_4th, *b_1st, *c_3rd);
                mul(*a_3rd, *b_2nd, *c_4th);
                mul(*a_4th, *b_2nd, *c_4th);
            }
            // two columns and two rows
            else {
                mul(*a_1st, *b_1st, *c_1st);
                mul(*a_2nd, *b_3rd, *c_1st);
                mul(*a_1st, *b_2nd, *c_2nd);
                mul(*a_2nd, *b_4th, *c_2nd);
                mul(*a_3rd, *b_1st, *c_3rd);
                mul(*a_4th, *b_3rd, *c_3rd);
                mul(*a_3rd, *b_2nd, *c_4th);
                mul(*a_4th, *b_4th, *c_4th);
            }
        }
        // when we finish the process,
        // the matrices automatically combine.
        delete a_1st;
        delete a_2nd;
        delete a_3rd;
        delete a_4th;
        
        delete b_1st;
        delete b_2nd;
        delete b_3rd;
        delete b_4th;
        
        delete c_1st;
        delete c_2nd;
        delete c_3rd;
        delete c_4th;
    }
    ~Matrix() {
        delete data;
    }
    
};

void print2DArr(int** a,int col, int row) {
	// int** b = new int*();
	// int** c = a;
	// *b = new int();
    for (int i = 0; i < row; i++) {
		
        for (int j = 0; j< col; j++) {
			// *b = *(a+i) + j;
			// **b = -1;
			//cout<<**b<<" ";
            cout<<*(*(a+i) + j)<<" ";
        }
        cout<<endl;
    }
}

int main(int argc, char*agrv[]) {

	// initial matrix
	// srand(5000);
    int** a = NULL;
	int col_a = 7;
	int row_a = 4;
    a = new int*[row_a];
	for (int i = 0; i < row_a; i++) {
		*(a+i) = new int[col_a];
		for (int j = 0; j< col_a; j++) {
			*(*(a+i) + j) = rand()%5;
		}
	}
    // *(*(a+1)+1) = 4;
    int** b = NULL;
	int col_b = 2;
	int row_b = col_a;
    b = new int*[row_b];
	for (int i = 0; i < row_b; i++) {
		*(b+i) = new int[col_b];
		for (int j = 0; j< col_b; j++) {
			*(*(b+i) + j) = rand()%1000;
		}
	}
    int** c = NULL;
	int col_c = col_b;
	int row_c = row_a;
	c = new int*[row_c];
	for (int i = 0; i < row_c; i++) {
		*(c+i) = new int[col_c];
		for (int j = 0; j< col_c; j++) {
			*(*(c+i) + j) = 0;
		}
	}

    Matrix* aa = new Matrix(a,col_a,row_a,0,0);
	Matrix* bb = new Matrix(b,col_b,row_b,0,0);
    Matrix* cc = new Matrix(c,col_c,row_c,0,0);    
    aa->mul(*aa,*bb,*cc);
    print2DArr(a,col_a,row_a);
	print2DArr(b,col_b,row_b);
	print2DArr(c,col_c,row_c);

    // release the memory allocated
	for (int i = 0; i < row_a; i++)
		delete []*(a+i);
	delete []a;
	a = NULL;

	for (int i = 0; i < row_b; i++)
		delete []*(b+i);
	delete []b;
	b = NULL;

	for (int i = 0; i < row_c; i++)
		delete []*(c+i);
	delete []c;
	c = NULL;
    return EXIT_SUCCESS;
}