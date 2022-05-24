/*
You might find the code here using some undefined functions and keywords. It should all work seamlessly
if you add this code inside the 
namespace cp {}
block available in cptemplates/required-code/initializationTemplate.cpp
*/

//sparse table (explicitly inserted --> cp)
template <typename T>
class sparse_tb {
    //the sparse table uses 0 based indexing

private:
    vc<vc<T>> sparseTable;
    function<T(T, T)> merge;
    bool idempotency;
    int size, bin_size;

public:
    sparse_tb(int s, function<T(T, T)> m, bool id = false) {
        merge = m;
        size = s;
        idempotency = id;
        bin_size = blog(s) + 1;
        sparseTable.assign(bin_size, vc<T> (s));
    }
    sparse_tb(int s, vc<T>& seq, function<T(T, T)> m, bool id = false) {
        merge = m;
        size = s;
        idempotency = id;
        bin_size = blog(s) + 1;
        sparseTable.assign(bin_size, vc<T> (s));
        sparseTable[0].assign(seq.begin(), seq.end());
        for(int i = 1; i<bin_size; i++)
            for(int j = 0; j<size-i; j++)
                sparseTable[i][j] = merge(sparseTable[i-1][j], sparseTable[i-1][j+(1<<(i-1))]);
    }
    void accept() {
        for(T& i : sparseTable[0])
            cin>>i;
        for(int i = 1; i<bin_size; i++)
            for(int j = 0; j<size-i; j++)
                sparseTable[i][j] = merge(sparseTable[i-1][j], sparseTable[i-1][j+(1<<(i-1))]);
    }
    T query(int l, int r) {
        int k = blog(r-l+1), c = l;
        T res = T();
        if(idempotency)
            return merge(sparseTable[k][l], sparseTable[k][r-(1<<k)+1]);
        while(c<=r) {
            res = merge(res, sparseTable[k][c]);
            c+=(1<<k);
            k = blog(r-c+1);
        }
        return res;
    }
};
