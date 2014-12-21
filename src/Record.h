/**
 *
 * @file Record.h
 * The header file of Record.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Dec 18 2014
 **/

#ifndef RECORD_H
#define RECORD_H

/* Number of attribute. */
#define NUMBER_OF_ATTR 16

/* Defined in requirements document. */
#define YEA 'y'
#define NAY 'n'
enum Partisan {democrat, republican};

/* The define of record. */
class Record {
 public:
  Record();
  Record (char* _attr, Partisan _partisan);
  Record (const Record &other);

  void setAttr(char* _attr);
  void setPart(Partisan _partisan);

  const char* getAttr() const;
  Partisan getPart() const;
 private:
  /* Record Properties. */
  char attr[NUMBER_OF_ATTR];

  /* The partisan of the record. */
  Partisan partisan;
};

#endif // Record.h
