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
 * File: Implementation file for LibraryUI Class
 */

#include "libraryui.h"

QTextStream qout(stdout);
QTextStream qin(stdin);

LibraryUI::LibraryUI(Library *lib) : m_Lib(lib) {}

void LibraryUI::add(QStringList objdata) {
  qout << objdata.join("[::]") << endl;
  QString type = objdata.first();
  RefItem *ref;

  switch (static_cast<Types>(TYPES.indexOf(type))) {
    case BOOK:
      ref = new Book(objdata);
      m_Lib->addRefItem(ref);
      break;

    case REFERENCEBOOK:
      ref = new ReferenceBook(objdata);
      m_Lib->addRefItem(ref);
      break;

    // end
    case TEXTBOOK:
      ref = new TextBook(objdata);
      m_Lib->addRefItem(ref);
      break;

    case DVD:
      ref = new Dvd(objdata);
      m_Lib->addRefItem(ref);
      break;

    case FILM:
      ref = new Film(objdata);
      m_Lib->addRefItem(ref);
      break;

    case DATADVD:
      ref = new DataDvd(objdata);
      m_Lib->addRefItem(ref);
      break;

    // start id=lclmenu
    default:
      qDebug() << "Bad type in add() function";
  }
}

void LibraryUI::read() {
  const QString sep("[::]");
  const int BADLIMIT(5);  // max number of bad lines
  QString line, type;
  QStringList objdata;
  QFile inf("libfile");

  inf.open(QIODevice::ReadOnly);
  QTextStream instr(&inf);
  int badlines(0);

  while (not instr.atEnd()) {
    if (badlines >= BADLIMIT) {
      qDebug() << "Too many bad lines! Aborting.";
      return;
    }
    line = instr.readLine();
    objdata = line.split(sep);

    if (objdata.isEmpty()) {
      qDebug() << "Empty Line in file!";
      ++badlines;
    } else if (not TYPES.contains(objdata.first())) {
      qDebug() << "Bad type in line: " << objdata.join(";;;");
      ++badlines;
    } else
      add(objdata);
  }
}

void LibraryUI::enterData() {
  QString typestr;

  while (1) {
    qout << "Library item type: " << flush;
    typestr = qin.readLine();

    if (not TYPES.contains(typestr)) {
      qout << "Please enter one of the following types:\n"
           << TYPES.join(" ,") << endl;
      continue;
    }
    break;
  }
  QStringList objdata;

  switch (TYPES.indexOf(typestr)) {
    case BOOK:
      objdata = promptBook();
      break;

    case REFERENCEBOOK:
      objdata = promptReferenceBook();
      break;

    // end
    case TEXTBOOK:
      objdata = promptTextBook();
      break;

    case DVD:
      objdata = promptDvd();
      break;

    case FILM:
      objdata = promptFilm();
      break;

    case DATADVD:
      objdata = promptDataBase();
      break;

    // start id=lclprompt
    default:
      qDebug() << "Bad type in enterData()";
  }
  objdata.prepend(typestr);
  add(objdata);
}

QString LibraryUI::find() {
  QString isbn, item;

  qout << "Search ISBN: " << flush;
  isbn = qin.readLine();
  item = m_Lib->getItemString(isbn);

  if (item == QString()) {
    qout << isbn << " not found." << endl;
    return item;
  } else {
    qout << item << endl;
    return isbn;
  }
}

void LibraryUI::remove() {
  QString isbn(find()), ans;

  if (isbn == QString()) {
    qout << isbn << " not found." << endl;
    return;
  }
  qout << "Remove this item (Y/N)? " << flush;
  ans = qin.readLine().toUpper();

  if (ans.startsWith("N")) return;

  int numCopiesLeft = m_Lib->removeRefItem(isbn);
  qout << "There are now  " << numCopiesLeft << " copies left in the library."
       << endl;
}

void LibraryUI::save() {
  QFile outf("libfile");

  outf.open(QIODevice::WriteOnly);
  QTextStream outstr(&outf);
  outstr << m_Lib->toString();
  outf.close();
}

void LibraryUI::list() { qout << m_Lib->toString() << endl; }

