import sys
from copy import deepcopy

def lista_sin_rep(lista):
	no_rep = []
	for i in lista:
		if len(no_rep)==0:
			no_rep.append(i)
		else:
			for j in no_rep:
				if i==j:
					break
			if j==no_rep[len(no_rep)-1] and j!=i:
				no_rep.append(i)
	return no_rep

def variables_hide(dominio,min_s1_s2,max_s1_s2,s1,s2,suma):
	var_hide ={}
	#Variables escondidas de letra+letra = letra
	for i in range(1,len(min_s1_s2)+1):
		label = "h"+str(i)
		var_hide[label]=[s1[-i],s2[-i],suma[-i],"x"+str(i-1),"x"+str(i)]
		dominio_aux=[(l1,l2,l3,r1,r2) for l1 in dominio[s1[-i]] for l2 in dominio[s2[-i]] for l3 in dominio[suma[-i]] for r1 in dominio.get("x"+str(i-1),[0]) for r2 in dominio.get("x"+str(i),[0]) if l1+l2+r1==l3+10*r2]
		if s1[-i]==s2[-i] and s1[-i]==suma[-i]:
			dominio[label]=[d for d in dominio_aux if d[0]==d[1] and d[0]==d[2]]
		elif s1[-1]==s2[-1]:
			dominio[label]=[d for d in dominio_aux if d[0]==d[1] and d[0]!=d[2]]
		elif s1[-1]==suma[-1]:
			dominio[label]=[d for d in dominio_aux if d[0]==d[2] and d[0]!=d[1]]
		elif s2[-1]==suma[-1]:
			dominio[label]=[d for d in dominio_aux if d[1]==d[2] and d[0]!=d[1]]
		else:
			dominio[label]=[d for d in dominio_aux if d[0]!=d[1] and d[0]!=d[2] and d[1]!=d[2]]
	#Variables escondidas de letra + nada = letra
	for i in range(len(min_s1_s2)+1,len(max_s1_s2)+1):
		label = "h"+str(i)
		var_hide[label]=[max_s1_s2[-i],suma[-i],"x"+str(i-1),"x"+str(i)]
		dominio_aux=[(l1,l2,r1,r2) for l1 in dominio[max_s1_s2[-i]] for l2 in dominio[suma[-i]] for r1 in dominio.get("x"+str(i-1),[0]) for r2 in dominio.get("x"+str(i),[0])]
		if max_s1_s2[-i]==suma[-i]:
			dominio[label]=[d for d in dominio_aux if d[0]==d[1]]
		else:
			dominio[label]=[d for d in dominio_aux if d[0]!=d[1]]
	return var_hide

def fail_first(dominio,var_sin_asignar):
	print var_sin_asignar
	dominio_min = 1000
	for j in var_sin_asignar:
		for i in j:
			if len(dominio[i])==0:
				return "CONFLICTO"
			if len(dominio[i])<dominio_min:
				dominio_min = len(dominio[i])
				var=i
	return var

def asignar(dominio,var,valor):
	print "\nSe asigna el valor " 
	print valor 
	print "a la variable " + var + " eliminando el resto del dominio de la variable\n"
	dominio[var]=[valor]

def all_diff(dominio,letras_no_asig,asig):
	print "\nSe restringe el dominio de las letras, con la restriccion de que no pueden ser igual a otra\n"
	for i in letras_no_asig:
		for j in dominio[i]:
			if j==asig:
				dominio[i].remove(asig)
				break

def act_dom_hide(dominio,hide,hide_no_asig):
	print "\nSe actualiza el dominio de las variables escondidas\n"
	for i in hide_no_asig:
		tupla = hide[i]
		dominio_aux = dominio[i]
		if len(hide[i])==4:
			dominio[i] = [t for t in dominio_aux if t[0] in dominio[hide[i][0]] and t[1] in dominio[hide[i][1]] and t[2] in dominio[hide[i][2]] and t[3] in dominio[hide[i][3]]]
		elif len(hide[i])==5:
			if hide[i][3]!="x0":
				dominio[i] = [t for t in dominio_aux if t[0] in dominio[hide[i][0]] and t[1] in dominio[hide[i][1]] and t[2] in dominio[hide[i][2]] and t[3] in dominio[hide[i][3]] and t[4] in dominio[hide[i][4]]]
			else:
				dominio[i] = [t for t in dominio_aux if t[0] in dominio[hide[i][0]] and t[1] in dominio[hide[i][1]] and t[2] in dominio[hide[i][2]] and t[4] in dominio[hide[i][4]]]



