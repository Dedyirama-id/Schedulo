#pragma once 
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace u {
  void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void wait(string text = "") {
    cout << text;
    cin.get();
  }

  string fixDoubleSpaces(string str) {
    while (str.find("  ") != string::npos) {
      str = str.replace(str.find("  "), 2, " ");
    }
    return str;
  }

  string removeSpaces(string str) {
    while (str.find(" ") != string::npos) {
      str = str.replace(str.find(" "), 1, "");
    }
    return str;
  }

  int getIntInput(string text = "> ") {
    int input;
    while (true) {
      cin.clear();
      cout << text;
      cin >> input;
      if (cin.fail()) {
        cout << "Input harus berupa angka!" << endl;
        cin.clear();
        clearBuffer();
      } else {
        clearBuffer();
        return input;
      }
    };
  }

  string getStringInput(string text = "> ", int maxLength = 0) {
    string input;
    cout << text;
    getline(cin, input, '\n');
    if (maxLength > 0) input = input.substr(0, maxLength);
    return input;
  }

  bool getBoolInput(string text = "") {
    while (true) {
      string input = getStringInput(text + " (Y/N): ");
      if (input == "y" || input == "Y") return true;
      else if (input == "n" || input == "N") return false;
      cout << "   Input tidak valid!";
    }
  }

  int getChoice(int min = 0, int max = 9, string text = "> ") {
    while (true) {
      int choice = getIntInput(text);
      if (choice < min || choice > max) cout << "Pilihan tidak valid!" << endl;
      else return choice;
    }
  }

  string capitalize(string str) {
    for (int i = 0; i < str.length(); i++) {
      if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z') continue;
      else if (i == 0 || str[i - 1] == ' ') str[i] = toupper(str[i]);
      else str[i] = tolower(str[i]);
    }
    return str;
  }

  string toUppercase(string str) {
    for (int i = 0; i < str.length(); i++) {
      if (toupper(str[i]) < 'A' || toupper(str[i]) > 'Z') continue;
      str[i] = toupper(str[i]);
    };
    return str;
  }

  string cleanString(string str) {
    str = fixDoubleSpaces(str);
    for (int i = 0; i < str.length(); i++) {
      if (str[i] != ' ' && str[i] != '\t' ) break;
      str.erase(i, 1);
    }

    for (int i = str.length() - 1; i >= 0; i--) {
      if (str[i] != ' ' && str[i] != '\t') break;
      str.erase(i, 1);
    }

    return str;
  }
}