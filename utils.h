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
    clearBuffer();
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
}