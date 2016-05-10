function [U,obj] = cdtv(B,lambda)
% use CD methods solve a l0TV problem

[m,n]=size(B);
U=B;
obj=zeros(1,200);
obj(1) =  lambda * sum(sum((abs(difX(U))+ abs(difY(U)))))  + sum(sum(abs(U-B)>0));
for l=2:1:200
for k=1:1:20000
    t=randi(m-2)+1;
    s=randi(n-2)+1;
    b=B(t,s);
    u1=U(t+1,s);
    u2=U(t-1,s);
    u3=U(t,s+1);
    u4=U(t,s-1);
    u=[b u1 u2 u3 u4];
   temp1=lambda*(abs(b-u1)+abs(b-u2)+abs(b-u3)+abs(b-u4));
   temp2=(u1~=b)+lambda*(abs(u1-u2)+abs(u1-u3)+abs(u1-u4));
   temp3=(u2~=b)+lambda*(abs(u1-u2)+abs(u2-u3)+abs(u2-u4));
   temp4=(u3~=b)+lambda*(abs(u3-u1)+abs(u3-u2)+abs(u3-u4));
   temp5=(u4~=b)+lambda*(abs(u4-u1)+abs(u4-u2)+abs(u4-u3));
   A=[temp1 temp2 temp3 temp4 temp5];
   [x,y]=sort(A);
   U(t,s)=u(y(1));
   if mod(k,50)==0
   % minimize the first row
   b=B(1,s);
   u1=U(1,s-1);
   u2=U(2,s);
   u3=U(1,s+1);
   u=[b u1 u2 u3];
   temp1=lambda*(abs(b-u1)+abs(b-u2)+abs(b-u3));
   temp2=(u1~=b)+lambda*(abs(u1-u2)+abs(u1-u3));
   temp3=(u2~=b)+lambda*(abs(u1-u2)+abs(u2-u3));
   temp4=(u3~=b)+lambda*(abs(u3-u1)+abs(u3-u2));
   A=[temp1 temp2 temp3 temp4];
   [x,y]=sort(A);
   U(1,s)=u(y(1));
   %minimize the last row
   b=B(m,s);
   u1=U(m,s-1);
   u2=U(m-1,s);
   u3=U(m,s+1);
   u=[b u1 u2 u3];
   temp1=lambda*(abs(b-u1)+abs(b-u2)+abs(b-u3));
   temp2=(u1~=b)+lambda*(abs(u1-u2)+abs(u1-u3));
   temp3=(u2~=b)+lambda*(abs(u1-u2)+abs(u2-u3));
   temp4=(u3~=b)+lambda*(abs(u3-u1)+abs(u3-u2));
   A=[temp1 temp2 temp3 temp4];
   [x,y]=sort(A);
   U(m,s)=u(y(1));
   %minimize the first column
    b=B(t,1);
   u1=U(t-1,1);
   u2=U(t,2);
   u3=U(t+1,1);
   u=[b u1 u2 u3];
   temp1=lambda*(abs(b-u1)+abs(b-u2)+abs(b-u3));
   temp2=(u1~=b)+lambda*(abs(u1-u2)+abs(u1-u3));
   temp3=(u2~=b)+lambda*(abs(u1-u2)+abs(u2-u3));
   temp4=(u3~=b)+lambda*(abs(u3-u1)+abs(u3-u2));
   A=[temp1 temp2 temp3 temp4];
   [x,y]=sort(A);
   U(t,1)=u(y(1));
   %minimize the last column
    b=B(t,n);
   u1=U(t-1,n);
   u2=U(t,n-1);
   u3=U(t+1,n);
   u=[b u1 u2 u3];
   temp1=lambda*(abs(b-u1)+abs(b-u2)+abs(b-u3));
   temp2=(u1~=b)+lambda*(abs(u1-u2)+abs(u1-u3));
   temp3=(u2~=b)+lambda*(abs(u1-u2)+abs(u2-u3));
   temp4=(u3~=b)+lambda*(abs(u3-u1)+abs(u3-u2));
   A=[temp1 temp2 temp3 temp4];
   [x,y]=sort(A);
   U(t,n)=u(y(1));
   end
end
%minimize four corner
b=B(1,1);
u1=U(1,2);
u2=U(2,1);
u=[b u1 u2];
temp1=lambda*(abs(b-u1)+abs(b-u2));
temp2=(u1~=b)+lambda*abs(u1-u2);
temp3=(u2~=b)+lambda*abs(u1-u2);
A=[temp1 temp2 temp3];
[x,y]=sort(A);
U(1,1)=u(y(1));

b=B(m,1);
u1=U(m,2);
u2=U(m-1,1);
u=[b u1 u2];
temp1=lambda*(abs(b-u1)+abs(b-u2));
temp2=(u1~=b)+lambda*abs(u1-u2);
temp3=(u2~=b)+lambda*abs(u1-u2);
A=[temp1 temp2 temp3];
[x,y]=sort(A);
U(m,1)=u(y(1));

b=B(1,n);
u1=U(2,n);
u2=U(1,n-1);
u=[b u1 u2];
temp1=lambda*(abs(b-u1)+abs(b-u2));
temp2=(u1~=b)+lambda*abs(u1-u2);
temp3=(u2~=b)+lambda*abs(u1-u2);
A=[temp1 temp2 temp3];
[x,y]=sort(A);
U(1,n)=u(y(1));

b=B(m,n);
u1=U(m-1,n);
u2=U(m,n-1);
u=[b u1 u2];
temp1=lambda*(abs(b-u1)+abs(b-u2));
temp2=(u1~=b)+lambda*abs(u1-u2);
temp3=(u2~=b)+lambda*abs(u1-u2);
A=[temp1 temp2 temp3];
[x,y]=sort(A);
U(m,n)=u(y(1));

obj(l) = lambda * sum(sum((abs(difX(U))+ abs(difY(U)))))  + sum(sum(abs(U-B)>0));
end
end

    