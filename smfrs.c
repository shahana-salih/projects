#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
#define MAX_NAME 50
#define MAX_INTERESTS 3
#define MAX_INTEREST_LEN 20
#define MAX_QUEUE 100
typedef struct {
int id;
char name[MAX_NAME];
char interests[MAX_INTERESTS][MAX_INTEREST_LEN];
} User;
User users[MAX_USERS];
int adj[MAX_USERS][MAX_USERS]; // friendship graph
int userCount = 0;
// Add new user
void addUser() {
if (userCount >= MAX_USERS) {
printf("User limit reached!\n");
return;
}
User u;
u.id = userCount;
printf("Enter name: ");
scanf(" %[^\n]", u.name);
printf("Enter %d interests:\n", MAX_INTERESTS);
for (int i = 0; i < MAX_INTERESTS; i++) {
printf("Interest %d: ", i + 1);
scanf(" %s", u.interests[i]);
}
users[userCount] = u;
userCount++;
printf("User added with ID %d\n", u.id);
}
// Add friendship (undirected edge)
void addFriendship() {
int id1, id2;
printf("Enter first user ID: ");
scanf("%d", &id1);
printf("Enter second user ID: ");
scanf("%d", &id2);
if (id1 >= userCount || id2 >= userCount || id1 == id2) {
printf("Invalid user IDs.\n");
return;
}
adj[id1][id2] = 1;
adj[id2][id1] = 1;
printf("Friendship added between %s and %s\n", users[id1].name, users[id2].name);
}
// Show direct friends
void showFriends() {
int id;
printf("Enter user ID: ");
scanf("%d", &id);
if (id >= userCount) {
printf("Invalid user ID.\n");
return;
}
printf("Friends of %s:\n", users[id].name);
for (int i = 0; i < userCount; i++) {
if (adj[id][i]) {
printf("- %s\n", users[i].name);
}
}
}
// Show mutual friends
void mutualFriends() {
int id1, id2;
printf("Enter first user ID: ");
scanf("%d", &id1);
printf("Enter second user ID: ");
scanf("%d", &id2);
if (id1 >= userCount || id2 >= userCount) {
printf("Invalid IDs.\n");
return;
}
printf("Mutual friends of %s and %s:\n", users[id1].name, users[id2].name);
for (int i = 0; i < userCount; i++) {
if (adj[id1][i] && adj[id2][i]) {
printf("- %s\n", users[i].name);
}
}
}
// Recommend friends based on mutual connections
void recommendFriends() {
int id;
printf("Enter user ID: ");
scanf("%d", &id);
if (id >= userCount) {
printf("Invalid user ID.\n");
return;
}
int suggested[MAX_USERS] = {0};
// Go through friends of friends
for (int i = 0; i < userCount; i++) {
if (adj[id][i]) {
for (int j = 0; j < userCount; j++) {
if (adj[i][j] && !adj[id][j] && j != id) {
suggested[j]++;
}
}
}
}
printf("Recommended friends for %s:\n", users[id].name);
for (int i = 0; i < userCount; i++) {
if (suggested[i] > 0) {
printf("- %s (Mutual Friends: %d)\n", users[i].name, suggested[i]);
}
}
}
// BFS to find shortest path
void shortestPath() {
int start, end;
printf("Enter source user ID: ");
scanf("%d", &start);
printf("Enter target user ID: ");
scanf("%d", &end);
if (start >= userCount || end >= userCount) {
printf("Invalid user IDs.\n");
return;
}
int visited[MAX_USERS] = {0};
int parent[MAX_USERS];
for (int i = 0; i < MAX_USERS; i++) parent[i] = -1;
int queue[MAX_QUEUE];
int front = 0, rear = 0;
queue[rear++] = start;
visited[start] = 1;
while (front < rear) {
int current = queue[front++];
if (current == end) break;
for (int i = 0; i < userCount; i++) {
if (adj[current][i] && !visited[i]) {
visited[i] = 1;
parent[i] = current;
queue[rear++] = i;
}
}
}
if (!visited[end]) {
printf("No connection found.\n");
return;
}
// Reconstruct path
int path[MAX_USERS];
int length = 0;
int crawl = end;
while (crawl != -1) {
path[length++] = crawl;
crawl = parent[crawl];
}
printf("Shortest path:\n");
for (int i = length - 1; i >= 0; i--) {
printf("%s", users[path[i]].name);
if (i > 0) printf(" -> ");
}
printf("\n");
}
// Show all users
void showAllUsers() {
for (int i = 0; i < userCount; i++) {
printf("ID %d: %s [", users[i].id, users[i].name);
for (int j = 0; j < MAX_INTERESTS; j++) {
printf("%s", users[i].interests[j]);
if (j < MAX_INTERESTS - 1) printf(", ");
}
printf("]\n");
}
}
// Menu
void menu() {
int choice;
while (1) {
printf("\n--- Social Network Menu ---\n");
printf("1. Add User\n");
printf("2. Add Friendship\n");
printf("3. Show Friends\n");
printf("4. Show Mutual Friends\n");
printf("5. Recommend Friends\n");
printf("6. Shortest Path\n");
printf("7. Show All Users\n");
printf("0. Exit\n");
printf("Choose an option: ");
scanf("%d", &choice);
switch (choice) {
case 1: addUser(); break;
case 2: addFriendship(); break;
case 3: showFriends(); break;
case 4: mutualFriends(); break;
case 5: recommendFriends(); break;
case 6: shortestPath(); break;
case 7: showAllUsers(); break;
case 0: exit(0);
default: printf("Invalid choice.\n");
}
}
}
int main() {
menu();
return 0;
}
