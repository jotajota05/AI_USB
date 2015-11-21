fid = fopen('test_imagenes.txt', 'r');
out = fopen('out_imagenes.txt', 'w');

line = fgetl(fid);

while ischar(line)
	IHappy = imread('Happy.jpg');
	INotHappy = imread('notHappy.jpg');
	I = imread(line);
	RHappy = IHappy - I;
	RNotHappy = INotHappy - I;
	for i=1 : 10
		for j=1 : 24
			fprintf(out,'%d ',RHappy(i,j));
		end
	end
	for i=1 : 10
		for j=1 : 24
			fprintf(out,'%d ',RNotHappy(i,j));
		end
	end
	fprintf(out,'\n')
	line = fgetl(fid);
	
end

fclose(fid);
