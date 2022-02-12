# coding: utf-8
import requests
import datetime
import time
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px
import os


host = "https://api.gateio.ws"
prefix = "/api/v4"
headers = {'Accept': 'application/json', 'Content-Type': 'application/json'}


def max_1000_dpts(interval, st_time, ed_time, currency_pair, df):
    
    dpts = 0
    gap = 0
    
    if(interval == "1w"):
        gap = 604800
    elif(interval == "1d"):
        gap = 86400
    elif(interval == "1h"):
        gap = 3600
    elif(interval == "4h"):
        gap = 14400
        
    dpts = int((ed_time - st_time)/gap)
    tmp_time = st_time
    t = 0
    while(tmp_time <= ed_time):
        #tmp_time->tmp_time + 999*gap
        query_param = "currency_pair=" + currency_pair + "&" + "interval=" + interval + "&from=" + str(int(tmp_time)) + "&to=" + str(int(tmp_time + min(dpts,999)*gap))
        r = requests.request('GET', host + prefix + url + "?" + query_param, headers=headers)

        for i in range(0, len(r.json())):
            currentItem = r.json()[i]
            #print(currentItem)
            df.loc[t] = currentItem
            t+=1
        
        tmp_time = tmp_time + 1000*gap

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

fp = open("test.txt", 'r')

t = int(fp.readline())
thresh = int(fp.readline())
stri = []

for i in range(0,t):
    j = str(fp.readline())
    #print(j)
    stri.append(j)

fp.close()


f= open("input.txt","w+")
f.write(str(os.getcwd().replace("\\","/")) + "/" + "\n")
f.write(str(t)+"\n")
f.write(str(thresh)+"\n")

    
for i in range(0, t):
    coin, duration, a, b = [x for x in stri[i].split(', ')]
    #print(query)

    print(coin + " " + duration + " " + a + " " + b)
    
    currency_pair = coin #input("Crypto_type:");
    start_date = a.strip() #input("Start_date (yyyy-mm-dd):")
    end_date = b.strip() #input("End_date (yyyy-mm-dd):")
    interval = duration #input("Interval(1h/4h/1d/1w):")

    start_date = datetime.datetime.strptime(start_date, "%m/%d/%Y")
    end_date = datetime.datetime.strptime(end_date, "%m/%d/%Y")

    st_time = int(time.mktime(start_date.timetuple()))
    ed_time = int(time.mktime(end_date.timetuple()))

    currency_pair += "_USDT"

    #print(start_date)

    url = '/spot/candlesticks'

    df = pd.DataFrame(columns = ["Time", "Volume", "Close", "High", "Low", "Open"])

    max_1000_dpts(interval, st_time, ed_time, currency_pair, df)
    df = df.astype(float)
    print(df)
    #print(type(df.loc[3,"Close"]))
    df.to_csv ("cryp" +str(i+1)+".csv", index = False, header=True)
    
    f.write("cryp" +str(i+1)+".csv\n")

    f1 = open("output" + str(i+1) + ".txt","w+")
    f1.close()
    
    #df2 = pd.read_csv('output.txt', sep=" ", header=None)
    #df2 = df2.astype(float)
    print(df)
    #print(df2)
    #plot_candlestick(df, df2)
f.close()
