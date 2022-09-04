#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define per(i, a, b) for(int i = b - 1; i >= a; --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define ff first
#define ss second
 
const ll mod = 1e9 + 7;
 
 
template<class T>
class Queue {
    
    T*arr;
    int f, r, cs, ms;
 
public:
    
    Queue(int n) {
        arr = new T[n];
        f = 0;
        r = n-1;
        cs = 0;
        ms = n;
    }
 
    bool full() {
        return cs == ms;
    }
 
    bool empty() {
        return cs == 0;
    }
 
    void push(T data) {
        if(!full()) {
            r = (r + 1)%ms;
            arr[r] = data;
            ++cs;
        }
    }   
 
    void pop() {
        if(!empty()) {
            f = (f + 1)%ms;
            --cs;
        }
    }
 
    T front() {
        return arr[f];
    }
 
    ~Queue() {
        if(arr != NULL) {
            delete [] arr;
            arr = NULL;
        }
    }
 
};
 
template<class T>
class node {
public:
    T data;
    node*next;
 
    node(T data) {
        this->data = data;
        next = NULL;
    }
};
 
template<class T>
class LinkedList {
 
public:
 
    static node<T>* insertAtTail(node<T>*&head, T data) {
        if(head == NULL) {
            node<T>*n = new node<T>(data);
            n -> next = NULL;
            head = n;
            return head;
        }
 
        node<T>*temp = head;
        while(temp -> next!=NULL) {
            temp = temp -> next;
        }
 
        node<T>*n = new node<T>(data);
        temp -> next = n;
        n -> next = NULL;
        return head;
    }
 
    static void deleteNode(node<T>*& head, int id) {
 
        node<T>*temp = head;
        node<T>*prev = temp;
 
        while(temp -> data != id) {
            prev = temp;
            temp = temp -> next;
        }
 
        prev -> next = temp -> next;
        delete temp;
        return;
    }
 
    void readInput(node<T>*&head) {
        T d;
        cin >> d;
        while(d!=-1) {
            head = insertAtTail(head, d);
            cin >> d;
        }
 
        return;
    }
 
    void print(node<T>*head) {
        while(head != NULL) {
            cout << head->data << "->";
            head = head -> next;
        }
        return;
    }
 
};
 
 
template<class T>
ostream& operator<<(ostream &os, node<T>*head) {
    print(head);
    return os;
}
 
template<class T>
istream& operator>>(istream &in, node<T>*&head) {
    readInput(head);
    return in; 
}
 
 
template<class T>
class Network : public LinkedList<T> {
 
    int N, M;
    vector<node<T>*> gr;
    vector<node<T>*> suggestions;
    vector<node<T>*> requests;
    
public:
 
    Network(int N, int M) {
        
        this -> N = N;
        this -> M = M;
 
        gr.resize(N);
        requests.resize(N);
        suggestions.resize(N);
    }
 
    vector<T> bfs(T u){
 
        vector<T> dis(N + 1);
        Queue<T> q(N);
 
 
        for(int i = 1; i <= N; ++i){
            dis[i] = INT_MAX;
        }
 
        dis[u] = 0;
        q.push(u);
 
        while(!q.empty()){
 
            T el = q.front();
            q.pop();
 
            node<T>* temp = gr[el];
            while(temp != NULL) {
                if(dis[temp -> data] == INT_MAX){
                    q.push(temp -> data);
                    dis[temp -> data] = dis[el] + 1;
                }
                temp = temp -> next;
            }
 
        }
 
        return dis;
    }
 
    void solve() {
 
        for(int i = 0; i <= N; ++i) {
            gr[i] = NULL;
            requests[i] = NULL;
        }
        
        while(M--){
            int X, Y;
            cin >> X >> Y;
                
            gr[X] = LinkedList<T>::insertAtTail(gr[X], Y);
            gr[Y] = LinkedList<T>::insertAtTail(gr[Y], X);
            
        }
 
 
        for(int i = 1; i < N; ++i) {
            
            vector<int> cur = bfs(i);
            
            
            for(int j = 0; j < cur.size(); ++j) {
                if(cur[j] == 2) {
                    suggestions[i] = LinkedList<T>::insertAtTail(suggestions[i], j);
                }
            }
 
        }
        
        return;
    }
 
    void displayFriends(T x) {
 
        cout << "Friends of " << x << " are ";
        node<T>* temp = gr[x];
        while(temp != NULL) {
            cout << temp -> data << " ";
            temp = temp -> next;
        }
        cout << "\n\n";
 
        return;
    }
 
    void seeSuggestions(T x) {
 
        node<T>* ans = suggestions[x];
 
        if(ans == NULL) {
            cout << "No suggestions :(";
        }
        else {
            cout << "Friends suggested for " << x << " are ";
            while(ans != NULL) {
                cout << ans -> data << " ";
                ans = ans -> next;
            }
        }
 
        cout << "\n\n";
        return;  
    }
 
