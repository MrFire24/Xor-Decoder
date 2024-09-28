#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

string decrypt(string input) {
    string output = "";
    while (!input.empty()) {
        bitset<8> A = 0, B = 0, C = 0, D = 0;
        A = input[0]; input.erase(0, 1);
        B = input[0]; input.erase(0, 1);
        C = input[0]; input.erase(0, 1);
        D = input[0]; input.erase(0, 1);

        output += (
            (B[0] << 0) |
            (C[1] << 1) |
            (D[2] << 2) |
            (A[2] << 3) |
            (B[3] << 4) |
            (C[4] << 5) |
            (D[6] << 6) |
            (A[6] << 7));

        output += (
            (C[0] << 0) |
            (D[1] << 1) |
            (A[1] << 2) |
            (B[2] << 3) |
            (C[3] << 4) |
            (D[4] << 5) |
            (A[4] << 6) |
            (B[6] << 7));

        output += (
            (D[0] << 0) |
            (A[0] << 1) |
            (B[1] << 2) |
            (C[2] << 3) |
            (D[3] << 4) |
            (A[3] << 5) |
            (B[4] << 6) |
            (C[6] << 7));
    }
    return output;
}


string keyDecrypt(const string& fileName, const string& key, bool addLineBreaks = false) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        return "";
    }

    string output;
    string line;

    while (getline(file, line)) {
        string decrypted = decrypt(line);

        for (size_t i = 0; i < decrypted.size(); i++) {
            size_t key_iter = i % key.length();
            output += decrypted[i] ^ key[key_iter];
        }

        if (addLineBreaks) {
            output += "\n";
        }
    }

    file.close();
    return output;
}

/*
void hackKeyDecrypt(string fileName) {
  FILE* file = fopen(fileName.c_str(), "rt");
  if (!file) {
    cout << "Failed to open file\n";
    return;
  }

  char str[9];
  fgets(str, 8, file);
  string text = decrypt(str);

  char kA = 'a';//, kB = 'a', kC  = 'a', kD  = 'a';
  while (kA != 'z' + 1) {
    string out = "";
    //out += text[0] ^ kA;
    //out += text[1] ^ kB;
    //out += text[2] ^ kC;
    //out += text[3] ^ kD;

    cout << kA << ":" << (text[0] ^ kA);

    kA++;
    //if (kA == 'z' + 1) kA = 'a';
    //if (kB == 'z' + 1) kB = 'a';
    //if (kC == 'z' + 1) kC = 'a';
  }
}
*/

int main() {
    cout << keyDecrypt("text_A.encoded", "TopSecret!");
}