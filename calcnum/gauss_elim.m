% Gauss elimination (no pivot)

function x = elim_gauss(A, b)
% A: matrix coef
% b: vec independent term
% x: solution vec

n = size(A, 1)

for k=1:n-1 % Iter over cols, last col is uneeded
    for i=k+1:n % Iter over rows of col.
        m = -A(i,k)/A(k,k);
        A(i, k:n) = A(i,k:n) + m*A(k,k:n);
        b(i) = b(i) + m*b(k);
    end
end

% disp('Hello, world')