    void sendRequest(int id, int frnd) {
        requests[frnd] = LinkedList<T>::insertAtTail(requests[frnd], id);
        cout << "\nFriend request send!!!\n";
    }
 
    void acceptRequest(int id) {
 
        cout << "Enter the friend's id : ";
        int frnd;
        cin >> frnd;
        cout << frnd << "\n\n";
 
        node<T>*check = requests[id];
        bool ok = 0;
 
        while(check != NULL) {
            if(check -> data == frnd) {
                ok = 1;
                break;
            }
            check = check -> next;
        }
 
        if(!ok) {
            cout << "\nNo such pending request!!!\n";
            return;
        }
 
        //add edge
        node<T>* temp = gr[id];
        LinkedList<T>::insertAtTail(temp, frnd);
        temp = gr[frnd];
        LinkedList<T>::insertAtTail(temp, id);
 
        //delete from pending requests
        temp = requests[id];
 
        LinkedList<T>::deleteNode(temp, frnd);
 
        cout << "Request of " << frnd << " is accepted!\n\n";
 
        return;
    }
 
    void deleteRequest(int id) {
 
        cout << "Enter the friend's id : ";
        int frnd;
        cin >> frnd;
        cout << frnd << "\n";
 
        node<T>*check = requests[id];
        bool ok = 0;
 
        while(check != NULL) {
            if(check -> data == frnd) {
                ok = 1;
                break;
            }
            check = check -> next;
        }
 
        if(!ok) {
            cout << "\nNo such request is there!!!\n";
            return;
        }
 
        node<T>*temp = requests[id];
        //delete from pending requests
 
        LinkedList<T>::deleteNode(temp, frnd);
 
        return;
    }
 
    void seePendingRequests(int id) {
 
        node<T>* temp = requests[id];
 
        if(temp == NULL) {
            cout << "No pending requests!!!\n";
            return;
        }
 
        cout << "\nPending requests of " << id << " are : ";
        while(temp != NULL) {
            cout << temp -> data << " ";
            temp = temp -> next;
        }
 
        cout << "\n\n";
 
        int choice;
        cout << "1. Accept anyone's request\n";
        cout << "2. Decline anyone's request\n";
        cout << "3. Do nothing\n\n";
 
        cin >> choice;
        
        if(choice == 1) {
            acceptRequest(id);
        }
        else if(choice == 2) {
            deleteRequest(id);
        }
        
        return;
    }
 
    void unfriend(int id) {
        
        cout << "Enter the id whom you want to unfriend : ";
        int frnd;
        cin >> frnd;
        cout << frnd << "\n";
 
        node<T>*check = gr[id];
        bool ok = 0;
 
        while(check != NULL) {
            if(check -> data == frnd) {
                ok = 1;
                break;
            }
            check = check -> next;
        }
 
        if(!ok) {
            cout << "\nThis person is not in your friend list!!!\n";
            return;
        }
 
        node<T>*temp = gr[id];
        LinkedList<T>::deleteNode(temp, frnd);
        temp = gr[frnd];
        LinkedList<T>::deleteNode(temp, id);
 
        cout << frnd << " is removed from " << id << "'s friend list\n";
        return;
    }
 
    void show() {
        for(int i = 1; i <= N; ++i) {
            cout << i << " ";
            cout << gr[i] << '\n';
        }
    }
 
    ~Network() {}
};
 
 
 
int main() {
 
    int N, M;
    cin >> N >> M;
 
    Network<int> Net(N, M);
 
    Net.solve();
    
    while(true) {
 
        cout << "\n";
        cout << "1. See friend list of a person\n";
        cout << "2. See friend suggestions for a person\n";
        cout << "3. See pending requests\n";
        cout << "4. Unfriend a friend of a person\n";
        cout << "5. Quit menu\n\n";
 
        cout << "Enter your choice : ";
 
        int choice;
        cin >> choice;
        cout << choice << "\n";
 
        if(choice == 1) {
            cout << "Enter the person id : ";
            int id;
            cin >> id;
            cout << id << "\n";
 
            Net.displayFriends(id);
        }
        else if(choice == 2) {
            cout << "Enter the person id : ";
            int id;
            cin >> id;
            cout << id << "\n";
 
            Net.seeSuggestions(id);
 
            cout << "Send friend request ?(Y/ N)\n";
            char c;
            cin >> c;
            if(c == 'N') {
                continue;
            }
            else {
                cout << "Enter the id of person : ";
                int Frnd;
                cin >> Frnd;
                cout << Frnd << "\n";
                Net.sendRequest(id, Frnd);
            }
        }
        else if(choice == 3) {
            cout << "Enter person id : ";
            int id;
            cin >> id;
            cout << id << "\n";
 
            Net.seePendingRequests(id);
        }
        else if(choice == 4) {
            cout << "Enter the person's id: ";
            int id;
            cin >> id;
            cout << id << "\n";
            Net.displayFriends(id);
            Net.unfriend(id);
        }   
        else if(choice == 5) {
            exit(0);
        }
        else {
            cout << "Invalid choice\n";
        }
    }
 
    return 0;
}
