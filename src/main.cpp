/**
 *
 * @file main.cpp
 * The main function of decision tree.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Dec 18 2014
 **/

#include "DecisionTree.h"
#include "Record.h"
#include <cstdio>
#include <cstring>

/* The number of data selected to train the decision tree. */
#define NUMBER_OF_TRAINING_DATA 100

/* The path of dataset. */
#define DATASET "data/dataset.txt"

/* The correct results of the records selected to forecast. */
#define CORRECT_RESULT "data/correctResult.txt"

/* The predictions of the records selected to forecast. */
#define PREDICTIONS "data/predictions.txt"

/**
 * @test
 * Calculate the correct rate forecast and print it.
 */
void test() {
  FILE *resultFile = fopen(CORRECT_RESULT, "r");
  FILE *outputFile = fopen(PREDICTIONS, "r");
  char resultPart[11], outputPart[11];
  double countSame = 0.0, countAll = 0.0;
  while (fscanf(resultFile, "%s\n", resultPart) != EOF &&
         fscanf(outputFile, "%s\n", outputPart) != EOF) {
    ++countAll;
    if (strcmp(resultPart, outputPart) == 0) {
      ++countSame;
    }
  }
  printf("Forecast accuracy: %lf percents\n", countSame / countAll * 100.0);
  fclose(resultFile);
  fclose(outputFile);
}

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  /* Read the data from the file. */
  FILE *dataFile = fopen(DATASET, "r");
  char part[11], attrs[32];
  vector<Record> records;
  while (fscanf(dataFile, "%[^,],%s\n", part, attrs) != EOF) {
    char recordAttrs[NUMBER_OF_ATTR];
    int count = 0;
    for (int i = 0; attrs[i] != '\0'; ++i) {
      if (attrs[i] != ',') {
        recordAttrs[count++] = attrs[i];
      }
    }
    records.push_back(Record(recordAttrs, (strcmp(part, "democrat") == 0 ? democrat : republican)));
  }
  fclose(dataFile);

  /* The records selected to train the decision tree. */
  vector<Record> examples(records.begin(), records.begin() + NUMBER_OF_TRAINING_DATA);

  /* The record selected to be forecast. */
  vector<Record> newRecord(records.begin() + NUMBER_OF_TRAINING_DATA, records.end());

  /* Write the correct result to file. */
  FILE *resultFile = fopen(CORRECT_RESULT, "w");
  for (vector<Record>::iterator it = newRecord.begin(); it != newRecord.end(); ++it) {
    fprintf(resultFile, "%s\n", it->getPart() == democrat ? "democrat" : "republican");
  }
  fclose(resultFile);

  /* Train the model. */
  DecisionNode* exampleNode = new DecisionNode();
  exampleNode->setRecords(examples);
  DecisionTree decisionTree;
  decisionTree.setHead(exampleNode);
  decisionTree.DTL(exampleNode);

  /* Write the Predictions to file. */
  FILE *outputFile = fopen(PREDICTIONS, "w");
  vector<Partisan> forecastPartisan = decisionTree.forecast(newRecord);
  for (vector<Partisan>::iterator it = forecastPartisan.begin(); it != forecastPartisan.end(); ++it) {
    fprintf(outputFile, "%s\n", *it == democrat ? "democrat" : "republican");
  }
  fclose(outputFile);
  return 0;
}
