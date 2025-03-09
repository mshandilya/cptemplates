//lazy segment tree (explicitly inserted --> cp)
template <typename T>
class lazy_tree {
    //the segment tree uses 1 based indexing
    //this segment tree uses a pre-ordering storage format for maximising efficiency

private:
    int size;
    T def;
    function<T(T, T)> merge, lazy_update, val_update;
    function<T(int, int, T, T)> rval_update;
    vc<T> ST, lazy;

public:
    lazy_tree(int s, vc<T>& seq, function<T(T, T)> m, T d, function<T(T, T)> lu = [](T a, T b){return a;}, function<T(T, T)> vu = [](T a, T b){return a;}, function<T(int, int, T, T)> ru = [](int x, int y, T a, T b){return a;}) {
        size = s;
        def = d;
        ST.resize(s<<1);
        lazy.assign(s<<1, def);
        merge = m;
        lazy_update = lu;
        val_update = vu;
        rval_update = ru;
        construct(1, 1, s, seq);
    }
    lazy_tree(int s, function<T(T, T)> m, T d, function<T(T, T)> lu = [](T a, T b){return a;}, function<T(T, T)> vu = [](T a, T b){return a;}, function<T(int, int, T, T)> ru = [](int x, int y, T a, T b){return a;}) {
        size = s;
        def = d;
        ST.resize(s<<1);
        lazy.assign(s<<1, def);
        merge = m;
        lazy_update = lu;
        val_update = vu;
        rval_update = ru;
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
        ST[pos] = rc<(size<<1)?merge(ST[lc], ST[rc]):ST[lc];
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
        if(lc<(size<<1))
            lazy[lc] = lazy_update(lazy[lc], lazy[at]);
        if(rc<(size<<1))
            lazy[rc] = lazy_update(lazy[rc], lazy[at]);
        ST[at] = rval_update(il, ir, ST[at], lazy[at]);
        lazy[at] = def;
        if(pos<=mid)
            update(pos, new_val, lc, il, mid);
        else
            update(pos, new_val, rc, mid+1, ir);
        ST[at] = rc<(size<<1)?merge(rval_update(il, mid, ST[lc], lazy[lc]), rval_update(mid+1, ir, ST[rc], lazy[rc])):rval_update(il, mid, ST[lc], lazy[lc]);
    }
    void range_update(int rl, int rr, T new_val, int at = 1, int il = 1, int ir = -1) {
        if(ir==-1)
            ir = size;
        if(il>size)
            return;
        if(il==ir) {
            ST[at] = val_update(new_val, ST[at]);
            return;
        }
        if(il==rl and ir==rr) {
            lazy[at] = lazy_update(lazy[at], new_val);
            return;
        }
        int mid = (il+ir)>>1, lc = at + 1, rc = at + ((mid-il+1)<<1);
        if(lc<(size<<1))
            lazy[lc] = lazy_update(lazy[lc], lazy[at]);
        if(rc<(size<<1))
            lazy[rc] = lazy_update(lazy[rc], lazy[at]);
        ST[at] = rval_update(il, ir, ST[at], lazy[at]);
        ST[at] = rval_update(rl, rr, ST[at], lazy_update(new_val, def));
        lazy[at] = def;
        if(rr<=mid)
            return range_update(rl, rr, new_val, lc, il, mid);
        if(rl>mid)
            return range_update(rl, rr, new_val, rc, mid+1, ir);
        range_update(rl, mid, new_val, lc, il, mid);
        range_update(mid+1, rr, new_val, rc, mid+1, ir);
    }
    T fetch(int rl, int rr, int pos = 1, int il = 1, int ir = -1) {
        if(ir==-1)
            ir = size;
        if(il==ir) {
            ST[pos] = rval_update(il, ir, ST[pos], lazy[pos]);
            lazy[pos] = def;
            return ST[pos];
        }
        int mid = (il+ir)>>1, lc = pos + 1, rc = pos + ((mid-il+1)<<1);
        if(lc<(size<<1))
            lazy[lc] = lazy_update(lazy[lc], lazy[pos]);
        if(rc<(size<<1))
            lazy[rc] = lazy_update(lazy[rc], lazy[pos]);
        ST[pos] = rval_update(il, ir, ST[pos], lazy[pos]);
        lazy[pos] = def;
        if(il==rl and ir==rr)
            return ST[pos];
        if(rr<=mid)
            return fetch(rl, rr, lc, il, mid);
        if(rl>mid)
            return fetch(rl, rr, rc, mid+1, ir);
        return merge(fetch(rl, mid, lc, il, mid), fetch(mid+1, rr, rc, mid+1, ir));
    }
};