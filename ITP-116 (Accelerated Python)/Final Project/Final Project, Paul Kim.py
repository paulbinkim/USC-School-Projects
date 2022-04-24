# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Final Project
# Description:
# Project that involves creating a stock tracking app that involves a GUI
# where the functionality is that the user is able to input a ticker symbol of given stocks that he/she
# want to track and analyze. The program in return, provides useful and relevant information about the given
# company through the use of APIs.

# Importing Useful Libraries and APIs
from tkinter import *
from tkmacosx import Button
from PIL import ImageTk, Image
import yfinance as yf
import yfinance
import plotly.graph_objects as go
import os
import textwrap


# Please download these packages onto Pycharm to use the functional APIs :)
# pip install plotly
# pip install yfinance
# pip install -U kaleido
# pip install tkmacosx
# pip install tk
# pip install Pillow


# Prompt Function for the First Row
def prompt():
    variable1 = """\
    Welcome to the ITP 116's very own Stock Tracking GUI!
    The purpose of this program is to provide you useful functionality and allow you to enter a ticker symbol of a stock you would like to analyze.
    Here are the 15 Stocks/Ticker Symbols available at your disposal. """
    x = textwrap.dedent(variable1)
    return x


# Reused Code Online (To Build Stock Chart) (TA said OK)
def buildPlotlyGraph(ticker):
    Stock = yfinance.Ticker(ticker)
    hist = Stock.history(period='1y')
    fig = go.Figure(data=go.Scatter(x=hist.index, y=hist['Close'], mode='lines'))
    fig.write_image("images/fig1.png")  # Creating Image onto Directory to use later for GUI


# Stores list of Tickers
def listTickers():
    myList = ["BABA", "GOOGL", "AMZN", "AAPL", "DIS", "FB", "GM", "MSFT", "NFLX", "NIO", "JPM", "CRM", "SNOW",
              "SHOP", "TSLA", "U"]
    return myList


# Function that concatenates strings to return to the Menu (Uses Object and API)
def PrintInformation(class1):
    Object1 = class1
    StockInfo = "Stock Information: " + str(Object1.description)
    City = "City: " + str(Object1.city)
    Employees = "Employees: " + str(Object1.fullTimeEmployees)
    CurrentPrice = "Price: " + str(Object1.currentPrice)
    MarketCap = "Market Cap: " + str(Object1.marketCap)
    EPS = "Earnings per Share: " + str(Object1.EPS)
    Consensus = "Consensus: " + str(Object1.Consensus.upper())
    FiftyTwoHigh = "52 Week High Stock Price: " + str(Object1.fiftytwoHigh)
    final = "\n".join([StockInfo, City, Employees, CurrentPrice, MarketCap, EPS, Consensus, FiftyTwoHigh])
    return final


