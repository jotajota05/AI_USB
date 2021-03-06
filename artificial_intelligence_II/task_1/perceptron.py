import sys
import random
import math
import matplotlib.pyplot as plt
import time

def prod_punto(a,b):
    sum = 0
    if len(a) == len(b):
        for i in range(0,len(a)):
           sum = sum + a[i]*b[i]
        return sum
    else:
        return False

class Perceptron:

    def __init__(self,inputs,target):
        self.x = inputs
        self.w = []
        self.target = target;
        self.output = [-1,-1,-1,-1]
        self.error = []
        self.num_it = []

    def training(self,learn_rate,w_zero):
        i = 0
        j = 0
        wi = random.random()/10
        self.w = [w_zero,wi,wi]
        for j in range(0,1000):
            err = 0.0
            for i in range(0,4):
                if prod_punto(self.x[i],self.w) > 0:
                    self.output[i] = 1
                else:
                    self.output[i] = 0
                stop_cond = self.target[i] - self.output[i];
                err += ((pow(self.target[i] - self.output[i],2) / 2.0))
                if stop_cond == 0:
                    continue
                else:
                    for k in range(0,len(self.w)):
                        self.w[k] = self.w[k] + learn_rate*stop_cond*self.x[i][k]
            self.error.append(err)
            self.num_it.append(j)
            if err == 0:
                break
        print "Out Training "+str(self.output)
        print "# Iteraciones = "+str(j+1)
        return self

def evaluation(percep,input):
    output = []
    i = 0
    for i in range(0,4):
        if (prod_punto(input[i],percep.w) > 0):
            output.append(1)
        else:
            output.append(0)
    return output
    
print "\n"

learn_rate_vector = [0.01,0.05,0.1,0.2,0.3,0.4,0.5,0.99]
inputs = [[1,0,0],[1,0,1],[1,1,0],[1,1,1]]
target_and = [0,0,0,1]
target_or = [0,1,1,1]
target_xor = [0,1,1,0]

p_and = Perceptron(inputs,target_and)

print "############# Training - AND #############\n"

for learn_rate in learn_rate_vector:

    p_and.training(learn_rate,1.5)
    print "Learning Rate = "+str(learn_rate)
    output = evaluation(p_and,inputs)
    print "Salida Test - AND "+str(output)
    print "\n"
#     plt.plot(p_and.num_it,p_and.error)
#     plt.ylim(-1,3)
#     plt.title("AND - Error con Tasa de aprendizaje = "+str(learn_rate))
#     plt.xlabel("# de iteraciones")
#     plt.ylabel("Error")
#     plt.show()

p_or = Perceptron(inputs,target_or)

print "############# Training - OR #############\n"

for learn_rate in learn_rate_vector:

    p_or.training(learn_rate,0.5)
    print "Learning Rate = "+str(learn_rate)
    output = evaluation(p_or,inputs)
    print "Salida Test - OR "+str(output)
    print "\n"
#     plt.plot(p_or.num_it,p_or.error)
#     plt.ylim(-1,3)
#     plt.title("OR - Error con Tasa de aprendizaje = "+str(learn_rate))
#     plt.xlabel("# de iteraciones")
#     plt.ylabel("Error")
#     plt.show()

p_xor = Perceptron(inputs,target_xor)

print "############# Training - XOR #############\n"

for learn_rate in learn_rate_vector:

    p_xor.training(learn_rate,1)
    print "Learning Rate = "+str(learn_rate)
    output = evaluation(p_xor,inputs)
    print "Salida Test - XOR "+str(output)
    print "\n"
#     plt.plot(p_xor.num_it,p_xor.error)
#     plt.ylim(-1,3)
#     plt.title("XOR - Error con Tasa de aprendizaje = "+str(learn_rate))
#     plt.xlabel("# de iteraciones")
#     plt.ylabel("Error")
#     plt.show()

