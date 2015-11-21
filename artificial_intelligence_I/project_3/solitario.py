import sys
import os

if (len(sys.argv)) != 2:
	print "Uso: python solitario.py <archivo_entrada>"
	exit()
if (sys.argv[1])[-5:] != ".inst":
	print "La extension del archivo de entrada debe ser .inst"
	exit()
archivo_salida = "cnf/"+(sys.argv[1])[:-5]+".cnf"
print "\nEl archivo en formato cnf utilizado para el solver se puede encontrar en "+archivo_salida+"\n"
comando_python = "python solitario-cnf.py "+sys.argv[1]+" "+archivo_salida
os.system(comando_python)
comando_zchaff = "./zchaff "+archivo_salida+" 100"
resultado = (os.popen(comando_zchaff).read()).split()

if resultado[-1]=="UNSAT":
	print "Solucion: 0\n"
else:
	print "Solucion: 1\n"
