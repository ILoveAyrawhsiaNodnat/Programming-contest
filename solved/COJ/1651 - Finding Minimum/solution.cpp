/**
 *  Implementation of RMQ using Splay trees.
 *  Sadly is not fast enough for this problem
 * */

using namespace std;
#include<bits/stdc++.h>
#define D(x) cout<<#x " = "<<(x)<<endl;


typedef int T;

struct node{
  node *left, *right, *parent;
  T key, value, ans;
  node (T k, T v) : key(k), value(v) , ans(v), left(0), right(0), parent(0) {}
};

struct splay_tree{

  node *root;

  void update(node *x) {
    if (!x) return;
    x->ans = x->value;
    if (x->right) x->ans = min(x->ans, x->right->ans);
    if (x->left) x->ans = min(x->ans, x->left->ans);
  }

  void right_rot(node *x) {
    node *p = x->parent;
    if (x->parent = p->parent) {
      if (x->parent->left == p) x->parent->left = x;
      if (x->parent->right == p) x->parent->right = x;
    }
    if (p->left = x->right) p->left->parent = p;
    x->right = p;
    p->parent = x;

    update(x->left);update(x->right); update(x);
  }

  void left_rot(node *x) {
    node *p = x->parent;
    if (x->parent = p->parent) {
      if (x->parent->left == p) x->parent->left = x;
      if (x->parent->right == p) x->parent->right = x;
    }
    if (p->right = x->left) p->right->parent = p;
    x->left = p;
    p->parent = x;
    update(x->left);update(x->right); update(x);
  }

  void splay(node *x, node *fa = 0) {

    while( x->parent != fa and x->parent != 0) {
      node *p = x->parent;
      if (p->parent == fa)
        if (p->right == x)
          left_rot(x);
        else
          right_rot(x);
      else {
        node *gp = p->parent;
        if (gp->left == p)
          if (p->left == x)
            right_rot(x),right_rot(x);
          else
            left_rot(x),right_rot(x);
        else
          if (p->left == x)
            right_rot(x), left_rot(x);
          else
            left_rot(x), left_rot(x);
      }
    }

    update(x);
    if (fa == 0) root = x;
    else update(fa);
  }

  void insert(T key, T val) {
    node *cur = root;
    node *pcur = 0;
    while (cur) {
      pcur = cur;
      if (key > cur->key) cur = cur->right;
      else cur = cur->left;
    }
    cur = new node(key, val);
    cur->parent = pcur;
    if (!pcur) root = cur;
    else if (key > pcur->key ) pcur->right = cur;
    else pcur->left = cur;
    splay(cur);
  }

  node *find(T key) {
    node *cur = root;
    while (cur) {
      if (key > cur->key) cur = cur->right;
      else if(key < cur->key) cur = cur->left;
      else return cur;
    }
    return 0;
  }

  T power(T a, T b) {
    node *begin = find(a - 1);
    node *end   = find(b + 1);
    splay(end, root), splay(begin, end);
    return begin->right->ans;
  }

  splay_tree(){ root = 0;};
};


const int inf = 1<<30;

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);


  splay_tree tree;
  int n;cin>>n;
  tree.insert(-1, inf);
  for (int i = 0; i < n; ++i) {
    int t;cin>>t;
    tree.insert(i,t);
  }
  tree.insert(n, inf);
  int q;cin>>q;
  int a,b;
  while (q--) {
    cin>>a>>b;
    a--;b--;
    if (a > b)
      swap(a,b);
    cout<<tree.power(a,b)<<endl;
  }
  return 0;
}