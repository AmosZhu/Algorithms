function [prediction,result,traceBack] = Casino(sequence)

M=[0.95,0.05;0.1,0.9];

F=[1/6;1/6;1/6;1/6;1/6;1/6];

L=[1/10;1/10;1/10;1/10;1/10;1/2];

mapNum={"1";"2";"3";"4";"5";"6"};

mapName=["F";"L"];

len=length(sequence);
len
%assume the casino begin from F
prediction=[""];
preProb=1;
preState="F";
result=zeros(3,1);
traceBack=['B';'S';'S'];
result(1,1)=1;

for j=2:len+1
	k=find(strcmp(mapNum,sequence(j-1)));
	result=[result,zeros(3,1)];
	traceBack=[traceBack,zeros(3,1)];
	for i=1:3
		preProb=0;
		if i==1
			result(i,j)=0;
			traceBack(i,j)=sequence(j-1);
		elseif j==2
			preState="B";
			preProb=1;
			curProb=log(preProb*F(k,1));
			result(2,j)=curProb;
			curProb=log(preProb*L(k,1));
			result(3,j)=curProb;
			traceBack(i,j)=preState;
		else
			curProb=log(0);
			preState="F";
			for idx=2:3
				if idx==2
					T=F;
				else
					T=L;
				end
				preProb=result(idx,j-1);
				curProbt=preProb+log(T(k,1)*M(idx-1,i-1));
				if curProb<curProbt
					curProb=curProbt;
					preState=mapName(idx-1,1);
				end
			end
			result(i,j)=curProb;
			traceBack(i,j)=preState;
		end
	end
end
% trace back here
len=length(traceBack);

maxPoint=result(2,len);
i=2;
if maxPoint<result(3,len)
	i=3;
end

preState=traceBack(i,len);

prediction=[preState,prediction];

j=len-1;

while j>=2
	if strcmp(preState,"F")
		i=2;
	else
		i=3;
	end
	preState=traceBack(i,j);
	prediction=[preState,prediction];
	j--;
end
end


