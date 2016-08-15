clear;
rootname='riftsics';

paramfile=[rootname '.param'];

param=load(paramfile);

sigma=param(:,2);

for i=1:length(param);
   i;
	Eradfile = [rootname num2str(i) 'tp' '.txt'];

   Eraddmp=load(Eradfile);
   Totalpwr(i)= Eraddmp;
end;

save ("-ascii","total.txt","Totalpwr"); 


