#include <iostream>
using namespace std;
#include <stack>
#include <string>
#include <cstring>

class Exp{
	stack<char> ops;//运算符栈
	stack<double> ds;//数据栈
	double v, lh, rh;//计算结果和临时操作数变量
	char op;//运算符
public:
	double calinput(){//读取并计算表达式直到结束
		do{
			readdata();//读取数据
			skipspace();//跳过空白
		}while(readop());//读取运算符
		calremain();//处理栈中剩余的运算符
		return v;
	}
	void readdata(){
		while(!(cin>>v)){//读取数据失败应该是'('
			cin.clear();
			cin >> op;//读取'('
			if(op!='(') throw string("在该出现数值的地方遇到了")+op;
			ops.push(op);
		}
		ds.push(v);
	}
	void skipspace(){//跳过空格
		while(cin.peek()==' ') cin.ignore();
	}
	bool readop(){//读取运算符，可能遇到')'或者'\n'
		while((op=cin.get())==')'){//遇到')'了
			while(ops.top()!='('){//找栈里的'('为止
				rh=ds.top();ds.pop();//从栈中取得右操作数
				lh=ds.top();ds.pop();//从栈中取得左操作数
				ds.push(cal(lh,ops.top(),rh));//计算并入栈
				ops.pop();
			}
			ops.pop();//丢弃'('
		}
		if(op=='\n') return false;//换行，表达式结束
		if(strchr("+-*/",op)==NULL)//无效运算符
			throw string("无效运算符")+op;
		while(!ops.empty()&&ops.top()!='('&&!prior(op,ops.top())){//处理栈中优先级不低的运算符
			rh=ds.top();ds.pop();
			lh=ds.top();ds.pop();
			ds.push(cal(lh,ops.top(),rh));
			ops.pop();
		}
		ops.push(op);
		return true;
	}
	void calremain(){
		while(!ops.empty()){//处理栈里剩余的全部运算符
			rh=ds.top();ds.pop();
			lh=ds.top();ds.pop();
			ds.push(cal(lh,ops.top(),rh));
			ops.pop();
		}
		if(ds.size()!=1) throw string("无效的表达式");
		v = ds.top();//最后数据栈里唯一的数据就是结果
		ds.pop();
	}
	double cal(double lh, char op, double rh){//计算
		return op=='+'?lh+rh:op=='-'?lh-rh:op=='*'?lh*rh:lh/rh;
	}
	bool prior(char o1, char o2){//比优先级
		return o1!='+'&&o1!='-'&&o2!='*'&&o2!='/';
	}
};

int main()
{
	Exp e;
try{
	cout << e.calinput() << endl;
}catch(const string& e){
	cout << e << endl;
}
}

