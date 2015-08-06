/****************************************************************************
 Copyright (c) 2015 QuanNguyen
 
 http://quannguyen.info
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CSVParser__
#define __CSVParser__

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
