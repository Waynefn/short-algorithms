#include"stdafx.h"
#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;
struct TreeNode {
	char data;int weight;
	bool isEnd;
	TreeNode* lChild;
	TreeNode* rChild;
	TreeNode(char d,int w) {
		this->data = d;this->weight = w;
		this->isEnd = true;
		this->lChild = this->rChild = nullptr;
	}
};
struct CmpByValue{
	bool operator()(const pair<char, int>& lhs, const pair<char, int>& rhs){
		return lhs.second > rhs.second;
	}
	bool operator()(const TreeNode* lhs, const TreeNode* rhs) {
		return lhs->weight>rhs->weight;
	}
};
/*get frequency of string str*/
auto frequency(string str) {
	map<char, int> frq;
	for (auto c : str) 
		++frq[c];
	vector<pair<char, int>>frq_vec(frq.begin(), frq.end());
	sort(frq_vec.begin(), frq_vec.end(),CmpByValue());
	return frq_vec;
}
/*create huffman tree*/
auto creatTree(vector<pair<char, int>> &frq) {
	priority_queue<TreeNode*, vector<TreeNode*>, CmpByValue> q;
	while (!frq.empty()) {
		TreeNode*newNode = new TreeNode{ frq.back().first, frq.back().second };
		q.push(newNode);frq.pop_back();
	}
	while (q.size() >= 2) {
		auto h1 = q.top(); q.pop();
		auto h2 = q.top(); q.pop();
		TreeNode*n = new TreeNode{ ' ',h1->weight + h2->weight };
		n->lChild = h1; n->rChild = h2;
		n->isEnd = false;
		q.push(n);
	}
	return q.top();
}
void bfs(TreeNode* t,string code="") {
	if (t == nullptr)return;
	if (t->isEnd)
		cout <<"\'" <<t->data <<"\'["<<t->weight  <<"]:" << code << endl;
	bfs(t->lChild, code + "0");
	bfs(t->rChild, code + "1");
}
void deleteTree(TreeNode* t) {
	if (t == nullptr)return;
	deleteTree(t->lChild);
	deleteTree(t->rChild);
	delete t;
}
int main(){
	auto frq = frequency("aaaaaeeiiitttttttouzuu");
	auto huff = creatTree(frq);
	bfs(huff);
	deleteTree(huff);
}


