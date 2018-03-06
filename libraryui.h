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
 * File: Header file for LibraryUI Class
 */

#ifndef LIBRARYUI_H
#define LIBRARYUI_H

#include <QDate>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include "library.h"

class LibraryUI {
 public:
  enum Choices { READ = 1, ADD, FIND, REMOVE, SAVE, LIST, QUIT };
  enum Types { BOOK, REFERENCEBOOK, TEXTBOOK, DVD, FILM, DATADVD };

  LibraryUI(Library *lib);

  void add(QStringList objdata);

  void read();

  void enterData();

  QString find();

  void remove();

  void save();

  void list();

  QStringList promptReferenceBook();

  QStringList promptRefItem();

  QStringList promptBook();

  QStringList promptTextBook();

  QStringList promptDvd();

  QStringList promptFilm();

  QStringList promptDataBase();

  Choices nextTask();

  void prepareToQuit(bool saved);

 private:
  Library *m_Lib;
  bool saved;

  const QStringList TYPES = (QStringList() << "BOOK"
                                           << "REFERENCEBOOK"
                                           << "TEXTBOOK"
                                           << "DVD"
                                           << "FILM"
                                           << "DATADVD");
};

#endif  // LIBRARYUI_H
