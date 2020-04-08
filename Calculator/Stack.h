#pragma once

// CStack ����Ŀ��

template<class T,int MAXSIZE> class CStack 
{
private:
	T stack[MAXSIZE];
	int Length;
public:
	CStack();
	virtual ~CStack();
	T peek();			//���ܣ��鿴ջ��Ԫ��
	void push(T ch);	//���ܣ���Ԫ��ѹջ
	T pop();			//���ܣ���ջ��Ԫ�ص�ջ
	bool isEmpty();		//���ܣ��ж�ջ�Ƿ�Ϊ��
	bool isFull();		//���ܣ��ж�ջ�Ƿ�����
	int size();			//���ܣ�����ջ��Ԫ�صĸ���
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




// CStack ��Ա����
