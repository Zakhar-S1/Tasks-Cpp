#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void activate_task();
int input_int_check();
// Task 1
void print_grid2(int, int);
// Task 2
vector<double> multicalcul(int, int );
vector<double> multicalcul(double, double);
vector<double> multicalcul(int, double);
vector<double> multicalcul(double, int);
void printResultsForMulticalcul(const vector<double>& results);
// Task 3
vector<vector<int>> transpose(const vector<vector<int>>& matrix);
void printMatrixForTask3(const vector<vector<int>>& matrix);

int main() {
    activate_task();
    return 0;
}

void activate_task(){
    int number_of_task;
    do {
        cout << "Input number of task (1, 2, 3) for checking the task or 0 to exit: ";
        number_of_task = input_int_check();
        switch (number_of_task) {
            case 1: {
                cout << "GROUP 1. Task 4. Print Grid 2." << endl;

                cout << "Input rows and cols: ";
                print_grid2(input_int_check(), input_int_check());

                cout << "End of task." << endl;
                break;
            }

            case 2: {
                cout << "GROUP 2. Task 11. Multicalculator." << endl;

                printResultsForMulticalcul(multicalcul(3,6)); // [9, -3, 18, 0.5, 3]
                // By convention, if there is a floating point number, it will return an empty array.
                // If we need to return an empty array when there are only two double variables, we just need to duplicate the code above from printResultsForMulticalcul(multicalcul(3,6)) case, add a couple of checks for the second number
                // according to our math operation and the variable double
                printResultsForMulticalcul(multicalcul(3.5,6)); // []
                printResultsForMulticalcul(multicalcul(4,6.1)); // []
                printResultsForMulticalcul(multicalcul(5.5,6.2)); // []

                cout << "End of task." << endl;
                break;
            }

            case 3: {
                cout << "GROUP 2. Task 2. Matrix Transpose." << endl;

                vector<vector<int>> matrix = {
                        {6, 4},
                        {9, 9},
                        {1, 1}
                };
                vector<vector<int>> result = transpose(matrix);
                printMatrixForTask3(result);

                cout << "End of task." << endl;
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

void print_grid2(int rows, int cols){
    vector<vector<int>> result(rows, vector<int>(cols, 0));
    int n = 1;

    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            result[row][col] = n++;
        }
    }

    cout << "[" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << " [";
        for (int j = 0; j < cols; ++j) {
            cout << result[i][j];
            if (j < cols - 1) cout << ", ";
        }
        cout << "]";
        if (i < rows - 1) cout << "," << endl;
    }
    cout << endl << "]" << endl;
}

vector<double> multicalcul(int a, int b) {
    vector<double> results;
    results.push_back(a + b);
    results.push_back(a - b);
    results.push_back(a * b);
    if (b != 0) {
        results.push_back(static_cast<double>(a) / b);
        results.push_back(a % b);
    }
    return results;
}

vector<double> multicalcul(double a, double b) {
    return {};
}

vector<double> multicalcul(int a, double b) {
    return {};
}

vector<double> multicalcul(double a, int b) {
    return {};
}

void printResultsForMulticalcul(const vector<double>& results) {
    cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << results[i];
        if (i < results.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return {};
    }

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    vector<vector<int>> transposed_matrix(cols, vector<int>(rows));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed_matrix[j][i] = matrix[i][j];
        }
    }

    return transposed_matrix;
}

void printMatrixForTask3(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}








