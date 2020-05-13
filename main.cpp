#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <typeinfo>
#include<bits/stdc++.h>
using namespace std;
ifstream f ("input.txt");
ifstream g ("input_orientat");



template<class T>
class Matrice {
protected:
    int count=0;
public:
    int mat[100][100];
    int n; //noduri
    Matrice(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat[i][j]=0;
        }
    }
    }
    ~Matrice(){
    delete mat;
    }

};

template <class T>
class vect
{
    T a[100];
    int n;
public:
    vect(int* v, int n){
    for(int i=0;i<n;i++)
        v[i]=0;
    }
    ~vect(){
    n=0;
    }
    vect(const vect& old){
    for (int i=0; i<old.n; i++)
        a.push_back(old.a[i]);
    }
    void citire()
    {
        cin>>n;
        for(int i = 0; i<n; i++)
            cin>>a[i];
    }
    void afisare()
    {
        for(int i = 0; i <n; i++)
            cout<<a[i]<<" ";
        cout<<endl;
    }
};

template <class T>
class Lista {
protected:

    int n;
public:
    T lis[100];
    Lista(){
    n=0;
    }
    ~Lista(){}
};




class Graf{
protected:
    int n;//nr de noduri
    int t[100];
    int r[100][100];
public:
    Graf(){};
    virtual ~Graf() { };
    virtual void addEdge(int u, int v){};


};
template <class T>
class Graf_Neorientat : public Graf{

public:
    Lista<vector<float>> L;

    void addEdge(int u,T v)
{
    L.lis[u].push_back(v);
}

friend void operator>>(istream& input, Graf_Neorientat& A)
{
    input>>A.n;
    T x,y;
    while(input){
        input>>x;
        input>>y;
        A.addEdge(x,y);
    }
}
friend void operator<<(ostream& output, Graf_Neorientat A){
    for (int v = 0; v < A.n; ++v)
    {
        cout << "\n Lista adiacenta a nodului "
             << v << "\n nod ";
        for (auto x : A.L.lis[v])
           cout << "-> " << x;
        printf("\n");
    }
}


};

class Graf_Orientat : public Graf{
public:
    Matrice<int> M;

    void addEdge(int u, int v)
{
    M.mat[v][u]=1; ///
}

    friend void operator>>(istream& input, Graf_Orientat& A)
    {
	input >> A.n;

	int x,y;
	while(input){
        input>>x;
        input>>y;
        A.addEdge(x,y);
	}

}
friend void operator<<(ostream& output, Graf_Orientat A){
   int i, j;
   cout<<"\n";
   cout<<"Matricea de adiacenta este: "<<endl;
   for(i = 0; i < A.n; i++) {
      for(j = 0; j < A.n; j++) {
         cout << A.M.mat[i][j] << " ";
      }
      cout << endl;
   }
}

void vectorDeTati(int x,int y) {
    int k;
    k=x;
    int p;
    cout<<"vector de tati: ";
    while(k!=y){
        for(p=0;p<5;p++){
            if(M.mat[k][p]==1){
                cout<<p<<" ";
                k=p;
                break;
            }
        }
    }
}

int isConnection(int x, int y) const {
    int k;
    k=x;
    int p;
    while(k!=y){
        for(p=0;p<5;p++){
            if(M.mat[k][p]==1){
                k=p;
                break;
            }
        }
        if(p>4 && k!=p){
            return 0;
        }
    }
    return 1;
}
};

void whatType(Graf &ob){
cout<<"Obiectul verificat este "<<typeid(ob).name()<<endl;
}


int main(){

    Graf_Neorientat<float> ob;
    f>>ob;
    cout<<ob;
    Graf_Orientat ob2;
    g>>ob2;
    cout<<ob2;
    Graf_Orientat ob3(ob2);
    cout<<ob3;
    whatType(ob2);
    if(ob2.isConnection(3,0)==1){
    ob2.vectorDeTati(3,0);}
    cout<<endl;
    vector<Graf*> vectorGraf[10];
    int p=0;
    for(int i=2;i<5;i++){
        string file_name= "input" + to_string(i) + ".txt";
        ifstream x(file_name);
        if(i%2==0){
            Graf_Orientat obiect;
            x>>obiect;
            vectorGraf[i].push_back(&obiect);
        }
        else{
            Graf_Neorientat<int> obiect;
            x>>obiect;
            vectorGraf[i].push_back(&obiect);
        }
        x.close();

    }
    for(int i =2;i<sizeof(vectorGraf);i++)
{
    //whatType(vectorGraf[i]);
}
    f.close();
    g.close();
    return 0;
}
