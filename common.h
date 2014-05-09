#pragma once
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<list>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef unsigned int UINT;

typedef enum {
	eTYPE_CALL='C',
	eTYPE_STK='S',
	eTYPE_PUSH='P',
	eTYPE_MEM='M',
	eTYPE_RET='R',
	eTYPE_FRM='F',
	eTYPE_ADD='A',
	eTYPE_SUB='s'
}eTYPE;

typedef enum {
	eCNT_CALL = 0,
	eCNT_RET,
	eCNT_PUSH,
	eCNT_STK,
	eCNT_MEM,
	eCNT_FRM,
	eCNT_ADD,
	eCNT_SUB,
}eCNT;

using namespace std;

vector<int> vec_miss;
