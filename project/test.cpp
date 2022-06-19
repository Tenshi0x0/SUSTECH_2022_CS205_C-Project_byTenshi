#include<bits/stdc++.h>
#include "Matrix.h"
using namespace std;

#define rep(i,a,b) for(int i=(a);i<=(b);i++)

struct Mat{
    int n, m;
    vector<vector<int>> w;

    Mat(){}
    Mat(int _n, int _m){
        n=_n, m=_m;
        w.resize(n+1, vector<int>(m+1, 0));
    }

    
    void I(){
    	assert(n==m);
        rep(i,1,n) rep(j,1,n) w[i][j]=(i==j);
    }

    Mat operator * (const Mat &o)const{
        assert(m==o.n);
        Mat res(n, o.m);

        rep(i,1,n) rep(j,1,o.m){
            int &t=res.w[i][j];
            rep(k,1,o.n) (t+=w[i][k]*o.w[k][j]);
        }

        return res;
    }
    
    Mat operator + (const Mat &o)const{
        assert(m==o.m && n==o.n);
        Mat res(n, m);

        rep(i,1,n) rep(j,1,m){
            res.w[i][j]=w[i][j]+o.w[i][j];
        }

        return res;
    }

    Mat fpow(int p){
        Mat res(n, m);
        Mat x=*this;
        res.I();
        for(; p; p>>=1, x=x*x) if(p&1) res=res*x;
        return res;
    }
};

