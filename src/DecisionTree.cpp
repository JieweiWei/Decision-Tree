/**
 *
 * @file Decisiontree.cpp
 * The implementation of DecisionNode and Decisiontree.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Dec 18 2014
 **/

#include "DecisionTree.h"
#include <cstdio>
#include <cstring>

DecisionNode::DecisionNode() {
  for (int i = 0; i < NUMBER_OF_ATTR; ++i) {
    OptionalAttr[i] = true;
  }
  for (int i = 0; i < NUMBER_OF_NEXT; ++i) {
    next[i] = NULL;
  }
  nextAttr = -1;
}

DecisionNode::DecisionNode(const DecisionNode& other) {
  allRecords[democrat] = other.allRecords[democrat];
  allRecords[republican] = other.allRecords[republican];
  memcpy(OptionalAttr, other.OptionalAttr, NUMBER_OF_ATTR);
  for (int i = 0; i < NUMBER_OF_NEXT; ++i) {
    next[i] = other.next[i];
  }
  nextAttr = other.nextAttr;
}

void DecisionNode::setRecords(vector<Record> records) {
  for (vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
    allRecords[it->getPart()].push_back(*it);
  }
}

void DecisionNode::setOptionalAttr(bool* _OptionalAttr) {
  memcpy(OptionalAttr, _OptionalAttr, NUMBER_OF_ATTR);
}


DecisionTree::DecisionTree() {
  head = new DecisionNode();
}

DecisionTree::~DecisionTree() {
  if (head != NULL) {
    deleteAllNode(head);
  }
}

void DecisionTree::setHead(DecisionNode* _head) {
  head = _head;
}


/**
 * if examples is empty then return default
 * else if all examples have the same classification then return the classification
 * else if attributes is empty then return Mode(examples)
 * else
 * best ← Choose-Attribute(attributes, examples)
 * tree ← a new decision tree with root test best
 * for each value v i of best do
 * examples i ← {elements of examples with best = v i }
 * subtree ← DTL(examples i , attributes − best, Mode(examples))
 * add a branch to tree with label v i and subtree subtree
 * return tree
 */
void DecisionTree::DTL(DecisionNode *examples) {
  if (examples->allRecords[democrat].empty() ||
      examples->allRecords[republican].empty()) {
    return;
  }

  int bestAttr = -1;
  double minEntropy = POSITIVE_INFINTITY;
  vector<Record> minEntropyRecords[NUMBER_OF_NEXT];
  for (int i = 0; i < NUMBER_OF_ATTR; ++i) {
    if (examples->OptionalAttr[i]) {
      double entropyOfAttr = 0.0;
      bool isNan = false;
      vector<Record> diffRecords[NUMBER_OF_NEXT];
      for (int j = 0; j < NUMBER_OF_PART; ++j) {
        for (vector<Record>::iterator it = examples->allRecords[j].begin();
          it != examples->allRecords[j].end(); ++it) {
          switch(it->getAttr()[i]) {
            case YEA: diffRecords[0].push_back(*it); break;
            case NAY: diffRecords[1].push_back(*it); break;
            default: diffRecords[2].push_back(*it); break;
          }
        }
      }
      for (int j = 0; j < NUMBER_OF_NEXT; ++j) {
        double frequency = getFrequency(diffRecords[j]);
        if (frequency == 0.0) {
          isNan = true;
        }
        double probability =
            (double) diffRecords[j].size() /
            (double) (examples->allRecords[democrat].size() + examples->allRecords[republican].size());
        entropyOfAttr += (frequency * log2(frequency) * probability);
      }
      if (isNan || entropyOfAttr < minEntropy) {
        bestAttr = i;
        minEntropy = entropyOfAttr;
        for (int j = 0; j < NUMBER_OF_NEXT; ++j) {
          minEntropyRecords[j] = diffRecords[j];
        }
        if (isNan) {
          break;
        }
      }
    }
  }

  if (bestAttr >= 0) {
    examples->nextAttr = bestAttr;
    for (int j = 0; j < NUMBER_OF_NEXT; ++j) {
      examples->next[j] = new DecisionNode();
      examples->next[j]->setRecords(minEntropyRecords[j]);
      examples->next[j]->setOptionalAttr(examples->OptionalAttr);
      examples->next[j]->OptionalAttr[bestAttr] = false;
      DTL(examples->next[j]);
    }
  }
}

vector<Partisan>
DecisionTree::forecast(vector<Record> newRecord) const {
  vector<Partisan> parts;
  if (head == NULL) {
    return parts;
  }
  for (vector<Record>::iterator it = newRecord.begin(); it != newRecord.end(); ++it) {
    DecisionNode *cur = head;
    while (cur->nextAttr >= 0) {
      switch (it->getAttr()[cur->nextAttr]) {
       case YEA: cur = cur->next[0]; break;
       case NAY: cur = cur->next[1]; break;
       default: cur = cur->next[2]; break;
      }
    }
    parts.push_back(cur->allRecords[democrat].size() > cur->allRecords[republican].size() ? democrat : republican);
  }
  return parts;
}

void DecisionTree::deleteAllNode(DecisionNode* &_head) {
  for (int i = 0; i < NUMBER_OF_NEXT; ++i) {
    if (_head->next[i] != NULL) {
      deleteAllNode(_head->next[i]);
      _head->next[i] = NULL;
    }
  }
  delete _head;
  _head = NULL;
}

double DecisionTree::getFrequency(vector<Record> records) {
  double numOfDemocrat = 0.0;
  for (vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
    if (it->getPart() == democrat) {
      ++numOfDemocrat;
    }
  }
  return numOfDemocrat / (double) records.size();
}
