import sys
import os

if (len(sys.argv)) != 2:
	print "Uso: python cardpuzzle.py <archivo_entrada>"
	exit()
if (sys.argv[1])[-4:] != "inst":
	print "La extension del archivo de entrada debe ser .inst"
	exit()
archivo_salida = "cnf/"+(sys.argv[1])[:-5]+".cnf"
print "\nEl archivo en formato cnf utilizado para el solver se puede encontrar en "+archivo_salida+"\n"
comando_python = "python cardpuzzle-cnf.py "+sys.argv[1]+" "+archivo_salida
os.system(comando_python)
comando_zchaff = "./zchaff "+archivo_salida+" 100"
resultado = (os.popen(comando_zchaff).read()).split()

if resultado[-1]=="UNSAT":
	print "Solucion: 0"
else:
	num_var = int(resultado[-42])
	solucion = [i for i in resultado[17:(17+num_var)]]
	print "Solucion:"
	for i in solucion:
		print i,
	print "\n"
