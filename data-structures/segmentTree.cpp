/*
You might find the code here using some undefined functions and keywords. It should all work seamlessly
if you add this code inside the 
namespace cp {}
block available in cptemplates/required-code/initializationTemplate.cpp
*/

//segment tree (explicitly inserted --> cp)
template <typename T>
class seg_tree {
    //the segment tree uses 1 based indexing
    //this segment tree uses a pre-ordering storage format for maximising efficiency

private:
    int size;
    function<T(T, T)> merge;
    vc<T> ST;
    
public:
    seg_tree(int s, vc<T>& seq, function<T(T, T)> m) {
        size = s;
        ST.resize(s<<1);
        merge = m;
        construct(1, 1, s, seq);
    }
    seg_tree(int s, function<T(T, T)> m) {
        size = s;
        ST.resize(s<<1);
        merge = m;
    }
    void accept() {
        vc<T> seq(size);
        for(auto& i : seq)
            cin>>i;
        construct(1, 1, size, seq);
    }
    void construct(int pos, int il, int ir, vc<T>& seq) {
        if(il>size)
            return;
        if(il==ir) {
            ST[pos] = seq[il-1];
            return;
        }
        int mid = (il+ir)>>1, lc = pos + 1, rc = pos + ((mid-il+1)<<1);
        construct(lc, il, mid, seq);
        construct(rc, mid+1, ir, seq);
        ST[pos] = rc<=(size<<1)?merge(ST[lc], ST[rc]):ST[lc];
    }
    void update(int pos, T new_val, int at = 1, int il = 1, int ir = -1) {
        if(ir==-1)
            ir = size;
        if(il>size)
            return;
        if(il==ir) {
            ST[at] = new_val;
            return;
        }
        int mid = (il+ir)>>1, lc = at + 1, rc = at + ((mid-il+1)<<1);
        if(pos<=mid)
            update(pos, new_val, lc, il, mid);
        else
            update(pos, new_val, rc, mid+1, ir);
        ST[at] = rc<=(size<<1)?merge(ST[lc], ST[rc]):ST[lc];
    }
    T fetch(int rl, int rr, int pos = 1, int il = 1, int ir = -1) {
        if(ir==-1)
            ir = size;
        if(il==ir or (il==rl and ir==rr))
            return ST[pos];
        int mid = (il+ir)>>1, lc = pos + 1, rc = pos + ((mid-il+1)<<1);
        if(rr<=mid)
            return fetch(rl, rr, lc, il, mid);
        if(rl>mid)
            return fetch(rl, rr, rc, mid+1, ir);
        return merge(fetch(rl, mid, lc, il, mid), fetch(mid+1, rr, rc, mid+1, ir));
    }
};
