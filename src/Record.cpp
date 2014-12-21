/**
 *
 * @file Record.cpp
 * The implementation of Record.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Dec 18 2014
 **/

#include "Record.h"
#include <cstring>

Record::Record() {}

Record::Record (char* _attr, Partisan _partisan) {
  memcpy(attr, _attr, NUMBER_OF_ATTR);
  partisan = _partisan;
}

Record::Record (const Record &other) {
  memcpy(attr, other.attr, NUMBER_OF_ATTR);
  partisan = other.partisan;
}

void Record::setAttr(char* _attr) {
  memcpy(attr, _attr, NUMBER_OF_ATTR);
}

void Record::setPart(Partisan _partisan) {
  partisan = _partisan;
}

const char* Record::getAttr() const {
  return attr;
}

Partisan Record::getPart() const {
  return partisan;
}
