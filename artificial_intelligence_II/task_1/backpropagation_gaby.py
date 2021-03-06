import sys
import math
import random
import matplotlib.pyplot as plt
#import matplotlib as plt

def read_patterns(file_name):
    file = open(file_name,'r')
    content = file.read()
    list_content = content.split()
    length = len(list_content)
    i = 0
    examples = []
    targets = []

    while (i < length):
        examples.append([float(list_content[i]), float(list_content[i+1])])

        if list_content[i+2] == "A":
            targets.append(0)
        else:
            targets.append(1)

        i += 3

    file.close()
    return [examples, targets]

class SigmoidUnit:

    # type = indica de que tipo es la sigmoid unit, si es de entrada 0, hidden 1 o salida 2.
    # inputs es una lista de sigmoid units, los valores output de cada una de estas 
    # neuronas, seran los valores de entrada de self.
    def __init__(self,type, inputs, output, weights):
        self.type = type
        self.inputs = inputs
        self.output = output
        self.weights = weights
        self.length = len(self.inputs)
        self.error = 0
        self.threshold = random.random() - 0.5

    def compute_output(self):
        net = 0

        for i in range(0, self.length):
            net += self.weights[i] * self.inputs[i].output

        net += self.threshold

        self.output = 1 / (1 + math.exp(-net))

    def compute_error_out(self, target):
        self.error = self.output * (1 - self.output) * (target - self.output)

    def compute_error_hidden(self, out_units, pos):
        sum = 0
        for o_u in out_units:
            sum += o_u.error * o_u.weights[pos]

        self.error = self.output * (1 - self.output) * sum

    def update_weights(self, learn_rate):
        self.threshold += learn_rate * self.error

        for i in range(0, self.length):
            self.weights[i] += learn_rate * self.error * self.inputs[i].output

    def print_weights(self):
        p = "Pesos: [ "
        for w in self.weights:
           p += str(w) + " "
        p += "]"

        print p
    
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

def backpropagation(examples, targets, learn_rate, num_hidden, num_out, num_examples, tests):
    in_1 = SigmoidUnit(0, [], 0, [])
    in_2 = SigmoidUnit(0, [], 0, [])

    hidden_units = []
    for i in range(0, num_hidden):
        hidden_units.append(SigmoidUnit(1, [in_1, in_2], 0, [random.random() - 0.5, random.random() - 0.5]))

    out_units = []
    out_weights = []
    for i in range(0, num_hidden):
        out_weights.append(random.random() - 0.5)

    for i in range(0, num_out):
        out_units.append(SigmoidUnit(2, hidden_units, 0, out_weights))

    it = 0
    while(it < 2000):
        for i in range(0, num_examples):
            # Propagate the input foward through the network
            in_1.output = examples[i][0]
            in_2.output = examples[i][1]
            
            units = hidden_units + out_units
            for u in units:
                u.compute_output()

            # Propagate the errors backward through the network
            for o in out_units:
                o.compute_error_out(targets[i])

            for j in range(0, num_hidden):
                hidden_units[j].compute_error_hidden(out_units, j)

            units = hidden_units + out_units
            for u in units:
                u.update_weights(learn_rate)                

        it += 1

    #print "---------- VALIDACION"
    results = validate_network(tests, hidden_units, out_units, len(tests))
    plot_results(tests, results, num_hidden)

    #print "---------- HIDDEN"
    #for h in hidden_units:
    #    h.print_weights()

    #print "---------- OUT"
    #for o in out_units:
    #    o.print_weights()

def plot_results(tests, results, num_hidden):
    length = len(results)
    i = 0
    red_x_pts = []
    red_y_pts = []
    blue_x_pts = []
    blue_y_pts = []
    for i in range(0, length):
        if results[i] >= 0.5:
            red_x_pts.append(tests[i][0])
            red_y_pts.append(tests[i][1])
        else:
            blue_x_pts.append(tests[i][0])
            blue_y_pts.append(tests[i][1])

    plt.plot(red_x_pts, red_y_pts, 'r+')
    plt.plot(blue_x_pts, blue_y_pts, 'b+')
    plt.title("Resultados con " + str(num_hidden) + " neuronas en la capa intermedia")
    print "Hace el show()"
    #plt.savefig("BP_"+str(num_hidden))
    plt.show()

def validate_network(tests, hidden_units, out_units, num_examples):
    in_1 = SigmoidUnit(0, [], 0, [])
    in_2 = SigmoidUnit(0, [], 0, [])
    #file = open("resultados.txt", 'w')
    results = []

    for i in range(0, num_examples):        
        #line = "Ejemplo: [ " + str(examples[i][0]) + ", " + str(examples[i][1]) + " ]\n"
        in_1.output = tests[i][0]
        in_2.output = tests[i][1]

        for h in hidden_units:
            h.inputs = [in_1, in_2]
            h.compute_output()
            
        for o in out_units:    
            o.compute_output()
            results.append(o.output)
            
        #file.write(str(o.output))

    #file.close()
    return results

def compare_results(x, y):
    file_9n = open("resultados_" + str(x) + "n.txt", 'r')
    file_10n = open("resultados_" + str(y) + "n.txt", 'r')

    content_9n = file_9n.read()
    content_10n = file_10n.read()
    
    list_9n = content_9n.split()
    list_10n = content_10n.split()

    length = len(list_9n)
    i = 0

    n_9 = 0
    n_10 = 0

    while (i < length):
        if list_9n[i] == '1':
            if (list_9n[i+1] > list_10n[i+1]):
                n_9 += 1
            else:
                n_10 += 1
        else:
            if (list_9n[i+1] < list_10n[i+1]):
                n_9 += 1
            else:
                n_10 += 1
        i += 2
    
    if n_9 > n_10:
        print "Red de " + str(x) + " neuronas"
    else:
        print "Red de " + str(y) + " neuronas"
        
def main():
    #examples = [[0, 0], [0, 1], [1, 0], [1, 1]]
    #targets = [0, 1, 1, 0]

    #
    result = read_patterns("500.txt")
    tests = generate_test_set()
    examples = result[0]
    targets = result[1]

    for i in range(2, 11):
        backpropagation(examples, targets, 0.1, i, 1, 500, tests)
            
main()
