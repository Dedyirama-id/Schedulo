#pragma once 
#include <iostream>

using namespace std;

namespace u {
  void wait(string text = "") {
    cout << text;
    cin.get();
  }

  int getIntInput(string text = "> ") {
    cout << text;
    int input;
    cin >> input;
    cin.ignore();
    return input;
  }

  string getStringInput(string text = "> ") {
    string input;
    cout << text;
    getline(cin, input, '\n');
    return input;
  }

  bool getBoolInput(string text = "") {
    string input = getStringInput(text + " (Y/N): ");
    if (input == "y" || input == "Y") return true;
    else if (input == "n" || input == "N") return false;
    else return false;
  }

  int getChoice(int min = 0, int max = 9, string text = "> ") {
    while (true) {
      int choice = getIntInput(text);
      if (choice < min || choice > max) cout << "Invalid choice!" << endl;
      else return choice;
    }
  }
}