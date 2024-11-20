#include <stdio.h>
#include <stdlib.h>
// commit 3
// Structure to represent a project
typedef struct {
    int id;
    double cost;
    double benefit;
    double ratio;
} Project;

// Comparison function to sort projects by benefit-to-cost ratio in descending order
int compare(const void *a, const void *b) {
    Project *projectA = (Project *)a;
    Project *projectB = (Project *)b;
    if (projectB->ratio > projectA->ratio) return 1;
    else if (projectB->ratio < projectA->ratio) return -1;
    return 0;
}

// Function to allocate budget using the greedy method
void allocateBudget(Project projects[], int n, double budget) {
    // Sort projects by benefit-to-cost ratio
    qsort(projects, n, sizeof(Project), compare);

    double totalBenefit = 0;
    printf("Selected Projects:\n");
    for (int i = 0; i < n && budget > 0; i++) {
        if (projects[i].cost <= budget) {
            // Allocate full budget for this project
            budget -= projects[i].cost;
            totalBenefit += projects[i].benefit;
            printf("Project %d: Full allocation (Cost: %.2f, Benefit: %.2f)\n",
                   projects[i].id, projects[i].cost, projects[i].benefit);
        } else {
            // Allocate partial budget for this project
            totalBenefit += (budget / projects[i].cost) * projects[i].benefit;
            printf("Project %d: Partial allocation (Cost: %.2f, Benefit: %.2f)\n",
                   projects[i].id, budget, (budget / projects[i].cost) * projects[i].benefit);
            budget = 0;
        }
    }

    printf("\nTotal Benefit Achieved: %.2f\n", totalBenefit);
}

int main() {
    int n;
    double budget;

    // Input number of projects and budget
    printf("Enter the number of projects: ");
    scanf("%d", &n);
    printf("Enter the total budget: ");
    scanf("%lf", &budget);

    // Input project details
    Project projects[n];
    for (int i = 0; i < n; i++) {
        projects[i].id = i + 1;
        printf("Enter cost and benefit for Project %d: ", i + 1);
        scanf("%lf %lf", &projects[i].cost, &projects[i].benefit);
        projects[i].ratio = projects[i].benefit / projects[i].cost;
    }

    // Call the function to allocate budget
    allocateBudget(projects, n, budget);

    return 0;
}