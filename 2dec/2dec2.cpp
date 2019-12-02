#include <iostream>
#include <vector>

using namespace std;

// mutate nums and return the new position, or -1 if program halts
long long compute(vector<long long>& nums, long long pos) {
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
        return -1;
    }
    else {
        return -2; // error code
    }
}
long long compute_with_input(vector<long long> nums, long long a, long long b) {
    long long pos = 0;
    nums[1] = a;
    nums[2] = b;
    while (pos >= 0) {
        pos = compute(nums, pos);
    }
    return nums[0];
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


    for (long long i = 0; ; i++) {
        for (long long j = 0; j <= i; j++) {
            long long r1 = compute_with_input(nums, i, j);
            if (r1 == 19690720) {
                cout << i << " " << j << endl;
                cout << i * 100 + j << endl;
                return 0;
            }
            long long r2 = compute_with_input(nums, j, i);
            if (r2 ==  19690720) {
                cout << j << " " << i << endl;
                cout << j * 100 + i << endl;
                return 0;
            }
        }
    }
}
