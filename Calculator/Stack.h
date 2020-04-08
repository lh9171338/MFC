#pragma once

// CStack 命令目标

template<class T,int MAXSIZE> class CStack 
{
private:
	T stack[MAXSIZE];
	int Length;
public:
	CStack();
	virtual ~CStack();
	T peek();			//功能：查看栈顶元素
	void push(T ch);	//功能：将元素压栈
	T pop();			//功能：将栈顶元素弹栈
	bool isEmpty();		//功能：判断栈是否为空
	bool isFull();		//功能：判断栈是否满了
	int size();			//功能：返回栈内元素的个数
};

// CStack

template<class T,int MAXSIZE>
CStack<T,MAXSIZE>::CStack()
{
	Length=0;
}

template<class T,int MAXSIZE>
CStack<T,MAXSIZE>::~CStack()
{

}

template<class T,int MAXSIZE>
T CStack<T,MAXSIZE>::peek()
{
	return Length>0?stack[Length-1]:NULL;
}

template<class T,int MAXSIZE>
void CStack<T,MAXSIZE>::push(T ch)
{
	if(Length==MAXSIZE)
		return ;
	stack[Length]=ch;
	Length++;
}

template<class T,int MAXSIZE>
T CStack<T,MAXSIZE>::pop()
{
	T e = NULL;
	if(Length>0)
	{
		e = stack[Length-1];
		Length--;
	}
	return e;
}

template<class T,int MAXSIZE>
bool CStack<T,MAXSIZE>::isEmpty()
{
	return Length == 0 ;
}

template<class T,int MAXSIZE>
bool CStack<T,MAXSIZE>::isFull()
{
	return Length == MAXSIZE;
}

template<class T,int MAXSIZE>
int CStack<T,MAXSIZE>::size()
{
	return Length;
}




// CStack 成员函数
