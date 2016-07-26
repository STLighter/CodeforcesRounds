#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
class st_trie {
private:
    // �ֵ����ڵ�
    struct TrieNode {
        // ��ʾ�Ƿ�Ϊ��β
        bool isEnd;
        // �洢��һλ�ĽǱ�, -1��ʾ��ʱ��û�нڵ�. ���������ĸֻ��26λСд��ĸ
        int next[26];

        // ��ʼ��
        TrieNode() {
            isEnd = false;
            memset(next,-1,sizeof(next));
        }
    };
    // �������ڵ�, nodes[0]Ϊ���ڵ�. ֱ�Ӳ�������洢, ��Ϊ��ɾ���������鲻���п�λ
    TrieNode *nodes;
    // ���ÿռ�
    int _size;
    // �������
    int _cap;
    // ����
    void resize(int new_cap) {
        TrieNode *tmp = new TrieNode[new_cap];
        memcpy(tmp, nodes, _cap*sizeof(TrieNode));
        delete[] nodes;
        nodes = tmp;
        _cap = new_cap;
    }
    // �����ַ���s, ��ǰ�ѵ��ڵ�nodes[c], s[sp]����һ���ַ�
    void _insert(const string &s, int sp, int c) {
        if(sp == s.length()) {
            // �����ַ�����β, ����Ǳ�Ϊtrue��ʾһ���ʽ�β
            nodes[c].isEnd = true;
            return;
        }
        // ���Ǵ�β��Ѱ�ұ�ʾ��һ���ַ��Ľڵ�
        int next = nodes[c].next[s[sp]-'a'];
        if(next == -1) {
            // �ڵ㻹������
            if(_size == _cap) // �����������������һ��
                resize(_cap*2);
            // �����µĽڵ�
            next = nodes[c].next[s[sp]-'a'] = _size++;
        }
        // �ݹ����, ������һ���ַ�
        _insert(s, sp+1, next);
    }
    // ��ѯ�ַ���, ���������������ͬ
    bool _find(const string &s, int sp, int c) {
        // ��ѯ����β, �����ǰ����Ϊ��β��˵���ֵ����������, ����û��
        if(sp == s.length())
            return nodes[c].isEnd;
        // ��ȡ��һ����ĸ�ڵ�
        int next = nodes[c].next[s[sp]-'a'];
        if(next == -1) // ��һ���ڵ㲻����, �������һ�������ֵ���
            return false;
        // ��ѯ��һ����ĸ
        _find(s, sp+1, next);
    }
public:

    st_trie() {
        // ��ʼ��nodes����
        nodes = new TrieNode[_cap = 16];
        // _sizeΪ1��Ϊ��һ�����ڵ�
        _size = 1;
    }
    ~st_trie() {
        // ��������ռ�õ��ڴ�
        delete[] nodes;
    }
    void insert(const string &s) {
        if(!s.length())
            return;
        _insert(s, 0, 0);
    }
    bool find(const string &s) {
        if(!s.length())
            return false;
        _find(s, 0, 0);
    }
};
class st_queue {
private:
    // ����
    int _size;
    // ����ͷ
    int _start;
    // ����β
    int _end;
    // ���г���
    int _len;
    // ��Ŷ��е�����(ѭ������)
    int *_arr;

    // ����������, �����������ݿ�����������
    void resize(int new_size) {
        int *tmparr = new int[new_size];
        // ��ԭ����Ӷ���ͷ�������β��λ�ø��ƽ�������Ŀ�ʼλ��
        memcpy(tmparr, _arr + _start, sizeof(int)*(_size - _start));
        // ��ԭ���������ͷ������β��λ�üӽ�������
        memcpy(tmparr + _size - _start, _arr, sizeof(int)*_end);
        delete[] _arr;
        _arr = tmparr;
        _size = new_size;
        // ����ͷ��β���¶�λ
        _start = 0;
        _end = _len;
    }

public:
    st_queue() {
        _start = 0;
        _end = 0;
        _len = 0;
        _size = 2;
        _arr = new int[2];
    }
    ~st_queue() {
        delete[] _arr;
    }
    void push(int v) {
        if(_len==_size) {
            // ��������������
            resize(_size*2);
        }
        // �ӵ�����β
        _arr[_end++] = v;
        // ���¶�βλ��
        _end %= _size;
        // ���¶��г���
        ++_len;
    }
    int pop() {
        if(_len==0)
            throw "error";
        // �Ӷ���ȡ��
        int ret = _arr[_start];
        // ���¶���λ��
        _start = (_start + 1) % _size;
        // ���¶��г���
        --_len;
        return ret;
    }
    bool isEmpty() {
        return (_len==0);
    }
    int size() {
        return _len;
    }
};

class st_stack {
private:
    // �������
    int _size;
    // ʵ�ʴ�С
    int len;
    // �洢���ݵ�����
    int *arr;

    // ���·���ռ�, �Ա���������
    void resize(int new_size) {
        int *tmparr = new int[new_size];
        memcpy(tmparr, arr, _size*sizeof(int));
        delete[] arr;
        arr = tmparr;
        _size = new_size;
    }
public:
    // ��ʼ��ջ�������ʹ�С
    st_stack() {
        len = 0;
        _size = 2;
        arr = new int[2];
    }
    // �ͷ�arrռ�õ��ڴ�
    ~st_stack() {
        delete[] arr;
    }
    void push(int v) {
        if(len==_size) {
            // �����������, ����һ��
            resize(_size*2);
        }
        // �����ݼӵ�����β��
        arr[len++] = v;
    }
    int pop() {
        // ������β��ȡ������
        if(len==0)
            throw "error";
        return arr[--len];
    }
    // ����ջ��С
    int size() {
        return len;
    }

    // ջ�Ƿ�Ϊ��
    bool isEmpty() {
        return (len==0);
    }
};

int main() {
    st_trie trie;
    string ar[] = {"afgfg","afgfgf","dcfdgsfg","dffgasdfa","ffg","rtbrf","dbfg"};
    string ar2[] = {"afgffg","ghgfggdf","dcfdgsdgfg","dffgasdfa","ffg","rtbrf","dbfg"};
    for(int i=0;i<7;++i)
        trie.insert(ar[i]);
    for(int i=0;i<7;++i)
        printf("%d\n",trie.find(ar[i]));
    for(int i=0;i<7;++i)
        printf("%d\n",trie.find(ar2[i]));
}
