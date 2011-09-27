//
//  File    : sort240.cpp
//  Usage   : sort240 [options] field file
//  options : -r : sort in descending order
//            -i : ignore case
//            -n : sort field should be treated as a number
//  field   : a particular field on each line (int value).
//  file    : name of text file     
//  Author  : Nathan Standiford <ns@byu.edu>
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;
int field = 0;           //field param
bool descFlag = false;   //descending flag 
bool ignoreFlag = false; //ignore case flag
bool numFlag = false;    //number field flag

char * skipWhiteSpace(char * line) {
  if(isspace(*line)) {
    line++;
    return skipWhiteSpace(line);
  } else {
    return line;
  }
}

char * skipText(char * line) {
  if(isspace(*line) || !(*line)) {
      return line;
  } else {
    line++;
    return skipText(line); 
  }
}

char * skip(char * line) {
  line = skipWhiteSpace(line);
  line = skipText(line);
  line = skipWhiteSpace(line);
  return line;
}
void isolateField(char * line) {
  char * end = strchr(line,' ');
  if(end) {
    *end = '\0';
  }
}

void toLowerCase(char * line) {
  if (*line) {
    if(isupper(*line))
      *line = tolower(*line);
    line++;
    toLowerCase(line);
  }
}

int compareWithFlags(char * first, char * second) {
  if(descFlag) {
    char * temp = first;
    first = second;
    second = temp; 
  }

  if(ignoreFlag) {
    toLowerCase(first);
    toLowerCase(second);
  }

  if(numFlag) {
    double a = atof(first);
    double b = atof(second);
    return (int)(a - b);  
  }
    
  return strcmp(first,second);
}

char * setField(char * line) {
  char * setFieldN(char*,int);
  return setFieldN(line,(field - 1));
}

char * setFieldN(char * line, int field) {
  if(field > 0) {
    line = skip(line);
    field--;
    return setFieldN(line,field);
  } else {
    isolateField(line);
    return line;
  }
}

int compare(const void * a, const void * b) {
  const char * ia = (const char *) a;
  const char * ib = (const char *) b;

  char * first = new char[MAX];
  strcpy(first,ia);
  
  char * second = new char[MAX];
  strcpy(second,ib);
  
  int val = compareWithFlags(setField(first),setField(second));
  delete[] first;
  delete[] second;

  return val;
}
void processFlags(char * flags) {
  if(*flags == '-') {
    flags++;
    processFlags(flags); 
  } else if(*flags == 'r') {
    descFlag = true;
    flags++;
    processFlags(flags);
  } else if(*flags == 'n') {
    numFlag = true;
    flags++;
    processFlags(flags);
  } else if(*flags == 'i') {
    ignoreFlag = true;
    flags++;
    processFlags(flags);
  }
}


char ** processTokens(int argc, char** argv) {
  const int FLAG_INCLUDE = 4;
  argv++;
  if(argc == FLAG_INCLUDE) {
    processFlags(*argv);
    argv++;
  }
  field = atoi(*argv);
  argv++;
  return argv;
}

bool checkSpace(char * data) {
  bool chkSpace(char *);
  char * d = data;  
  d = data;
  bool chk = chkSpace(d);
  return chk;
}

bool chkSpace(char * d) {
  if(!(*d)) {
    return false; 
  } else if(!isspace(*d)) {
    return true;
  } else { 
    d++;
    return chkSpace(d);
  }
}

int main(int argc, char ** argv) {
  if(argc <= 2) {
    cout << "Usage: sort240 [options] field file"
	 << endl;
    exit(0);
  }
  argv = processTokens(argc, argv);
  ifstream in(*argv);
  if(in.fail()) {
    cerr << "Error opening '"
	 << *argv << "'"
	 << endl;
    exit(0);
  }

  char data[MAX][MAX];

  int count = 0; 
  for(count = 0; count<MAX && in.good(); count++) {
    in.getline(static_cast<char*>(data[count]),static_cast<int>(MAX));
     if(!checkSpace(data[count])) {
    	count--;
    }
  }

  qsort(data,count,MAX,compare);

  for(int i=0; i < count; i++) {
    cout << data[i]
         << endl;
  }
  return 0;
}

