#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
ll buildSumTree(ll arr[], ll *segment_tree, ll arr_start, ll arr_end, ll segment_index){
    if(arr_start == arr_end){
        segment_tree[segment_index] = arr[arr_end];
        return segment_tree[segment_index];
    }
 
    ll  mid = arr_start + (arr_end - arr_start)/2;
 
    segment_tree[segment_index] = buildSumTree(arr, segment_tree, arr_start, mid, segment_index*2+1)+
        buildSumTree(arr, segment_tree, mid+1, arr_end, segment_index*2+2);
    return segment_tree[segment_index];
}

void updateSegmentSumQuery(ll *segment_tree, ll segment_left, ll segment_right, ll index, ll diff, ll curr_index){
    
    if (index < segment_left || index > segment_right)  
        return;

    segment_tree[curr_index] = segment_tree[curr_index] + diff;
    if (segment_left != segment_right)  
    {
        ll mid = segment_left+(segment_right-segment_left)/2;
        updateSegmentSumQuery(segment_tree, segment_left, mid, index, diff, 2*curr_index + 1);
        updateSegmentSumQuery(segment_tree, mid+1, segment_right, index, diff, 2*curr_index + 2);
    }
}

ll sumSegmentQuery(ll *segment_tree, ll lindex, ll rindex, ll segment_left, ll segment_right, ll curr_index){
    if( lindex <= segment_left && rindex >= segment_right ){
        return segment_tree[curr_index];
    }
    if( lindex > segment_right || rindex < segment_left){
        return 0;
    }
    ll mid = segment_left+(segment_right-segment_left)/2;
    return sumSegmentQuery(segment_tree, lindex, rindex, segment_left, mid, curr_index*2+1)+
            sumSegmentQuery(segment_tree, lindex, rindex, mid+1, segment_right, curr_index*2+2);
}
 
void RangeSum(ll arr[], ll n){
    ll x = ceil(log2(n));
    ll segment_tree_size = 2*pow(2, x) - 1;
    cout<<segment_tree_size<<endl;
    ll *segment_tree = new ll[segment_tree_size];
 
    buildSumTree(arr, segment_tree, 0, n-1, 0);

    cout<<"Enter No of Queries:\n"<<endl;
    int q;
    cin>>q;
    while(q--){
        int type;
        cout<<"Update query-> \"1\"\nSum Query -> \"2\""<<endl;
        cout<<"Enter type of query"<<endl;
        cin>>type;
        if(type == 1){
            ll value, index;
            cout<<"Enter value & index"<<endl;
            cin>>value>>index;
            
            if (index < 0 || index > n-1)  
            {  
                cout<<"Invalid Input";
                return;  
            }  
        
            //difference between new value and old value  
            int diff = value - arr[index];  
        
            // Update that index
            arr[index] = value;
            updateSegmentSumQuery(segment_tree,0,n-1,index,diff,0);
        }
        else{
            ll lindex, rindex;
            cout<<"Enter left index & right index"<<endl;
            cin>>lindex>>rindex;
            cout<<sumSegmentQuery(segment_tree, lindex, rindex, 0, n-1, 0)<<endl;
        }
    }

 
}
void RangeMin(ll arr[], ll n){

}
void RangeMax(ll arr[], ll n){

}
int main(){
 
    ll t;
    cout<<"**********1-D Segment Tree Implementation**************"<<endl;
    ll n;
    cout<<"Enter no of elements in array:"<<endl;
    cin>>n;
    ll arr[10000];
    cout<<"Enter Array Elements:"<<endl;
    for(ll i=0;i<n;i++){
        cin>>arr[i];
    }
    int ch;
    cout<<"Enter choice which type of segment tree you want:\n";
    cout<<"1. Range Sum\n2. Range Minimum\n3. Range Maximum\n";
    cin>>ch;
    switch(ch){
        case 1: RangeSum(arr, n);
            break;
        case 2: RangeMin(arr, n);
            break;
        case 3: RangeMax(arr, n);
            break;
        default: cout<<"Invalid Choice"<<endl;
    }
    return 0;
}