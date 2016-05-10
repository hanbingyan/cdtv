function [R] = difX(X)
R = X(:,[2:end end],:)-X;