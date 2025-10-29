
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cerr << "Error: incorrect usage." << endl;
    cerr << "Usage: " << argv[0] << " <file_path>" << endl;
    exit(1);
  }

  string file_path = argv[1];
  ifstream file(file_path);

  if (!file.is_open()) {
    cerr << "Error: could not open file at " << file_path << endl;
    exit(1);
  }

  int lines_to_parse = 15;
  int count = 0;

  string line;

  while (getline(file, line) && count < lines_to_parse) {
    cout << line << endl;
    count++;
  }

  file.close();
  return 0;
}
