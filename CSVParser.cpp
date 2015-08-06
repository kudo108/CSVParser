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

#include "CSVParser.h"
#include "cocos2d.h"

USING_NS_CC;

CSVParser::~CSVParser(void)
{
    
}

void CSVParser::splitString( const std::string& str, std::vector<std::string>& tokens, const char& delimiters )
{
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    
    while (std::string::npos != pos || std::string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos-lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}


void CSVParser::split( std::vector<std::string>& field, std::string line )
{
    std::string fld;
    unsigned int i,j = 0;
    
    if( line.length() ==0 ){
        return;
    }
    
    i = 0;
    
    do{
        if(j<line.length() && line[i]=='"'){
            j = advquoted(line, fld, ++i);
        }
        else{
            j = advplain(line, fld, i);
        }
        
        field.push_back(fld);
        i = j+1;
        
    } while (j<line.length());
}



int CSVParser::advplain( const std::string& s, std::string& fld, int i)
{
    unsigned int j;
    j = s.find_first_of(fieldsep, i);
    
    if(j>s.length()){
        j=s.length();
    }
    
    fld = std::string(s,i,j-i);
    
    return j;
}

int CSVParser::advquoted( const std::string& s, std::string& fld, int i)
{
    unsigned int j;
    fld = "";
    
    for (j=i; j<s.length(); ++j){
        
        if(s[j]=='"' && s[++j]!='"'){
            unsigned int k = s.find_first_of(fieldsep, j);
            if(k>s.length()){
                k = s.length();
            }
            for(k-=j; k-->0;){
                fld += s[j++];
            }
            break;
        }
        
        fld += s[j];
    }
    
    return j;
}

bool CSVParser::openFile( const char* fileName )
{
    auto fileData = FileUtils::getInstance()->getDataFromFile(fileName);
    std::string str = std::string((const char *)fileData.getBytes());
    
    std::vector<std::string> line;
    splitString(str, line, '\r');
    
    for(unsigned int i=0; i<line.size(); ++i){
        std::vector<std::string> field;
        split(field, line[i]);
        data.push_back(field);
        cols = std::max(cols, (int)field.size());
    }
    
    return true;
}

const char* CSVParser::getData(unsigned int rows, unsigned int cols )
{
    if (rows >= data.size() || cols >= data[rows].size()){
        return "";
    }
    
    return data[rows][cols].c_str();
}

int CSVParser::findColsData( int cols, const char* value )
{
    for (unsigned int i = 0; i < data.size(); ++i){
        if(strcmp(getData(i,cols),value)==0){
            return i;
        }
    }
    
    return -1;
}