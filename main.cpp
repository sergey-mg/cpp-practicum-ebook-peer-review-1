#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <iomanip>

using namespace std;

class Ebook {
public:
    void ReadRequest(const string& request) {
        if (request == "READ"s) {
            int user, page;
            cin >> user;
            cin >> page;
            if (user_pages_[user] != 0) {
                for (int i = user_pages_[user] + 1; i <= page; ++i) {
                    ++page_users_[i];
                }
            }
            else {
                for (int i = 1; i <= page; ++i) {
                    ++page_users_[i];
                }
                total_users_.insert(user);
            }
            user_pages_[user] = page;
        }
        else if (request == "CHEER"s) {
            int user;
            cin >> user;
            if (total_users_.count(user) == 0) {
                cout << 0 << endl;
            }
            else if (total_users_.count(user) == 1 && total_users_.size() == 1) {
                cout << 1 << endl;
            }
            else {             
                double didnt_read = total_users_.size() - page_users_[user_pages_[user]];
                cout << setprecision(6) << didnt_read / (total_users_.size() - 1) << endl;
            }
        }
    }
    
private:
    vector<int> user_pages_ = vector<int>(100000, 0);
    vector<int> page_users_ = vector<int>(1000, 0);
    unordered_set<int> total_users_;
};


int main() {  

    Ebook ebook;
    int request_count;
    cin >> request_count;
    for (int i = 0; i < request_count; ++i) {
        string request;
        cin >> request;
        ebook.ReadRequest(request);
    }
}