def act_dom_var(dominio,hide):
	print "\nSe actualiza el dominio de las variables no escondidas\n"
	for h in hide.keys():
		for i in range(0,len(hide[h])):
			if hide[h][i]!="x0":
				dominio_var = [t[i] for t in dominio[h]]
				dominio_var = lista_sin_rep(dominio_var)
				dominio_aux = deepcopy(dominio[hide[h][i]])
				dominio[hide[h][i]] = [j for j in dominio_aux if j in dominio_var]
		i=0

def arbol(dominio,hide,var_sin_asig,clave):
	if len(var_sin_asig[clave][0])==0 and len(var_sin_asig[clave][1])==0 and len(var_sin_asig[clave][2])==0:
		print dominio[clave]
	else:
		nueva_var = fail_first(dominio[clave],var_sin_asig[clave])
		print nueva_var
		if nueva_var == "CONFLICTO":
			print "Backtracking"
		else:
			nuevo_dominio = deepcopy(dominio[clave])
			asignacion = (nueva_var,nuevo_dominio[nueva_var][0])
			asignar(nuevo_dominio,nueva_var,asignacion[1])
			new_var_sin_asig = deepcopy(var_sin_asig[clave])
			if "x" in nueva_var:
				new_var_sin_asig[2].remove(nueva_var)
			elif "h" in nueva_var:
				new_var_sin_asig[1].remove(nueva_var)
			else:
				new_var_sin_asig[0].remove(nueva_var)
				all_diff(nuevo_dominio,new_var_sin_asig[0],asignacion[1])
			while True:
				act_dom_hide(nuevo_dominio,hide,new_var_sin_asig[1])
				dom_aux = deepcopy(nuevo_dominio)
				act_dom_var(nuevo_dominio,hide)
				if (nuevo_dominio==dom_aux):
					break
			dominio[nueva_var]=nuevo_dominio
			var_sin_asig[nueva_var]=new_var_sin_asig
			arbol(dominio,hide,var_sin_asig,nueva_var)

if len(sys.argv)!=4:
	print "\nUso:python crypto.py <s1> <s2> <suma>\n"
	print "\tEjemplo: python crypto AS A MOM\n"
	sys.exit()
if len(sys.argv[1])>len(sys.argv[3]) or len(sys.argv[2])>len(sys.argv[3]):
	print "\nEntrada invalida:\n\t La longitud de los dos sumandos debe ser menor o igual a la longitud del resultado\n"
	sys.exit()
s1 = sys.argv[1]
s2 = sys.argv[2]
suma = sys.argv[3]
letras = lista_sin_rep(s1+s2+suma)
if len(set(letras)&set(map(chr,range(65,91))))!=len(letras):
	print "\nEntrada invalida:\n\t Los caracteres que representan cada numero estan restringidos a letras mayusculas del alfabeto\n"
	sys.exit()

dominio = {}
for i in letras:
	if s1[0]==i or s2[0]==i or suma[0]==i:
		dominio[i]=[j for j in range(1,10)]
	else:
		dominio[i]=[j for j in range(0,10)]
if len(s1)<=len(s2):
	min_s1_s2 = s1
	max_s1_s2 = s2
else:
	min_s1_s2 = s2
	max_s1_s2= s1

var_aux = []
for i in range(1,len(max_s1_s2)+1):
	dominio["x"+str(i)]=[0,1]
	var_aux.append("x"+str(i))
	
hide = variables_hide(dominio,min_s1_s2,max_s1_s2,s1,s2,suma)
hide_no_asig = hide.keys()
letras_no_asig = letras
aux_no_asig = var_aux
variables_no_asig = [letras_no_asig]+[hide_no_asig]+[aux_no_asig] 

diccionario_dominios = {"nivel0":dominio}
diccionario_asig = {"nivel0":variables_no_asig}

print letras
print var_aux
print hide

arbol(diccionario_dominios,hide,diccionario_asig,"nivel0")
