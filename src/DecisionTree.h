/**
 *
 * @file Decisiontree.h
 * The header file of DecisionNode and Decisiontree.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Dec 18 2014
 **/

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <vector>
#include <cmath>
#include "Record.h"
using std::vector;

/* The number of children in DecisionNode. */
#define NUMBER_OF_NEXT 3

/* The number of partisan. */
#define NUMBER_OF_PART 2

/* Positive infintity. */
#define POSITIVE_INFINTITY (-log2(0.0))

/* Negative infintity. */
#define NEGATIVE_INFINTITY (-log2(0.0))

/* The define of decision node. */
struct DecisionNode {
  /* Record array, the first element record information of decltype
   * and the second element record information of republican. */
  vector<Record> allRecords[NUMBER_OF_PART];

  /* Record which property is optional. */
  bool OptionalAttr[NUMBER_OF_ATTR];

  /* The children of current node. */
  DecisionNode* next[NUMBER_OF_NEXT];

  /* Record the attribute of classification. */
  int nextAttr;

  DecisionNode();
  DecisionNode(const DecisionNode& other);

  void setRecords(vector<Record> records);
  void setOptionalAttr(bool* _OptionalAttr);
};

/* The define of decision tree. */
class DecisionTree {
 public:
  DecisionTree();
  ~DecisionTree();
  void setHead(DecisionNode* _head);

  /**
   * @DTl
   * Decision tree learning.
   * @param {examples} the examples of the model.
   */
  void DTL(DecisionNode *examples);

  /**
   * @forecast
   * Forecast parties by decision tree trained.
   * @param {newrecord} the array of records to forecast.
   * @return the result of forecast.
   */
  vector<Partisan> forecast(vector<Record> newRecord) const;

 private:
  /* The root of the decision tree. */
  DecisionNode* head;

  /**
   * @deleteAllNode
   * delete all decision node in the decision tree.
   * @param {head} the root of decision tree.
   */
  void deleteAllNode(DecisionNode* &_head);

  /**
   * @getFrequency
   * Calculate the frequency of record whose partisan is democrat.
   * @param {records} the record array need to calculate.
   * @return the frequency of the record array.
   * The result may be not a number.
   */
  double getFrequency(vector<Record> records);
};

#endif // DecisionTree.h
