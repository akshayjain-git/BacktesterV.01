import yfinance as yf

ticker = yf.Ticker("TCS.NS")

data = ticker.history(
    period="5y",
    interval="1d",
    auto_adjust=False
)

data.to_csv("TCS_5Y.csv")

print(data)
print("\nCorporate Actions:")
print(ticker.actions)