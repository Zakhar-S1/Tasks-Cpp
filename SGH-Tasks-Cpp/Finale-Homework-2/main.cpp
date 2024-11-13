#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void activate_task();
int input_int_check();

int main() {
    activate_task();
    return 0;
}

void activate_task(){
    int number_of_task;
    do {
        cout << "Input number of task group (1, 2, 3) for checking the task or 0 to exit: ";
        number_of_task = input_int_check();
        switch (number_of_task) {
            case 1: {
                cout << "GROUP 1. Task 2. Maximum Edge of a Triangle." << endl;

                int a, b;

                cout << "Input side1: ";
//                a = input_int_check();
                cin >> a;

                cout << "Input side2: ";
//                b = input_int_check();
                cin >> b;

                cout << "The range of third edge: from " << fabs(a - b) << " to " << a + b
                     << ". The max value of third edge: " << a + b - 1 << endl;

                cout << "End of task 1." << endl;
                break;
            }

            case 2: {
                cout << "GROUP 2. Task 3. Filter Repeating Character Strings." << endl;

                const int line_count = 6;
                string input_str;
                vector <string> texts;
                vector <string> result;

                for (int i = 0; i < line_count; ++i) {
                    cout << "Input str: " << (i + 1) << ": ";
                    getline(cin, input_str);
                    texts.push_back(input_str);
                }

                for (string text : texts) {
                    /* I'm a little confused about the condition. If we don't consider uppercase letters, we can just leave such strings out of the result.
                     But also we can use this loop to make them regular letters. Then such strings will be included in the result, while letters will be ignored. */

//                        for (char &c : text){
//                            c = tolower(c);
//                        }

                        if (!text.empty()){
                            char first_elem = text[0];
                            bool all_elem_similar = true;
                            for(char c : text){
                                if(c != first_elem) {
                                    all_elem_similar = false;
                                    break;
                                }
                            }

                            if (all_elem_similar){
                                result.push_back(text);
                            }
                        }
                }

                if (!result.empty()) {
                    for (const string& r : result) {
                        cout << r << endl;
                    }
                } else {
                    cout << "no values" << endl;
                }

                cout << "End of task 2." << endl;
                break;
            }

            case 3: {
                cout << "GROUP 3. Task 4. Print Grid 1" << endl;

                int rows, cols;

                cout << "Enter the number of rows: ";
                rows = input_int_check();
//                cin >> rows;

                cout << "Enter the number of cols: ";
                cols = input_int_check();
//                cin >> cols;

                if (rows > 0 && rows < 16 && cols > 0 && cols < 16) {
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            cout << "[ ]";
                        }
                        cout << endl;
                    }
                } else {
                    cout << "Error: rows and cols values must be positive and less than 16." << endl;
                }

                cout << "End of task 3." << endl;
                break;
            }

            default: {
                if (number_of_task != 0) {
                    cout << "Error. Repeat again or input '0' for exit." << endl;
                } else {
                    cout << "Exit!" << endl;
                }
            }
        }
    } while(number_of_task != 0);
}

int input_int_check() {
    int n;
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. An incorrect input format has been entered. Repeat again." << endl;
        } else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. An incorrect input format has been entered. Repeat again." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
    }
}