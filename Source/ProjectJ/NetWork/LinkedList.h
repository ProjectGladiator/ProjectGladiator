#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Global.h"

//노드---------------------------------------------------------------------------------------------------------------------------------------
template <typename Type>
class cNode																	//클래스 노드
{
private:
	Type  Data;																//노드에 저장된 데이터
	cNode<Type> * Link;														//노드가 가리키는 다음노드
public:
	cNode() { memset(&Data, 0, sizeof(Data)), Link = nullptr; }				//기본 생성자
	cNode(Type _Data) { Data = _Data, Link = nullptr; }						//저장될 데이터를 받는 생성자
	~cNode() {}																//소멸자

	void SetData(Type _Data) { Data = _Data; }
	Type  GetData() { return Data; }										//노드에 저장된 데이터 반환
	cNode<Type> * GetLink() { return Link; }								//노드가 가리키는 다음노드 반환
	void SetNextLink(cNode<Type>*_Link) { Link = _Link; }					//노드가 가리키는 다음노드 셋팅
};
//-----------------------------------------------------------------------------------------------------------------------------------------


//포인터 타입 데이터 노드----------------------------------------------------------------------------------------------------------------------
template <typename Type>													
class cNode<Type*>															//포인터 타입 완전 특수화 노드
{
private:
	Type*  Data;															//노드에 저장된 포인터타입 데이터
	cNode<Type*> * Link;													//노드가 가리키는 다음노드
public:
	cNode() { memset(&Data, 0, sizeof(Data)), Link = nullptr; }				//기본 생성자	
	cNode(Type* _Data) { Data = _Data, Link = nullptr; }					//저장될 데이터를 받는 생성자
	~cNode() { if(Data != NULL) delete Data; }												//포인터타입 데이터일 경우 delete로 동적 할당된 메모리 반환

	void SetData(Type* _Data) { Data = _Data; }
	Type*  GetData() { return Data; }										//노드에 저장된 포인터타입 데이터 반환
	cNode<Type*> * GetLink() { return Link; }								//노드가 가리키는 다음노드 반환
	void SetNextLink(cNode<Type*>*_Link) { Link = _Link; }					//노드가 가리키는 다음노드 셋팅
};


//-----------------------------------------------------------------------------------------------------------------------------------------


//연결리스트---------------------------------------------------------------------------------------------------------------------------------
template <typename Type>
class cLinkedList															//연결리스트 클래스
{
private:
	cNode<Type> * Headp;													//연결 리스트의 헤드 포인터
	cNode<Type> * Tailp;													//연결 리스트의 꼬리 포인터
	int Listnum;															//연결 리스트의 저장된 노드 갯수
public:
	cLinkedList();															//기본생성자
	~cLinkedList();															//기본 소멸자

	cNode<Type> * GetHead() { return Headp; }								//연결 리스트의 헤드 포인터 반환
	cNode<Type> * GetTail() { return Tailp; }								//연결 리스트의 꼬리 포인터 반환
	int GetListnum() { return Listnum; }									//연결 리스트의 저장된 노드 갯수 반환


	bool Insert(Type);														//연결 리스트에 노드 삽입
	bool Except(Type);														//연결리스트에서 데이터 제외
	bool Delete(Type);														//연결 리스트에 노드 삭제
	void ExceptAll();														//모든 데이터 제외
	void DeleteAll();
};

template <typename Type>
cLinkedList<Type>::cLinkedList()											//생성자
{
	Headp = new cNode<Type>;												//헤트포인터 동적 할당
	Tailp = Headp;															//연결리스트 처음 생성지 꼬리 == 헤드
	Listnum = 0;															//연결리스트 저장된 노드 갯수 0

}

template <typename Type>													
cLinkedList<Type>::~cLinkedList()											//소멸자
{
	cNode<Type> * Deletep = Headp;											//Deletep에 헤드 포인터 대입
	for (int i = 0; i <= Listnum; i++)										//
	{
		Headp = Headp->GetLink();											//헤드포인터를 다음 링크로 변경
		delete Deletep;														//Deletep 삭제
		Deletep = Headp;													//Deletep 다시 헤드포인터 대입
	}

}

