//2 a (1p)
#include <iostream>
using namespace std;
int except(int v) {
if (v < 0) {throw 1; }
else if (v > 0){
throw std::exception ("A");
}
return 0;
}
int main(){
try {
cout << except(1 < 1);
cout << except(-5);
cout << except(5);
}catch (std::exception& e) {
cout << "A";
}catch (int x) {
cout << "B";
}
cout << "C";
return 0;
}