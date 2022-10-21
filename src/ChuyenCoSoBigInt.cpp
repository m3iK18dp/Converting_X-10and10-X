#include <iostream>
#include <string>
#include <math.h>
using namespace std;
string ma = "0123456789ABCDEF";
// Khai bao node du lieu
struct Node
{
   int Data;   // Du lieu
   Node *Next; // con tro lien ket
};
//Khai bao Stack
typedef struct Stack
{
   Node *Top; //con tro lien ket
} Stack;
//Tạo Stack moi
void Newstack(Stack &S)
{
   S.Top = NULL;
}
//Tao Node du lieu moi
Node *Make_Node(int x)
{
   Node *P = new Node(); // Cap phat bo nho cho Node
   P->Data = x;
   P->Next = NULL;
   return P;
}
// Ham Push - Them vao dau danh sach
void Push(Stack &a, int value)
{
   Node *P = Make_Node(value);
   P->Next = a.Top;
   a.Top = P;
}
// Ham Pop - Lay gia tri phan tu dau va xoa no ra khoi danh sach
int Pop(Stack &a)
{
   Stack temp = a;
   int data = temp.Top->Data;
   a.Top = a.Top->Next;
   temp.Top->Next = NULL;
   delete temp.Top;
   return data;
}
/*Vi de bai chi yeu cau voi so tu nhien nen cac phep bien doi va phep tinh ben
duoi chi tinh toan voi so tu nhien nen se khong xet truong hop am voi thap phan.*/
int charToInt(char c) //Chuyen char sang int
{
   return c - '0';
}
char intToChar(int n) //Chuyen int sang char
{
   return (char)(n + 48);
}
string intToString(int n) //Chuyen int sang string
{
   string str = "";
   int count = n;
   while (count > 0)
   {
      char c = intToChar(count % 10); //lay ky tu hang don vi
      count /= 10;                    //chia de bo ky tu hang don vi
      str = c + str;                  //them ky tu hang don vi da tinh o tren vao dau xau st
   }
   return str; //tra ve string sau khi chuyen doi so n thanh
}
int stringToInt(string s) //Chuyen string sang int
{
   int num = 0;             //khoi tao bien tra ve
   int id = s.length() - 1; //bien duyet
   while (id >= 0)          //while duyet ky tu tu cuoi den ky tu dau trong xau s
   {
      int value = charToInt(s[id]);                //chuyen ky tu thanh int
      num += value * pow(10, s.length() - 1 - id); //cong num nhan 10^ vi tri tuong ung trong thu tu chu so, vd don vi, chuc, tram, nghin
      id--;
   }
   return num; //tra ve gia tri
}
string Add(string a, string b) //Ham tinh tong, tra ve a+b
{
   string add = "";
   int l = (a.length() > b.length()) ? a.length() : b.length();
   //2 dong duoi co  muc dich them so 0 vao dau xau nao ngan hon de 2 xau co do dai bang nhau
   a.insert(0, l - a.length(), '0'); // chen them cac ky tu '0' vao dau cua a.
   b.insert(0, l - b.length(), '0'); //chen them cac ky tu '0' vao dau cua b.
   int temp = 0;
   for (int i = l - 1; i >= 0; i--) // duyet tung phan tu tu cuoi den dau va cong
   {
      temp = charToInt(a[i]) + charToInt(b[i]) + temp; // tinh tong tung doi mot
      add.insert(0, 1, intToChar(temp % 10));          // gan phan don vi vao
      temp = temp / 10;                                // lay lai phan hang chuc
   }
   if (temp > 0) // neu hang chuc > 0 thi them vao kq
      add.insert(0, 1, intToChar(temp));
   return add;
}
string Mul(int a, string b) //Ham nhan. Tra ve a*b
{
   string mul = "0";            //bien tra ve gia tri a*b
   for (int i = a; i >= 1; i--) //cong b a lan gan vao mul
      mul = Add(mul, b);
   return mul;
}
string Div(string number, int div) //Ham chia nguyen, tra ve a/b
{
   string res = "";                   // ket qua tra ve
   int idx = 0;                       // biem dem cua bien number
   int temp = charToInt(number[idx]); // bien tmp lay so dau tien
   while (temp < div)                 // vong lap lay bien temp sao cho temp > div
      temp = temp * 10 + charToInt(number[++idx]);
   while (number.size() > idx) // Vong lap xu li chia nguyen
   {
      res += intToChar(temp / div);                        // lay ket qua cua phep chia luu vao res
      temp = (temp % div) * 10 + charToInt(number[++idx]); // lay chu so tiep theo cua number
   }
   if (res.length() == 0)
      return "0";
   return res;
}
int Mod(string num, int a) //Ham chia lay du
{
   int res = 0;                                 // ket qua tra ve
   for (int i = 0; i < num.length(); i++)       // Vong lap xu li lay phan du
      res = (res * 10 + charToInt(num[i])) % a; //Tung vong lap xu li so du
   return res;
}
string tenToX(string n, int x) //Ham chuyen doi so x co co so 10 sang co so x
{
   Stack st;                           //khoi tao st
   Newstack(st);                       //Khoi tao stack voi st
   if (n.length() == 1 && n[0] == '0') //neu n==0 thi push gia tri "0" vao stack
      Push(st, 0);
   else //nguoc lai chay khoi lenh trong else
   {
      string s = n;                                               //Khoi tao bien s=n
      while ((s.length() == 1 && s[0] != '0') || s.length() != 1) //lap khi s khac "0"
      {
         Push(st, Mod(s, x)); //push gia chia du s%x vào stack
         s = Div(s, x);       //chia nguyen s/x
      }
   }
   string value = "";       //khoi tao bien
   while (st.Top != NULL)   //lap khi stack !=NULL
      value += ma[Pop(st)]; //Cong k tu tai vi tri tuong ung voi gia tri pop ra tu stack
   return value;            //tra ve gia tri can tim
}
string xToTen(string n, int x) //Ham chuyen doi so x co co so X sang co so 10
{
   Stack st;            //khoi tao st
   Newstack(st);        //Khoi tao stack voi st
   int i, j;            //khai bao bien
   while (n[i] != '\0') //Duyet tung phan tu cua n cho den phan tu cuoi
   {
      j = 0;
      while (ma[j] != '\0') //Duyet tung phan tu cua ma(khai bao o dau bai) cho den phan tu cuoi
      {
         if (n[i] == ma[j]) //Neu 2 ky tu bang nhau thi chay lenh trong if
         {
            Push(st, j); //day gia tri j vao stack
            break;       //ngắt while ung voi bien j
         }
         j++; //tăng biến j
      }
      i++; //tang bien i
   }
   string pow = "1", mul = "", value = "0";
   bool check = false;
   while (st.Top != NULL) //Lap neu stack!=NULL
   {
      if (check)
         pow = Mul(x, pow);    //luong mu tuong ung voi vi tri trong day so n, vd 10(2) -> 1*16^1 + 0*16^0
      mul = Mul(Pop(st), pow); //Nhan voi gia tri tuong ung trong stack
      value = Add(value, mul); //Cong gia tri mul vao value
      check = true;
   }
   return value; //tra ve gia tri can tim
}
int main()
{
   string a = "";
   int x;
   int check = 1;
   do
   {
      cout << "\n=====================================================" << endl;
      cout << "$$               CHUYEN DOI CO SO                  $$" << endl;
      cout << "||    1. Chuyen so tu co so 10 sang co so X.       ||" << endl;
      cout << "||    2. Chuyen so tu co so X sang co so 10.       ||" << endl;
      cout << "$$    3. Nhan bat ki phim nao de thoat.            $$" << endl;
      cout << "=====================================================" << endl;
      cout << "                 Nhap lua chon:  ";
      cin >> check;
      switch (check)
      {
      case 1:
      {
         cout << "Nhap gia tri a can chuyen:   ";
         cin >> a;
         bool check = false;
         for (int i = 0; i < a.length(); i++)
            if (a[i] < '0' || a[i] > '9')
            {
               cout << ">Co so 10 chi gom cac chu so tu 0->9" << endl;
               cout << ">Du lieu dau vao khong hop le. Xin lua chon lai!!!";
               check = true;
               break;
            }
         if (check)
            break;
         cout << "Nhap co so can chuyen (2<=x<=16): ";
         cin >> x;
         cout << ">>> Ket qua:   ";
         cout << tenToX(a, x) << endl;
         break;
      }
      case 2:
      {
         cout << "> > Nhap gia tri can chuyen:   ";
         cin >> a;
         cout << "> > Nhap co so cua cua so can chuyen (2<=x<=16): ";
         cin >> x;
         bool check = false;
         for (int i = 0; i < a.length(); i++)
         {
            a[i] = toupper(a[i]);
            if (ma.substr(0, x).find(a[i]) == string::npos)
            {
               cout << ">Du lieu dau vao khong hop le doi voi co so " << x << ". Xin lua chon lai!!!";
               check = true;
               break;
            }
         }
         if (check)
            break;
         cout << "> > >Ket qua:   ";
         cout << xToTen(a, x) << endl;
      }
      }
   } while (check == 1 || check == 2);
   return 0;
}
