out = fopen('out_targets.txt', 'w');
for i=1 : 102
	fprintf(out,'%d\n',1);
end
for i=1 : 26
	fprintf(out,'%d\n',0);
end
fclose(out);
