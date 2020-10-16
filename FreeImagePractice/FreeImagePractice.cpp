#include <iostream>
#include <FreeImage.h>
using namespace std;

int main(){
	auto loaded = FreeImage_Load(FIF_PNG, "C:\\Users\\xogud02\\Desktop\\Monsters\\Aquatic0.png");
	cout<<FreeImage_GetWidth(loaded);
}
