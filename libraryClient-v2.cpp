/*
 * Created by Hung Nguyen
 * Student ID: 905925175
 * Email: dnhung7@vt.edu
 * Class: ECE 3574
 * Assignment: Homework 2 - Problem 2
 *
 * As a Hokie, I will conduct myself with honor and integrity at all times.
 * I will not lie, cheat, or steal, nor will I accept the actions of those
 * who do.”
 *
 * File: Client command line interface file for LibraryUI
 */

#include "library.h"
#include "libraryui.h"

bool saved(false);

int main() {
  Library lib;
  LibraryUI libui(&lib);

  while (1) {
    switch (libui.nextTask()) {
      case LibraryUI::READ:
        libui.read();
        saved = false;
        break;

      case LibraryUI::ADD:
        libui.enterData();
        saved = false;
        break;

      case LibraryUI::FIND:
        libui.find();
        break;

      case LibraryUI::REMOVE:
        libui.remove();
        saved = false;
        break;

      case LibraryUI::SAVE:
        libui.save();
        saved = true;
        break;

      case LibraryUI::LIST:
        libui.list();
        break;

      case LibraryUI::QUIT:
        libui.prepareToQuit(saved);
        break;

      default:
        break;
    }
  }
}
