//
// Created by Satyabrat Bhol on 11/12/23.
//

#include "Helper_SatyabratBhol.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
using namespace std;


Helper::Helper() { }


string Helper::convertToStringDecimal(double d) const
{
    stringstream ss; // read in the d to stringstream, and convert it to string, then return
    ss << fixed << setprecision(2) << d; // set two decimal points
    return ss.str();
}

string Helper::convertToString(double d) const
{
    stringstream ss;
    ss << d;
    return ss.str();
}

string Helper::convertTimeToString(long d) const
{
    stringstream ss;
    ss << d;
    return ss.str();
}


string Helper::getCurrentDate() const
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // format the date
    string time = convertToString(1 + ltm->tm_mon) + "/" +
                  convertToString(ltm->tm_mday) + "/" + convertToString(1900 + ltm->tm_year);
    return time;
}

string Helper::getCurrentTime() const
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // format the time
    string time = convertToString(ltm->tm_hour) + ":" +
                  convertToString(ltm->tm_min) + ":" + convertToString(ltm->tm_sec);
    return time;
}

time_t Helper::getCurrentTimeInSeconds() const
{
    time_t seconds = time(0);
    return seconds;
}

bool Helper::doesFileExist(string file_name) const
{
    fstream fs;
    bool result;
    fs.open(file_name, ios::in | ios::out);
    int ch;
    ch = fs.get(); // read a char in file
    if (ch == EOF) { // if read a EOF, it means nothing in file
        result = false;
    }
    else {
        result = true;
    }
    fs.close();
    return result;
}

void Helper::clearFile(string file_name)
{
    ofstream ofs;
    ofs.open(file_name);
    if (ofs.fail()) { //faile to open file
        cout << "Error: " << file_name << " cannot open" << endl;
        return;
    }
    else {
        ofs << ""; //rewrite "" to the file
        ofs.close();
    }
}

string Helper::searchFileForKey(string file_name, string key) const
{
    string result = "";
    ifstream ifs;
    ifs.open(file_name);
    if (ifs.fail()) {
        cerr << "Error: " << strerror(errno);
        cout << "Error: " << file_name << " cannot open" << endl;
    }
    else {
        string line;
        while (getline(ifs, line)) {
            if (getNthWordInString(line, 1) == key) {// get the first word in the line, compare it with the key
                result = line;
                break;
            }
        }
    }
    return result;
}

int Helper::getNumberOfLines(string file_name) const
{
    int num = 0;
    ifstream ifs;
    ifs.open(file_name);
    if (ifs.fail()) {
        cout << "Error: " << file_name << " cannot open" << endl;
        return 0;
    }
    else {
        string line;
        while (getline(ifs, line)) {
            num++; // just go over the file and add the num
        }
        ifs.close();
    }
    return num;
}

void Helper::printAllLines(string file_name) const
{
    ifstream ifs;
    ifs.open(file_name);
    if (ifs.fail()) {
        cout << "Error: " << file_name << " cannot open" << endl;
        return;
    }
    else {
        string line;
        while (getline(ifs, line)) {
            cout << line << endl; // print every line
        }
        ifs.close();
    }
}

void Helper::writeStringToFile(string file_name, string s)
{
    clearFile(file_name);
    fstream fs;
    fs.open(file_name);
    if (fs.fail()) {
        cout << "Error: " << file_name << " cannot open" << endl;
        return;
    }
    else {
        fs << s; // rewrite the number d to the file
        fs.close();
    }
}

void Helper::appendStringToLastLine(string file_name, string str)
{
    ofstream ofs;
    ofs.open(file_name, ios::app);
    if (ofs.fail()) {
        cout << "Error: " << file_name << " cannot open" << endl;
        return;
    } else {
        ofs << str; // write str to the last line
        ofs.close();
    }
}

string Helper::getLastLineOfFile(string file_name) const
{
    string lastline;
    ifstream ifs;
    ifs.open(file_name);
    if (ifs.fail()) {
        cout << "Error: " << file_name << " cannot open" << endl;
        return "";
    }
    else {
        while (getline(ifs, lastline)) {} // when while finishes, the lastline will be the content of last line
        ifs.close();
    }
    return lastline;
}

string Helper::getNthWordInString(string str, int num) const
{
    stringstream strs(str);
    string tok;
    int cnt = 0;
    while (getline(strs, tok, '\t') && ((++cnt) != num)) {} // get the n-th word seperated by "\t" in the string
    return tok;
}