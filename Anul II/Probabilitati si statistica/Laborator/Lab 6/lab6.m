clc
clf
m = 165;
s = 10;
noruns = 500;
X = normrnd(m, s, 1, noruns);
figure
title('1.i) Histograma frecventelor absolute a inaltimilor')
hold on
hist(X, 10)

figure
title('1.ii) Histograma frecventelor relative a inaltimilor')
[~, XX] = hist(X, 10);
hist(X, XX, 10 / (max(X) - min(X)));
hold on
t = linspace(min(X), max(X), 1000);
plot(t, normpdf(t, 165, 10), '-r', 'LineWidth', 3);

fprintf('//1\n')
fprintf(' iii) valoarea medie din simulare m = %d\n', mean(X))
fprintf('      deviatia standard din simulare s = %d\n', std(X))
values = X((160<=X) & (X<=170));
fprintf('      valoarea medie a valorilor [160,170] = %d\n', mean(values))
fprintf('      proportia relativa = %d\n', length(values)/noruns)
fprintf('      proportia din distributie = %d\n', normcdf(170, 165, 10) - normcdf(160, 165, 10))
