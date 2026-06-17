#pragma once
#include <vector>
#include <string> 
using namespace std;
int read(string& a,vector<string>& set,char ch=' ') {
	int pos = a.size();
	pos = a.find(ch);

	// Extract substring after pos
	string sub = a.substr(0,pos);
	vector<int> sets;
	for (int i = 0; i < set.size(); i++) {
		if (set[i].size() == sub.size()) {
			sets.push_back({ i });
		}
	}
	if (sets.size() == 0) return -1;
	for (int s : sets) {
		for (int i = 0; i < sub.size();i++) {
			if (set[s][i] != sub[i]) goto skip;
		}
		if(a.size()!=pos){
			a=a.substr(pos+1,a.size()-pos);
		}
		else {
			a = "";
		}
		return s;
	skip:;
	}
	return -1;
}

short chartoint(char a) {
	switch (a)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default:
		break;
		return -1;
	}
}

int getint(string& a, char ch = ' ') {
	int pos = a.size();
	pos = a.find(ch);
	int value=0;
	string sub = a.substr(0, pos);
	for (int i = 0; i < sub.size(); i++) {
		if (sub[i] >= '0' and sub[i]<='9'){
		value *= 10;
		value+=chartoint(sub[i]);
		}
		else {
			return -1;
		}
	}
	if (a.size() != pos) {
		a = a.substr(pos + 1, a.size() - pos - 1);
	}
	else {
		a = "";
	}
	return value;
}