#include <iostream>
#include <cstdlib> //for malloc

using namespace std;

class hmm{
     public:

         const int numofblocks;
         int blocksize;
         friend class data;
         class data;
         data* builddat;
         int count;
         hmm(int n): numofblocks(n){
             cout << "hmm() : allocate memory" << endl;
             count = 0;
             blocksize = 2;
             void* const heapmem = malloc(numofblocks*sizeof(data));
             cout <<"numofblocks :" << numofblocks << endl << "size of data: " << sizeof(data) << endl << "total size :" << numofblocks*sizeof(data) <<endl;
             //create blocks
             for(int y =0; y < numofblocks; y++){
                 data* d = new( ((data*)heapmem + (y*sizeof(data)) + 1) ) data;
                 if (0 != y){
                     d->prev = builddat;
                     builddat->next = d;
                 }
                 builddat = d;                 
             }
         }
         data* allocblock(){
             cout << "allocblock() :" << endl;
             data* datptr;
             if(count != numofblocks){
                count++;
                datptr = builddat;
                builddat = builddat->prev;
                cout << "allocated block add: " << datptr << endl;
             }
             else{
                datptr = NULL;
                cout << "Opps no space..Start praying for more!!"<< endl;
             }
             return datptr;
         }
         void deallocblock(data* d){
                cout << "deallocblock()" <<endl;
                if(count != numofblocks){
                    builddat->next = d;
                    d->prev = builddat;
                }
                else{
                    d->prev=NULL;
                }
                builddat = d;

                memset(builddat->i,0,blocksize);         
         }
         class data{
             public:
                 int i[2];//blocksize = 2
                 data* prev;
                 data* next;
                 data(){
                     cout << "data() :intialise block with 0" << endl;
                     memset(i,0,2);//blocksize = 2
                     next = prev = NULL;
                 }
         };
         
};

int main(){
int numofblocks = 4;

hmm::data* dat[4];
hmm hmem(numofblocks);
cout << "hmem in stack? :" << &hmem << endl;
for(int x =0; x< (numofblocks); x++){
    dat[x] = hmem.allocblock();
    dat[x]->i[0] = x;
    cout << "allocblock number :" << x << "  address :"<< dat[x] << endl;
    }
//see the opps message?
hmem.allocblock();
for(int x =0; x< (numofblocks); x++){
    cout << "deallocblock number :" << x << "  address :"<< dat[x] << "  data1: " << dat[x]->i[0] << "  data2: " << dat[x]->i[1] << endl;
    hmem.deallocblock(dat[x]);
    }
return 0;
}

