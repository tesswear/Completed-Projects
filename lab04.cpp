/*
Name: Tess Wear           NetID: taw504
Date: 9/15/23             Due Date: 9/28/23

Description: This program reads text from two different files. The first one contains a story with blanks.
The second contains prompts to fill in those blanks. The program outputs the prompts from the second file 
so that the user can enter the words they want to use. Then the contents of the first file are displayed
with the blanks replaced by the user input.  Afterwards, the user has the option to save the MadLib to a new 
file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// function declarations
void generateMadLib(vector<string>& madLibVector, vector<string>& labelVector);
string getArticle(string succeedingWord);

// main function
int main() {
    ifstream inFile;
    string fileName;
    string madLibFile;
    string labelFile;
    string madLibWord;
    string labelWord;
    string completeMadLib = "";
    
    
    // get fileName
    cout << "Enter the name of the MadLib you would like to use. Do not include the extension." << endl;
    cin >> fileName;
    
    // use fileName input to locate actual files (add extensions)
    madLibFile = fileName + ".txt";

    // attempt to open madLibFile
    inFile.open(madLibFile);
    while (!inFile.is_open()) {
        cout << "Error: could not open file. Please try again." << endl;
        cin >> fileName;
        madLibFile = fileName + ".txt";
        inFile.open(madLibFile);
        /* i included the next statement as a way to break the loop if
        for some reason the file isn't being read correctly */
        if (fileName == "-1") {
            break;
        }
    }
    cout << "File opened successfully!" << endl << endl;

    // create empty MadLib vector
    vector<string> madLibVector;
    
    // read MadLib file into MadLib vector
    while (inFile >> madLibWord) { 
        madLibVector.push_back(madLibWord);
    }
    inFile.close();

    // end of reading from MadLib file

   // now the stuff with the label file

    labelFile = fileName + "_labels.txt";

    // attempt to open labelFile
    inFile.open(labelFile);
    while (!inFile.is_open()) {
        cout << "Error: could not open file. Please try again." << endl;
        cin >> fileName;
        labelFile = fileName + "_labels.txt";
        inFile.open(labelFile);
        /* i included the next statement as a way to break the loop if
        for some reason the file isn't being read correctly */
        if (fileName == "-1") {
            break;
        }
    }
    
    // create empty labelFile vector
    vector<string> labelVector;
    
    // read label file into labelVector
    while (getline(inFile, labelWord)) {
        labelVector.push_back(labelWord);
    }
    inFile.close();

    // end of reading from label file

    // done with file opening/reading/closing

    cin.ignore();
    generateMadLib(madLibVector, labelVector);
    
    // create string for finished MadLib
    for (int i = 0; i < madLibVector.size(); i++) {
        if (madLibVector[i + 1] != ".") {
            completeMadLib += madLibVector[i] + " ";
        }
        else {
            completeMadLib += madLibVector[i];
        }
    }

    // display finished MadLib

    cout << completeMadLib;

    // bonus section

    // ask to save story
    string response;
    cout << endl << endl << "Would you like to save this story? (yes/no)" << endl;
    cin >> response;
    while (response != "yes" and response != "no") {
        cout << "Error. Please enter yes or no." << endl;
        cin >> response;
    }

    // if they don't want to save the story
    if (response == "no") {
        cout << "Ok. Goodbye!" << endl;
    }

    // if they do want to save the story
    else {
        ofstream outFile;
        outFile.open("madlib.txt");

        if (!outFile.is_open()) {
            cout << "Error opening/creating file." << endl;
            return 1;
        }

        outFile << completeMadLib << endl;

        cout << "File saved successfully!" << endl;

        outFile.close();
    }
    
    return 0;
}

// function that makes the MadLib
void generateMadLib(vector<string>& madLibVector, vector<string>& labelVector) {
    int counter = 0;
    string replacement;
    string succeedingWord;
    for (int i = 0; i < madLibVector.size(); i++) {
        if (madLibVector[i] == "REPLACE") {
            succeedingWord = labelVector[counter];
            cout << "Enter " << getArticle(succeedingWord) << succeedingWord << ": ";
            getline(cin, replacement);
            madLibVector.at(i) = replacement;
            counter++;
            
        }
    }
}

// function that decides when to use "a" vs "and" in the output of the 
// generateMadLib function
string getArticle(string succeedingWord) {
    string article;
    switch(succeedingWord[0]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            article = "an ";
            break;
        default:
            article = "a ";
    }
    return article;
}