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
            
    print('Collected '+str(len(addresses))+' addresses.')
        
    return js_data['prev_block']

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
    
    
    #To do: devise a method so this will not devour your RAM like a hungry hyena
    
    if os.path.isfile('addresses.csv'):
        FILE = open('addresses.csv','r+')
        content = FILE.read()
        
        content = content.split(',')
        
        for adress in addresses:
            if adress not in content:
                FILE.write(adress+',')
                
        FILE.close()
        
    else:
        content = ','.join(addresses)
        
        FILE = open('addresses.csv','w')
        content = FILE.write(content)
        FILE.close()
    
        
    
    print('Batch was stored')


addresses = []

if len(sys.argv)> 1:
    addr = get_block(sys.argv[1])
else:
    InitKey = "000000000000000004ec466ce4732fe6f1ed1cddc2ed4b328fff5224276e3f6f"
    addr = get_block(InitKey)
    
    
store(addresses)

for i in range(number_of_blocks):
    addr = get_block(addr)
    store(addresses)
    addresses = []
