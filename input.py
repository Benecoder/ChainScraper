#!/usr/bin/env python3

import urllib3
import certifi
import sys
import json
import os


lookup = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
number_of_blocks = 5

def insert_address(string):
    
    global addresses
    if string not in addresses:
        addresses.append(string)
    
    
#downloads a block
def get_block(blockhash):
    

    #donwloads the block
    URL = "https://blockchain.info/rawblock/"+blockhash
    http = urllib3.PoolManager(cert_reqs='CERT_REQUIRED',ca_certs=certifi.where())
    content = http.request('GET',URL)
    assert content.status == 200
    
    
    Decoder = json.JSONDecoder()
    js_data = Decoder.decode(content.data.decode('utf-8'))

    #roams through the transaction and collects the addresses
    for transaction in js_data['tx']:
        
        for senders in transaction['inputs']:
            try:
                insert_address(senders['prev_out']['addr'])
            except:
                pass
        
        for receivers in transaction['out']:
            try:
                insert_address(receivers['addr'])
            except:
                pass
            
    print('Collected '+str(len(addresses))+' addresses from Block: '+str(blockhash))
    
    FILE = open('prev_block.txt','w')
    FILE.write(js_data['prev_block'])
    FILE.close()



#implements base 58 logic
class b58():
    def __init__(self,number):
        self.n = number
    def __lt__(self,other):
        if self.n == other.n:
            return False
        
        if len(self.n) == len(other.n):
            index = len(self.n)-1
            
            while True:
                if lookup.find(self.n[index]) > lookup.find(other.n[index]):
                    return True
                elif lookup.find(self.n[index]) < lookup.find(other.n[index]):
                    return False
                index -= 1
        else:
            if len(self.n)>len(other.n):
                return True
            else:
                return False


def store(addresses):


    content = str(len(addresses))+'\n'
    for address in addresses:
        if address[0] == '1' or address[0] == '3':
            content += address +'\n'
    
    FILE = open('new_block.csv','w')
    content = FILE.write(content)
    FILE.close()


if __name__ == '__main__':
    addresses = []

    if len(sys.argv)> 1:
        get_block(sys.argv[1])
        store(addresses)

    else:
        if os.path.isfile('prev_block.txt'):
            
            FILE = open('prev_block.txt','r')
            content = FILE.readlines()
            FILE.close()

            get_block(content[0])
            store(addresses)


        else:
            print('requires Adress of requested Block')
            print('either through terminal argument or prev_block.txt')
            print('usage: '+str(sys.argv[0])+' *Adress*')
            sys.exit(2)
