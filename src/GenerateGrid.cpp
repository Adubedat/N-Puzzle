#include "GenerateGrid.hpp"

Grid* const             GenerateRandomGrid(int const &size) {

    std::vector<int>  matrix(size * size);
    unsigned    seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < size * size; i++) {
        matrix[i] = i;
    }

    std::shuffle(matrix.begin(), matrix.end(), std::default_random_engine(seed));
    return (new Grid(size, matrix));
}

Grid* const             GenerateGridFromFile(std::string const &src) {
    std::ifstream   myFile(src);
    Grid*           grid;

    if (myFile.is_open())
        grid = parseFile(myFile);
    else
        throw SyntaxException("Error : This file can not be opened");
    return (grid);
}

Grid*                   parseFile(std::ifstream &ifs) {

    std::string         line;
    std::vector<int>    finalVector;
    std::vector<int>    lineVector;
    int                 size;

    size = 0;
    while (std::getline(ifs, line)) {
        parseLine(line, lineVector);
        if (size == 0 && lineVector.size() > 1)
            throw SyntaxException("Error : The first line must specify the puzzle size");
        else if (size != 0 && lineVector.size() != size)
            throw SyntaxException("Error : Each line must contain " + std::to_string(size) + " numbers");
        else if (lineVector.size() == 1)
            size = lineVector[0];
        else {
            finalVector.insert(finalVector.end(), lineVector.begin(), lineVector.end());
        }
        lineVector.clear();
    }
    if (finalVector.empty() || size <= 0)
        throw SyntaxException("Error : Unvalid puzzle description");
    else if (finalVector.size() > size * size)
        throw SyntaxException("Error : Unvalid grid description, too much numbers");
    else if (finalVector.size() < size * size)
        throw SyntaxException("Error : Unvalid grid description, not enough numbers");
    checkMatrixNumbers(finalVector, size);
    return (new Grid(size, finalVector));
}

void                    parseLine(std::string &line, std::vector<int> &v) {

    for (std::string::iterator it = line.begin(); it != line.end(); it++) {
        if (*it == '#')
            return ;
        else if (*it == ' ' || *it == '\t')
            ;
        else if (isdigit(*it))
            v.push_back(parseWord(it));
        else {
            throw SyntaxException("Error : Unexpected character found");
        }
    }
}

int                     parseWord(std::string::iterator &it) {

    std::string     str;

    while (isdigit(*it)) {
        str += *it;
        ++it;
    }
    --it;
    return (std::stoi(str));
}

void                    checkMatrixNumbers(std::vector<int> matrix, int const &size) {

    std::sort(matrix.begin(), matrix.end());

    for (int i = 0; i < matrix.size(); i++) {
        if (i != matrix[i])
            throw SyntaxException("Error : puzzle must contain every values from 0 to " + std::to_string(size * size - 1));
    }
}
/*
**                  Exception class
*/

SyntaxException::SyntaxException(std::string msg) :
	_msg(msg)
{}

const char*		SyntaxException::what(void) const throw() {

	return (_msg.c_str());
}
