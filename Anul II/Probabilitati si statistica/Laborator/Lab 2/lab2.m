clc
clf
fprintf('// 1\n')
noc=0;
noruns=300;
for c=1:noruns
  pers=randi(365, 23, 1);
  unidates=unique(pers);
  if length(unidates)==length(pers)
    noc=noc+1;
  endif
end
freq=noc/noruns;
fprintf(' frecventa relativa = %d\n', freq)

fprintf('// 2\n')
Ax=0; Ay=1; Bx=0; By=0; Cx=1; Cy=0; Dx=1; Dy=1;
plot([Ax Bx Cx Dx Ax],[Ay By Cy Dy Ay],'b','LineWidth',3)
axis square;

nopoints=500;
noc=0;
hold on;
for c=1:nopoints
  rx=rand();
  ry=rand();
  if pdist([[rx,ry];[0.5,0.5]]) <= 0.5
    plot(rx,ry,'b','MarkerSize',8)
    noc=noc+1;
  endif
end
freq=noc/nopoints;
prg=(pi*(0.5*0.5))/2;
fprintf(' a) frecventa relativa = %d\n', freq)
fprintf('    probabilitatea geometrica = %d\n', prg)

noc=0;
hold on;
for c=1:nopoints
  rx=rand();
  ry=rand();
  distcentre=pdist([[rx,ry];[0.5,0.5]]);
  if distcentre <= pdist([[rx,ry];[0,0]]) && distcentre <= pdist([[rx,ry];[0,1]]) && distcentre <= pdist([[rx,ry];[1,0]]) && distcentre <= pdist([[rx,ry];[1,1]])
    plot(rx,ry,'g','MarkerSize',8)
    noc=noc+1;
  endif
end
freq=noc/nopoints;
prg=pdist([[0,0.5];[0.5,0]])*pdist([[0,0.5];[0.5,0]]);
fprintf(' b) frecventa relativa = %d\n', freq)
fprintf('    probabilitatea geometrica = %d\n', prg)

noc=0;
hold on;
for c=1:nopoints
  rx=rand();
  ry=rand();
  a=pdist([[rx,ry];[0,0]]);
  b=pdist([[rx,ry];[0,1]]);
  c=pdist([[rx,ry];[1,0]]);
  d=pdist([[rx,ry];[1,1]]);

end


