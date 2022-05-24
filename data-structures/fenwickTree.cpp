/*
You might find the code here using some undefined functions and keywords. It should all work seamlessly
if you add this code inside the 
namespace cp {}
block available in cptemplates/required-code/initializationTemplate.cpp
*/

//fenwick tree (explicitly inserted --> cp)
template <typename seqT, typename retT>
class BIT {
    //the fenwick tree uses 1 based indexing
    /* please take special care of the following while using this live template
     * -> the BIT is designed for reversible functions but irreversible functions can be used with some modifications;
     *    however ensuring that the updates for such a BIT are valid is the responsibility of the user.
     * -> the types seqT and retT are generally the same, unless, in some case it is possible to store individual elements
     *    in a less memory consuming type (seqT) which can implicitly be caste to retT.
     */
    
private:
    int size;
    vc<seqT> sequence;
    vc<retT> fenTree;
    function<retT(retT, retT)> op, rev_op;
    seqT d;

public:
    BIT(int n, vc<seqT>& seq, seqT def, function<retT(retT, retT)> up, function<retT(retT, retT)> rev) {
        size = n;
        d = def;
        sequence = seq;
        fenTree.assign(size, d);
        op = up;
        rev_op = rev;
        construct();
    }
    BIT(int n, vc<seqT>& seq, seqT def, function<retT(retT, retT)> up) {
        size = n;
        d = def;
        sequence = seq;
        fenTree.assign(size, d);
        op = up;
        construct();
    }
    void construct() {
        for(int i = 0, pos = 1; i<size; i++, pos = i+1)
            while(pos<=size) {
                fenTree[pos-1] = op(fenTree[pos-1], sequence[i]);
                pos += pos&(-pos);
            }
    }
    void update(int pos, seqT updValue) {
        int ind = pos-1;
        while(pos<=size) {
            fenTree[pos-1] = rev_op(op(fenTree[pos-1], updValue), sequence[ind]);
            pos += pos&(-pos);
        }
        sequence[ind] = updValue;
    }
    retT query(int pos) {
        retT res = d;
        while(pos>0) {
            res = op(res, fenTree[pos-1]);
            pos -= pos&(-pos);
        }
        return res;
    }
    retT query(int from, int to) {
        return rev_op(query(to), query(from-1));
    }
};
