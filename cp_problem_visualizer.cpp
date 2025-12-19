/*
CP Problem Visualizer

This project is a terminal-based C++ tool that helps visualize how common
competitive programming algorithms work internally.

Instead of only producing the final answer, the program prints each step
of execution, such as pointer movement in Binary Search, queue evolution
in BFS, recursion flow in DFS, and table construction in Dynamic Programming.

The goal of this project is to improve understanding, debugging, and
explanation of algorithms by making their internal state and decision
process visible step-by-step.
*/
#include <bits/stdc++.h>
using namespace std;


/* ================== BINARY SEARCH ================== */
void visualizeBinarySearch(vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    int step = 1;

    cout << "\n--- Binary Search Visualization ---\n";

    while (l <= r) {
        int mid = l + (r - l) / 2;

        cout << "Step " << step++ << ":\n";
        cout << "  l = " << l << ", r = " << r << ", mid = " << mid << "\n";
        cout << "  a[mid] = " << a[mid] << "\n";

        if (a[mid] == target) {
            cout << "Target found at index " << mid << "\n";
            return;
        } 
        else if (a[mid] < target) {
            cout << "➡ Move right\n\n";
            l = mid + 1;
        } 
        else {
            cout << "⬅ Move left\n\n";
            r = mid - 1;
        }
    }

    cout << "Target not found\n";
}

/* ================== BFS ================== */
void visualizeBFS(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;

    cout << "\n--- BFS Visualization ---\n";

    q.push(start);
    visited[start] = true;
    int step = 1;

    while (!q.empty()) {
        cout << "Step " << step++ << " | Queue: [ ";
        queue<int> temp = q;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "]\n";

        int node = q.front();
        q.pop();
        cout << "Visiting node " << node << "\n";

        for (int neigh : adj[node]) {
            if (!visited[neigh]) {
                visited[neigh] = true;
                q.push(neigh);
                cout << "  -> Push " << neigh << "\n";
            }
        }
        cout << "\n";
    }
}

/* ================== DFS ================== */
void dfsHelper(int node, vector<vector<int>>& adj, vector<bool>& visited, int depth) {
    visited[node] = true;

    cout << string(depth * 2, ' ') << "Visiting node " << node << "\n";

    for (int neigh : adj[node]) {
        if (!visited[neigh]) {
            cout << string(depth * 2, ' ') << "Go deeper to " << neigh << "\n";
            dfsHelper(neigh, adj, visited, depth + 1);
        }
    }
}

void visualizeDFS(int start, vector<vector<int>>& adj) {
    cout << "\n--- DFS Visualization (Recursion Tree) ---\n";
    vector<bool> visited(adj.size(), false);
    dfsHelper(start, adj, visited, 0);
}

/* ================== DP (FIBONACCI) ================== */
void visualizeDP(int n) {
    cout << "\n--- DP Visualization (Fibonacci) ---\n";

    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    if (n >= 1) dp[1] = 1;

    cout << "dp[0] = 0\n";
    if (n >= 1) cout << "dp[1] = 1\n";

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
        cout << "dp[" << i << "] = dp[" << i - 1 << "] + dp[" << i - 2 << "] = "
             << dp[i] << "\n";
    }

    cout << "Fibonacci(" << n << ") = " << dp[n] << "\n";
}

/* ================== MAIN MENU ================== */
int main() {
    cout << "=====================================\n";
    cout << "        CP PROBLEM VISUALIZER         \n";
    cout << "=====================================\n\n";

    cout << "Choose algorithm:\n";
    cout << "1. Binary Search\n";
    cout << "2. BFS\n";
    cout << "3. DFS\n";
    cout << "4. Dynamic Programming (Fibonacci)\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Enter size of array: ";
        cin >> n;

        vector<int> a(n);
        cout << "Enter " << n << " sorted elements:\n";
        for (int i = 0; i < n; i++) cin >> a[i];

        int target;
        cout << "Enter target element: ";
        cin >> target;

        visualizeBinarySearch(a, target);
    } 
    else if (choice == 2 || choice == 3) {
        int n, m;
        cout << "Enter number of nodes: ";
        cin >> n;

        cout << "Enter number of edges: ";
        cin >> m;

        vector<vector<int>> adj(n);
        cout << "Enter edges (u v) [0-based indexing]:\n";
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int start;
        cout << "Enter starting node: ";
        cin >> start;

        if (choice == 2)
            visualizeBFS(start, adj);
        else
            visualizeDFS(start, adj);
    } 
    else if (choice == 4) {
        int n;
        cout << "Enter n for Fibonacci DP: ";
        cin >> n;
        visualizeDP(n);
    } 
    else {
        cout << "Invalid choice\n";
    }

    return 0;
}
