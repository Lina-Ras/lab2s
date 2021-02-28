#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>

class Student {
public:
    std::string _name;
    std::string _surname;
    std::string _middle_name;
    std::string _student;
    int _course;
    std::string _word = "курса";
    std::string _id;
};

std::string Choice(){
    bool f;
    std::string Path;
    std::cout << "ANSI == 0, UTF8 == 1 (isn't supported yet)\n";
    std::cin >> f;
    if (f)
        Path = "L1_UTF8";
    else
        Path = "L1_ANSI";
    return Path+".txt";
};

class ReadText {
private:
    void Pars(std::string& line,Student& some_dude, std::string type){
        std::regex re;
        if (type == "L1_ANSI.txt") {
            re = ("((([A-za-z+])([1-9]+)){4})([1-9]{1})(A-Z+)(a-z+)([1-9]{3})"
                          "([1-9]{8})");
        }
        else{
            re = ("((([А-Я+а-я+])(\d{3})){4})(\d{1})(A-Z+)(а-я+)(\d{3})"
                  "(\d{8})");
        }
        some_dude._surname = std::regex_replace(line, re, "$1");
        some_dude._name = std::regex_replace(line, re, "$3");
        some_dude._middle_name = std::regex_replace(line, re, "$5");
        some_dude._student = std::regex_replace(line, re, "$7");
        std::string tmp= std::regex_replace(line, re, "$9");
        std::stringstream conv(tmp);
        conv >> some_dude._course;
        some_dude._id = std::regex_replace(line, re, "$13");
    }
    public:
    std::vector<std::shared_ptr<Student>>  _result;

    friend std::istream& operator>> (std::istream &input, ReadText &cl){
        cl.ReadFromFile();
        return input;
    }

    void ReadFromFile() {
        std::string Path;
        Path = Choice();
        std::ifstream fin(Path);
        std::string line;
        while (!fin.eof()) {
            std::getline(fin, line, '\n');
            auto *st = new Student;
            Pars(line, *st, Path);
            std::shared_ptr<Student> ptr(st);
            _result.push_back(ptr);
        }
        fin.close();
    }
};

int main(){
    ReadText Test;
    Test.ReadFromFile();
    std::cout << Test._result[1]->_course;
    return 0;
}
