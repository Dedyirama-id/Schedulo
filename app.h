#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include "ansi_escape_sequences.h"

using namespace std;

namespace app {
  class Menu {
  public:
    vector<string> menuList;
    int currentOption = 1;

    Menu(initializer_list<string> menuItems) : menuList(menuItems) {}

    void printMenu() {
      cout << "\e[?25l";
      for (int i = 1; i < menuList.size(); i++) {
        if (i == currentOption) cout << BOLD << BLUE;
        cout << (currentOption == i ? "> " : "  ") << menuList.at(i) << endl;
        cout << RESET;
      }

      if (currentOption == 0) cout << BOLD << BLUE;
      cout << (currentOption == 0 ? "> " : "  ") << menuList.at(0) << endl;
      cout << RESET;
    }

    int getChoice() {
      cout << "\e[?25l";
      while (true) {
        printMenu();

        cout << "\033[" << menuList.size() << "A";

        char key = _getch();

        switch (key) {
        case 72: // Panah atas
          currentOption = (currentOption - 1 + menuList.size()) % menuList.size();
          break;
        case 80: // Panah bawah
          currentOption = (currentOption + 1) % menuList.size();
          break;
        case 13: // Tombol Enter
        case 32: // Tombol spasi
          cout << "\e[?25h";
          system("cls");
          return currentOption;
        }
      }
    }
  };

  void printH1(string text) {
    cout << BG_WHITE << BLACK << text << " " << RESET << endl;
  }

  void printH2(string text) {
    cout << BOLD << text << RESET << endl;
  }

  void printSuccess(string text) {
    cout << GREEN << text << RESET << endl;
  }

  void printWarning(string text) {
    cout << YELLOW << text << RESET << endl;
  }

  void printError(string text) {
    cout << RED << text << RESET << endl;
  }
}