template <typename Type>
bool cLinkedList<Type>::Insert(Type  _Data)									//연결리스트에 노드 삽입
{
	cNode<Type> * Empt = new cNode<Type>(_Data);							//데이터를 저장할 노드를 생성후
	Tailp->SetNextLink(Empt);												//꼬리노드 다음 링크에 생성된 노드 삽입
	Tailp = Empt;															//꼬리노드를 생성된 노드로 설정
	Listnum++;																//연결리스트의 노드갯수 ++
	return true;															//노드 생성 완료 함수 종료
}

template <typename Type>
bool cLinkedList<Type>::Delete(Type  _Data)									//연결리스트에 노드 삭제
{
	cNode<Type> * Connectp = Headp;											//삭제하기 전 노드, 삭제할 노드 다음링크를 연결해줄 노드
	cNode<Type> * Deletep = Connectp->GetLink();							//삭제할 노드
	bool flag = false;
	for (int i = 0; i < Listnum; i++)										//노드갯수만큼 반복 
	{
		if (Deletep->GetData() == _Data)									//삭제할 데이터를 탐색
		{
			flag = true;													//데이터를 찾은경우
			Connectp->SetNextLink(Deletep->GetLink());						//Connectp의 다음노드를 Deletep의 다음노드로 설정
			if (Deletep == Tailp)											//꼬리노드일경우 
			{
				Tailp = Connectp;											//꼬리노드를 Connectp로 설정
			}
			delete Deletep;													//Deletep 삭제
			Listnum--;														//연결리스트의 노드갯수 --
			return flag;													//노드 삭제 완료 함수 종료									
			break;
		}																	//데이터 탐색 실패시
		Connectp = Deletep;													//Connectp를 Deletep로
		Deletep = Deletep->GetLink();										//Deletep를 Deletep 다음 노드로 설정						
	}

	return flag;															//노드 삭제 실패 함수 종료 

}


template <typename Type>
bool cLinkedList<Type>::Except(Type  _Data)									//연결리스트에 노드 삭제
{
	cNode<Type> * Connectp = Headp;											//삭제하기 전 노드, 삭제할 노드 다음링크를 연결해줄 노드
	cNode<Type> * Deletep = Connectp->GetLink();							//삭제할 노드
	bool flag = false;
	for (int i = 0; i < Listnum; i++)										//노드갯수만큼 반복 
	{
		if (Deletep->GetData() == _Data)									//삭제할 데이터를 탐색
		{
			flag = true;													//데이터를 찾은경우
			Connectp->SetNextLink(Deletep->GetLink());						//Connectp의 다음노드를 Deletep의 다음노드로 설정
			if (Deletep == Tailp)											//꼬리노드일경우 
			{
				Tailp = Connectp;											//꼬리노드를 Connectp로 설정
			}
			Deletep->SetData(NULL);
			delete Deletep;													//Deletep 삭제
			Listnum--;														//연결리스트의 노드갯수 --
			return flag;													//노드 삭제 완료 함수 종료									
			break;
		}																	//데이터 탐색 실패시
		Connectp = Deletep;													//Connectp를 Deletep로
		Deletep = Deletep->GetLink();										//Deletep를 Deletep 다음 노드로 설정						
	}

	return flag;															//노드 삭제 실패 함수 종료 

}

template <typename Type>
void cLinkedList<Type>::ExceptAll()// 연결 리스트 초기화
{
	cNode<Type> * Connectp = Headp;										
	cNode<Type> * Deletep = Connectp->GetLink();					
	for (int i = 0; i < Listnum; i++)									
	{
		Connectp->SetNextLink(Deletep->GetLink());				
		if (Deletep == Tailp)										
		{
			Tailp = Connectp;										
		}
		Deletep->SetData(NULL);
		delete Deletep;																		
	}
	Listnum = 0;
}

template <typename Type>
void cLinkedList<Type>::DeleteAll()// 연결 리스트 초기화
{
	cNode<Type> * Connectp = Headp;
	cNode<Type> * Deletep = Connectp->GetLink();
	for (int i = 0; i < Listnum; i++)
	{
		Connectp->SetNextLink(Deletep->GetLink());
		if (Deletep == Tailp)
		{
			Tailp = Connectp;
		}
		delete Deletep;
	}
	Listnum = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

#endif // !LINKEDLIST_H
