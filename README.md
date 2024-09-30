## **README.md**

# Stock Analysis and Trading Signals

This project provides a C++ stock analysis tool that fetches real-time stock data, calculates various technical indicators like Moving Averages, RSI (Relative Strength Index), and Bollinger Bands, and logs buy/sell/hold signals based on these indicators. The project utilizes external APIs (like Alpha Vantage) for fetching market data and is designed to be extended for more complex trading strategies.

### **Features**

- Fetch real-time stock market data.
- Calculate technical indicators:
  - Short and Long Simple Moving Averages (SMA).
  - Relative Strength Index (RSI).
  - Bollinger Bands.
- Log buy/sell/hold signals based on indicator values.
- Simple menu interface to select stocks and view analysis.
  
### **Technologies Used**

- **C++**: Core programming language.
- **cURL**: For making HTTP requests to the stock API.
- **JSON for Modern C++**: For parsing API responses.
- **Alpha Vantage API**: For fetching stock market data (can be replaced with other APIs if needed).
- **Doxygen**: Used for generating documentation.

### **How to Set Up the Project**

#### Prerequisites:
- **C++17 or higher**.
- **cURL** library installed.
- **JSON for Modern C++** header installed.
- Alpha Vantage API key or another stock market API that supports JSON responses.

#### Steps:
1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/stock-analysis-tool.git
    cd stock-analysis-tool
    ```
2. Install dependencies:
    - Ensure you have `libcurl` and the JSON library for C++ available.
    - Create a `.env` file in the root directory with your API key:
      ```
      API_KEY=your_api_key_here
      ```

3. Compile the project:
    ```bash
    g++ -std=c++17 -o stock_analysis main.cpp utils.cpp strategy.cpp -lcurl
    ```

4. Run the program:
    ```bash
    ./stock_analysis
    ```

### **Usage**

1. Once the program is running, you can choose options from the menu:
   - Option 1: Display available stocks.
   - Option 2: Enter a stock symbol to fetch market data and display trading signals.
   - Option 3: Exit the program.

2. The program will fetch stock data, calculate the chosen indicators (SMA, RSI, Bollinger Bands), and log the corresponding buy, sell, or hold signals based on the values.

### **API Integration**

The project currently uses the Alpha Vantage API to fetch market data. You can replace this API with another one that provides similar functionality. Make sure to adjust the API URL and data parsing logic accordingly.

### **Contributing**

Contributions are welcome! Feel free to open an issue or submit a pull request for any improvements, bug fixes, or new features. Please ensure that your code follows the existing code style and is well-documented using Doxygen.

### **License**

This project is licensed under the MIT License.
