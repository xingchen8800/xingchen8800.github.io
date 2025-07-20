//order存储子树内容，treeStack存储被回收的节点
ll order[N], cnt = 0;
ll treeStack[N], top = 0;
void InOrder(ll u) {
    if(!u) return;      //到叶子节点
    InOrder(t[u].ls);   //递归左子节点
    if(!t[u].del) order[++cnt] = u; //记录子树内容
    else treeStack[++top] = u;      //回收被删除的节点
    InOrder(t[u].rs);   //递归右子节点
}