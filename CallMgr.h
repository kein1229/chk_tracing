#pragma once
#include"common.h"

class CCall {

public:
	CCall(UINT c_ip, UINT c_lee, UINT c_ler, UINT c_nip, int n_line):
		  ip(c_ip),callee(c_lee),caller(c_ler),n_ip(c_nip), nLine(n_line) { ret = 0; }

	~CCall(void){};

public:
	
	UINT GetCallee(){ return this->callee; }
	UINT GetCaller(){ return this->caller; }
	UINT GetIp(){ return this->ip; }
	UINT GetNIp(){ return this->n_ip; }
	UINT GetRet(){ return this->ret; }
	int  GetLine(){	return this->nLine; }
	void SetRet(UINT c_ret){ this->ret = c_ret; }

private:
	UINT ip;
	UINT callee;
	UINT caller;
	UINT n_ip;
	UINT ret;
	int  nLine;
};


class CCallMgr {

public:
	CCallMgr(void){};
	~CCallMgr(void){};

public:
	CCall* InsertCall(UINT, UINT, UINT, UINT, int);

	void CheckMismatch();

private:
	vector<CCall*> list_call;
};

CCall* CCallMgr::InsertCall(UINT ip, UINT callee, UINT caller, UINT n_ip, int nLine) {

	CCall* pNew = new CCall(ip, callee, caller, n_ip, nLine);

	if(pNew) 	list_call.push_back(pNew);
	else  		return NULL;

	return pNew;
}

void CCallMgr::CheckMismatch() {

	if(list_call.empty())
		return;
	
	int nSize = list_call.size();
	for(int i = 0 ; i < nSize ; ++i) {

		CCall* pCall = list_call[i];
		if(pCall) {

			if(pCall->GetRet() == 0 && pCall->GetLine() != 1)
				vec_miss.push_back(pCall->GetLine());
		}
	}
}
