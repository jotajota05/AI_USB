import sys
import os
import random
import math
import matplotlib.pyplot as plt

def prod_punto(a,b):
    sum = 0
    if type(a).__name__ != "float" and type(b).__name__ != "float":
        if len(a) == len(b):
            for i in range(0,len(a)):
                sum = sum + a[i]*b[i]
            return sum
        else:
            return False
    else:
        if type(a).__name__ == 'float':
            for i in range(0,len(b)):
                sum = sum + a*b[i]
            return sum
        else:
            if type(b).__name__ == 'float':
                for i in range(0,len(a)):
                    sum = sum + a[i]*b
                return sum
            else:
                return False

def set_target(x,y):
    if pow(x-15,2)+pow(y-6,2) <= 9:
        return "B"
    else:
        return "A"

class Net:

    def __init__(self,examples,target):
        self.examples = examples
        self.target = target
        self.num_hidden = 2
        self.o_k = []
        self.o_h = []
        self.w = []
        self.w_target = []
        self.threshold = random.random() - 0.5
        w_current = []
        for i in range(0,self.num_hidden):
            for j in range(0,len(self.examples[0])):
                w_current.append(random.uniform(-0.5,0.5))
            self.w_target.append(random.uniform(-0.5,0.5))
            self.w.append(w_current)
            w_current = []
        
    def get_output(self,target):
        if target == "A":
            return 0
        else:
            return 1

    def training(self):
        for ex in range(0,len(self.examples)):
            
            for it in range(0,200):

            ### Compute of the Outputs ###
                
                # Output hiddens items
                self.o_h = self.o_k = []
                net  = 0
                for j in range(0,self.num_hidden):
                    net += prod_punto(self.examples[ex],self.w[j])
                net += self.threshold
                self.o_h.append(1.0 / (1.0 + math.exp(-1.0*net)))
                print "Output_h = "+str(1.0 / (1.0 + math.exp(-1.0*net)))

                # Output output items
                net = prod_punto(self.o_h,self.w_target)
                net += self.threshold
                self.o_k.append(1 / (1 + math.exp(-1.0*net)))
                print "Output_k = "+str(1.0 / (1.0 + math.exp(-1.0*net)))

                # Compute error of the output items
                for i in range(0,len(self.o_k)):
                    error_k = self.o_k[i]*(1-self.o_k[i])*(self.get_output(self.target[i])-self.o_k[i])
                    print "Error_k = "+str(error_k)

                # Compute error of the hidden items
                for i in range(0,len(self.o_h)):
                    error_h = self.o_h[i]*(1-self.o_h[i])*(prod_punto(self.w_target,error_k))
                    print "Error_h = "+str(error_h)

            ### Update of the weigths ###
               
                # Weigths of hidden items
                for i in range(0,self.num_hidden):
                    for j in range(0,len(self.examples[0])):
                        self.w[i][j] = self.w[i][j] + ((0.001)*self.o_h[i])*self.examples[ex][j]
               
                # Weights of the output items
                for i in range(0,self.num_hidden):
                    for j in range(0,len(self.examples[0])):
                        self.w_target[i] = self.w_target[i] + ((0.01)*self.o_k[0])*self.examples[ex][j]
                    
        return self

def read_patterns(name_file):
    pattern_vector = []
    current_vector = []
    example_vector = []
    target_vector = []
    file = open(name_file,'r')
    while True:
        linea = file.readline()
        if not linea: break
        string = ""
        for i in range(0,len(linea)):
            if linea[i] == " ":
                current_vector.append(float(string))
                string = ""
            else:
                string += linea[i]
                if string == "A" or string == "B":
                    target_vector.append(string)
        example_vector.append(current_vector)
        current_vector = []
    pattern_vector.append(example_vector)
    pattern_vector.append(target_vector)
    file.close()
    return pattern_vector

def generate_patterns(num):
    pattern_vector = []
    current_vector = []
    example_vector = []
    target_vector = []
    a  = b = j = 0
    patterns = []    
    while j < num:
        x = (math.floor(random.uniform(0,20)*1000000))/1000000
        y = (math.floor(random.uniform(0,12)*1000000))/1000000
        target = set_target(x,y)
        if target == "A" and a < num/2: 
            a += 1
            current_vector.append(x)
            current_vector.append(y)
            target_vector.append("A")
            j += 1
            example_vector.append(current_vector)
        else: 
            if target == "B" and b < num/2:
                b += 1
                current_vector.append(x)
                current_vector.append(y)
                target_vector.append("B")
                j += 1
                example_vector.append(current_vector)
        current_vector = []
    pattern_vector.append(example_vector)
    pattern_vector.append(target_vector)
    return pattern_vector

def generate_test_set():
    examples = []
    current = []
    div_x = 20.0 / 99.0
    div_y = 12.0 / 99.0
    i = j = 0.0
    while i <= 20.0:
        while j <= 12.0:
            current.append(i)
            current.append(j)
            examples.append(current)
            current = []
            j += div_y
        j = 0
        i += div_x
    return examples

tests = generate_test_set()
length = len(tests)
i = 0
x = [] 
y = []
for i in range(0, length):
    x.append(tests[i][0])
    y.append(tests[i][1])
    
plt.plot(x, y, 'r+')
plt.show()

# patterns = []
# patterns.append(read_patterns("500.txt"))
# patterns.append(read_patterns("1000.txt"))
# patterns.append(read_patterns("2000.txt"))
# patterns.append(generate_patterns(500))
# patterns.append(generate_patterns(1000))
# patterns.append(generate_patterns(2000))

# net = Net(patterns[0][0],patterns[0][1])
# print net.w
# print net.w_target
# net.training()
# print net.w
# print net.w_target


# file = open("500_mine.txt",'a')
# for i in range(0,500):
#     file.write(str(patterns[3][i].x)+" "+str(patterns[3][i].y)+" "+patterns[3][i].target+"\n")
# file.close()

# file = open("1000_mine.txt",'a')
# for i in range(0,1000):
#     file.write(str(patterns[4][i].x)+" "+str(patterns[4][i].y)+" "+patterns[4][i].target+"\n")
# file.close()

# file = open("2000_mine.txt",'a')
# for i in range(0,2000):
#     file.write(str(patterns[5][i].x)+" "+str(patterns[5][i].y)+" "+patterns[5][i].target+"\n")
# file.close()

