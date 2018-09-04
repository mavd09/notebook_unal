/// Complexity: O(|N|*log|N|)
/// Tested: Not yet
struct treap {
  struct node {
    int prior, size;
    ii val, mn;
    bool rev;
    node *l, *r;
    node () {}
    node (int val, int idx) : l(0), r(0), rev(false),
      val(val, idx), mn(val, idx) {
      prior = rand();
      size = 1;
    }
  };
  typedef node *pnode;
  pnode head;
  treap () : head(0) {}
  int size (pnode t) {
    return t ? t->size : 0;
  }
  ii get_val (pnode t) {
    return t ? t->val : ii(INT_MAX, -1);
  }
  ii get_mn (pnode t) {
    return t ? t->mn : ii(INT_MAX, -1);
  }
  void update (pnode t) {
    if (t) {
      t->size = 1 + size(t->l) + size(t->r);
      t->mn = min(t->val, min(get_mn(t->l), get_mn(t->r)));
    }
  }
  void propagate (pnode it) {
    if (it && it->rev) {
      it->rev = false;
      swap(it->l, it->r);
      if (it->l) it->l->rev ^= true;
      if (it->r) it->r->rev ^= true;
    }
  }
  void merge (pnode &t, pnode l, pnode r) {
    propagate(l);
    propagate(r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l),  t = r;
    update(t);
  }
  void split (pnode t, pnode &l, pnode &r, int key, int add = 0) {
    if (!t) return void(l = r = 0);
    propagate(t);
    int cur_key = add + size(t->l);
    if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
    else split(t->r, t->r, r, key, add + 1 + size(t->l)), l = t;
    update(t);
  }
  int get_mn_idx (pnode t, ii val) {
    propagate(t);
    if (get_val(t) == val) return size(t->l);
    if (get_mn(t->l) == val) return get_mn_idx(t->l, val);
    return 1 + size(t->l) + get_mn_idx(t->r, val);
  }
  int get_mn_idx (int l, int r, ii val) {
    pnode t1, t2, t3;
    split(head, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    int idx = get_mn_idx(t2, val) + size(t1);
    merge(head, t1, t2);
    merge(head, head, t3);
    return idx;
  }
  void insert (int pos, int val) {
    pnode t1, t2, tmp = new node(val, pos);
    split(head, t1, t2, pos);
    merge(t1, t1, tmp);
    merge(head, t1, t2);
  }
  void erase (pnode &t, int pos, int add = 0) {
    int cur_key = add + size(t->l);
    if (cur_key == pos) merge (t, t->l, t->r);
    else {
      if (pos < cur_key) erase(t->l, pos, add);
      else erase(t->r, pos, add + 1 + size(t->l));
    }
    update(t);
  }
  void erase (int pos) {
    erase(head, pos);
  }
  void reverse (int l, int r) {
    pnode t1, t2, t3;
    split(head, t1, t2, l);
    split(t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge(head, t1, t2);
    merge(head, head, t3);
  }
  ii get_mn (int l, int r) {
    pnode t1, t2, t3;
    split(head, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    ii tmp = t2->mn;
    merge(head, t1, t2);
    merge(head, head, t3);
    return tmp;
  }
  vector<int> final_array;
  void build (pnode t) {
    if (!t)  return;
    propagate(t);
    build(t->l);
    final_array.push_back(t->val.first);
    build(t->r);
  }
  void build () {
    final_array.clear();
    build(head);
  }
};
