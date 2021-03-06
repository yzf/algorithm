#include <cstdio>
#include <iostream>

using namespace std;

char  ha[ 1 << 24 ]; // hash[i]=得到状态i所用的操作
int  a[] = { 1 , 2 , 3 , 4 , 5, 6, 7, 8 } ; // 初始状态
const int QLen = 10000 ; // 队列长度
int  q[QLen], b = 0, e = 0 ; // 循环队列及首、尾指针 

inline  int  A( int  n) 
{ 
	return (((63 << 12) & n) << 6 | ((63 & n) << 6)) | (((63 << 18) & n) >> 6 | (((63 << 6) & n) >> 6));  
} 

inline  int  B( int  n) 
{ 
    return  ((7 | 7 << 12) & n ) << 9 | (~(7 | 7 << 12) & n) >> 3 ;
}

inline  int  C( int  n) 
{ 
    return  ( 7 | 7 << 9 | 7 << 12 | 7 << 21 ) & n  |  (( 7 << 3 ) & n) << 12   |  (( 7 << 6 ) & n) >> 3   |  (( 7 << 18 ) & n) >> 12   |  (( 7 << 15 ) & n) << 3 ;
}

inline  int  zip( int  a[]) 
{ // 用于将8个数压缩为1个小于2^24(约1670万)的整数
    int  s = 0 ;
    for (int  i = 0; i < 8; ++ i) 
		s = s | (a[i] - 1 ) << ( 3 * i);
    return  s;
}

inline void inc( int &  p)
{ 
	if(++ p ==QLen) 
		p=0;
} //用于移动队列首尾指针

int main()
{
    //freopen( "input.txt", "r", stdin );
    //freopen( "output.txt", "w", stdout );
    
    int i, j, n, bgn = zip(a);//bgn是初始状态（压缩后）
    ha[bgn] = 'E';
    q[b] = bgn; 
	inc(b);
    while (b != e)
    {
        i = q[e]; 
		inc(e);//取队首
        j = A(i);
        if (!ha[j]) ha[j]='A', q[b]=j, inc(b);
        j = B(i);
        if (!ha[j]) ha[j]='B', q[b]=j, inc(b);
        j = C(i);
        if (!ha[j]) ha[j]='C', q[b]=j, inc(b);
    }
    char s[1000];//s[]用于保存生成的操作序列
    while (scanf( "%d", &n ) && n!=-1)
    {
        for (i = 0; i < 8; ++i) scanf( "%d", &a[i] );
        for (i = zip(a),j = 0; i != bgn; ++ j)
        {
           s[j] = ha[i];
           switch (s[j])
           {
               case 'A': i = A(i);        break;
               case 'B': i = B(B(B(i)));    break;
               case 'C': i = C(C(C(i)));    break;
           }
        }
        if (j > n) 
            printf( "-1\n" );
        else
        {
            printf( "%d ", j );
            while (j --) putchar(s[j]);
            putchar( '\n' );
        }
    }   
    return 0;
}
