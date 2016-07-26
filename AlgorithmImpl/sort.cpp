#include<cstdio>
#include<vector>
using namespace std;
void merge_sort(vector<int> &v) {
    // �ݹ���ֹ����, ������һ��Ԫ��, ��������, ֱ�ӷ���
    if(v.size()<=1)
        return;
    int l = v.size();
    int half = l/2;
    // �������Ϊ����
    vector<int> left(v.begin(),v.begin() + half);
    vector<int> right(v.begin() + half, v.end());

    // �ݹ�, �����ηֱ�����
    merge_sort(left);
    merge_sort(right);

    // �ϲ�����, ������������ֵ�໥�Ƚ�, ����С��ֵ����ԭ������
    for(int i=0,j=0,k=0;i<left.size()||j<right.size();) {
        // ��������ζ��Ž���ԭ����, ��ֱ�ӷ��Ҳ������
       if(i==left.size())
        v[k++] = right[j++];
        // �Ҳ������ζ��Ž���ԭ����, ��ֱ�ӷ���������
       else if(j==right.size())
        v[k++] = left[i++];
        // ��������ֵС
       else if(left[i]<right[j])
        v[k++] = left[i++];
        // �Ҳ������ֵС
       else
        v[k++] = right[j++];
    }
}
void _qsort(vector<int> &v, int st, int end) {
    // Ԫ����������, ֱ�ӷ���
    if(end - st < 2)
        return;
    // ��v[st]ѡΪpivot, small_end��ʾһ������, v[st+1]��v[small_end](����v[small_end])��������v[st], ��v[small_end+1]֮�󶼴���v[st]
    int small_end = st, pv = v[st], tmp;
    for(int i=st+1;i<end;++i) {
        if(v[i] <= pv) {
            // v[i]ҲС��pivot��ֵ, ��Ҫ��v[i]�ŵ�small_end֮��
            ++small_end;
            if(small_end!=i) {
                // small_end֮��������ǵ�ǰλ��i, ��һ����һ������pivot��ֵ, ��ֱ�Ӻ�v[i]����
                tmp = v[i];
                v[i] = v[small_end];
                v[small_end] = tmp;
            }
        }
    }
    if(small_end!=st) {
        // �����������ֵ������pivot, ��pivot����ȷλ�ò���st����small_end.
        v[st] = v[small_end];
        v[small_end] = pv;
    }
    // �ֱ�ݹ�����
    _qsort(v, st, small_end);
    _qsort(v, small_end+1, end);
}
void quick_sort(vector<int> &v) {
    _qsort(v, 0, v.size());
}

class Heap {
private:
    // �ڲ�������洢, ģ�������, ���ڵ�����Ϊ0, ���ڵ�����Ϊidʱ, �������id*2+1, �Ҷ�����id*2+2, ���ڵ���(id-1)/2
    vector<int> arr;
public:
    // �����µĽڵ�
    void push(int v) {
        int p = arr.size(), q, tmp;
        // ����ֵ��������β��
        arr.push_back(v);

        // ��β����ʼά��С��������, �Ӽ���λ�ÿ�ʼ���, ������ڵ�ϴ�ͽ���������ά�����ڵ�. p�ǵ�ǰ�ڵ�����, q�Ǹ��ڵ�����
        while(p!=0&&arr[p]<arr[(q = (p-1)/2)]) {
            tmp = arr[p];
            arr[p] = arr[q];
            arr[q] = tmp;
            p = q;
        }
    }
    int pop() {
        // û��ֵ����pop();
        if(!arr.size()) {
            throw "error";
        }
        // ��ret�洢���ڵ�(�Ѷ�)��ֵ, Ҳ����Ҫ���ص�ֵ
        int ret = arr[0], p=0, q, tmp, l;
        // ���������һ��Ԫ�ص�ֵ�ŵ����ڵ�, ���Ƴ����һ��Ԫ��, �ȼ��ڽ������Ƴ����ڵ��ֵ
        arr[0] = arr[arr.size()-1];
        arr.pop_back();
        l = arr.size();

        // �Ӷ�����ʼά���ѵ�����.
        while(1) {
            // �ҵ���ǰ�ڵ������������н�Сֵ�ĽǱ�
            if(p*2+1 < l && arr[p]>arr[p*2+1]) {
                q = p*2+1;
            } else {
                q = p;
            }
            if(p*2+2 < l && arr[q]>arr[p*2+2]) {
                q = p*2+2;
            }

            if(q!=p) {
                // ���һ�����ӵ�ֵ��С, ����Ҫ����, ������ά������
                tmp = arr[p];
                arr[p] = arr[q];
                arr[q] = tmp;
                p = q;
            } else {
                // ��ǰ�ڵ���С, ���Ѿ�����С��������
                break;
            }
        }
        return ret;
    }
    void clear() {
        arr.clear();
    }
};
void heap_sort(vector<int> &v) {
    Heap heap;
    int l = v.size();
    // �����, c++11�﷨
    for(auto i: v) {
        heap.push(i);
    }
    // �Ӷ�������ȡ��
    for(int i=0;i<l;++i) {
        v[i] = heap.pop();
    }
}

void insert_sort(vector<int> &v) {
	int l = v.size();
	int tmp;
	// ��������ö��i, v[0]��v[i-1]�Ѿ����򵫲�������˳��, ÿ�ν�v[i]��������ʵ�λ��
	for(int i=1;i<l;++i) {
        // ��ʼv[i] = v[j]
		for(int j=i;j>0;--j) {
		    // ��v[j]��ǰ���ֵ�Ƚ�
			if(v[j]<v[j-1]) {
			    // ���v[j]�Ƚ�С, ����ǰ���ֵ����
				tmp = v[j];
				v[j] = v[j-1];
				v[j-1] = tmp;
			} else {
			    // ����������Ѿ���֤��v[0]��v[i]����
			    break;
			}
		}
	}
}

void bubble_sort(vector<int> &v) {
    int l = v.size();
    int tmp;
    bool flag;
    // ��������ö��i, v[i+1]��v[l-1]�Ѿ�������������˳��, ÿ��ѭ������v[0]��v[i]�����ֵ����v[i]
    for(int i=l-1;i>0;--i) {
        // ��v[0]��ʼ�����Ƚ�, ��������ŵ��Ҳ�, ��������Ȼ����������v[i]
        flag = false;   // ���˴�ѭ���Ƿ񽻻���, ���û�����������������Ѿ�����
        for(int j=0;j<i;++j) {
            // �����Ƚ�
            if(v[j]>v[j+1]) {
                // ���ϴ��򽻻�, ʹ�ñ����Ҳ�ϴ�
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
                flag = true;
            }
        }
        if(!flag)
            break;  //û�з�������, �����Ѿ�����, ֱ���˳�
    }
}

int main() {
    vector<int> arr = {
        123,35,235,784,234,68,45,6,3,236,2,125,64366,1283,12454,1,579
    };
	merge_sort(arr);
	for(auto i : arr) {
        printf("%d\n", i);
	}
}
