// a O(n) complexity method
int hval(const vector<int> H) {  
    deque<int>q;  
    q.push_back(0);  
    int hval = 0;  
    for (auto i : H) {  
  
        if (hval == 0 && i > 0)hval = 1;  
        else if(q.size()>0 &&  (q.size()>=hval) && (q.front()>hval)&&((i>q.back())||(i>hval)))  
            ++hval;   
  
        while (!q.empty() && q.front() <= hval)  
            q.pop_front();  
        if (q.empty() || i > q.back())  
            q.push_back(i);  
        else q.push_front(i);  
        while (q.size() > hval)  
            q.pop_front();  
    }  
    return hval;  
}  
