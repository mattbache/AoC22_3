//
//  main.cpp
//  AoC22_3
//
//  Created by Matthew Bache on 12/5/22.
//

using namespace std;
#include <iostream>
#include <fstream>
#include <string>

int breakOutCompartments(string& comp1, string& comp2, const string& contents);

int getCommonContent(char& common, const string& comp1, const string& comp2);

int priorityValue(const char& common);

int getBadgeForGroup(char& badge, const string& bag1, const string& bag2, const string& bag3);

bool stringHasChar(const string& str, const char& c);

int main(int argc, const char * argv[]) {
    fstream inputFile;
    inputFile.open("/Users/matthewbache/Documents/AoC22/AoC22_3/AoC22_3 Input.txt");
    if (!inputFile.is_open()) {
        cout << "Could not open file\n";
        return 1;
    }
    
    long sumPriorities = 0, sumBadgePriorities = 0;
    string contents("");
    int groupSize = 3;
    string bags[groupSize];
    int bagCount = 0;
    while (getline(inputFile, contents)) {
        string comp1, comp2;
        breakOutCompartments(comp1, comp2, contents);
        char common;
        getCommonContent(common, comp1, comp2);
        sumPriorities += priorityValue(common);
        
        bags[bagCount] = contents;
        if (bagCount == groupSize-1) {
            // we have a set
            char badge;
            getBadgeForGroup(badge, bags[0], bags[1], bags[2]);
            sumBadgePriorities += priorityValue(badge);
            bagCount = 0;
        } else {
            bagCount++;
        }
    }
 
    cout << "Sum of Priorities is " << sumPriorities << "\n";
    cout << "Sum of Badge Priorities is " << sumBadgePriorities << "\n";
    
    inputFile.close();
    return 0;
}

int breakOutCompartments(string& comp1, string& comp2, const string& contents) {
    unsigned long len = contents.length();
    comp1 = contents.substr(0, len/2);
    comp2 = contents.substr(len/2);
    return 0;
}

int getCommonContent(char& common, const string& comp1, const string& comp2) {
    for (int i = 0; i < comp1.length(); i++) {
        //if (comp2.find(comp1[i]) != string::npos) {
        if (stringHasChar(comp2,comp1[i])) {
            common = comp1[i];
            return 0;
        }
    }
    return 1;
}

int priorityValue(const char& common) {
    int priority = (int)common;
    // a == 97, z == 122, A == 65, Z == 90
    if (priority >= 97 && priority <= 122)
        return priority - 96;
    if (priority >= 65 && priority <= 90)
        return priority - 64 + 26;
    // we should handle this better! The algo is very rough and ready
    // magic numbers - ugh
    return 0;
}

int getBadgeForGroup(char& badge, const string& bag1, const string& bag2, const string& bag3) {
    for (int i = 0; i < bag1.length(); i++) {
        if (stringHasChar(bag2, bag1[i]) && stringHasChar(bag3, bag1[i])) {
            badge = bag1[i];
            return 0;
        }
    }
    return 1;
}

bool stringHasChar(const string& str, const char& c) {
    return (str.find(c) != string::npos);
}
