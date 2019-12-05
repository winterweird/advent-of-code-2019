#include <iostream>
#include <vector>

using namespace std;

// quality of life improvements
template<class T>
class pvector: public vector<T> {
    public:
        pvector() { }
        T pop() {
            T ret = this->back();
            this->pop_back();
            return ret;
        }
};

template<class T>
ostream& operator<<(ostream& os, const pvector<T>& v) {
    for (auto& i: v) {
        os << i << " ";
    }
    return os;
}

struct {
    long long operator[](long long code) {
        switch(code) {
            case 1:
            case 2:
            case 7:
            case 8:
                return -3;
            case 3:
                return -1;
            case 4:
                return 1;
            case 5:
            case 6:
                return 2;
            case 99:
                return 0;
        }
        return -100; // missing opcode
    }
} n_args;

void push_to_stack(pvector<long long>& stack, const pvector<long long>& input, long long start, long long count, long long modes, bool last_param_is_position) {
    for (long long i = start+1; i <= start+count; i++) {
        if      (modes % 10 == 1) stack.push_back(input[i]);
        else if (modes % 10 == 0) stack.push_back(input[input[i]]);
        else cout << "Stacking error: expected mode to be 0 or 1, but was " << modes%10 << endl;
        modes /= 10;
    }
    if (last_param_is_position) {
        stack.pop_back();
        stack.push_back(input[start+count]);
    }
    //cout << "STACK: " << stack << endl;
}

int main() {
    long long n;
    char separator;

    pvector<long long> input;
    while(cin >> n) { input.push_back(n); cin >> separator; if (separator == '.') break; }
    long long pos = 0;
    pvector<long long> stack;

    cout << input << endl;
    cout << "--------" << endl;

    while (input[pos] != 99) {
        long long opc = input[pos] % 100;
        //cout << "OPCODE: " << opc << endl;
        long long modes = input[pos] / 100;
        long long k = n_args[opc];
        if (k == -100) {
            cout << "Invalid opcode: " << opc;
            return 1;
        }
        //cout << "Pos: " << pos << endl;
        bool last_param_is_position = k < 0;
        k = abs(k);
        push_to_stack(stack, input, pos, k, modes, last_param_is_position);

        pos += k+1;

        long long p = stack.pop(); // optional positional arg
        //cout << "param: " << p << endl;
        switch (opc) {
            case 1:
                input[p] = stack[0] + stack[1];
                break;
            case 2:
                input[p] = stack[0] * stack[1];
                break;
            case 3:
                cin >> input[p];
                break;
            case 4:
                cout << p << endl;
                break;
            case 5:
                if (stack.back() != 0) pos = p;
                break;
            case 6:
                if (stack.back() == 0) pos = p;
                break;
            case 7:
                if (stack[0] < stack[1]) input[p] = 1;
                else input[p] = 0;
                break;
            case 8:
                if (stack[0] == stack[1]) input[p] = 1;
                else input[p] = 0;
                break;

        }

        stack.clear();
    }
    cout << "input[0] = " << input[0] << endl;
}
