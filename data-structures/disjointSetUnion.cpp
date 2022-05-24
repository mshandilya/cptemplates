/*
You might find the code here using some undefined functions and keywords. It should all work seamlessly
if you add this code inside the 
namespace cp {}
block available in cptemplates/required-code/initializationTemplate.cpp
*/

//disjoint set union (explicitly inserted --> cp)
class dsu {
    //the dsu uses 0 based indexing
    //this dsu uses path-optimization and performs union by size for maximum efficiency
    
private:
    vi parent, size;

public:
    explicit dsu(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for(int i = 0; i<n; i++)
            parent[i] = i;
    }
    void make_set() {
        parent.push_back((int)parent.size());
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a==b)
            return;
        if(size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
    int find_set(int v) {
        if(parent[v]==v)
            return v;
        return parent[v] = find_set(parent[v]);
    }
};
