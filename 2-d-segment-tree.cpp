#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int> > mat;
vector<vector<int> > st;
int left(int p) { return p << 1; }
int right(int p) { return (p << 1) + 1; }

void updateY(int px, int lx, int rx, int py, int ly, int ry, int i, int j, int v) {
    if (ly == ry) {
        st[px][py] = (lx == rx) ? v : st[left(px)][py] + st[right(px)][py];
        return;
    }
    int mid = (ly + ry) >> 1;
    if (j <= mid) updateY(px, lx, rx, left(py), ly, mid, i, j, v);
    else updateY(px, lx, rx, right(py), mid+1, ry, i, j, v);
    st[px][py] = st[px][left(py)] + st[px][right(py)];
}

void updateX(int px, int lx, int rx, int i, int j, int v) {
    if (lx == rx) {
        updateY(px, lx, rx, 1, 0, N-1, i, j, v);
        return;
    }
    int mid = (lx + rx) >> 1;
    if (i <= mid) updateX(left(px), lx, mid, i, j, v);
    else updateX(right(px), mid+1, rx, i, j, v);
    updateY(px, lx, rx, 1, 0, N-1, i, j, v);
}

int querySumY(int px, int py, int ly, int ry, int k, int l) {
    if (k == ly && l == ry) return st[px][py];

    int mid = (ly + ry) >> 1;
    if (l <= mid) return querySumY(px, left(py), ly, mid, k, l);
    if (k > mid) return querySumY(px, right(py), mid+1, ry, k, l);

    return querySumY(px, left(py), ly, mid, k, mid) + querySumY(px, right(py), mid+1, ry, mid+1, l);
}

int querySumX(int px, int lx, int rx, int i, int j, int k, int l) {
    if (i == lx && j == rx) return querySumY(px, 1, 0, N-1, k, l);
    int mid = (lx + rx) >> 1;
    if (j <= mid) return querySumX(left(px), lx, mid, i, j, k, l);
    if (i > mid) return querySumX(right(px), mid+1, rx, i, j, k, l);

    return querySumX(left(px), lx, mid, i, mid, k, l) + querySumX(right(px), mid+1, rx, mid+1, j, k, l);
}

int main(int argc,char* argv[])
{
    int cur=0;
    if(argc==2)
        cur=atoi(argv[1]);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    int ks=1;
    cin>>t;
    /***
     for outfile ******/
    ofstream myfile;
    //myfile.open ("results.txt",ios::trunc);
    //myfile.close();
    myfile.open("results.txt",ios::app);
    myfile<<"\n\n\t\t\t\t\t   #"<<cur<<"\n"; 
    while(t--)
    {  
        myfile<<"\nCase:"<<ks<<"\n";
        cin>>N;
        string cmd="";
      
        mat.clear();
        st.clear();
        mat.resize(N,vector<int>(N,0));
        st.resize(2*N+1,vector<int>(2*N+1,0));
        while(cmd!="END")
        {
            cin>>cmd;
            if(cmd=="SET")
            {
                int x,y,num;
                cin>>x>>y>>num;
                updateX(1, 0, N-1, x, y, num);
            }
            else if(cmd=="SUM")
            {
                int x1,y1,x2,y2;
                cin>>x1>>y1>>x2>>y2;
                int res=0;
                res=querySumX(1, 0, N-1, x1, x2, y1, y2);
                //cout<<res<<endl;
                myfile<<res<<"\n";
            }
            
        }
        ks++;
    }
    myfile.close();
    return 0;
}