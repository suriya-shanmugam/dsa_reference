'''

# Basics
Immutable - operations returns new strings - no in place operation

'hello' - single  "Hello" - double
No difference between single and double literal just follow the ecosystem convention

'''

''' Multi line \n with escape processing ''' # With escape processing

r"/user/new\ file"  # No escape processing


b"...." # byte string 

r'''
1. raw bytes instead of unicode text string 
2. Used with Dealing with Network / Raw files 

Example :

import socket

sock = socket.socket()
sock.connect(("example.com", 80))
sock.sendall(b"GET / HTTP/1.1\r\nHost: example.com\r\n\r\n")  # HTTP request as bytes
response = sock.recv(1024)  # returns bytes
print(response.decode("utf-8"))  # decode to string

'''

name = "suriya"

f"{name}"  # Format specifiers

s = b"Caf\xc3\xa9"

print(s)
print(s.decode("UTF-8"))

# Raw bytes 0-255
l = list(s)  # [67, 97, 102, 195, 169]
print(l)