# GUI Implementation
class GUI:
    def __init__(self):
        # Initializing GUI Object
        root = Tk()
        root.title("Stock Tracking GUI")
        # root.geometry("952x800") # Commented out because format looked weird on Windows but hopefully this helps(ish)
        root.config(bg="#9CE38A")
        root.resizable(0, 0)
        self.myFrame = Frame(root)
        self.myFrame.grid()

        # Creating a new Frame for the Body
        self.bodyFrame = Frame(root)
        self.bodyFrame.grid()
        self.bodyFrame.config(bg="#F9CAC0", bd=2, relief=SOLID)

        # Prompt Statement
        prompt1 = prompt()
        self.promptGUI = Label(self.myFrame, text=prompt1, bg="#F07E65", relief=SOLID, font="Arial 14 bold")
        self.promptGUI.grid(row=0, column=0, sticky="")

        # List of Tickers
        self.tickers1 = listTickers()
        self.Tickers = Label(self.myFrame, text=self.tickers1, bg="#D18878", relief=SOLID, font="Arial 12 bold", bd=2.5)
        self.Tickers.grid(row=1, column=0, sticky="", ipadx=221)

        # Textfield and Button
        self.temprow2 = Label(self.myFrame, bg="#D6D1C6", borderwidth=2, relief=SOLID, pady=3)
        self.temprow2.grid(row=2, column=0, sticky="", ipadx=471)
        self.textfield = Entry(self.myFrame, bg="#E6D6AB", bd=3, highlightbackground="#D6D1C6")
        self.textfield.grid(row=2, column=0, sticky="")
        self.enterButton = Button(self.myFrame, text="Enter", command=self.buttonClicked, highlightbackground="#D6D1C6",
                                  bg='black', fg='white')
        root.bind('<Return>', self.buttonClicked)
        self.enterButton.grid(row=2, column=0, padx=290, sticky=E)
        self.statusMessageLabel = Label(self.myFrame, bg="#D6D1C6")
        self.statusMessageLabel.grid(row=2, column=0, padx=215, sticky=W)

        # Empty Space for Format
        self.space = Label(self.myFrame, bg="#9CE38A")
        self.space.grid(row=3, column=0, ipadx=472)

        # Start of Body (Use New Frame)
        self.BodyFrameTitle = Label(self.bodyFrame, bg="#F9CAC0")
        self.BodyFrameTitle.grid(row=5, column=1, padx=200)
        self.BodyFrameTitle.grid_propagate(False)

        # Message Field
        self.Message1 = Message(self.bodyFrame, width=700, bg="lightgrey", bd=2, relief=SOLID,
                                text="Please Enter Ticker Above")
        self.Message1.grid(row=6, column=1)

        # Graph Canvas
        self.canvas1 = Canvas(self.bodyFrame, bg="lightgrey", bd=2, relief=SOLID, width=700, height=250)
        self.canvas1.grid(row=7, column=1)

    # Button Clicked Function
    def buttonClicked(self, event=None):
        Ticker = self.textfield.get()
        if Ticker.upper() in self.tickers1:
            self.statusMessageLabel.config(text="Ticker is a valid input.")
            self.BodyFrameTitle.config(text=Ticker.upper(), font="Arial 14 bold")
            self.displayTickerInformation(Ticker)
        else:
            self.statusMessageLabel.config(text="Ticker is an invalid input.")

    # Display Ticker Information Function (uses position of ticker in list)
    def displayTickerInformation(self, Ticker):
        TickerIndex = self.tickers1.index(Ticker.upper())
        if TickerIndex == 0:
            Alibaba = self.BABA()
            Text1 = PrintInformation(Alibaba)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("BABA")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 1:
            Google = self.GOOGL()
            Text1 = PrintInformation(Google)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("GOOGL")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 2:
            Amazon = self.AMZN()
            Text1 = PrintInformation(Amazon)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("AMZN")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 3:
            Apple = self.AAPL()
            Text1 = PrintInformation(Apple)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("AAPL")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 4:
            Disney = self.DIS()
            Text1 = PrintInformation(Disney)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("DIS")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 5:
            Facebook = self.FB()
            Text1 = PrintInformation(Facebook)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("FB")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 6:
            GeneralMotors = self.GM()
            Text1 = PrintInformation(GeneralMotors)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("GM")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 7:
            Microsoft = self.MSFT()
            Text1 = PrintInformation(Microsoft)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("MSFT")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 8:
            Netflix = self.NFLX()
            Text1 = PrintInformation(Netflix)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("NFLX")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 9:
            NIO1 = self.NIO()
            Text1 = PrintInformation(NIO1)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("NIO")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 10:
            JPMorgan = self.JPM()
            Text1 = PrintInformation(JPMorgan)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("JPM")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 11:
            Salesforce = self.CRM()
            Text1 = PrintInformation(Salesforce)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("CRM")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 12:
            Snowflake = self.SNOW()
            Text1 = PrintInformation(Snowflake)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("SNOW")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 13:
            Shopify = self.SHOP()
            Text1 = PrintInformation(Shopify)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("SHOP")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 14:
            Tesla = self.TSLA()
            Text1 = PrintInformation(Tesla)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("TSLA")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

        elif TickerIndex == 15:
            Unity = self.U()
            Text1 = PrintInformation(Unity)
            self.Message1.config(text=Text1, font="Arial 12 bold", justify="center")
            buildPlotlyGraph("U")

            ImageTemp = (Image.open("images/fig1.png"))
            resizeImg1 = ImageTemp.resize((400, 300), Image.ANTIALIAS)
            self.image1 = ImageTk.PhotoImage(resizeImg1)
            self.canvas1.create_image(350, 125, image=self.image1)

    # Here we use the yfinance API to parse information from Yahoo Finance rather than manually inputting data

    # Alibaba Object
    class BABA:
        def __init__(self):
            stock_info = yf.Ticker('BABA').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Google Object
    class GOOGL:
        def __init__(self):
            stock_info = yf.Ticker('GOOGL').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Amazon Object
    class AMZN:
        def __init__(self):
            stock_info = yf.Ticker('AMZN').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Apple Object
    class AAPL:
        def __init__(self):
            stock_info = yf.Ticker('AAPL').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Disney Object
    class DIS:
        def __init__(self):
            stock_info = yf.Ticker('DIS').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Facebook Object
    class FB:
        def __init__(self):
            stock_info = yf.Ticker('FB').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # General Motors Object
    class GM:
        def __init__(self):
            stock_info = yf.Ticker('GM').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Microsoft Object
    class MSFT:
        def __init__(self):
            stock_info = yf.Ticker('MSFT').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Netflix Object
    class NFLX:
        def __init__(self):
            stock_info = yf.Ticker('NFLX').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # NIO Object
    class NIO:
        def __init__(self):
            stock_info = yf.Ticker('NIO').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Salesforce Object
    class CRM:
        def __init__(self):
            stock_info = yf.Ticker('CRM').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # JPM Object
    class JPM:
        def __init__(self):
            stock_info = yf.Ticker('JPM').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Snowflake Object
    class SNOW:
        def __init__(self):
            stock_info = yf.Ticker('SNOW').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Shopify Object
    class SHOP:
        def __init__(self):
            stock_info = yf.Ticker('SHOP').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Tesla Object
    class TSLA:
        def __init__(self):
            stock_info = yf.Ticker('TSLA').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']

    # Unity Object
    class U:
        def __init__(self):
            stock_info = yf.Ticker('U').info
            self.description = stock_info['longBusinessSummary']
            self.city = stock_info['city']
            self.fullTimeEmployees = stock_info['fullTimeEmployees']
            self.currentPrice = stock_info['regularMarketPrice']
            self.marketCap = stock_info['marketCap']
            self.EPS = stock_info['forwardEps']
            self.Consensus = stock_info['recommendationKey']
            self.fiftytwoHigh = stock_info['fiftyTwoWeekHigh']


# Main Function
def main():
    # Statement that creates "images" folder in directory (for graph)
    if not os.path.exists("images"):
        os.mkdir("images")

    myGUI = GUI()
    myGUI.myFrame.mainloop()


# Call to main()
main()
