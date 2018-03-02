#include <iostream>
#include <fstream>
#include <sstream>

class matrix_t{
private:
	int ** data_;
	unsigned int rows_;
	unsigned int collumns_;

public:
	matrix_t() {
		data_ = nullptr;
		rows_ = 0;
		collumns_ = 0;
	}

	matrix_t(const unsigned int rows, const unsigned int collumns) {
		rows_ = rows;
		collumns_ = collumns;
		
		data_ = new int * [rows_];
		for (unsigned int i = 0; i < rows_; ++i) {
			data_[i] = new int[collumns_];
		}
	}

	matrix_t & operator = (matrix_t const & matrix) {
		std::cout << "per" << std::endl;
		if (this != &matrix) {
			for (unsigned int i = 0; i < rows_; ++i) {
				delete[] data_[i];
			}
			delete[] data_;
			
			rows_ = matrix.rows_;
			std::cout << matrix.rows_ << std::endl;
			collumns_ = matrix.collumns_;
			data_ = new int * [rows_];
			for (unsigned int i = 0; i < rows_; ++i) {
				data_[i] = new int[collumns_];
				for (unsigned int j = 0; j < collumns_; ++j) {
					data_[i][j] = matrix.data_[i][j];
				}
			}
		}

		return * this;
	}

	matrix_t add(matrix_t const & other) const {
		
		if (rows_ == other.rows_ &&
			collumns_ == other.collumns_) {

			matrix_t result(rows_, collumns_);
			
			for (unsigned int i = 0; i < rows_; ++i) {
				for (unsigned int j = 0; j < collumns_; ++j) {
					result.data_[i][j] = data_[i][j] + other.data_[i][j];
				}
			}
			return result;
		}
		else {
			error();
			exit(0);
		}
	}
  
	std::ifstream & read( std::ifstream & stream, const std::string fileName ) {
		stream.open(fileName.c_str());

		char symb;
		if (stream.is_open() &&
			stream >> rows_ &&
			stream >> symb && symb == ',' &&
			stream >> collumns_) {
			data_ = new int *[rows_];
			for (unsigned int i = 0; i < rows_; ++i) {
				data_[i] = new int[collumns_];
				for (unsigned int j = 0; j < collumns_; ++j) {
					stream >> data_[i][j];
				}
			}
		}
		else {
			error();
		}
		return stream;
	}

	std::ofstream & write( std::ofstream & stream, const std::string fileName ) const {
		stream.open(fileName.c_str());

		if (stream.is_open()) {
			for (unsigned int i = 0; i < rows_; ++i) {
				for (unsigned int j = 0; j < collumns_; ++j) {
					stream << data_[i][j] << '\t';
					if (j == collumns_ - 1) {
						stream << '\n';
					}
				}
			}
		}
		else {
			error();
		}
		return stream;
	}

	void error() const {
		std::cout << "An error has occured while reading input data__\n";
	}

	~matrix_t() {
		for (unsigned int i = 0; i < rows_; ++i) {
			delete[] data_[i];
		}
		delete[] data_;
	}
};


int main()
{
	matrix_t A;

	std::string line;
	std::getline(std::cin, line);

	std::istringstream stroka(line);
	std::string fileNameA;
	
	std::ifstream streamA;
	
	stroka >> fileNameA;
	char symb;
	if ((A.read(streamA, fileNameA)) && (stroka >> symb)) {
		if (symb == '+' || symb == '-' || symb == '*' ) {
			matrix_t B;
			matrix_t R;

			std::string fileNameB, fileNameR = "result.txt";
			std::ifstream streamB;
			stroka >> fileNameB;
			std::ofstream streamR;

			if (B.read(streamB, fileNameB)) {
	             
				if (symb == '+') {
					R = A.add(B); // вот здесь
					R.write(streamR, fileNameR);
				}
			}
			else {
				B.error();
			}
			streamB.close();
			streamR.close();
		}
		else {
			A.error();
		}
	}
	else {
		A.error();
	}
	
	streamA.close();
	std::cin.get();
    return 0;
}

