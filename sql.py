#!/usr/bin/env python3
# SAMPLE SQL FILE
# Will create a file in the current directory 'blockchain.db'

import sqlite3 as lite

create_table = """
CREATE TABLE IF NOT EXISTS Blockchain (
    ID              INTEGER PRIMARY KEY AUTOINCREMENT,
    PubKey          TEXT,
    Coins           INTEGER
);
"""

def CreateDataBase():
  con = lite.connect("blockchain.db")
  c = con.cursor()
  c.execute(create_table)
  print("Table Blockchain created.")

def DeleteDataBase():
  con = lite.connect("blockchain.db")
  with con:
    c = con.cursor()
    c.execute("DROP TABLE IF EXISTS Blockchain;")
    print("Table Blockchain deleted.")

def AddPubKey(key, coins):
  con = lite.connect("blockchain.db")
  with con:
    c = con.cursor()
    c.execute("INSERT INTO Blockchain (PubKey, Coins) VALUES (?, ?);", (key, coins))

def PrintPubKeys():
  con = lite.connect("blockchain.db")
  with con:
    c = con.cursor()
    c.execute("SELECT * FROM Blockchain;")
    row = c.fetchall()
    print(str(row))

CreateDataBase()
AddPubKey("91298e9812eh81298he9h182e", 420)
PrintPubKeys()

DeleteDataBase()
