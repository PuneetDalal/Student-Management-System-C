#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[64];
    int roll_no;
    int num_subjects;
    float marks[20];
    float total_marks;
    float avg_marks;
};

struct student students[60];
int student_count = 0;

void calc_marks(struct student *s) {
    s->total_marks = 0;
    for (int i = 0; i < s->num_subjects; i++) {
        s->total_marks += s->marks[i];
    }
    s->avg_marks = s->total_marks / s->num_subjects;
}
void print_all_students() {
    if (student_count == 0) {
        printf("No student records to display.\n");
        return;
    }

    printf("\n--- All student Records ---\n");

    for (int i = 0; i < student_count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Roll No: %d\n", students[i].roll_no);
        printf("Marks: ");
        for (int j = 0; j < students[i].num_subjects; j++)
            printf("%.2f ", students[i].marks[j]);
        printf("\nTotal Marks: %.2f\n", students[i].total_marks);
        printf("Average Marks: %.2f\n", students[i].avg_marks);
    }
}
void add_stu() {
    if (student_count >= 60) {
        printf("Error: Maximum number of students reached.\n");
        return;
    }

    struct student new_student;

    printf("Enter student name: ");
    scanf("%63s", new_student.name);

    printf("Enter roll number: ");
    scanf("%d", &new_student.roll_no);

    printf("Enter number of subjects (max 20): ");
    scanf("%d", &new_student.num_subjects);
    if (new_student.num_subjects > 20) new_student.num_subjects = 20;

    printf("Enter marks for %d subjects:\n", new_student.num_subjects);
    for (int i = 0; i < new_student.num_subjects; i++) {
        printf("Subject %d marks: ", i + 1);
        scanf("%f", &new_student.marks[i]);
    }

    calc_marks(&new_student);
    students[student_count++] = new_student;

    printf("student record created successfully.\n");
}

void linear_search(int roll_no) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_no == roll_no) {
            printf("\n--- student Found (Linear Search) ---\n");
            printf("Name: %s\nRoll No: %d\nTotal Marks: %.2f\nAverage: %.2f\n",
                   students[i].name, students[i].roll_no,
                   students[i].total_marks, students[i].avg_marks);
            return;
        }
    }
    printf("student with roll number %d not found.\n", roll_no);
}
int binary_search(int roll_no) {
    int low = 0, high = student_count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].roll_no == roll_no)
            return mid;
        else if (students[mid].roll_no < roll_no)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void merge(struct student arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    struct student L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(struct student arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void swap(struct student *a, struct student *b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct student arr[], int low, int high) {
    float pivot = arr[high].total_marks;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].total_marks > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(struct student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() {
    int choice, roll_no, index;

    do {
        printf("\n--- student Management System ---\n");
        printf("1. Add student\n");
        printf("2. Linear Search (by Roll No)\n");
        printf("3. Binary Search (by Roll No)\n");
        printf("4. Sort by Roll No (Merge Sort)\n");
        printf("5. Sort by Total Marks (Quick Sort)\n");
        printf("6. Print All Students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_stu();
                break;

            case 2:
                printf("Enter roll number to search (Linear): ");
                scanf("%d", &roll_no);
                linear_search(roll_no);
                break;

            case 3:
                merge_sort(students, 0, student_count - 1);
                printf("Enter roll number to search (Binary): ");
                scanf("%d", &roll_no);
                index = binary_search(roll_no);
                if (index != -1)
                    printf("\n--- student Found (Binary Search) ---\nName: %s\nRoll No: %d\nTotal Marks: %.2f\nAverage: %.2f\n",
                           students[index].name, students[index].roll_no,
                           students[index].total_marks, students[index].avg_marks);
                else
                    printf("student with roll number %d not found.\n", roll_no);
                break;

            case 4:
                merge_sort(students, 0, student_count - 1);
                printf("Students sorted by roll number.\n");
                break;

            case 5:
                quick_sort(students, 0, student_count - 1);
                printf("Students sorted by total marks (descending).\n");
                break;

            case 6:
                print_all_students();
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
