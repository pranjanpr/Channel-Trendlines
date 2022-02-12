# coding: utf-8
import requests
import datetime
import time
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px
import os

def plot_candlestick(df, df2):
    fig = go.Figure(data = [go.Candlestick(x = df['Time'],
        open = df['Open'],
        high = df['High'],
        low = df['Low'],
        close = df['Close'])])
    
    
    for ind in df2.index:
        x0 = df2.iloc[ind, 0]
        y0 = df2.iloc[ind, 1]
        x1 = df2.iloc[ind, 2]
        y1 = df2.iloc[ind, 3]
        fig.add_shape(type='line', x0= x0, x1 =x1, y0= y0, y1 = y1, line=dict(color='Blue',), xref='x',yref='y')
    
    fig.show()

t = int(input("Write no of test cases:"))

for i in range(0,t):
    df = pd.read_csv("cryp" + str(i+1) + ".csv")
    df = df.astype(float)
    try:
        df2 = pd.read_csv("output" + str(i+1) + ".txt", sep=" ", header=None)
        df2 = df2.astype(float)

        plot_candlestick(df, df2)
        
    except:
        print("Sorry No trendlines found for test case no. " + str(i+1))
    #print(df) 