QStringList LibraryUI::promptReferenceBook() {
  int idx(0);
  bool ok;
  QString str;
  QStringList retval(promptBook());
  QStringList cats(ReferenceBook::getRefCategories());

  while (1) {
    qout << "Enter the index of the correct Reference Category: ";

    for (int i = 0; i < cats.size(); ++i)
      qout << "\n\t(" << i << ") " << cats.at(i);
    qout << "\n\t(-1)None of these\t:::" << flush;
    idx = qin.readLine().toInt(&ok);

    if (ok) {
      retval << str.setNum(idx);
      break;
    }
  }
  return retval;
}

QStringList LibraryUI::promptRefItem() {
  const int MAXCOPIES(10);
  const int ISBNLEN(13);
  int copies;
  QString str;
  QStringList retval;

  while (1) {
    qout << "ISBN (" << ISBNLEN << " digits): " << flush;
    str = qin.readLine();

    if (str.length() == ISBNLEN) {
      retval << str;
      break;
    }
  }
  qout << "Title: " << flush;
  retval << qin.readLine();

  while (1) {
    qout << "Number of copies: " << flush;
    copies = qin.readLine().toInt();

    if (copies > 0 and copies <= MAXCOPIES) {
      str.setNum(copies);
      break;
    }
  }
  retval << str;
  return retval;
}

QStringList LibraryUI::promptBook() {
  static const int MINYEAR(1900), MAXYEAR(QDate::currentDate().year());
  int year;
  QStringList retval(promptRefItem());
  QString str;

  qout << "Author: " << flush;
  retval << qin.readLine();
  qout << "Publisher: " << flush;
  retval << qin.readLine();

  while (1) {
    qout << "Copyright year: " << flush;
    year = qin.readLine().toInt();

    if (year >= MINYEAR and year <= MAXYEAR) {
      str.setNum(year);
      break;
    }
  }
  retval << str;
  return retval;
}

QStringList LibraryUI::promptTextBook() {
  QStringList retval(promptBook());

  qout << "Course: " << flush;
  retval << qin.readLine();
  return retval;
}

QStringList LibraryUI::promptDvd() {
  bool ok;
  QString str, ans;
  int dnum;
  const int MAXDISKS(10);
  QStringList retval(promptRefItem());

  while (1) {
    qout << "Number of disks (no more than " << MAXDISKS
         << " please): " << flush;
    dnum = qin.readLine().toInt(&ok);

    if (ok and dnum > 0 and dnum <= MAXDISKS) break;
  }
  str.setNum(dnum);
  retval << str;
  qout << "Two-sided disks (Y/N)? " << flush;
  ans = qin.readLine().toUpper();

  if (ans.startsWith("Y"))
    str.setNum(1);
  else
    str.setNum(0);
  retval << str;
  return retval;
}

QStringList LibraryUI::promptFilm() {
  int min;
  const int MAXTIME(1000);
  bool ok;
  QString str, ans;
  QStringList retval(promptDvd());

  qout << "Star of film: " << flush;
  retval << qin.readLine();
  qout << "Director of film: " << flush;
  retval << qin.readLine();

  while (1) {
    qout << "Length of film (minutes): " << flush;
    min = qin.readLine().toInt(&ok);

    if (ok and min > 0 and min <= MAXTIME) break;
  }
  str.setNum(min);
  retval << str;
  qout << "BlueRay (Y/N)? " << flush;
  ans = qin.readLine().toUpper();

  if (ans.startsWith("Y"))
    str.setNum(1);
  else
    str.setNum(0);
  retval << str;
  return retval;
}

QStringList LibraryUI::promptDataBase() {
  QStringList retval(promptDvd());

  qout << "Database protocol: " << flush;
  retval << qin.readLine();
  return retval;
}

LibraryUI::Choices LibraryUI::nextTask() {
  int choice;
  QString response;

  do {
    qout << READ << ". Read data from a file.\n"
         << ADD << ". Add items to the Library.\n"
         << FIND << ". Find and display an item.\n"
         << REMOVE << ". Remove an item from the Library.\n"
         << SAVE << ". Save the Library list to a file.\n"
         << LIST << ". Brief listing of Library items.\n"
         << QUIT << ". Exit from this program.\n"
         << "Your choice: " << flush;
    response = qin.readLine();
    choice = response.toInt();
  } while (choice < READ or choice > QUIT);
  return static_cast<Choices>(choice);
}

void LibraryUI::prepareToQuit(bool saved) {
  QString ans;

  if (not saved) {
    qout << "Save data first (Y/N)? " << flush;
    ans = qin.readLine().toUpper();

    if (ans.startsWith("Y")) {
      save();
      exit(0);
    }
  }
  exit(1);
}
