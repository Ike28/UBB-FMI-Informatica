clc
fprintf('// 1\n')
urna = ['r', 'r', 'r', 'r', 'r', 'b', 'b', 'b', 'g', 'g'];
noruns=5000;
noca=0;
nocb=0;
noc_intersect=0;
nocb_a=0;
for c=1:noruns
  y = randsample(urna, 3, REPLACEMENT=false);

  if y(1) == y(2) == y(3)
    nocb=nocb+1;
  endif

  if y(1)=='r' || y(2)=='r' || y(3)=='r'
    noca=noca+1;
    if y(1) == y(2) == y(3)
      nocb_a=nocb_a+1;
    endif
  endif

  if y(1)=='r' && y(2)=='r' && y(3)=='r'
    noc_intersect = noc_intersect + 1;
  endif
end
freqa=noca/noruns;
freq_intersect=noc_intersect/noruns;
fprintf(' i) proportia ev. A = %d\n', freqa)
fprintf(' ii) proportia ev. AnB = %d\n', freq_intersect)
fprintf(' iii) probabilitatea estimata P(B|A) = %d\n', nocb_a/noruns)
fprintf('      probabilitatea teoretica P(B|A) = %d\n', freq_intersect/freqa)
fprintf(' iv) B in relatie cu A = %d\n', nocb_a/noca)

fprintf('// 2\n')
m=randi(20);
n=randi(100);
p=rand();
x=binornd(n,p,1,m);
N=hist(x,0:n);
bar(0:n, N/m, 'hist', 'FaceColor', 'b');
bar(0:n, binopdf(0:n, n, p), 'FaceColor', 'y');
legend('probabilitatile estimate', 'probabilitatile teoretice');
set(findobj('type','patch'),'facealpha', 0.7);
xlim([-1 n+1]);
no_zaruri = 5;
p = 1/3;
noruns = 5000;
distrib = binornd(no_zaruri, p, 1, noruns);
fprintf(' b) probabilitatea estimata = %d\n', sum(distrib == 2)/noruns)
fprintf('    probabilitatea teoretica = %d\n', binopdf(2, no_zaruri, p))

fprintf('// 3\n')
noruns=1000;
valori=zeros(1,24);
noc_iv=0;
for c=1:noruns
  zaruri = randi(6, 1, 4);
  s = sum(zaruri);
  valori(s)++;
  if s>=10 && s<=20
    noc_iv++;
  endif
endfor
axis1 = [];
axis2 = [];
dim = 0;
fprintf(' i)')
for c=4:24
  if valori(c) > 0
    fprintf(' frecventa absoluta pentru %d: %d\n', c, valori(c))
    axis1 = [axis1, c];
    axis2 = [axis2, valori(c)];
    dim++;
  endif
endfor

mat = [axis1; axis2];
axis3 = [];
for i=1:dim
  axis3 = [axis3; axis2(i) / noruns];
endfor
figure
title('3.ii) Histograma sumelor a 4 zaruri obtinute in 1000 aruncari')
hold on
hist(axis2, 1:dim)
figure
title('3.ii) Graficul sumelor a 4 zaruri obtinute raportat la 1000 aruncari')
bar(1:dim, axis3, 'hist', 'FaceColor', 'b')
fprintf(' iv) probabilitatea estimata = %d\n', noc_iv/noruns)