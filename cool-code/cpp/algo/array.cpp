//在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

//链接：https://leetcode-cn.com/leetbook/read/illustrate-lcof/xs5w4d/


#include <iostream>
#include <vector>

int MinArray(std::vector<int> arr){
	int left = 0;
	int right = arr.size() - 1;
	while(left < right){
		int mid = (right + left) / 2 ;
		if(arr[mid] < arr[right]){
			mid = right;
		}
	}
}

int main(){
	std:vector<int> arr{1,42,345,4654,7757657,76567};

}
