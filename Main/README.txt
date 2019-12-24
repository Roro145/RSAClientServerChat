README for RSA Encrypted client-server messaging system

Instructions to use:
user inputs an English message client-side(C++) which is encoded using RSA and uses UDP
to send data via sockets. Server-side (Python) listens in on the incoming port and receives the message, converts it back to the original message by decrypting the RSA

To adjust the RSA encryption parameters, edit the following values:
Prime 1, Prime 2 & E



To compile:
g++ -o RSA RSA.cpp Network.cpp

Then run the Python script, execute the .exe file built by the previous command and complete the instructions in the exe file