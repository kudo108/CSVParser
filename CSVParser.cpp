//
//  CSVParser.cpp
//  
//
//  Created by Quan Nguyen on 10/10/14.
//
//

#include "CSVParser.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

CSVParser::~CSVParser(void)
{
    
}

void CSVParser::splitString( const string& str, vector<string>& tokens, const char& delimiters )
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos-lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}


void CSVParser::split( vector<string>& field, string line )
{
    string fld;
    unsigned int i,j=0;
    
    if( line.length() ==0 )
        return;
    i=0;
    
    do
    {
        if(j<line.length() && line[i]=='"')
            j = advquoted(line, fld, ++i);
        else
            j = advplain(line, fld, i);
        
        field.push_back(fld);
        i = j+1;
    } while (j<line.length());
}



int CSVParser::advplain( const string& s, string& fld, int i)
{
    unsigned int j;
    j = s.find_first_of(fieldsep, i);
    if(j>s.length())
        j=s.length();
    fld = string(s,i,j-i);
    return j;
}

int CSVParser::advquoted( const string& s, string& fld, int i)
{
    unsigned int j;
    fld = "";
    for (j=i; j<s.length(); ++j)
    {
        if(s[j]=='"' && s[++j]!='"')
        {
            unsigned int k = s.find_first_of(fieldsep, j);
            if(k>s.length())
                k = s.length();
            for(k-=j; k-->0;)
                fld += s[j++];
            break;
        }
        fld += s[j];
    }
    return j;
}

bool CSVParser::openFile( const char* fileName )
{
    string pathKey = FileUtils::getInstance()->fullPathForFilename(fileName);
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(pathKey.c_str(), "r", &bufferSize);
    
    string s = (char*)pBuffer;
    string str = s.substr(0,bufferSize);
    
    vector<string> line;
    splitString(str, line, '\r');
    for(unsigned int i=0; i<line.size(); ++i)
    {
        vector<string> field;
        split(field, line[i]);
        data.push_back(field);
        cols = max(cols, (int)field.size());
    }
    
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
    return true;
}

const char* CSVParser::getData(unsigned int rows, unsigned int cols )
{
    if (rows >= data.size() || cols >= data[rows].size())
    {
        return "";
    }
    
    return data[rows][cols].c_str();
}

int CSVParser::findColsData( int cols, const char* value )
{
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        if(strcmp(getData(i,cols),value)==0)
            return i;
    }
    return -1;
}