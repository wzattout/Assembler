//
// Created by walid on 5/27/20.
//

#include <utility>

#include "bits/stdc++.h"

using namespace std;

#ifndef ASSEMBLER_DATATYPESHANDLER_H
#define ASSEMBLER_DATATYPESHANDLER_H

#endif //ASSEMBLER_DATATYPESHANDLER_H

string decToHexa(int n) {
    // char array to store hexadecimal number
    string hexaDeciNum;

    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum += std::to_string(temp + 48);
            i++;
        } else {
            hexaDeciNum += std::to_string(temp + 55);
            i++;
        }

        n = n / 16;
    }

    // printing hexadecimal number array in reverse order
    reverse(hexaDeciNum.begin(), hexaDeciNum.end());
    return hexaDeciNum;
}

class dataTypesHandler {
    unordered_map<string, string> symbolicTable;

    string handleDataType(vector<string> line, string location) {
        symbolicTable[line[0]] = std::move(location);
        int length;
        string result;
        if (line[1] == "word") {
            result = decToHexa(stoi(line[2]));
            length = 6;
        } else if (line[1] == "resw") {
            length = 3 * stoi(line[2]);
        } else if (line[1] == "byte") {
            result = decToHexa(stoi(line[2]));
            length = 2;
        } else {
            length = stoi(line[2]);
        }
        while (result.size() < length) {
            result.append(0, '0');
        }
        return result;
    }
};
