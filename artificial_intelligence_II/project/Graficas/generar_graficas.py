import matplotlib.pyplot as plt

it = []
error = []
file = open("corrida_20_20_10.txt",'r')
while True:
    line = file.readline()
    if not line: break
    line_content = line.split()
    it.append(int(line_content[0]))
    error.append(float(line_content[1]))
file.close()

plt.plot(it,error)
plt.title("ECM con 20_20_10 neuronas en la capa intermedia")
plt.xlabel("Iteraciones")
plt.ylabel("Error")
#plt.xlim(0,850)
#plt.ylim(0,0.3)
plt.savefig("error_20_20_10_neuronas")
