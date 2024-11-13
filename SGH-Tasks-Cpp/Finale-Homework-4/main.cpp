#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>
#include <ql/quantlib.hpp>
#include <xlnt/xlnt.hpp>

using namespace Eigen;
using namespace QuantLib;
namespace plt = matplot;
using namespace xlnt;

struct CustomerData {
    int customer_age;
    int dependent_count;
    double credit_limit;
    double total_trans_amt;
};

std::vector<CustomerData> read_excel(const std::string& filename) {
    std::vector<CustomerData> data;
    workbook wb;
    wb.load(filename);
    auto ws = wb.active_sheet();

    bool skip_header = true;
    for (auto row : ws.rows(false)) {
        if (skip_header) {
            skip_header = false;
            continue;
        }

        CustomerData customer;
        customer.customer_age = row[2].value<int>(); // Customer_Age
        customer.dependent_count = row[4].value<int>(); // Dependent_count
        customer.credit_limit = row[10].value<double>(); // Credit_Limit
        customer.total_trans_amt = row[15].value<double>(); // Total_Trans_Amt
        data.push_back(customer);
    }

    return data;
}

void prepare_data(const std::vector<CustomerData>& data, MatrixXd& X, VectorXd& y) {
    int n = data.size();
    X = MatrixXd(n, 3);
    y = VectorXd(n);

    for (int i = 0; i < n; ++i) {
        X(i, 0) = data[i].customer_age;
        X(i, 1) = data[i].dependent_count;
        X(i, 2) = data[i].total_trans_amt;
        y(i) = data[i].credit_limit;
    }
}

void train_test_split(const MatrixXd& X, const VectorXd& y, MatrixXd& X_train, VectorXd& y_train, MatrixXd& X_test, VectorXd& y_test, double test_size=0.2) {
    int n = X.rows();
    int n_test = static_cast<int>(n * test_size);
    int n_train = n - n_test;

    std::vector<int> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

    X_train = MatrixXd(n_train, X.cols());
    y_train = VectorXd(n_train);
    X_test = MatrixXd(n_test, X.cols());
    y_test = VectorXd(n_test);

    for (int i = 0; i < n_train; ++i) {
        X_train.row(i) = X.row(indices[i]);
        y_train(i) = y(indices[i]);
    }

    for (int i = 0; i < n_test; ++i) {
        X_test.row(i) = X.row(indices[n_train + i]);
        y_test(i) = y(indices[n_train + i]);
    }
}

VectorXd train_linear_regression(const MatrixXd& X_train, const VectorXd& y_train) {
    return (X_train.transpose() * X_train).ldlt().solve(X_train.transpose() * y_train);
}

VectorXd predict(const MatrixXd& X, const VectorXd& coefficients) {
    return X * coefficients;
}

double mean_squared_error(const VectorXd& y_true, const VectorXd& y_pred) {
    return (y_true - y_pred).array().square().mean();
}

void forecast_interest_rates() {

    Date evalDate(8, June, 2024);
    Settings::instance().evaluationDate() = evalDate;

    std::vector<Date> dates = { Date(8, June, 2024), Date(8, June, 2025), Date(8, June, 2027), Date(8, June, 2029), Date(8, June, 2031), Date(8, June, 2033) };
    std::vector<Rate> rates = { 0.01, 0.015, 0.02, 0.025, 0.03, 0.035 };


    //Handle<YieldTermStructure> yieldCurve(boost::make_shared<ZeroCurve>(dates, rates, Actual360()));
    auto curve = boost::make_shared<ZeroCurve>(dates, rates, Actual360());

    curve->enableExtrapolation();

    Handle<YieldTermStructure> yieldCurve(curve);

    std::vector<double> forecastedRates;
    std::vector<double> forecastDates;
    for (int i = 1; i <= 10; ++i) {
        Date forecastDate = evalDate + Period(i, Years);
        forecastedRates.push_back(yieldCurve->zeroRate(forecastDate, Actual360(), Continuous).rate());
        forecastDates.push_back(i);
    }

    plt::plot(forecastDates, forecastedRates, "-o");
    plt::xlabel("Years into Future");
    plt::ylabel("Forecasted Interest Rate");
    plt::title("Forecasted Interest Rates using QuantLib");
    plt::show();
}

int main() {
    std::string filename = "/Users/zakhar/CLionProjects/HW_4/data/data1.xlsx";
    std::vector<CustomerData> data = read_excel(filename);

    if (data.empty()) {
        std::cerr << "Error: No data loaded." << std::endl;
        return -1;
    }

    MatrixXd X;
    VectorXd y;
    prepare_data(data, X, y);

    MatrixXd X_train, X_test;
    VectorXd y_train, y_test;
    train_test_split(X, y, X_train, y_train, X_test, y_test);

    VectorXd coefficients = train_linear_regression(X_train, y_train);

    VectorXd y_pred = predict(X_test, coefficients);

    double mse = mean_squared_error(y_test, y_pred);
    std::cout << "Mean Squared Error: " << mse << std::endl;

    std::vector<double> true_values(y_test.data(), y_test.data() + y_test.size());
    std::vector<double> predicted_values(y_pred.data(), y_pred.data() + y_pred.size());

    plt::plot(true_values, "-o");
    plt::hold(true);
    plt::plot(predicted_values, "-x");
    plt::xlabel("Sample");
    plt::ylabel("Credit Limit");
    plt::legend({"True Values", "Predicted Values"});
    plt::title("True vs Predicted Credit Limit");
    plt::show();

    std::vector<int> ages;
    for (const auto& customer : data) {
        ages.push_back(customer.customer_age);
    }
    auto fig2 = plt::figure(true);
    plt::hist(ages, 10);
    plt::xlabel("Age");
    plt::ylabel("Frequency");
    plt::title("Customer Age Distribution");
    plt::show();

    std::vector<double> ages_d, credit_limits;
    for (const auto& customer : data) {
        ages_d.push_back(customer.customer_age);
        credit_limits.push_back(customer.credit_limit);
    }
    auto fig3 = plt::figure(true);
    plt::scatter(ages_d, credit_limits);
    plt::xlabel("Customer Age");
    plt::ylabel("Credit Limit");
    plt::title("Credit Limit vs Customer Age");
    plt::show();

    std::vector<double> total_trans_amts;
    credit_limits.clear();
    for (const auto& customer : data) {
        total_trans_amts.push_back(customer.total_trans_amt);
        credit_limits.push_back(customer.credit_limit);
    }

    plt::figure();
    plt::scatter(total_trans_amts, credit_limits);
    plt::xlabel("Total Transaction Amount");
    plt::ylabel("Credit Limit");
    plt::title("Credit Limit vs Total Transaction Amount");
    plt::show();

    forecast_interest_rates();

    return 0;
}
