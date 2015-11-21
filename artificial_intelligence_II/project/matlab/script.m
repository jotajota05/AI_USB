load datos_jota.txt
file = fopen('transformaciones_jota.txt', 'w')

lineas = 238
i = 1

while i < lineas
  A = [datos_jota(i,2) datos_jota(i,3) 1 0; datos_jota(i,3) -datos_jota(i,2) 0 1; datos_jota(i,4) datos_jota(i,5) 1 0; datos_jota(i,5) -datos_jota(i,4) 0 1]
  b = [7; 15; 17; 15]
  resultado = A\b
  fprintf(file, '%f', resultado(1,1))
  fprintf(file, ' ')
  fprintf(file, '%f', resultado(2,1))
  fprintf(file, ' ')
  fprintf(file, '%f', resultado(3,1))
  fprintf(file, ' ')
  fprintf(file, '%f', resultado(4,1))
  fprintf(file, '\n')
  i = i + 1
end
	  
fclose(file)
  
  
