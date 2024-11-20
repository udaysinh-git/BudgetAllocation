#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double cost;
    double benefit;
    double ratio;
} Project;

int compare(const void *a, const void *b) {
    Project *projectA = (Project *)a;
    Project *projectB = (Project *)b;
    if (projectB->ratio > projectA->ratio) return 1;
    else if (projectB->ratio < projectA->ratio) return -1;
    return 0;
}

void allocateBudget(Project projects[], int n, double budget, HWND hEdit) {
    qsort(projects, n, sizeof(Project), compare);

    double totalBenefit = 0;
    char output[1024];
    snprintf(output, sizeof(output), "Selected Projects:\r\n");
    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)output);

    for (int i = 0; i < n && budget > 0; i++) {
        if (projects[i].cost <= budget) {
            budget -= projects[i].cost;
            totalBenefit += projects[i].benefit;
            snprintf(output, sizeof(output), "Project %d: Full allocation (Cost: %.2f, Benefit: %.2f)\r\n",
                     projects[i].id, projects[i].cost, projects[i].benefit);
        } else {
            totalBenefit += (budget / projects[i].cost) * projects[i].benefit;
            snprintf(output, sizeof(output), "Project %d: Partial allocation (Cost: %.2f, Benefit: %.2f)\r\n",
                     projects[i].id, budget, (budget / projects[i].cost) * projects[i].benefit);
            budget = 0;
        }
        SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)output);
    }

    snprintf(output, sizeof(output), "\r\nTotal Benefit Achieved: %.2f\r\n", totalBenefit);
    SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)output);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit, hButton, hEntries[22];
    static int numProjects = 0;
    static HWND *projectEntries = NULL;

    switch (uMsg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "Enter the number of projects:", WS_VISIBLE | WS_CHILD, 10, 10, 200, 20, hwnd, NULL, NULL, NULL);
            hEntries[0] = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 10, 100, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "Enter the total budget:", WS_VISIBLE | WS_CHILD, 10, 40, 200, 20, hwnd, NULL, NULL, NULL);
            hEntries[1] = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 40, 100, 20, hwnd, NULL, NULL, NULL);

            hButton = CreateWindow("BUTTON", "Set Projects", WS_VISIBLE | WS_CHILD, 330, 10, 100, 50, hwnd, (HMENU)2, NULL, NULL);
            hEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 10, 410, 420, 150, hwnd, NULL, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 2) {
                char buffer[256];
                GetWindowText(hEntries[0], buffer, sizeof(buffer));
                numProjects = atoi(buffer);

                if (projectEntries != NULL) {
                    for (int i = 0; i < numProjects * 2; i++) {
                        DestroyWindow(projectEntries[i]);
                    }
                    free(projectEntries);
                }

                projectEntries = (HWND *)malloc(numProjects * 2 * sizeof(HWND));
                if (projectEntries == NULL) {
                    MessageBox(hwnd, "Memory allocation failed!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                for (int i = 0; i < numProjects; i++) {
                    char label_text[64];
                    snprintf(label_text, sizeof(label_text), "Enter cost and benefit for Project %d:", i + 1);
                    CreateWindow("STATIC", label_text, WS_VISIBLE | WS_CHILD, 10, 70 + i * 30, 200, 20, hwnd, NULL, NULL, NULL);

                    projectEntries[i * 2] = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 70 + i * 30, 100, 20, hwnd, NULL, NULL, NULL);
                    projectEntries[i * 2 + 1] = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 330, 70 + i * 30, 100, 20, hwnd, NULL, NULL, NULL);
                }

                CreateWindow("BUTTON", "Allocate Budget", WS_VISIBLE | WS_CHILD, 10, 70 + numProjects * 30 + 10, 150, 30, hwnd, (HMENU)1, NULL, NULL);
            } else if (LOWORD(wParam) == 1) {
                char buffer[256];
                GetWindowText(hEntries[1], buffer, sizeof(buffer));
                double budget = atof(buffer);

                Project *projects = (Project *)malloc(numProjects * sizeof(Project));
                if (projects == NULL) {
                    MessageBox(hwnd, "Memory allocation failed!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                for (int i = 0; i < numProjects; i++) {
                    projects[i].id = i + 1;
                    GetWindowText(projectEntries[i * 2], buffer, sizeof(buffer));
                    projects[i].cost = atof(buffer);
                    GetWindowText(projectEntries[i * 2 + 1], buffer, sizeof(buffer));
                    projects[i].benefit = atof(buffer);
                    projects[i].ratio = projects[i].benefit / projects[i].cost;
                }

                allocateBudget(projects, numProjects, budget, hEdit);
                free(projects);
            }
            break;
        }
        case WM_DESTROY: {
            if (projectEntries != NULL) {
                free(projectEntries);
            }
            PostQuitMessage(0);
            break;
        }
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "BudgetAllocationWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Budget Allocation",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}