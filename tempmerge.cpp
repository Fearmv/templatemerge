
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//Defined class for less-than comparison
class Gum {
    int priority;
public:
    Gum(int priority);
    Gum();
    friend bool operator< (const Gum &l, const Gum &r);
    friend bool operator> (const Gum &l, const Gum &r);
};

Gum::Gum(){
    priority = 0;
}

Gum::Gum(int p){
    priority = p;
}

//less than comparison
bool operator< (const Gum &left, const Gum &right)
{
    return left.priority < right.priority;
}

//greater than comparison
bool operator> (const Gum &left, const Gum &right) {
    return left.priority > right.priority;
}

template <class T>
void merge(vector<T> & a, vector<T> & x, int s, int e, int m){
    int i = s , j = m + 1;
    
    while(i <= m and j <= e){
        if (x[i] < x[j])
        {
            a[s] = x[i];
            s++;
            i++;
        }
        else
        {
            a[s] = x[j];
            s++;
            j++;
        }
    }
    
    while(i <= m){
        a[s] = x[i];
        s++;
        i++;
    }
    
    while(j <= e){
        a[s] = x[j];
        s++;
        j++;
        
        
        for(; i <= e ; i++){
            x[i - s] = a[i];
        }
    }
}


template <class T>
void msort(vector<T> & a, vector<T> & x, int s, int e) {
    if (s >= e){
        return;
    }
    int m = (e + s)/2;
    msort(a, x, s, m);
    msort(a, x, m + 1, e);
    merge(a, x, s, e, m);
}

template<class T>
void merge_sort(vector<T> & v) {
    int n = v.size();
    vector<T> x(n);
    msort(v, x, 0, n - 1);
}

template <class T>
bool sorted(vector<T> & a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        if (a[i] > a[i + 1]){
            return false;
        }
    }
    return true;
}

int main(int argc, char * args[]) {
    vector<int> a(1000);
    
    for (int i = 0; i < 1000; ++i) a[i] = -50 + rand() % 100;
    merge_sort(a);
    assert(sorted(a));
    
    vector<int> b(1001);
    for (int i = 0; i < 1001; ++i) b[i] = -50 + rand() % 100;
    merge_sort(b);
    assert(sorted(b));
    
    vector<int> c(1, 2);
    merge_sort(c);
    assert(sorted(c));
    
    
    vector<int> d (5);
    for (int i = 1; i <= d.size(); i++) d[i] = i;
    merge_sort(d);
    assert(sorted(d));
    
    vector<Gum> e(5);
    
    for (int i = 8; i >= 0; i--) {
        Gum doc(i);
        e[i] = doc;
    }
    merge_sort(e);
    assert(sorted(e));
    
    cout << "All tests passed." << endl;
}
