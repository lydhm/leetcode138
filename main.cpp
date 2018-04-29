#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
    RandomListNode(){}
};

RandomListNode* build(const vector<int>& label, const vector<int>& random, int n)
{
    assert(label.size() == random.size() && label.size() == n);
    //vector<RandomListNode>* pool = new vector<RandomListNode>(n);
    auto pool = new vector<RandomListNode>(n);
    RandomListNode* head = &(*pool)[0];
    RandomListNode* last = head;

    for(int i = 0;i < label.size() - 1;i++) {
        last->label = label[i];
        last->random = head + random[i];
        last->next = last + 1;
        last++;
    }
    last->label = label.back();
    last->random = head + random.back();
    last->next = nullptr;
    return head;
}

void printlist(RandomListNode* head)
{
    auto cur = head;
    while(cur->next)
    {
        cout<<cur->label<<"->";
        cur = cur->next;
    }
    cout<<cur->label<<endl;
    cur = head;
    while(cur->next)
    {
        cout<<cur->random->label<<"->";
        cur = cur->next;
    }
    cout<<cur->random->label<<endl;
}

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return nullptr;
        RandomListNode* cur = head;
        RandomListNode* res = nullptr;

        while(cur)
        {
            RandomListNode* nextone = cur->next;
            RandomListNode* newone = new RandomListNode(cur->label);
            cur->next = newone;
            newone->next = nextone;
            cur = nextone;
        }

        cur = head;
        while(cur)
        {
            RandomListNode* newlistnode = cur->next;
            RandomListNode* nextone = newlistnode->next;
            if(cur->random) newlistnode->random = cur->random->next;
            cur = nextone;
        }

        cur = head;
        res = head->next;
        RandomListNode* newlast = nullptr;
        while(cur)
        {
            RandomListNode* newnow = cur->next;
            RandomListNode* oldnext = newnow->next;
            if(newlast) newlast->next = newnow;
            newlast = newnow;
            cur->next = oldnext;
            cur = oldnext;
        }
        return res;
    }
};

int main()
{
    vector<int> labels = {1,2,3};
    vector<int> randoms = {0,2,1};
    RandomListNode* head = build(labels,randoms,labels.size());
    printlist(head);
    RandomListNode* copyhead = Solution().copyRandomList(head);
    printlist(copyhead);
    return 0;
}