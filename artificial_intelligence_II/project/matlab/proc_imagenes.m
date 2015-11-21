fid = fopen('nombres_imagenes_jota.txt', 'r');
out = fopen('nuevas_imagenes_jota.txt', 'r');
load transformaciones_jota.txt;

line = fgetl(fid);
line2 = fgetl(out);
i = 1

while ischar(line) && ischar(line2)
	I = imread(line);
	tform = maketform('affine', [transformaciones_jota(i,1) -transformaciones_jota(i,2) 0; transformaciones_jota(i,2) transformaciones_jota(i,1) 0; transformaciones_jota(1,3) transformaciones_jota(i,4) 1]);
	I_T = imtransform(I,tform);
	imwrite(I_T, line2);

    	line = fgetl(fid);
	line2 = fgetl(out);
	i = i + 1
end

fclose(fid);
fclose(out);
