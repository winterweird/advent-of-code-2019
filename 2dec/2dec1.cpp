#include <iostream>
#include <vector>

using namespace std;

// mutate nums and return the new position, or -1 if program halts
long long compute(vector<long long>& nums, long long pos) {
    cout << "At position " << pos << endl;
    long long p1 = nums[pos+1],p2 = nums[pos+2],p3 = nums[pos+3];
    if (nums[pos] == 1) {
        nums[p3] = nums[p1] + nums[p2];
        return pos + 4;
    }
    else if (nums[pos] == 2) {
        nums[p3] = nums[p1] * nums[p2];
        return pos + 4;
    }
    else if (nums[pos] == 99) {
        cout << "99, halt" << endl;
        return -1;
    }
    else {
        return -2; // error code
    }
}

int main() {
    vector<long long> nums;
    long long n;
    char comma;
    while (cin >> n) {
        nums.push_back(n);
        if (!(cin >> comma))
            break;
    }

    for (auto& i: nums) {
        cout << i << endl;
    }

    long long pos = 0;
    while (pos >= 0) {
        pos = compute(nums, pos);
    }
    cout << nums[0] << endl;
}
