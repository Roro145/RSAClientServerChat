import socket
import sys
import math
from decimal import *

#RSA decryption function
def decrypt(req_data):
    raw_msg = req_data['Message']
    E = req_data['E']
    n = req_data['n']
    privKey = req_data['privKey']
    
    print("Encrypted Message: " + str(raw_msg))
    
    decrypted_msg = raw_msg ** privKey
    decrypted_msg = math.fmod(decrypted_msg, n)
    
    return str(decrypted_msg)

#Initializes a UDP Socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#bind the socket to port & localhost
server_address = ('127.0.0.1', 5000)
sock.bind(server_address)
print("Binded")

while True:
    print("Waiting to recieve message")
    data, address = sock.recvfrom(5000)
    
    #data needed in order to decrypt incoming message
    req_data = {
        'Message' : float(data),
        'E' : 3,
        'n' : 143,
        'privKey': 0.333333
    }
    print("Data recieved: " + str(data) + " From: " + str(address))
    print("Decoded message: " + decrypt(req_data))

