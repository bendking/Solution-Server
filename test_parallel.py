from socket import *
import numpy
from random import randint

def random_matrix():
      # Generate matrix dimensions
      rows = randint(10, 50)
      cols = randint(10, 50)
      
      # Generate matrix
      matrix = numpy.random.randint(-1, 10, (rows, cols))
      # Make sure matrix is valid
      matrix[0][0] = 0
      matrix[rows-1,cols-1] = 0
      # Send off!
      return matrix, rows, cols

def random_point(rows, cols):
      i = randint(0, rows)
      j = randint(0, cols)
      return (i,j)

# Define matrixes
m1, r1, c1 = random_matrix()
start1 = random_point(r1, c1)
end1 = random_point(r1, c1)
print ("Matrix 1 dimensions: {0},{1}, Matrix 1 start: {2[0]},{2[1]}, Matrix 1 end: {3[0]},{3[1]}".format(r1, c1, start1, end1))
print (m1)

m2, r2, c2 = random_matrix()
start2 = random_point(r2, c2)
end2 = random_point(r2, c2)
print ("Matrix 2 dimensions: {0},{1}, Matrix 2 start: {2[0]},{2[1]}, Matrix 2 end: {3[0]},{3[1]}".format(r2, c2, start2, end2))
print (m2)

m3, r3, c3 = random_matrix()
start3 = random_point(r3, c3)
end3 = random_point(r3, c3)
# Print matrix info and the matrix ite
print ("Matrix 3 dimensions: {0},{1}, Matrix 3 start: {2[0]},{2[1]}, Matrix 3 end: {3[0]},{3[1]}".format(r3, c3, start3, end3))
print (m3)

# Define & connect sockets to server
s1 = socket(AF_INET, SOCK_STREAM)
s2 = socket(AF_INET, SOCK_STREAM)
s3 = socket(AF_INET, SOCK_STREAM)
s1.connect(('127.0.0.1', 5400))
s2.connect(('127.0.0.1', 5400))
s3.connect(('127.0.0.1', 5400))

# Send matrixes
for i in range(50):
      if (i < r1):
            s1.send((",".join(map(str,m1[i])) + "\n").encode())
      
      if (i < r2):
            s2.send((",".join(map(str,m2[i])) + "\n").encode())
      
      if (i < r3):
            s3.send((",".join(map(str,m3[i])) + "\n").encode())
      

# Send start
s1.send(("{0[0]},{0[1]}".format(start1) + "\n").encode())
s2.send(("{0[0]},{0[1]}".format(start2) + "\n").encode())
s3.send(("{0[0]},{0[1]}".format(start3) + "\n").encode())
# Send goal
s1.send(("{0[0]},{0[1]}".format(end1) + "\n").encode())
s2.send(("{0[0]},{0[1]}".format(end2) + "\n").encode())
s3.send(("{0[0]},{0[1]}".format(end3) + "\n").encode())
# Send end
s1.send(("end" + "\n").encode())
s2.send(("end" + "\n").encode())
s3.send(("end" + "\n").encode())

# Print solutions
print(s1.recv(1024))
print(s2.recv(1024))
print(s3.recv(1024))