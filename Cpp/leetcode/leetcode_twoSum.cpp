#include<cstdio>
#include<map>
#include<vector>
using namespace std;

typedef multimap<int, int> MMAP;

vector<int> twoSum(vector<int>& nums, int target) {
	MMAP map;
	size_t nsz = nums.size();
	for (int i = 0; i < nsz; i++) {
		auto it = map.find(target - nums[i]);
		if (it != map.end()) {
			return { it->second, i };
		}
		map.insert(pair<int, int>(nums[i], i));
	}
	return {};
}

int main() {
	vector<int>nums;
	int pre, tar;
	if (scanf_s("nums = [%d,", &pre)) nums.push_back(pre);
	while (scanf_s("%d,", &pre)) nums.push_back(pre);
	scanf_s("], target = %d", &tar);
	
	vector<int> res = twoSum(nums, tar);
	printf("[%d,%d]", res[0], res[1]);
	return 0;
}

/*
nums = [2,7,11,15], target = 9
*/