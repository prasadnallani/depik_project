int sum;

int avearge(int x, int y, int z)
{
 int av;
 av = (x+y+z)/3;
 return av;
}
void TestFunc()
{
 int a,b,c;
 a =20;
 b= a;
 c = a+b;
 sum = average(a, b,c);
 printf("%d",sum);
}
