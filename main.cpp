#include"common.h"
#include"CallMgr.h"

vector<CCall*> CallStack;
int nLine=1;

void search_mismatch_ret_stack(UINT ret) {

	if(CallStack.empty()) 	return;

 	int nSize = CallStack.size()-1;
	while(nSize >= 0) {

		CCall* pCall= CallStack[nSize];
		if(pCall) {

			if(pCall->GetNIp() == ret && pCall->GetRet()== 0) {
				pCall->SetRet(ret);;
				CallStack.pop_back();
				return;
			}
		}
		--nSize;
	}

	vec_miss.push_back(nLine);
}

void FileRead(ifstream& fin, CCallMgr& c_mgr) {

	while(!fin.eof()) {

		char cType;
		fin >> cType;

		switch(cType)
		{
		case eTYPE_CALL:
			{
				UINT callee, ip, n_ip;
				UINT caller;
				string str;

				fin >> hex >> ip >> callee >> n_ip;
				fin >> str;

				if(!CallStack.empty()) {

					CCall* pCall = CallStack.back();
					if(pCall)
						caller = pCall->GetCallee();
				}

				CCall* pNew = c_mgr.InsertCall(ip, callee, caller, n_ip, nLine);
				if(pNew)
					CallStack.push_back(pNew);
			}
			break;
		case eTYPE_RET:
			{
				UINT ip,ret, retValue;
				fin >> hex >> ip >> ret >> retValue;

				search_mismatch_ret_stack(ret);
			}
			break;
		case eTYPE_FRM:
		case eTYPE_ADD:
		case eTYPE_STK:
		case eTYPE_MEM:
		case eTYPE_SUB:
		case eTYPE_PUSH:
			{
				char buf[100]={0,};
				fin.getline(buf,100);
			}
			break;
		}
		nLine++;
	}
}

void recreate_log(char* pstr, ifstream& fin) {

	int cnt=0;
	char tmp[100]={0,};

	sprintf(tmp,"%s_rmv.out",pstr);
	FILE* pf = fopen(tmp,"w");
	if(!pf) {
		printf("File open failed : %s\n", tmp);
		return;
	}

	fin.clear();
	fin.seekg(0, ios::beg);

	while(!fin.eof()) {

		fin.getline(tmp,100);
		cnt++;

		vector<int>::iterator it = find(vec_miss.begin(), vec_miss.end(), cnt);
		if(it == vec_miss.end())
			fprintf(pf,"%s\n",tmp);
	}

	fclose(pf);
}

int main(int argc, char* argv[])
{
	ifstream fin;

	char buf[256]={0,};
	sprintf(buf,"%s.out",argv[1]);

	fin.open(buf);
	if(!fin.is_open()) {

		printf("File Open Failed\n");
		return 0;
	}

	CCallMgr c_mgr;
	FileRead(fin,c_mgr);
	c_mgr.CheckMismatch();

	recreate_log(argv[1], fin);

	fin.close();

	return 0;
}
