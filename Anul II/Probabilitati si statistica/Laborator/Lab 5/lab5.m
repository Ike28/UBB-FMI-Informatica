clc
grupe = [1 2 3 4];
p = [0.46 0.4 0.1 0.04];
s = cumsum(p);
noruns = 1000;
X = [];
for i=1:noruns
	u = rand;
	k = 1;
	while s(k) < u
		k++;
	end
	X(i) = grupe(k);
endfor

figure
title('1) Histograma grupelor prin observare')
hold on
grid on
bar(1:4, histc(X, 1:4)/noruns, 'hist', 'FaceColor', 'b')
X = randsample(grupe, noruns, replacement=true, p);
figure
title('1) Histograma grupelor prin distributia discreta')
hold on
grid on
bar(1:4, histc(X, 1:4)/noruns, 'FaceColor', 'y')
grupe_labels = {'0', 'A', 'B', 'AB'};
set(gca, 'xticklabel', grupe_labels)

fprintf('// 2)\n')
lambda = 1/12;
noruns = 1000;
F = @(x) -1/lambda*log(1-x);
X = [];
for i=1:noruns
	u = rand;
	X(i) = F(u);
endfor

fprintf('	valoarea medie E(X) din simulare = %d\n', mean(X))
fprintf('	deviatia standard Std(X) din simulare = %d\n', std(X))
X = exprnd(1/lambda, 1, noruns);
fprintf('	valoarea medie E(X) dupa distributie = %d\n', mean(X))
fprintf('	deviatia standard Std(X) dupa distributie = %d\n', std(X))

fprintf('// 3)\n')
noruns = 1000;
coordsX = [];
coordsY = [];
for i=1:noruns
	u1 = rand;
	u2 = rand;
	ro(i) = sqrt(-2*log(u1));
	fi(i) = 2*pi*u2;

	coordsX(i) = ro(i)*cos(fi(i));
	coordsY(i) = ro(i)*sin(fi(i));
endfor

hits = sum((coordsX.^2 + coordsY.^2) < 0.25);

fprintf('	frecventa relativa din simulare = %d\n', hits/noruns)
fprintf('	probabilitatea exacta = %d\n', 1-exp(-1/8))
X_norm = normrnd(0, 1, 2, noruns);
hits_norm = sum((X_norm(1,:)).^2 + (X_norm(2,:)).^2 < 0.25);
fprintf('	frecventa dupa distributia normala = %d\n', hits_norm/noruns)