int main(){
    srand(time(0));
    // freopen("output.out", "w", stdout);

    clock_t startclk, endclk;

    // test: compare the cost of time in A * B and if it's correct
    if(1){
        std::cout<< "test: compare the cost of time in A * B and if it's correct" << std::endl;

        const int N=1000;
        Matrix<int> A(N, N), B(N, N);
        Mat A_(N, N), B_(N, N);
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(rand()%100==0){
            int val=rand()%100+1;
            A.insert(i, j, val);
            A_.w[i+1][j+1]=val;
        }
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(rand()%100==0){
            int val=rand()%100+1;
            B.insert(i, j, val);
            B_.w[i+1][j+1]=val; 
        }
        startclk=clock();
        A=A*B;
        endclk=clock();

        cout<<"cost "<<(endclk-startclk)/1000 <<" ms"<<endl;

        startclk=clock();
        A_=A_*B_;
        endclk=clock();

        cout<<"cost "<<(endclk-startclk)/1000 <<" ms"<<endl;

        bool match=true;
        auto A_get=A.getAll();
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) match&=(A_get[i][j]==A_.w[i+1][j+1]);
        puts(match? "YES": "NO");
        std::cout << std::endl;
    }

    // test: if it's corrects
    if(1){
        std::cout<< "test: if it's correct" << std::endl;
        bool ok=true;

        int T=10; // number of test cases
        while(T--){
            int N=rand()%50+1;
            Matrix<int> A(N, N), B(N, N);
            Mat A_(N, N), B_(N, N);

            for(int i=0; i<N; i++) for(int j=0; j<N; j++){
                int val=rand()%100+1;
                A.insert(i, j, val);
                A_.w[i+1][j+1]=val;
            }
            for(int i=0; i<N; i++) for(int j=0; j<N; j++){
                int val=rand()%100+1;
                B.insert(i, j, val);
                B_.w[i+1][j+1]=val; 
            }
            A=A*B;
            A_=A_*B_;
            auto A_get=A.getAll();
            for(int i=0; i<N; i++) for(int j=0; j<N; j++) ok&=(A_get[i][j]==A_.w[i+1][j+1]);
        }
        puts(ok? "OK": "NG");
        std::cout << std::endl;
    }

    // test: read the matrix by stdin (read tuple (row, column, value))
    if(0){
        std::cout<< "test: read the matrix by stdin (read tuple (row, column, value))" << std::endl;
        Matrix<int> A;
        // input size of Matrix A
        try{
            puts("Enter rows and columns:");
            int n, m; cin>>n>>m;
            A.resize(n, m);

            // input k data
            puts("Enter number of datas:");
            int k; cin>>k;
            for(int i=1; i<=k; i++){
                cout<<"Entering the "<<i<<" th data: ";
                int x, y, z; cin>>x>>y>>z;
                if(x>=n || y>=m) throw "input for the matrix out-of-bounds!";
                A.insert(x, y, z);
            }

            A.print();
            std::cout << std::endl;
        }
        catch(const char *e){
            cout<<e<<endl;
        }
    }

    // test: std::complex
    if(1){
        std::cout<< "test: std::complex" << std::endl;
        const int N=3;
        Matrix<complex<double>> A(N, N);
        A.insert(0, 0, {1.0, 1.0});
        A.insert(1, 2, {2.0, 3.0});
        puts("A:");
        A.print();

        Matrix<complex<double>> B(N, N);
        B.insert(0, 0, {1.0, 1.0});
        B.insert(1, 1, {2.0, 2.0});
        B.insert(2, 2, {3.0, 3.0});
        puts("B:");
        B.print();

        A=A*B;
        puts("result of A * B");
        A.print();
        std::cout << std::endl;
    }

    // test: get max, min, sum 
    if(1){
        std::cout<< "test: get max, min, sum" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        // 1 0 0
        // 0 4 2
        // 0 1 3

        cout<<"max: "<<A.get_max()<<endl;
        cout<<"min: "<<A.get_min()<<endl;
        cout<<"sum: "<<A.get_sum()<<endl;
        std::cout << std::endl;
    }

    // test: A + B
    if(1){
        std::cout<< "test: A + B" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 4 2
        // 0 1 3

        Matrix<int> B(N, N);
        B.insert(0, 1, 12);
        B.insert(1, 0, 1);
        B.insert(1, 1, 5);
        B.insert(2, 1, 6);
        B.sort();
        // 0 12 0
        // 1 5 0 
        // 0 6 0 
        
        A=A+B;
        A.print();
        std::cout << std::endl;
    }
    
    // test: compare the cost of time in A + B and if it's correct
    if(1){
        std::cout<< "test: compare the cost of time in A + B and if it's correct" << std::endl;
        const int N=5000;
        Matrix<int> A(N, N), B(N, N);
        Mat A_(N, N), B_(N, N);
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(rand()%500==0){
            int val=rand()%100+1;
            A.insert(i, j, val);
            A_.w[i+1][j+1]=val;
        }
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(rand()%500==0){
            int val=rand()%100+1;
            B.insert(i, j, val);
            B_.w[i+1][j+1]=val; 
        }
        startclk=clock();
        A=A+B;
        endclk=clock();

        cout<<"cost "<<(endclk-startclk)<<" ms"<<endl;

        startclk=clock();
        A_=A_+B_;
        endclk=clock();

        cout<<"cost "<<(endclk-startclk)<<" ms"<<endl;

        bool match=true;
        auto A_get=A.getAll();
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) match&=(A_get[i][j]==A_.w[i+1][j+1]);
        puts(match? "YES": "NO");
        std::cout << std::endl;
    }

    // test: A - B
    if(1){
        std::cout<< "test: A - B" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 4 2
        // 0 1 3

        Matrix<int> B(N, N);
        B.insert(0, 1, 12);
        B.insert(1, 0, 1);
        B.insert(1, 1, 5);
        B.insert(2, 1, 6);
        B.sort();
        // 0 12 0
        // 1 5 0 
        // 0 6 0 
        
        A=A-B;
        A.print();
        std::cout << std::endl;
    }

    // test: A * k
    if(1){
        std::cout<< "test: A * k" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 4 2
        // 0 1 3
        
        A=A*10;
        A.print();
        std::cout << std::endl;
    }

    // test: A / k
    if(1){
        std::cout<< "test: A / k" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 4 2
        // 0 1 3
        
        A=A/2;
        A.print();
        std::cout << std::endl;
    }

    // test: dot(A, B)
    if(1){
        std::cout<< "test: dot(A, B)" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 4 2
        // 0 1 3

        Matrix<int> B(N, N);
        B.insert(0, 1, 12);
        B.insert(1, 0, 1);
        B.insert(1, 1, 5);
        B.insert(2, 1, 6);
        B.sort();
        // 0 12 0
        // 1 5 0 
        // 0 6 0 
        
        A=A.dot(B);
        A.print();
        std::cout << std::endl;
    }

    // test: transposition
    if(1){
        std::cout<< "test: transposition" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 0, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 2 4 0
        // 0 1 3

        Matrix<int> res=A.transposition();
        res.print();
        std::cout << std::endl;
    }

    // test: Matrix A * vector B
    if(1){
        std::cout<< "test: Matrix A * vector B" << std::endl;
        const int N=3;
        Matrix<int> A(N, N);
        vector<int> B, res;
        A.insert(0, 0, 1);
        A.insert(1, 1, 2);
        A.insert(2, 2, 3);
        A.sort();
        // 1 0 0
        // 0 2 0
        // 0 0 3

        B={1, 2, 3};
        res=A*B;
        for(auto i: res) cout<<i<<' ';
        cout<<endl;

        A.O();
        A.insert(0, 0, 1);
        A.insert(1, 2, 1);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0
        // 0 0 1
        // 0 1 0

        B={1, 114, 514};
        res=A*B;
        for(auto i: res) cout<<i<<' ';
        cout<<endl;
        std::cout << std::endl;
    }

    // test: conjugation
    if(1){
        std::cout<< "test: conjugation" << std::endl;
        const int N=2;
        Matrix<complex<int>> A(N, N);
        A.insert(0, 0, {1, 1});
        A.insert(1, 0, {2, 3});
        A.insert(1, 1, {4, 7});
        A.sort();
        // (1,1) (0,0)
        // (2,3) (4,7)
        
        auto res=A.conjugation<int>();
        res.print();
        std::cout << std::endl;
    }

    // test reshape
    if(1){
        const int N=3, M=4;
        Matrix<int> A(N, M);
        A.insert(0, 0, 1);
        A.insert(0, 3, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0 1
        // 0 4 2 0
        // 0 1 3 0

        A=A.reshape(2, 6);
        A.print();
        std::cout << std::endl;
    }

    // test slicing
    if(1){
        std::cout<< "test: slicing" << std::endl;
        const int N=3, M=4;
        Matrix<int> A(N, M);
        A.insert(0, 0, 1);
        A.insert(0, 3, 1);
        A.insert(1, 2, 2);
        A.insert(1, 1, 4);
        A.insert(2, 2, 3);
        A.insert(2, 1, 1);
        A.sort();
        // 1 0 0 1
        // 0 4 2 0
        // 0 1 3 0

        A=A.slicing({1, 1}, {2, 3});
        A.print();
        std::cout << std::endl;
    }

    // test inv
    if(1){
        std::cout<< "test: inv" << std::endl;
        const int N=3, M=3;
        Matrix<double> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 1, 2);
        A.insert(2, 2, 3);
        A.sort();
        // 1 0 0
        // 0 2 0
        // 0 0 3

        auto B=A.get_inv();
        B.print();

        puts("============================");

        A.O();
        A.insert(0, 0, 8), A.insert(0, 1, 1), A.insert(0, 2, 4);
        A.insert(1, 0, 4), A.insert(1, 1, 6), A.insert(1, 2, 5);
        A.insert(2, 0, 2), A.insert(2, 1, 1), A.insert(2, 2, 3);
        A.sort();
        // [8, 1, 4],
        // [4, 6, 5],
        // [2, 1, 3]

        // output of numpy:
        // [[ 0.18571429  0.01428571 -0.27142857]
        // [-0.02857143  0.22857143 -0.34285714]
        // [-0.11428571 -0.08571429  0.62857143]]

        B=A.get_inv();
        B.print();

        puts("=================");

        A.O();
        A.insert(0, 0, 8), A.insert(0, 1, 1), A.insert(0, 2, 4);
        A.insert(1, 0, 4), A.insert(1, 1, 6), A.insert(1, 2, 5);
        A.insert(2, 0, 2), A.insert(2, 1, 1), A.insert(2, 2, 3);
        A.sort();
        // -1 1 
        // 1 -1

        B=A.get_inv();
        B.print();
        std::cout << std::endl;
    }

    // test det
    if(1){
        std::cout<< "test: det" << std::endl;
        const int N=3, M=3;
        Matrix<double> A(N, N);
        A.insert(0, 0, 1);
        A.insert(1, 1, 2);
        A.insert(2, 2, 3);
        A.sort();
        // 1 0 0
        // 0 2 0
        // 0 0 3

        auto res=A.get_det();
        printf("%lf\n", res);

        A.O();
        A.insert(0, 0, 8), A.insert(0, 1, 1), A.insert(0, 2, 4);
        A.insert(1, 0, 4), A.insert(1, 1, 6), A.insert(1, 2, 5);
        A.insert(2, 0, 2), A.insert(2, 1, 1), A.insert(2, 2, 3);
        A.sort();
        // [8, 1, 4],
        // [4, 6, 5],
        // [2, 1, 3]

        // output of numpy:
        // 69.99999999999996

        res=A.get_det();
        printf("%lf\n", res);

        A.O();
        A.insert(0, 0, 32), A.insert(0, 1, 54), A.insert(0, 2, 4);
        A.insert(1, 0, 4), A.insert(1, 1, 6), A.insert(1, 2, 55);
        A.insert(2, 0, 2), A.insert(2, 1, 45), A.insert(2, 2, 3);
        A.sort();
        // [32, 54, 4],
        // [4, 6, 55],
        // [2, 45, 3]

        // output of numpy:
        // -72660.00000000001

        res=A.get_det();
        printf("%lf\n", res);
        std::cout << std::endl;
    }

    //test conv
    if(1){
            std::cout<< "test: conv" << std::endl;
            Matrix<int> A(5, 5);
            A.insert(0, 0, 17);A.insert(0, 1, 24);A.insert(0, 2, 1);A.insert(0, 3, 8);A.insert(0, 4, 15);
            A.insert(1, 0, 23);A.insert(1, 1, 5);A.insert(1, 2, 7);A.insert(1, 3, 14);A.insert(1, 4, 16);
            A.insert(2, 0, 4);A.insert(2, 1, 6);A.insert(2, 2, 13);A.insert(2, 3, 20);A.insert(2, 4, 22);
            A.insert(3, 0, 10);A.insert(3, 1, 12);A.insert(3, 2, 19);A.insert(3, 3, 21);A.insert(3, 4, 3);
            A.insert(4, 0, 11);A.insert(4, 1, 18);A.insert(4, 2, 25);A.insert(4, 3, 2);A.insert(4, 4, 9);
            A.sort();
            //A.print();

            Matrix<int> B(3, 3);
            B.insert(0, 0, 1);B.insert(0, 1, 2);B.insert(0, 2, 1);
            B.insert(1, 0, 0);B.insert(1, 1, 2);B.insert(1, 2, 0);
            B.insert(2, 0, 3);B.insert(2, 1, 1);B.insert(2, 2, 3);
            B.sort();
            //B.print(); 
            Matrix<int> D(2, 2);
            D.insert(0, 0, 1);D.insert(0, 1, 2);
            D.insert(1, 0, 0);D.insert(1, 1, 2);
            
            // D.print();
             
            Matrix<int> C(6, 6);
            cout<< "CONV2(A,B)"<<endl;
            cout<< "-----full-----"<<endl;
            C = A.conv(A,B,"full");
            C.print();
            cout<< "-----same-----"<<endl;
            C = A.conv(A,B,"same");
            C.print();
            cout<< "-----vaild-----"<<endl;
            C = A.conv(A,B,"vaild");
            C.print();
            cout<< "-----full-----"<<endl;
            cout<< "CONV2(A,D)"<<endl;
            C = A.conv(A,D,"full");
            C.print();
            cout<< "-----same-----"<<endl;
            C = A.conv(A,D,"same");
            C.print();
            cout<< "-----vaild-----"<<endl;
            C = A.conv(A,D,"vaild");
            C.print();
            cout<< "----------"<<endl;
            std::cout << std::endl;
        }

    // test cvToMat
    if(1){
            std::cout<< "test test cvToMat" <<std::endl;
            cv::Mat m4 = (cv::Mat_ <int>(3, 3) << 1, 2, 3, 4, 4, 6, 7, 8, 9);
            Matrix<int> C(3,3); 
            C = C.cvToMat(m4);
            
            
            C.print();
            std::cout << std::endl;

        }

    // test matToCv
    if(1){
            std::cout<< "test matToCv" <<std::endl;
            Matrix<int> B(3, 3);
            B.insert(0, 0, 1);B.insert(0, 1, 2);B.insert(0, 2, 1);
            B.insert(1, 0, 0);B.insert(1, 1, 2);B.insert(1, 2, 0);
            B.insert(2, 0, 3);B.insert(2, 1, 1);B.insert(2, 2, 3);
            B.sort();
            cv::Mat mat1;
            mat1 = B.matToCv(B);
            std::cout<< mat1 <<std::endl;
            std::cout << std::endl;
        }



    // test 
    if(1){
        std::cout<< "test eigenValue and eigenVector" <<std::endl;
        Matrix<double> m(2,2);
        m.insert(0, 0, 2);m.insert(0, 1, 1);
        m.insert(1, 0, 1);m.insert(1, 1, 2);
        m.eigenValue();
        m.eigenVector();

    }

    return 0;
}