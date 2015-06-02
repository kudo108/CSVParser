//
//  CSVParser.h
//  
//
//  Created by Quan Nguyen on 10/10/14.
//
//

#ifndef __CSVParser__
#define __CSVParser__

#include <stdio.h>
#include <vector>
#include <iostream>

class CSVParser
{
public:
    ~CSVParser(void);
    CSVParser(std::istream& fin = std::cin, std::string sep = ","):
    fieldsep(sep),
    cols(0)
    {
        
    }
    
    std::vector<std::vector<std::string> > data;
    bool openFile(const char* fileName);
    const char* getData(unsigned int rows, unsigned int cols);
    int findColsData(int cols, const char* value);
    
    inline int getCols(){return cols;}
    inline int getRows(){return data.size();}
    
private:
    std::string fieldsep;
    int cols;
    
    void splitString(const std::string& str, std::vector<std::string>& tokens, const char& delimiters);
    void split(std::vector<std::string>& field, std::string line);
    int advplain(const std::string& line, std::string& fld, int);
    int advquoted(const std::string& line, std::string& fld, int);
};

#endif /* defined(__CSVParser__) */
