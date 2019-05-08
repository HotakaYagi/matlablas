function [timer, perf] = perftest
% xpy: 3.3e5, dot: 5e5, mv: 2e3, mm: 6e2
ave = 10;
m = 3000;
timer = zeros(m/10, ave);
perf = zeros(m/10, ave);
a0 = rand(m);
b0 = rand(m, 1);
for i = 10 : 10 : m
    a = a0(1:i, 1:i);
    b = b0(1:i);
    c = a * b;
    for j = 1 : ave
        tic;
        c = dgemv(a, b);
        t = toc;
        timer(i/10, j) = timer(i/10, j) + t;
        perf(i/10, j) = 2 * i^2 / timer(i/10, j) / 10^9;
    end
end
end