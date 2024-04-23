#pragma once
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

namespace app {
  class Menu {
  public:
    vector<string> menuList;
    int currentOption = 1;

    Menu(initializer_list<string> menuItems) : menuList(menuItems) {}

    void printMenu() {
      for (int i = 1; i < menuList.size(); i++) {
        cout << (currentOption == i ? "> " : "  ") << menuList.at(i) << endl;
      }
      cout << (currentOption == 0 ? "> " : "  ") << menuList.at(0) << endl;
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
          return currentOption;
        }
      }
    }
  };
}
