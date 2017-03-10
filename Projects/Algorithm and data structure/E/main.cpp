#include <vector>
#include <queue>
#include <cstdio>
#include <climits>

using namespace std;

struct node {
    int min_distance;
    bool visited;
    vector<pair<int, int>> edges; // para<nast_wierzchołek, dystans>
    node() : min_distance(INT_MAX), visited(false) {}
};

void dijkstra(node* graph) {
    graph[1].min_distance = 0;
    priority_queue<pair<int, int>> q;
    q.emplace(-graph[1].min_distance, 1);
    while (!(q.empty())) {
        pair <int, int> p = (q.top());
        int index = p.second;
        q.pop();
        if (graph[index].visited == false) {
            graph[index].visited = true;
            int size_t = graph[index].edges.size();
            for(int i = 0; i <  size_t; i++) {
                int alt = graph[index].min_distance + graph[index].edges[i].second;
                int index2 = graph[index].edges[i].first;
                if (alt < graph[index2].min_distance) {
                    graph[index2].min_distance = alt;
                    q.emplace(-graph[index2].min_distance, index2);
                }
            }
        }
    }
}

int main() {
    int num_node, num_edges, num_dest_points;
    scanf("%d%d%d", &num_node, &num_edges, &num_dest_points);
    node* graph = new node[num_node+1];
    int a,b,c;
    for (int i = 0; i < num_edges; i++) {
        scanf("%d%d%d", &a ,&b, &c);
        graph[a].edges.emplace_back(b,c);
        graph[b].edges.emplace_back(a,c);
    }
    int* dest_points = new int [num_dest_points];
    for (int i = 0; i < num_dest_points; i++) {
        scanf("%d", &dest_points[i]);
    }
    dijkstra(graph);
    long int sum = 0;
    for (int i = 0; i < num_dest_points; i++) {
        if (!graph[dest_points[i]].visited) {
            printf("NIE\n");
            return 0;
        }
        sum += graph[dest_points[i]].min_distance;
    }
    printf("%ld\n", 2*sum);
    return 0;
}