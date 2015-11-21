import matplotlib.pyplot as plt
import sys
import time

class LinearUnit:

    # x = vector de vectores con ejemplos de cada Xi
    # w = vector con pesos
    # target = vector con valor que deberia devolver la funcion output
    # output = vector con resultado de calculo de funcion output del perceptron.
    def __init__(self,inputs,weights,target,output):
        self.x = inputs
        self.num_ex = len(self.x)
        self.w = weights
        self.num_input_val = len(self.w)
        self.target = target
        self.output = output
        self.err = []
        self.it = []

    def update_weights(self, learn_rate):
        for i in range(0, self.num_input_val):
            sum = 0
            for j in range(0, self.num_ex):
                sum += (self.target[j] - self.output[j]) * self.x[j][i]    
            self.w[i] += learn_rate * sum

    def incremental_update_weights(self, learn_rate, example):        
        for i in range(0, self.num_input_val):            
            self.w[i] += learn_rate * (self.target[example] - self.output[example]) * self.x[example][i]

    def compute_output(self, example):
        result = 0

        for i in range(0, self.num_input_val):
            result += self.w[i] * self.x[example][i]

        self.output[example] = result

        return

    def compute_error(self):
        err_sum = 0

        for i in range(0, self.num_ex):
            err_sum += (self.target[i] - self.output[i])**2

        return err_sum/2

    def compute_incremental_error(self, i):
        return ((self.target[i] - self.output[i])**2)/2


    def print_outputs(self):
        output = "Output: [ "
        for i in range(0, self.num_ex):
           output += str(self.output[i]) + " "
        output += "]\n"
        print output

    def print_weights(self):
        pesos = "Pesos: [ "
        for i in range(0, self.num_input_val):
            pesos += str(self.w[i]) + " "
        pesos += "]\n"
        print pesos

    def delta_rule_training(self, learn_rate):
        it = 0
        while it < 5000:
            #self.print_weights()
            for i in range(0, self.num_ex):
                self.compute_output(i)
            self.update_weights(learn_rate)
            self.err.append(self.compute_error())
            self.it.append(it)
            it += 1

    # Aqui cada posicion del arreglo de errores corresponde con cada ejemplo
    def incremental_delta_rule_training(self, learn_rate):
        it = 0
        while it < 5000:
            #self.print_weights()            
            ready = 1
            for i in range(0, self.num_ex):
                self.compute_output(i)
                self.incremental_update_weights(learn_rate, i)
            it += 1

def main():
    learn_rate_vector = [0.01,0.05,0.1,0.2,0.3,0.4,0.5,0.99]

    # Aprendizaje con regla delta y gradient descent
    # AND
    and_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 0, 0, 1], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #and_l_unit.delta_rule_training(learn_rate)
    and_l_unit.delta_rule_training(0.1)
    and_l_unit.print_weights()
    and_l_unit.print_outputs()
        
        #plt.plot(and_l_unit.err, and_l_unit.it)
        #plt.show()

    # OR
    #or_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 1, 1, 1], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #    or_l_unit.delta_rule_training(learn_rate)

    # XOR
    #xor_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 1, 1, 0], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #    xor_l_unit.delta_rule_training(learn_rate)
    
    # Aprendizaje con regla delta y incremental o stochastic gradient descent
    # AND
    #and_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 0, 0, 1], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #    and_l_unit.incremental_delta_rule_training(learn_rate)

    # OR
    #or_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 1, 1, 1], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #    or_l_unit.incremental_delta_rule_training(learn_rate)

    # XOR
    #xor_l_unit = LinearUnit([[1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1]], [0.5, 0.5, 0.5], [0, 1, 1, 0], [0, 0, 0, 0])
    #for learn_rate in learn_rate_vector:
    #    xor_l_unit.incremental_delta_rule_training(learn_rate)

main()
