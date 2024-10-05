#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/utils.hpp"
#include "../inc/strategy.hpp" // Assuming these files are in your inc folder

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateStockList(); // Populate the stock dropdown on startup

    // Manually connect the button's clicked signal to the slot
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateStockList()
{
    // Fetch the list of available stocks from the API
    std::vector<std::string> stocks = getAvailableStocks();

    // Add them to the QComboBox
    for (const auto& stock : stocks) {
        ui->stockComboBox->addItem(QString::fromStdString(stock));
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString selectedStock = ui->stockComboBox->currentText();
    if (selectedStock.isEmpty()) {
        ui->resultLabel->setText("Please select a stock.");
        return;
    }

    const char* apiKey = std::getenv("API_KEY");
    if (apiKey == nullptr) {
        ui->resultLabel->setText("API Key not found.");
        return;
    }

    // Fetch market data for the selected stock
    std::string response = fetchMarketData(apiKey, selectedStock.toStdString());
    std::vector<double> closePrices = parseMarketData(response);

    if (closePrices.empty()) {
        ui->resultLabel->setText("Failed to fetch stock data.");
        return;
    }

    // Perform the analysis (this is simplified, you can add more indicators)
    double shortSMA = Strategy::calculateShortPeriodMovingAverage(closePrices);
    double longSMA = Strategy::calculateLongPeriodMovingAverage(closePrices);

    // Display the result based on moving averages
    if (shortSMA > longSMA) {
        ui->resultLabel->setText("Buy Signal");
    } else if (shortSMA < longSMA) {
        ui->resultLabel->setText("Sell Signal");
    } else {
        ui->resultLabel->setText("Hold Signal");
    }
}
