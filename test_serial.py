# from socket import *

# # Define matrixes
# m1 = [[0, 9, 5, 1, 0, 3,-1, 5, 2, 0],
#       [7, 6, 4, 2, 6, 3, 8, 9, 1,-1],
#       [9, 7, 4,-1, 3, 5,-1, 9, 2, 9],
#       [9, 6, 9, 2, 6, 8, 6, 7, 1, 9],
#       [6, 9, 3, 0,-1, 9, 3, 8, 6, 5],
#       [7, 5, 1, 1, 6, 5, 5, 4, 4, 6],
#       [3, 3, 3, 2, 5, 8, 9, 1, 3, 0],
#       [-1, 9, 8, 3,-1, 9, 0, 1, 5,8],
#       [6, 0, 3, 8, 2, 8, 1, 9, 2, 6],
#       [5, 7, 8, 7, 8, 3, 4, 8, 4, 0]]


# # Define & connect sockets to server
# s1 = socket(AF_INET, SOCK_STREAM)
# s1.connect(('127.0.0.1', 5400))

# # Send matrixes
# for i in range(10):
#     to_send = (",".join(map(str,m1[i])) + "\n").encode()
#     s1.send(to_send)

# # Send start
# s1.send(("0,0" + "\n").encode())
# # Send goal
# s1.send(("9,9" + "\n").encode())
# # Send end
# s1.send(("end" + "\n").encode())

# # Print solution
# print(s1.recv(1024))

import numpy

print(numpy.random.random((3, 3)))