import matplotlib.pyplot as plt

it = []
error = []
file = open("corrida_20.txt",'r')
while True:
    line = file.readline()
    if not line: break
    line_content = line.split()
    it.append(int(line_content[0]))
    error.append(float(line_content[1]))
file.close()

plt.plot(it,error)
plt.title("Error con 20 neuronas en la capa intermedia")
plt.xlabel("Iteraciones")
plt.ylabel("Error")
plt.xlim(0,600)
plt.ylim(0,0.3)
plt.savefig("error_20_neuronas")
