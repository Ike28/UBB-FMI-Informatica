clc
fprintf('// 1\n')
w='word';
perms(w)
fprintf('// 2\n')
nchoosek([2 3 5 7],2)

fprintf('// 3\n')
function A=aranjamente(v,k)
  A=[];
  y=nchoosek(v,k);
  for c=1:length(y)
    ar=perms(y(c,:));
    A = [A;ar];
  endfor
end

aranjamente([2,3,5,7],2)

